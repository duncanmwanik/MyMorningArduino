#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_DRV2605.h>
#include "OneButton.h"

Adafruit_DRV2605 drv;
OneButton btn(18, true);

int vibrationPatterns[] = {9, 19, 29, 39};

int action = 0;

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click()
{
    action = 1;
}

// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStart()
{
    action = 2;
}

void setupMotor()
{
    Serial.println("Setting up motor controller...");

    if (!drv.begin())
    {
        Serial.println("Could not find DRV2605");
        while (1)
            delay(10);
    }
    else
    {
        Serial.println("Set up DRV2605 successfully!");
    }
    drv.selectLibrary(1);
    // running in realtime mode to set vibration strength/amplitute
    // drv2.setMode(DRV2605_MODE_REALTIME);
    drv.setMode(DRV2605_MODE_INTTRIG);
}

bool vibrateMotor(int snoozeOn, int pattern, int _strength)
{
    bool snoozed = false;
    // set the pattern to play
    drv.setWaveform(0, vibrationPatterns[pattern]); // play pattern
    drv.setWaveform(1, 0);                          // end waveform

    // setting the vibration strength
    // max value is 255
    // weak = 85 / strength = 1
    // medium = 170 / strength = 2
    // strong = 255 / strength = 3
    uint8_t st = _strength * 85;
    drv.setRealtimeValue(st);

    btn.setDebounceTicks(30); // debounce time
    btn.setClickTicks(50);   // click period to register double press
    btn.setPressTicks(800);   // period to register long press

    // link the button functions.
    btn.attachClick(click);
    btn.attachLongPressStart(longPressStart);

    while (1)
    {
        btn.tick();
        if (action == 1 && snoozeOn == 1)
        {
            Serial.println("... alarm snoozed!");
            snoozed = true;
            break; // stop vibrating motor
        }
        if (action == 1 && snoozeOn == 0)
        {
            Serial.println("... alarm stopped!");
            break; // stop vibrating motor
        }
        if (action == 2)
        {
            Serial.println("... alarm stopped!");
            break; // stop vibrating motor
        }

        drv.go();
        delay(1000);
    }
    action = 0;
    return snoozed;
}