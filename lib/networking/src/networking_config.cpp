#include "networking_config.h"
json_edit_config configC_network;
WiFiScanClass wifiscan;
String networking_config::genretepass()
{
  String letters[40] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  String ap_pass = "";
  Serial.println("-");
  for (int i = 0; i < 8; i++)
  {
    Serial.println("*");
    Serial.println(i);

    ap_pass.concat(letters[random(0, 39)]);
  }
  bool keep = true;
  while (keep)
  {
    if (ap_pass.length() >= 8)
    {
      Serial.println("**");

      Serial.println(ap_pass);
      keep = false;
    }
    else
    {
      Serial.println("--");
      Serial.println(ap_pass);
      for (int i = 0; i < 8; i++)
      {
        Serial.println("*");
        Serial.println(i);

        ap_pass.concat(letters[random(0, 39)]);
      }
    }
  }
  return ap_pass;
}
// SetApSsid
// SetApPass
void networking_config::mack_ap(String ap_ssid, String ap_pass)
{
  Serial.println(ap_pass);
  WiFi.softAP(ap_ssid, ap_pass, 12, 0, 1);
}
bool networking_config::connect_wifi(String ssid, String pass)
{
  WiFi.disconnect();
  // String ssid=config_network.GetSsid();
  // String pass=config_network.GetPass();
  WiFi.begin(ssid, pass);

  int time_trys_conect = 0;

  while (true)
  {
    if (time_trys_conect == configC_network.GetWiFiBeginTimeWait() || WiFi.status() == WL_CONNECT_FAILED)
    {

      return false;
    }

    if (WiFi.status() == WL_CONNECTED)
    {

      return false;
    }
    if (WiFi.status() == WL_NO_SSID_AVAIL)
    {

      return true;
    }

    time_trys_conect++;
    delay(1000);
  }
}
String networking_config::wifi_list()
{
  JsonDocument doc;
  String data = "";
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan end");
  Serial.println(n);  
  Serial.println(WiFi.scanComplete());

  bool loop_en=true;
  while (loop_en)
  {
                  feedLoopWDT();

  int status = WiFi.scanComplete();
  if (status == WIFI_SCAN_RUNNING)
  {  Serial.println("WIFI_SCAN_RUNNING");

   
  }

  if (status == WIFI_SCAN_FAILED)
  {
    loop_en=false;
    Serial.println("WIFI_SCAN_FAILED");
          return ("WIFI_SCAN_FAILED");

  }

 
    if (n == -1)
    {
          loop_en=false;

      return ("no networks found");
    }
    else
    {

      for (int i = 0; i < n; i++)
      {
        Serial.println(WiFi.SSID(i));
        Serial.println(WiFi.BSSIDstr(i));
        String ssid = WiFi.SSID(i);
        ssid.remove(WiFi.SSID(i).indexOf("\n"),2);

        doc[i]["ssid"] = ssid;
        doc[i]["rssi"] = WiFi.RSSI(i);
        doc[i]["mac"] = WiFi.BSSIDstr(i);
      }

      serializeJson(doc, data);
      Serial.println(data);
                loop_en=false;
WiFi.scanDelete();
  Serial.println("DATA RETURNED----------------");

      return data;
    
  }
  }
  
}
