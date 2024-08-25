#include <leb.h>
#include <json_edit_config.h>
#include <ESP32Time.h>
#include <soc/rtc_wdt.h>
#include <esp_task_wdt.h>

#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H
class time_config
{
private:
    /* data */
public:
bool isvaledehour(bool checkeing_first, int hour0, int min0, int hour1, int min1);

bool isvalededate(bool checkeing_first, int date0, int month0, int year0, int date1, int month1, int year1);

    String GetPublicIp();
    String GetTime();
    int Getyear();
    int Getdate();
     int Getmonth();
    String Getday();
    int Gethour();
    int Getmin();
};

#endif