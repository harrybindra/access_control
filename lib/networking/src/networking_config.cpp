#include "networking_config.h"

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
// SetSsid
// SetPass
bool networking_config::connect_wifi(String ssid, String pass)
{
  WiFi.disconnect();
  // String ssid=config_network.GetSsid();
  // String pass=config_network.GetPass();
  WiFi.begin(ssid, pass);

  int time_trys_conect = 0;
  
  while (true)
  {
    if (time_trys_conect == 600 || WiFi.status() == WL_CONNECT_FAILED)
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
    delay(100);
  }
}
