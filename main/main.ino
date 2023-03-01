#include <Arduino.h>
#include <Preferences.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "def.h"

Preferences preferences;

void setup()
{
    Serial.begin(115200);
    Serial.println("\n....................STARTING.....................\n");
    // init();

    checkBatteryVoltage();
    setupBLE();
    setupMotor();

    // Set the time here or connect to phone to sync time
    setupTime(0, 0, 16, 10, 2, 2023); // seconds, minute, hour, day, month, year
    getTodaysAlarmList();
}

void loop()
{
    checkBatteryVoltage();

    if (deviceConnected)
    {
        checkForNewData();
        sendBatteryPercentage();
    }

    checkForActiveAlarm();
    checkForSnoozedAlarm();
}