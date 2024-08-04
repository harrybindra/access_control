#include "screen_compo.h"



QRCode qrcode;
ILI9488 myScreen = ILI9488(CS, DC, MOSI, SCLK, RESET, MISO);
const unsigned char *loding_icon[] = {
     loding_icon_frame_00_delay_0,
     loding_icon_frame_01_delay_0,
     loding_icon_frame_02_delay_0,
     loding_icon_frame_03_delay_0,
     loding_icon_frame_04_delay_0,
     loding_icon_frame_05_delay_0,
     loding_icon_frame_06_delay_0,
     loding_icon_frame_07_delay_0,
     loding_icon_frame_08_delay_0,
     loding_icon_frame_09_delay_0,
     loding_icon_frame_10_delay_0,
     loding_icon_frame_11_delay_0,
     loding_icon_frame_12_delay_0,
     loding_icon_frame_13_delay_0,
     loding_icon_frame_14_delay_0,
     loding_icon_frame_15_delay_0,
     loding_icon_frame_16_delay_0,
     loding_icon_frame_17_delay_0,
     loding_icon_frame_18_delay_0,
     loding_icon_frame_19_delay_0,
     loding_icon_frame_20_delay_0,
     loding_icon_frame_21_delay_0,
     loding_icon_frame_22_delay_0,
     loding_icon_frame_23_delay_0,
     loding_icon_frame_24_delay_0,
     loding_icon_frame_25_delay_0,
     loding_icon_frame_26_delay_0,
     loding_icon_frame_27_delay_0};

const unsigned char *correct_icon[] = {
	 correct_icon_frame_00_delay_0,
	 correct_icon_frame_01_delay_0,
	 correct_icon_frame_02_delay_0,
	 correct_icon_frame_03_delay_0,
	 correct_icon_frame_04_delay_0,
	 correct_icon_frame_05_delay_0,
	 correct_icon_frame_06_delay_0,
	 correct_icon_frame_07_delay_0,
	 correct_icon_frame_08_delay_0,
	 correct_icon_frame_09_delay_0,
	 correct_icon_frame_10_delay_0,
	 correct_icon_frame_11_delay_0,
	 correct_icon_frame_12_delay_0,
	 correct_icon_frame_13_delay_0,
	 correct_icon_frame_14_delay_0,
	 correct_icon_frame_15_delay_0,
	 correct_icon_frame_16_delay_0,
	 correct_icon_frame_17_delay_0,
	 correct_icon_frame_18_delay_0,
	 correct_icon_frame_19_delay_0,
	 correct_icon_frame_20_delay_0,
	 correct_icon_frame_21_delay_0,
	 correct_icon_frame_22_delay_0,
	 correct_icon_frame_23_delay_0,
	 correct_icon_frame_24_delay_0,
	 correct_icon_frame_25_delay_0,
	 correct_icon_frame_26_delay_0,
	 correct_icon_frame_27_delay_0
};
void letter_icon(bool render, int x, int y, String lett,bool click=false, int w = 50, int h = 50)
{
  if (render)
  {
   
  
    
  
     if (click)
    {
    myScreen.fillRect(x, y, w, h, BLACK);
    delay(100);
    myScreen.fillRect(x+10,y+10,w-20,h-20,WHITE);
   myScreen.fillRect(x, y, w, h, WHITE);
     
    }else{
        myScreen.fillRect(x, y, w, h, WHITE);
 
    }
        myScreen.setTextColor(BLACK);
    myScreen.setCursor(x + (w / 2.5), y + (h / 3));
    myScreen.print(lett);
  }
  else
  {
    myScreen.fillRect(x, y, w, h, BLACK);
  }
}
const unsigned char* incorrect_icon[28] = {
	incorrect_icon_frame_00_delay_0,
	incorrect_icon_frame_01_delay_0,
	incorrect_icon_frame_02_delay_0,
	incorrect_icon_frame_03_delay_0,
	incorrect_icon_frame_04_delay_0,
	incorrect_icon_frame_05_delay_0,
	incorrect_icon_frame_06_delay_0,
	incorrect_icon_frame_07_delay_0,
	incorrect_icon_frame_08_delay_0,
	incorrect_icon_frame_09_delay_0,
	incorrect_icon_frame_10_delay_0,
	incorrect_icon_frame_11_delay_0,
	incorrect_icon_frame_12_delay_0,
	incorrect_icon_frame_13_delay_0,
	incorrect_icon_frame_14_delay_0,
	incorrect_icon_frame_15_delay_0,
	incorrect_icon_frame_16_delay_0,
	incorrect_icon_frame_17_delay_0,
	incorrect_icon_frame_18_delay_0,
	incorrect_icon_frame_19_delay_0,
	incorrect_icon_frame_20_delay_0,
	incorrect_icon_frame_21_delay_0,
	incorrect_icon_frame_22_delay_0,
	incorrect_icon_frame_23_delay_0,
	incorrect_icon_frame_24_delay_0,
	incorrect_icon_frame_25_delay_0,
	incorrect_icon_frame_26_delay_0,
	incorrect_icon_frame_27_delay_0
};

