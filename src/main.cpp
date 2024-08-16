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
screen_compo screen_main;
fingerprint_leb finger_main;
TimerEvent timer;
TimerEvent screen_loding_timer;

networking_config network;
json_edit_config config_main;
telegram mes;
sd_edit_config sd_config_main;
time_config t_config;
ac_system_tasks system_tasks_main;
TaskHandle_t Task1;
TaskHandle_t Task2;

void Task1code(void *parameter)
{

  for (;;)
  {
    esp_task_wdt_reset();
    if (Serial1.available())
    {

     String key = Serial1.readStringUntil(';');
 
      system_tasks_main.verification(key);
    
    }
  }
}
void Task2code(void *parameter)
{

  for (;;)
  {   
 // vTaskDelay(400);
  }
}
void setup()
{

  Serial.begin(9600, SERIAL_8N1);
  Serial1.begin(9600, SERIAL_8N1, 14, 12);
  Serial1.setRxTimeout(2);
finger_main.start_fing_sen();
                        finger_main.set_sensor_color(0);

  sd_config_main.start_sd();
   screen_main.screen_start();
  // screen_main.keypadscreen(true, config_main.GetSessionShowPin(), "Invalid Pin...", true, true);
  config_main.SetSsid("Viu_A7E39D");
  config_main.SetPass("rm850x80");
  network.connect_wifi(config_main.GetSsid(), config_main.GetPass());
config_main.make_temp_user("HARRY","12345678","0",true,true);

  config_main.SetTelToken("7275182988:AAF8tqOPkFuc81nsYQZA_W96WcD3qhyiVzI");
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  rtc_wdt_disable();
  t_config.GetTime();
  rtc_wdt_enable();


  xTaskCreate(
      Task1code,
      "verification",
      50000,
      NULL,
      1,
      &Task1);
  
  // xTaskCreate(
  //     Task2code,
  //     "teligram",
  //     10000,
  //     NULL,
  //     1,
  //     &Task2
  //     );

}


void loop()
{
  esp_task_wdt_reset();

Serial.println("-");

    String messige = mes.get_last_mass();
      Serial.println(messige);

    if (messige != "false")
    {

      JsonDocument doc;
      deserializeJson(doc, messige);
      String text = doc["text"];
      Serial.println(text);

      mes.conand_map(text);
    
  }

}
