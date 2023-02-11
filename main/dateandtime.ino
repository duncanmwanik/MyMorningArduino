#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <ESP32Time.h>
#include "alarms.h"

ESP32Time rtcz;

String daysOfTheWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setupTime(int second, int minute, int hour, int day, int month, int year)
{
    Serial.println("Setting RTC Time...");
    // Set the date & time here
    rtcz.setTime(second, minute, hour, day, month, year);
}

int getCurrentDay()
{
    int day = rtcz.getDayofWeek();
    Serial.print("Today's no: ");
    Serial.println(day);
    return day;
}

String getCurrentTime()
{
    int hour = rtcz.getHour(true);
    int minute = rtcz.getMinute();
    String currentTime = String(hour) + ":" + String(minute);
    // if (currentTime.equals("0:0"))
    // {
    //     getTodaysAlarmList();
    // }
    // Serial.print("Time:");
    // Serial.println(currentTime);
    return currentTime;
}