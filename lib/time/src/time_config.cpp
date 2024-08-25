#include "time_config.h"
json_edit_config json_time_config;
HTTPClient http_time_config;
ESP32Time rtc;

String time_config::GetPublicIp()
{
    Serial.println("--");
    String url = json_time_config.GetPublicIpHttpUrl();
    String host = url;
    host.remove(0, host.indexOf("/") + 2);
    Serial.println(host);

    host.remove(host.indexOf("/"));

    Serial.println(host);

    bool http_start = http_time_config.begin(url);
    http_time_config.addHeader("Host", host);

    if (http_start)
    {
        int status = http_time_config.GET();
        while (status != 200)
        {
            Serial.println("status:");
            status = http_time_config.GET();
            Serial.println(status);
            if (status == -1)
            {    ESP.restart();

            }

            delay(10);
        }

        String resulet = http_time_config.getString();
        http_time_config.end();

        JsonDocument doc;
        deserializeJson(doc, resulet);
        String string_ip = doc["ip"];
        Serial.println(string_ip);

        json_time_config.SetPublicIp(string_ip);
        return string_ip;
    }
}

String time_config::GetTime()
{

    String ip = GetPublicIp();
    String url = json_time_config.GetTimeHttpurl() + ip;

    String host = url;
    host.remove(0, host.indexOf("/") + 2);
    Serial.println(host);

    host.remove(host.indexOf("/"));

    Serial.println(host);

    bool http_start = http_time_config.begin(url);
    http_time_config.addHeader("Host", host);


    if (http_start)
    {
        int timer =0;
        int status = http_time_config.GET();
        while (status != 200)
        {
            Serial.println("status:");
            status = http_time_config.GET();
            Serial.println(status);
            if (timer==10)
            {
                ESP.restart();

            
            }
            

            delay(1000);
        }


        String resulet = http_time_config.getString();
        JsonDocument doc_request;
        deserializeJson(doc_request, resulet);
        int date = doc_request["day"];
        int month = doc_request["month"];
        int year = doc_request["year"];
        int hour = doc_request["hour"];
        int minute = doc_request["minute"];
        String day = doc_request["dayOfWeek"];
        rtc.setTime(0, minute, hour, date, month, year);

        json_time_config.SetCurrentTime(date, month, year, minute, hour, day);

        return json_time_config.GetCurrentTime();
    }
};
int time_config::Getyear()
{
    return rtc.getYear();
}
int time_config::Getdate()
{
    return rtc.getDay();
}

String time_config::Getday()
{
    String days_s[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

    return days_s[rtc.getDayofWeek()];
}

int time_config::Gethour()
{
    int hour = rtc.getHour();
    if (rtc.getAmPm() == "PM")
    {
        hour = (hour + 10) + 2;
    }

    return hour;
}
int time_config::Getmin()
{
    return rtc.getMinute();
}
int time_config::Getmonth()
{
    return rtc.getMonth();
}
bool time_config::isvalededate(bool checkeing_first, int date0, int month0, int year0, int date1, int month1, int year1)
{
  if (checkeing_first)
  {

    if (date0 <= Getdate() && month0 <= Getmonth() && year0 <= Getyear())
    {
      return false;
    }
  }
  else
  {

    if (date0 > date1 && month0 > month1 && year0 > year1)
    {
      return false;
    }
  }
  return true;
}

bool time_config::isvaledehour(bool checkeing_first, int hour0, int min0, int hour1, int min1)
{
  if (checkeing_first)
  {
    // if (hour0 < timer_teligram.Gethour())
    // {
    //   return false;
    // }
    if (hour0 > hour1)
    {
      return false;
    }
  }
  else
  {

    if (hour0 > hour1)
    {
      return false;
    }
  }

  return true;
}

