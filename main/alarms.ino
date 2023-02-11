#include <Arduino.h>
#include <LinkedList.h>
#include "main.h"
#include "dateandtime.h"
#include "motor.h"

int today = 0;
String justRungAlarm = "";

  LinkedList<String> d0;               // list of all Sunday alarms
LinkedList<String> d1;               // list of all Monday alarms
LinkedList<String> d2;               // list of all Tuesday alarms
LinkedList<String> d3;               // list of all Wednesday alarms
LinkedList<String> d4;               // list of all Thursday alarms
LinkedList<String> d5;               // list of all Friday alarms
LinkedList<String> d6;               // list of all Saturday alarms
LinkedList<String> todaysAlarmList;  // list of all Saturday alarms"'
LinkedList<String> snoozedAlarmList; // list of alarms already rung for the day

void savePreferences(int day, String data)
{
    String dayValue = "d" + String(day);
    preferences.begin("system", false);
    preferences.putString(dayValue.c_str(), data);
    preferences.end();
}

String getPreferences(int day)
{
    String dayValue = "d" + String(day);
    preferences.begin("system", false);
    String alarmList = preferences.getString(dayValue.c_str(), "");
    preferences.end();

    return alarmList;
}

void getTodaysAlarmList()
{
    // String alarmList = getPreferences(5);
    String alarmList = getPreferences(getCurrentDay());
    todaysAlarmList.clear();
    // ----- get list of alarms for the particular day
    int r = 0, t = 0;
    for (int i = 0; i < alarmList.length(); i++)
    {
        if (alarmList.charAt(i) == '|')
        {
            todaysAlarmList.add(alarmList.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    Serial.print("\nToday's alarm list: ");
    Serial.println(alarmList);
    Serial.println("");
}

// loads the current day's alarm list into a list (but for now loads all the days for debug)
void getAllAlarms()
{
    Serial.print("");
    Serial.println("Getting all alarms...");
    String alarms;
    String allAlarms;
    int r = 0, t = 0;

    d0.clear();
    d1.clear();
    d2.clear();
    d3.clear();
    d4.clear();
    d5.clear();
    d6.clear();

    // for day 0 ---------------------------
    alarms = getPreferences(0);

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d0.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "----------\nd0 : " + String(d0.size()) + alarms + "\n----------";

    // for day 1 ---------------------------
    alarms = getPreferences(1);
    r = 0, t = 0;

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d1.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "\nd1 : " + String(d1.size()) + alarms + "\n----------";

    // for day 2 ---------------------------
    alarms = getPreferences(2);
    r = 0, t = 0;

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d2.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "\nd2 : " + String(d2.size()) + alarms + "\n----------";

    // for day 3 ---------------------------
    alarms = getPreferences(3);
    r = 0, t = 0;

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d3.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "\nd3 : " + String(d3.size()) + alarms + "\n----------";

    // for day 4 ---------------------------
    alarms = getPreferences(4);
    r = 0, t = 0;

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d4.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "\nd4 : " + String(d4.size()) + alarms + "\n----------";

    // for day 5 ---------------------------
    alarms = getPreferences(5);
    r = 0, t = 0;

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d5.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "\nd5 : " + String(d5.size()) + alarms + "\n----------";

    // for day 6 ---------------------------
    alarms = getPreferences(6);
    r = 0, t = 0;

    for (int i = 0; i < alarms.length(); i++)
    {
        if (alarms.charAt(i) == '|')
        {
            d6.add(alarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    allAlarms += "\nd6 : " + String(d6.size()) + alarms + "\n----------";
    Serial.println(allAlarms);
    Serial.println("");
}

// ----- adds a new alarm to a day's alarm list
void addAlarmToList(int day, String alarm)
{
    String dayAlarmList = getPreferences(day);
    String newDayAlarmList = dayAlarmList + alarm + String("|");
    savePreferences(day, newDayAlarmList);
}

void addAlarm(String data)
{
    Serial.print(">>> Adding alarm: ");
    Serial.println(data);

    LinkedList<String> dataList;
    String alarm;
    String days;

    for (int i = 0; i < data.length(); i++)
    {
        if (data.charAt(i) == '/')
        {
            alarm = data.substring(0, i);
            days = data.substring((i + 1));
            break;
        }
    }
    // ----- save the new day alarm list
    for (int i = 0; i < days.length(); i++)
    {
        int day = String(days.charAt(i)).toInt();
        addAlarmToList(day, alarm);
    }
    Serial.println("... added alarm.");
    // getAllAlarms();
    getTodaysAlarmList();
}

void editAlarm(int day, String data)
{
    Serial.print(">>> Editing alarm: ");
    Serial.println(data);

    String prevTime;
    String alarm;
    String dayAlarms = getPreferences(day);
    String newDayAlarms = "";
    LinkedList<String> dayAlarmsList;
    int r = 0, t = 0;

    // ----- get the previous alarm time and the new alarm
    for (int i = 0; i < data.length(); i++)
    {
        if (data.charAt(i) == '/')
        {
            prevTime = data.substring(0, i);
            alarm = data.substring(i + 1);
        }
    }
    // ----- get list of alarms for the particular day
    for (int i = 0; i < dayAlarms.length(); i++)
    {
        if (dayAlarms.charAt(i) == '|')
        {
            dayAlarmsList.add(dayAlarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    // ----- replace the alarm item
    for (int i = 0; i < dayAlarmsList.size(); i++)
    {
        if (dayAlarmsList[i].substring(6).equals(prevTime))
        {
            dayAlarmsList[i] = alarm;
            Serial.println("... made changes to alarm.\n");
            break;
        }
    }
    // ----- save new alarm list
    for (int i = 0; i < dayAlarmsList.size(); i++)
    {
        newDayAlarms += (dayAlarmsList[i] + String("|"));
    }
    savePreferences(day, newDayAlarms);
    // getAllAlarms();
    getTodaysAlarmList();
}

void deleteAlarm(int day, String time)
{
    Serial.print(">>> Deleting alarm: ");
    // int _day = day.toInt();
    String dayAlarms = getPreferences(day);
    String newDayAlarms = "";
    LinkedList<String> dayAlarmsList;
    int r = 0, t = 0;
    // ----- get list of alarms for the particular day
    for (int i = 0; i < dayAlarms.length(); i++)
    {
        if (dayAlarms.charAt(i) == '|')
        {
            dayAlarmsList.add(dayAlarms.substring(r, i));
            r = (i + 1);
            t++;
        }
    }
    // ----- remove the previous alarm by checking it's time
    // means the app never adds two alarms with the same time
    for (int i = 0; i < dayAlarmsList.size(); i++)
    {
        if (dayAlarmsList[i].substring(6).equals(time))
        {
            dayAlarmsList.remove(i);
            Serial.println("... deleted alarm.\n");
            break;
        }
    }
    // ----- save the new day alarm list
    for (int i = 0; i < dayAlarmsList.size(); i++)
    {
        newDayAlarms += (dayAlarmsList[i] + String("|"));
    }
    savePreferences(day, newDayAlarms);
    // getAllAlarms();
    getTodaysAlarmList();
}

// get all alarms as a string
String getFullAlarmList()
{
    String alarmList = "";
    preferences.begin("system", false);
    for (int i = 0; i < 7; i++)
    {
        String day = "d" + String(i);
        String dayList = preferences.getString(day.c_str(), "");

        if (i == 6)
        {
            alarmList += dayList;
        }
        else
        {
            alarmList += dayList + "#";
        }
    }
    preferences.end();
    return alarmList;
}

void resetDevice()
{
    preferences.begin("system", false);
    preferences.putString("d0", "");
    preferences.putString("d1", "");
    preferences.putString("d2", "");
    preferences.putString("d3", "");
    preferences.putString("d4", "");
    preferences.putString("d5", "");
    preferences.putString("d6", "");
    preferences.putString("deviceName", "MyMorning Device");
    preferences.end();
    Serial.println("Reset done...\n");
    getAllAlarms();
}

void init()
{
    preferences.begin("system", false);
    if (preferences.getBool("firstTime", true))
    {
        Serial.println("Initializing device for the first time...\n");
        resetDevice();
    }
    preferences.putBool("firstTime", false);
    preferences.end();
}

bool alreadyRung(String alarm)
{
    bool isRung = justRungAlarm.equals(alarm) ? true : false;
    return isRung;
}

void addSnoozedAlarm(int vibrationPattern, int vibrationStrength, int snoozeMin, String prevTime)
{
    int minute = 0, hour = 0;
    for (int i = 0; i < prevTime.length(); i++)
    {
        if (prevTime.charAt(i) == ':')
        {
            hour = prevTime.substring(0, i).toInt();
            minute = prevTime.substring(i + 1).toInt();
        }
    }
    minute += snoozeMin;
    if (minute > 59)
    {
        minute = 0;
        hour += 1;
    }
    hour = (hour > 24) ? 0 : hour;
    String snoozedAlarm = String(vibrationPattern) + String(vibrationStrength) + String(snoozeMin) + String(hour) + ":" + String(minute);
    snoozedAlarmList.add(snoozedAlarm);
    Serial.print("... created snoozed alarm: ");
    Serial.println(snoozedAlarm);
}

void checkForActiveAlarm()
{
    String currentTime = getCurrentTime();
    // loop through todays alarm list to find an alarm matching the current time
    for (int i = 0; i < todaysAlarmList.size(); i++)
    {
        // if an alarm is found and is active and is not in the list of already rung alarms for the day
        if (todaysAlarmList[i].substring(6).equals(currentTime) && todaysAlarmList[i].substring(0, 1).equals("1"))
        {
            String alarm = todaysAlarmList[i];
            if (!alreadyRung(alarm.substring(6)))
            {
                Serial.print("... ringing alarm: ");
                Serial.println(alarm);
                String alarmTime = alarm.substring(6);
                int alarmActive = alarm.substring(0, 1).toInt();
                int alarmRepeat = alarm.substring(1, 2).toInt();
                int vibrationPattern = alarm.substring(2, 3).toInt();
                int vibrationStrength = alarm.substring(3, 4).toInt();
                int snoozeOn = alarm.substring(4, 5).toInt();
                int snoozeMin = alarm.substring(5, 6).toInt();
                justRungAlarm = alarmTime;

                bool snoozed = vibrateMotor(snoozeOn, vibrationPattern, vibrationStrength);
                if (snoozed)
                {
                    addSnoozedAlarm(vibrationPattern, vibrationStrength, snoozeMin, alarmTime);
                }
                // if repeat is turned off, make alarm inactive
                if (alarmRepeat == 0)
                {
                    alarmActive = 0;
                    String updatedAlarm = String(alarmActive) + String(alarmRepeat) + String(vibrationPattern) + String(vibrationStrength) + String(snoozeOn) + String(snoozeMin) + alarmTime;
                    String data = alarmTime + "/" + updatedAlarm;
                    editAlarm(getCurrentDay(), data);
                }
            }
        }
    }
}

void checkForSnoozedAlarm()
{
    String currentTime = getCurrentTime();
    // loop through todays alarm list to find an alarm matching the current time
    for (int i = 0; i < snoozedAlarmList.size(); i++)
    {
        // if an alarm is found and is active and is not in the list of already rung alarms for the day
        if (snoozedAlarmList[i].substring(3).equals(currentTime))
        {
            String alarm = snoozedAlarmList[i];
            if (!alreadyRung(alarm.substring(3)))
            {
                Serial.print("... ringing snoozed alarm: ");
                Serial.println(alarm);
                String alarmTime = snoozedAlarmList[i].substring(3);
                int vibrationPattern = alarm.substring(0, 1).toInt();
                int vibrationStrength = alarm.substring(1, 2).toInt();
                int snoozeMin = alarm.substring(2, 3).toInt();
                bool snoozed = vibrateMotor(1, vibrationPattern, vibrationStrength);
                justRungAlarm = alarmTime;
                if (snoozed)
                {
                    addSnoozedAlarm(vibrationPattern, vibrationStrength, snoozeMin, alarmTime);
                }
            }
            snoozedAlarmList.remove(i); // delete after ringing to free space
        }
    }
}
