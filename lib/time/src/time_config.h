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