#include <leb.h>
#include <img.h>
#include "loding_icon.h"
#include "corect_icon.h"
#include "incorrect_icon.h"

class screen_compo
{
private:


public:
void screen_start();
void loading_pop_up(bool render,int x=210,int y = 50,int  l_color=WHITE,int b_color=BLACK);
void finger_screen(bool render,bool click_n,bool click_b);

void clear_display();
//"no error"
void keypadscreen(bool render, int show ,String error_text,bool click_n,bool click_b);
void keypadscreen_update_pin(bool render, int show ,String pin, int index);
void incorrect(bool render,bool animation,int x=210,int y = 50);
void correct(bool render,bool animation,int x=210,int y = 50);
void qr_screen(bool render,String data, int size=3,String page_titel="QR",int btn_ops=3,bool click_n = false, bool click_b = false, int offset_x = 150, int offset_y = 80);
void ap_screen(bool render,String ssid, String pass, int pass_s_h,String page_titel="AP Info",int btn_ops=1,bool click_n  = false, bool click_b= false);
void com_error(bool render, String page_titel ="WiFi Error",int theem_coler=RED, int btn_ops =3, bool click_n =false, bool click_b =false);
void selectscreen(bool render,String option_first="Unlocke", bool selected =false ,int x=60,int y=90 ,String page_titel="Mode",String input_letter="A",int btn_ops=0,bool click_n =false, bool click_b =false);
};

