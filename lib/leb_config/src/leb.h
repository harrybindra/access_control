#include <ArduinoJson.h>
#include <Arduino.h>
#include <iostream>
#include <qrcode.h>
#include <HTTPClient.h>
#include <TimerEvent.h>


#define BLACK 0x0000
#define RED 0xF800
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE  0xFFFF

#define SCLK 21
#define MOSI 22
#define MISO -1
#define CS 15
#define DC 0
#define RESET 4
#define led 33

