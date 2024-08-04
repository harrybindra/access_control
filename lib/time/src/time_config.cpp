#include "time_config.h"
json_edit_config json_time_config;
HTTPClient http_time_config;

IPAddress time_config::GetPublicIp()
{
    String url = "https://api.ipify.org/?format=json";
    http_time_config.begin(url);
    int status = http_time_config.GET();
    String resulet;
    if (status == 200)
    {
        resulet = http_time_config.getString();
        JsonDocument doc;
        deserializeJson(doc, resulet);
        String string_ip = doc["ip"];
        IPAddress ip;
        ip.fromString(string_ip);
        return ip;
    }
    if (status == 400)
    {
        return IPAddress(400, 400, 400, 400);
    }
}
String time_config::GetTime()
{
    String ip = GetPublicIp().toString();
    String url = "https://timeapi.io/api/Time/current/ip?ipAddress=" + ip;
    http_time_config.begin(url);
    int status = http_time_config.GET();
    String resulet;
    if (status == 200)
    {
        resulet = http_time_config.getString();
        JsonDocument doc_request;
        deserializeJson(doc_request, resulet);
        int date = doc_request["day"];
        int month = doc_request["month"];
        int year = doc_request["year"];
        int hour = doc_request["hour"];
        int minute = doc_request["minute"];
        String day = doc_request["dayOfWeek"];

        json_time_config.SetCurrentTime(date, month, year, minute, hour,day);

        return  json_time_config.GetCurrentTime();
        
    }
    if (status == 400)
    {
        return "400";
    }
};