int cal_wid(String text,int size){
int w = size*6;

return w;

}
int cal_hig(String text,int size){

int h = size*8;
return h;

}
int cal_mid_x(String text,int size){
int w = size*6;
return (text.length()*w)/2;

}
int cal_mid_y(String text,int size){
int h = size*8;
return (text.length()*h)/2;

}

// draw box
void icon(bool render, int x, int y, int w = 50, int h = 50)
{
  if (render)
  {
    myScreen.drawRect(x, y, w, h, WHITE);
    myScreen.fillRect(x, y, w, h, WHITE);
  }
  else
  {
    myScreen.drawRect(x, y, w, h, BLACK);
    myScreen.fillRect(x, y, w, h, BLACK);
  }
}
void next_icon(bool render, int color, bool click)
{
  if (render)
  {
    letter_icon(true, 480 - 100, 320 - 50, "A",click);
    myScreen.drawRect(480 - 50, 320 - 50, 50, 50, WHITE);
    myScreen.drawBitmap(480 - 50, 320 - 50, next, 50, 50, color);
  
  }
  else
  {
    letter_icon(false, 480 - 100, 320 - 50, "A",click);

    myScreen.fillRect(480 - 50, 320 - 50, 50, 50, BLACK);
  }
}
void back_icon(bool render, int color, bool click)
{
  if (render)
  {
    letter_icon(true, 0 + 50, 320 - 50, "B",click);
    myScreen.drawRect(0, 320 - 50, 50, 50, WHITE);
    myScreen.drawBitmap(0, 320 - 50, back, 50, 50, color);
  
  }
  else
  {
    letter_icon(false, 0 + 50, 320 - 50, "B",click);
    myScreen.fillRect(0, 320 - 50, 50, 50, BLACK);
  }
}
void overlay(bool render, String page_titel, int btn_ops, bool click_n = false, bool click_b = false, int x = 200, int y = 3)
{    int page_titel_half= cal_mid_x(page_titel,2);

  if (render)
  {
   //240
    myScreen.setTextColor(WHITE);
    myScreen.setCursor(240-page_titel_half, y);
    myScreen.setTextSize(2);
    myScreen.print(page_titel + ":");
    myScreen.drawRect(0, 25, 480, 1, WHITE);


    switch (btn_ops)
    {
    case 0:
      break;
    case 1:
      next_icon(true, WHITE, click_n);
      break;
    case 2:
      back_icon(true, WHITE, click_b);
      break;
    case 3:
      next_icon(true, WHITE, click_n);
      back_icon(true, WHITE, click_b);
      break;
    default:
      break;
    }
  }
  else
  {
    myScreen.fillRect(x, y, cal_wid(page_titel,2), cal_hig(page_titel,2), BLACK);

    switch (btn_ops)
    {
    case 0:
      break;
    case 1:
      next_icon(false, BLACK, click_n);
      break;
    case 2:
      back_icon(false, BLACK, click_b);
      break;
    case 3:
      next_icon(false, BLACK, click_n);
      back_icon(false, BLACK, click_b);
      break;
    default:
      break;
    }
  }
}
void waitfor_finger(int per, int y = 300)
{

  myScreen.setCursor(per, y);
  myScreen.setTextSize(1);
  myScreen.setTextColor(0xffff);
  myScreen.println(".");
}

