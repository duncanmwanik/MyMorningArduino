#include <Arduino.h>

//extern String d0[100]; // list of all Sunday alarms
//extern String d1[100]; // list of all Monday alarms
//extern String d2[100]; // list of all Tuesday alarms
//extern String d3[100]; // list of all Wednesday alarms
//extern String d4[100]; // list of all Thursday alarms
//extern String d5[100]; // list of all Friday alarms
//extern String d6[100]; // list of all Saturday alarms

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
