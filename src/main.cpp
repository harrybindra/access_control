#include <Arduino.h>
#include <json_edit_config.h>
json_edit_config configC;
void setup()
{
  Serial.begin(9600, SERIAL_8N1);
  configC.SetSetup("hello");
  Serial.println(configC.GetSsid());
  

}

void loop()
{
}
