#ifndef DEF_H
#define DEF_H

#include <Arduino.h>
#include <Preferences.h>
#include <BLEServer.h>

// BLE
//* BLE UUIDs... Change here if need be!
#define SERVICE_UUID "4fafc201-1666-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_BATTERY "beb54800-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID_ALARM "beb54811-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_UUID_COMMAND "beb54822-36e1-4688-b7f5-ea07361b26a8"

// battery voltage level
#define BATTERY_VOLTAGE_PIN 15
#define BATTERY_LOW_LED_PIN 4

#define CHECK_BATTERY_VOLTAGE_INTERVAL_MS 10000

#define BATTERY_VOLTAGE_FULL (3.8 * (3.3 / 4.2) * 4095)
#define BATTERY_VOLTAGE_OKAY (3.3 * (3.3 / 4.2) * 4095)
#define BATTERY_VOLTAGE_LOW (3.0 * (3.3 / 4.2) * 4095)

// ---------- Main
extern Preferences preferences;

// ---------- Alarms
void addAlarm(String data);
void editAlarm(int day, String data);
void deleteAlarm(int day, String time);

void getTodaysAlarmList();
void getAllAlarms();
String getFullAlarmList();
void resetDevice();
void init();

void checkForActiveAlarm();
void checkForSnoozedAlarm();

// ---------- BLE
extern BLEServer *pServer;
extern BLECharacteristic *pCharacteristic;
extern bool deviceConnected;
extern bool oldDeviceConnected;

extern String previous;
extern String current;

void setupBLE();
void checkForNewData();

void sendBatteryPercentage();
void sendAlarmList();
void notifyClientAlarmIsRinging(bool isRinging);

// ---------- Date & Time
void setupTime(int second, int minute, int hour, int day, int month, int year);
int getCurrentDay();
String getCurrentTime();

// ---------- Motor
void setupMotor();
bool vibrateMotor(int snoozeOn, int pattern, int _strength);

// ---------- Power
void setupPower();
void checkBatteryVoltage();
String getBatteryPercentage();

// ----------

#endif