void screen_compo::screen_start()
{
  myScreen.begin();
  myScreen.setRotation(3);
  myScreen.fillScreen(BLACK);
};
void screen_compo::loading_pop_up(bool render,int x,int y, int l_color, int b_color)
{
  if (render)
  {
    int f = 0;
    while (true)
    {
      if (f == 27)
      {
        f = 0;
      }
      myScreen.drawBitmap(x, y, loding_icon[f], 60, 60,WHITE );
            delay(1); 
      myScreen.fillRect(x+2,y+24, 60, 12, b_color);
      f++;
    }
  }
};
void screen_compo::finger_screen(bool render, bool click_n = false, bool click_b = false)
{
  if (render)
  {

    overlay(true, "Fingerprint", 1, click_n, click_b, 180, 5);

    myScreen.drawBitmap(150, 50, fingerprint, 179, 150, 0xFFFF);
  }
  else
  {
    overlay(false, "Fingerprint", 1, click_n, click_b, 180, 5);
    myScreen.fillRect(150, 50, 179, 150, BLACK);
  }
}
void screen_compo::keypadscreen(bool render, int show, String error_text, bool click_n = false, bool click_b = false)
{
  int g = error_text.length();
  if (render)
  {

    myScreen.setTextColor(0xffff);
    myScreen.setCursor(200, 3);
    myScreen.setTextSize(2);

    // myScreen.print("Pin:");
    // myScreen.drawRect(0, 25, 480, 1, 0xffff);
    overlay(true, "Pin", 3, click_n, click_b);
    myScreen.fillRect(50, 50, 340, 80, WHITE);

    if (show == 1)
    {
      myScreen.fillRect(390 + 2, 50, 80, 80, 0x0000);
      myScreen.drawRect(390 + 2, 50, 80, 80, 0xffff);

      myScreen.drawBitmap(390 + 2 + (80 / 4.5), 50 + (80 / 4.5), eye, 50, 50, 0xffff);
    }
    else
    {

      myScreen.fillRect(390 + 2, 50, 80, 80, 0x0000);
      myScreen.drawRect(390 + 2, 50, 80, 80, 0xffff);
      myScreen.drawBitmap(390 + 2 + (80 / 4.5), 50 + (80 / 4.5), no_eye, 50, 50, 0xffff);
    }

    if (error_text.indexOf("no error") == -1)
    {
      myScreen.fillRect(0, 180, 480, 30, 0x0000);

      myScreen.fillRect(50, 180, g * 12 + 20, 30, 0x0000);

      myScreen.drawRect(50, 180, g * 12 + 20, 30, 0xffff);
      myScreen.setCursor(60, 185);
      myScreen.setTextSize(2);
      myScreen.setTextColor(RED);
      myScreen.println(error_text);
      myScreen.setTextColor(0x0000);
    }

    // it should be 390x50 but to put black bodere 390 +2
    // letter_icon(390+2,50," ",80,80);

    // BACK
    //  myScreen.setCursor(28,102);
    //  myScreen.fillRect(16,100,40,20,0xffff);
    // myScreen.setTextSize(2);
    // myScreen.println("B");
    // myScreen.drawBitmap(10,100,back,20,20,0x0000);
  }
  else
  {
    myScreen.drawRect(0, 25, 480, 1, 0x0000);
    myScreen.fillRect(390 + 2, 50, 80, 80, 0x0000);
    myScreen.fillRect(50, 50, 340, 80, 0x0000);
    myScreen.fillRect(50, 180, g * 12 + 20, 30, 0x0000);

    overlay(false, "pin", 3, click_n, click_b, 180, 5);
  }
}
void screen_compo::keypadscreen_update_pin(bool render, int show, String pin, int index)
{
  if (index > 7)
  {
    ESP_LOG_ERROR;
  }
  int offset = index * 45 + 15;
  if (render)
  {

    myScreen.setTextSize(6);

    for (int i = 0; i < pin.length(); i++)
    {
      offset = offset + i * 45;
      myScreen.setCursor(offset, 70);
      if (show)
      {
        myScreen.println(pin[i]);
      }
      else
      {
        myScreen.fillRect(offset, 70, 36, 48, WHITE);
        myScreen.println("*");
      }
    }
    myScreen.setTextSize(2);
  }
  else
  {
    myScreen.fillRect(50, 50, 340, 80, WHITE);
  }
}

