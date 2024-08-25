#include <Arduino.h>
#include "leb.h"
#include <telegram.h>
#include <json_edit_config.h>
#include <networking_config.h>
#include <sd_edit_config.h>
#include <TimerEvent.h>
#include <time_config.h>
#include <ac_system_tasks.h>
#include <screen_compo.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/rtc_wdt.h"
#include <fingerprint_leb.h>
#include "web_server_lis.h"
screen_compo screen_main;
fingerprint_leb finger_main;
TimerEvent timer;
TimerEvent screen_loding_timer;
web_server_lis web_server_lis_main;
networking_config network;
json_edit_config config_main;
telegram mes;
sd_edit_config sd_config_main;
time_config t_config;
ac_system_tasks system_tasks_main;
TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
void Task1code(void *parameter)
{

  for (;;)
  {

    esp_task_wdt_reset();
    esp_task_wdt_deinit();

    if (Serial1.available())
    {
      vTaskSuspend(Task2);
      String key = Serial1.readStringUntil(';');
      system_tasks_main.verification(key);
      vTaskResume(Task2);
    }
    esp_task_wdt_init(3, true);
    esp_task_wdt_add(NULL);
  }
}
void Task2code(void *parameter)
{

  for (;;)
  {  
  //   Serial.println("-");
  // String messige = mes.get_last_mass();
  // Serial.println(messige);
  // if (messige != "false")
  // {
  //   JsonDocument doc;
  //   deserializeJson(doc, messige);
  //   String text = doc["text"];
  //   Serial.println(text);
  //   mes.conand_map(text);
  // }
   
  }
}
void Task3code(void *parameter)
{

  for (;;)
  { 
    //  esp_task_wdt_reset();
    // esp_task_wdt_deinit();

    // String data =network.wifi_list();
    
    //  config_main.SetWiFiList(data);
    //     esp_task_wdt_init(3, true);
    // esp_task_wdt_add(NULL);
  }
}

void setup()
{

  Serial.begin(9600, SERIAL_8N1);
  Serial1.begin(9600, SERIAL_8N1, 14, 12);
  Serial1.setRxTimeout(2);
  finger_main.start_fing_sen();
  sd_config_main.start_sd();
  screen_main.screen_start();
  mes.teligram_reset();
  system_tasks_main.verification_reset();
  // screen_main.keypadscreen(true, config_main.GetSessionShowPin(), "Invalid Pin...", true, true);
  config_main.SetSsid("Viu_A7E39D");
  config_main.SetPass("rm850x80");
  network.connect_wifi(config_main.GetSsid(), config_main.GetPass());
    config_main.SetWiFiList(network.wifi_list());

  finger_main.del_finger(420);
  config_main.SetTelToken("7275182988:AAF8tqOPkFuc81nsYQZA_W96WcD3qhyiVzI");
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  rtc_wdt_disable();
  t_config.GetTime();
  rtc_wdt_enable();
  Serial.println("---");
  Serial.println("---");
  web_server_lis_main.web_server_start();
  Serial.println(sd_config_main.list_schedule());

  xTaskCreatePinnedToCore(
      Task1code,
      "verification",
      50000,
      NULL,
      1,
      &Task1,
      0);

   xTaskCreatePinnedToCore(
       Task2code,
       "teligram",
       10000,
       NULL,
       1,
       &Task2,
       1);
    // xTaskCreatePinnedToCore(
    //    Task3code,
    //    "wifi",
    //    20000,
    //    NULL,
    //    1,
    //    &Task3,
    //    0);
}

void loop()
{
 
delay(1000);

}
