#include <Arduino.h>
#include "leb.h"
#include <telegram.h>
#include <screen_compo.h>
#include <json_edit_config.h>
#include <networking_config.h>
#include <sd_edit_config.h>
#include <TimerEvent.h>
#include "esp_core_dump.h"
#include <time_config.h>

TimerEvent timer;
networking_config network;
json_edit_config config_main;
screen_compo screen;
telegram mes;
sd_edit_config sd_config_main;
time_config t_config;

void setup()
{    

  Serial.begin(9600, SERIAL_8N1);

   sd_config_main.start_sd();

  config_main.SetSsid("Viu_A7E39D");
   config_main.SetPass("rm850x80");
   network.connect_wifi(config_main.GetSsid(), config_main.GetPass());

   config_main.SetTelToken("7275182988:AAF8tqOPkFuc81nsYQZA_W96WcD3qhyiVzI");
   timer.set(1000, []()
            {      

  String messige =mes.get_last_mass();
  Serial.println(messige);
  t_config.GetTime();
 if (messige != "false")
  {
    JsonDocument doc;
  deserializeJson(doc,messige);
  String text = doc["text"];
 mes.conand_map(text);
  } });
}

void loop()
{
   timer.update();
}
