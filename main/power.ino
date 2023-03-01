#include <Arduino.h>
#include "def.h"

void setupPower()
{
    Serial.print("Setting up power pins...");
    pinMode(BATTERY_LOW_LED_PIN, OUTPUT);
}

void checkBatteryVoltage()
{
    int batteryLevel = analogRead(BATTERY_VOLTAGE_PIN);
    // If battery voltage is low
    if (batteryLevel >= BATTERY_VOLTAGE_FULL)
    {
        digitalWrite(BATTERY_LOW_LED_PIN, HIGH); // turns off low battery led
    }
    else if (batteryLevel >= BATTERY_VOLTAGE_OKAY && batteryLevel < BATTERY_VOLTAGE_FULL)
    {
        digitalWrite(BATTERY_LOW_LED_PIN, HIGH); // turns off low battery led
    }
    else if (batteryLevel >= BATTERY_VOLTAGE_LOW && batteryLevel < BATTERY_VOLTAGE_OKAY)
    {
        digitalWrite(BATTERY_LOW_LED_PIN, LOW); // turns on low battery led
    }
    else
    {
        digitalWrite(BATTERY_LOW_LED_PIN, LOW); // turns on low battery led
        //
        //
        // initiate sleep
    }
}

String getBatteryPercentage()
{
    int batteryPercentage = map(analogRead(BATTERY_VOLTAGE_PIN), 0.0f, 4095.0f, 0, 100) + 1;
    batteryPercentage = (batteryPercentage < 0) ? 0 : batteryPercentage;
    batteryPercentage = (batteryPercentage > 100) ? 100 : batteryPercentage;

    return String(batteryPercentage);
}
