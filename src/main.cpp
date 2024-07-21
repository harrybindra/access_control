#include <Arduino.h>
#include <leb.h>
void setup()
{
  Serial.begin(9600, SERIAL_8N1);
//configC.SetSsid("hello");
screen.screen_start();

screen.selectscreen(true,"UNLOCK",true,60,90,"Mode","A");

screen.selectscreen(true,"CONFIG",true,60,190,"Mode","B");

}
void loop()
{  

}
