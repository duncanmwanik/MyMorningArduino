#include <Arduino.h>
#include <LinkedList.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "def.h"

BLEServer *pServer = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

unsigned long previousMillis = 0;

// ------------- this characteristic handles sending of the battery percentage to the app
BLECharacteristic batteryCharacteristic(CHARACTERISTIC_UUID_BATTERY, BLECharacteristic::PROPERTY_READ |
                                                                         BLECharacteristic::PROPERTY_WRITE |
                                                                         BLECharacteristic::PROPERTY_NOTIFY |
                                                                         BLECharacteristic::PROPERTY_INDICATE);
BLEDescriptor batteryDescriptor(BLEUUID((uint16_t)0x2902));

// ------------- this characteristic handles sending alarms from this device to the app
BLECharacteristic alarmCharacteristic(CHARACTERISTIC_UUID_ALARM, BLECharacteristic::PROPERTY_READ |
                                                                     BLECharacteristic::PROPERTY_WRITE |
                                                                     BLECharacteristic::PROPERTY_NOTIFY |
                                                                     BLECharacteristic::PROPERTY_INDICATE);
BLEDescriptor alarmDescriptor(BLEUUID((uint16_t)0x2903));

// ------------- this characteristic handles receiving of commands from the app
BLECharacteristic commandCharacteristic(CHARACTERISTIC_UUID_COMMAND, BLECharacteristic::PROPERTY_READ |
                                                                         BLECharacteristic::PROPERTY_WRITE |
                                                                         BLECharacteristic::PROPERTY_NOTIFY |
                                                                         BLECharacteristic::PROPERTY_INDICATE);
BLEDescriptor commandDescriptor(BLEUUID((uint16_t)0x2903));

class MyServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        Serial.println(">><< Client Connected!!");
        deviceConnected = true;
        BLEDevice::startAdvertising();
    };

    void onDisconnect(BLEServer *pServer)
    {
        Serial.println(">><< Client Disconnected!!");
        deviceConnected = false;
        pServer->startAdvertising();
    }
};

String getDeviceName()
{
    preferences.begin("system", false);
    String name = preferences.getString("deviceName", "MyMorning Device");
    preferences.end();
    return name;
}

void setDeviceName(String name)
{
    preferences.begin("system", false);
    preferences.putString("deviceName", name);
    preferences.end();
    Serial.print(">>> Changed device name...");
}

void setupBLE()
{
    // Create the BLE Device
    String deviceName = getDeviceName();
    Serial.print("Setting up BLE server [");
    Serial.print(deviceName);
    Serial.println("]...");
    BLEDevice::init(deviceName.c_str());

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    pServer->disconnect(0);

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    pService->addCharacteristic(&batteryCharacteristic);
    batteryDescriptor.setValue("Battery");
    batteryCharacteristic.addDescriptor(&batteryDescriptor);

    pService->addCharacteristic(&alarmCharacteristic);
    alarmDescriptor.setValue("Alarm");
    alarmCharacteristic.addDescriptor(new BLE2902());

    pService->addCharacteristic(&commandCharacteristic);
    commandDescriptor.setValue("Command");
    commandCharacteristic.addDescriptor(new BLE2902());

    // Start the service
    pService->start();
    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x0); // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    Serial.println("Waiting for a client to connect...\n");
}

void sendBatteryPercentage()
{
    unsigned long currentMillis = millis();

    if ((currentMillis - previousMillis) >= CHECK_BATTERY_VOLTAGE_INTERVAL_MS)
    {
        previousMillis = currentMillis;
        String battery = getBatteryPercentage();
        batteryCharacteristic.setValue((char *)battery.c_str());
        batteryCharacteristic.notify();
    }
}

void sendAlarmList()
{
    Serial.println("------------------------");
    String alarmList = getFullAlarmList();
    Serial.println(alarmList);
    Serial.println("\nSent alarm list");
    Serial.println("------------------------");

    alarmCharacteristic.setValue((char *)alarmList.c_str());
    alarmCharacteristic.notify();
}

void syncTime(String time)
{
    Serial.println("Syncing time...");
    LinkedList<int> timeData;
    int r = 0, t = 0;
    for (int i = 0; i < time.length(); i++)
    {
        if (time.charAt(i) == '-')
        {
            timeData.add(time.substring(r, i).toInt());
            r = (i + 1);
            t++;
        }
    }
    setupTime(timeData[0], timeData[1], timeData[2], timeData[3], timeData[4], timeData[5]);
}

// makes changes based on command received from the app
void makeChange(String command)
{
    if (command.startsWith("a"))
    {
        addAlarm(command.substring(1));
    }
    if (command.startsWith("e"))
    {
        editAlarm(command.substring(1, 2).toInt(), command.substring(3));
    }
    if (command.startsWith("d"))
    {
        deleteAlarm(command.substring(1, 2).toInt(), command.substring(3));
    }
    if (command.startsWith("r"))
    {
        Serial.println("reseting alarms...\n");
        resetDevice();
    }
    if (command.startsWith("g"))
    {
        sendAlarmList();
    }
    if (command.startsWith("n"))
    {
        setDeviceName(command.substring(1));
    }
    if (command.startsWith("t"))
    {
        syncTime(command.substring(1));
    }
    if (command.startsWith("off"))
    {
        Serial.println("turning device off...\n");
    }
}

// check for new commands from the app
void checkForNewData()
{
    if (deviceConnected)
    {
        std::string received_data = commandCharacteristic.getValue();
        String command = String(received_data.c_str());

        if (!command.equals("*") && command.length() >= 1)
        {
            Serial.print("\nReceived Command: ");
            Serial.println(command);
            Serial.println("");

            makeChange(command);

            // change characteristic value to prevent getting the same command twice
            commandCharacteristic.setValue("*");
            // commandCharacteristic.notify();
        }
    }
}

void notifyClientAlarmIsRinging(bool isRinging)
{
    if (isRinging)
    {
        String message = "1";
        alarmCharacteristic.setValue((char *)message.c_str());
        alarmCharacteristic.notify();
    }
    else
    {
        String message = "0";
        alarmCharacteristic.setValue((char *)message.c_str());
        alarmCharacteristic.notify();
    }
}