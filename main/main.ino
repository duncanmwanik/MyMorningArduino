#include <Arduino.h>
#include <Preferences.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "ble.h"
#include "alarms.h"
#include "motor.h"
#include "power.h"
#include "dateandtime.h"

Preferences preferences;

void setup()
{
    Serial.begin(115200);
    Serial.println("....................STARTING.....................");
    // init();

    checkBatteryVoltage();

    setupMotor();
    // Set the time here or connect to phone to sync time
    setupTime(0, 0, 16, 10, 2, 2023); // seconds, minute, hour, day, month, year
    getTodaysAlarmList();
    setupBLE();
}

void loop()
{
    // Serial.println("checking time...");
    // int d = getCurrentDay();
    // String t = getCurrentTime();
    // delay(2000);
    // Serial.println("\n");

    // checkBatteryVoltage();

    if (deviceConnected)
    {
        checkForNewData();
        sendBatteryPercentage();
    }

    checkForActiveAlarm();
    checkForSnoozedAlarm();
}