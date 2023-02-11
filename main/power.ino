#include <Arduino.h>

#define THRESHOLD (3.3 / 4.2) * 4095

int bat_pin = 15;

void setupPower()
{
    Serial.print("Setting up power pins...");
    // pinMode(bat_pin, INPUT);
}

void checkBatteryVoltage()
{
    // If battery voltage is low
    if (analogRead(bat_pin) < THRESHOLD)
    {
        // put ESP32 to sleep
        Serial.println("Battery level is very low!!");
    }
    else
    {
    }
}

String getBatteryPercentage()
{
    int batteryPercentage = map(analogRead(33), 0.0f, 4095.0f, 0, 100) + 1;
    batteryPercentage = (batteryPercentage < 0) ? 0 : batteryPercentage;
    batteryPercentage = (batteryPercentage > 100) ? 100 : batteryPercentage;

    // return String(batteryPercentage);
    return String(random(0, 101));
}