void screen_compo::clear_display()

{

  myScreen.fillRect(0, 0, 480, 320, 0x00);
}
void screen_compo::correct(bool render,bool animation,int x,int y)
{
  if (render)
  {
    if (animation)
    { 
    for (int i = 0; i < 26; i++)
    {
        myScreen.fillRect(x+10, y+10, 30, 30,BLACK);
        myScreen.drawBitmap(x, y, correct_icon[i], 50, 50, GREEN);
    }
    }else{
        myScreen.drawBitmap(x, y, correct_icon[26], 50, 50, GREEN);

    }
  
    
    }else{
      myScreen.fillRect(x, y, 50, 50,BLACK);
    }
  

}
void screen_compo::incorrect(bool render,bool animation,int x,int y)
{ 
      if (render)
  {
    if (animation)
    { 
    for (int i = 0; i < 27; i++)
    {
        myScreen.fillRect(x, y, 50, 50,BLACK);
        myScreen.drawBitmap(x, y, incorrect_icon[i], 50, 50, RED);
    }
    }else{
        myScreen.drawBitmap(x, y, incorrect_icon_s, 50, 50, RED);

    }
  
    
    }else{
      myScreen.fillRect(x, y, 50, 50,BLACK);
    }
  
}
void screen_compo::qr_screen(bool render,String data, int size,String page_titel,int btn_ops,bool click_n  , bool click_b, int offset_x , int offset_y )
{  
  if (render)
  {
 
  overlay(render,page_titel,btn_ops,click_n,click_b);
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, data.c_str());

  // Text starting point
  int cursor_start_y = 10;
  int cursor_start_x = size;
  int font_height = 12;

  // QR Code Starting Point

  for (int y = 0; y < qrcode.size; y++)
  {
  
    for (int x = 0; x < qrcode.size; x++)
    { 
      int newX = offset_x + (x * cursor_start_x);
      int newY = offset_y + (y * cursor_start_x);

      if (qrcode_getModule(&qrcode, x, y))
      {
        myScreen.fillRect(newX, newY, cursor_start_x, cursor_start_x, 0xffff);
      }
      else
      {
        myScreen.fillRect(newX, newY, cursor_start_x, cursor_start_x, 0x0000);
      }
    }
  }  
  }else
  { 
  
  overlay(render,page_titel,btn_ops,click_n,click_b);
 myScreen.fillRect(offset_x, offset_y, qrcode.size*size, qrcode.size*size, BLACK);

  }
  
  
}
void screen_compo::ap_screen(bool render,String ssid, String pass, int pass_s_h,String page_titel,int btn_ops,bool click_n  , bool click_b)
{
  int left = 25;
 if (render)
 {

  overlay(render,page_titel,btn_ops,click_n,click_b);
  // SSID
  myScreen.drawRect(0 + left, 95, 90, 50, 0xffff);
  myScreen.setCursor(20 + left, 110);
  myScreen.setTextColor(0xffff);
  myScreen.print("SSID:");
  myScreen.fillRect(90 + left, 95, 300, 50, 0xffff);
  myScreen.setTextColor(0x0000);
  myScreen.setCursor(90 + 20 + left, 110);
  myScreen.print(ssid);
  // Pass
  myScreen.drawRect(0 + left, 160, 90, 50, 0xffff);
  myScreen.setCursor(20 + left, 160 + 15);
  myScreen.setTextColor(0xffff);
  myScreen.print("PASS:");
  myScreen.fillRect(90 + left, 160, 300, 50, 0xffff);

  myScreen.setTextColor(0x0000);
  myScreen.setCursor(90 + 20 + left, 160 + 15);
  String hid_pass;
  String sho_pass = "";

     for (int i = 0; i <= 8; i++)
  {
    hid_pass.concat("*");
    sho_pass.concat(pass[i]);
  }

  if (pass_s_h == 0)
  {

    myScreen.setTextColor(0x0000);
    myScreen.print(hid_pass);
 
  }
  if (pass_s_h == 1)
  {
    myScreen.setTextColor(0x0000);
    myScreen.print(sho_pass);
 
  }

 }
 else
 {
  {
     overlay(render,page_titel,btn_ops,click_n,click_b);
   myScreen.fillRect(0 + left, 95, 90, 50, BLACK);
    myScreen.fillRect(90 + left, 95, 300, 50, BLACK);

  myScreen.fillRect(0 + left, 160, 90, 50, BLACK);
  myScreen.fillRect(90 + left, 160, 300, 50, BLACK);

  }
 }
 
}
void screen_compo::com_error(bool render, String page_titel,int theem_coler, int btn_ops, bool click_n , bool click_b )
{  
  int page_titel_half =  cal_mid_x(page_titel,3);
  if (render)
  {

  overlay(render, page_titel,  btn_ops,  click_n,  click_b );
  myScreen.drawBitmap(215, 35, warning, 50, 50, theem_coler);
  myScreen.drawRect(60, 100, 360, 60, 0xffff);
  myScreen.setCursor(240-page_titel_half, 120);
  myScreen.setTextSize(3);
  myScreen.setTextColor(theem_coler);
  myScreen.println(page_titel);
  }else
  {
  overlay(render, page_titel,  btn_ops,  click_n,  click_b );
  myScreen.fillRect(215, 35,50, 50,BLACK);
    myScreen.drawRect(60, 100, 360, 60, BLACK);
  myScreen.setCursor(240-page_titel_half, 120);
  myScreen.setTextSize(3);
  myScreen.setTextColor(BLACK);
  myScreen.println(page_titel);
  }
  
  

}
void screen_compo::selectscreen(bool render,String option_first, bool selected,int x,int y ,String page_titel,String input_letter,int btn_ops,bool click_n  , bool click_b)
{
  
  int page_titel_x_half =  cal_mid_x(page_titel,3);
  int page_titel_y_half =  cal_mid_y(page_titel,3);

 if (render)
 {

  overlay(render,page_titel,btn_ops,click_n,click_b);
  // 1
  letter_icon(true,x, y,input_letter,selected,60,60);

  myScreen.drawRect(x, y, 360, 60, WHITE);
  myScreen.setTextColor(WHITE);
  myScreen.setTextSize(3);
  //myScreen.setCursor(204, 90+18);
    myScreen.setCursor((x+(360/2))-page_titel_x_half, y+18);

  Serial.println(page_titel_x_half);
  myScreen.print(option_first);
  // //2
  // myScreen.drawRect(60, 160, 360, 60, WHITE);
  // myScreen.setTextColor(WHITE);
  // myScreen.setTextSize(3);
  // myScreen.setCursor(240-page_titel_x_half, 160-30);
  // myScreen.print(option_first);

 }
 else
 {
  {
   
  }
 }
 
}
