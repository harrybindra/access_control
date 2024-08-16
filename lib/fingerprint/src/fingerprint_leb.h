#include <leb.h>
#include <Adafruit_Fingerprint.h>

#ifndef FINGERPRINT_LEB_H
#define FINGERPRINT_LEB_H
class fingerprint_leb
{
private:
    /* data */
public:  
//#define FINGERPRINT_LED_WHITE 0x00
//#define FINGERPRINT_LED_RED 0x01         //!< Red LED
//#define FINGERPRINT_LED_BLUE 0x02        //!< Blue LED
//#define FINGERPRINT_LED_PURPLE 0x03 
//#define FINGERPRINT_LED_GREEN 0x04  
//#define FINGERPRINT_LED_WHITE_GREEN 0x05  
 void set_sensor_color(bool turn_on,int  color=2);

    void del_finger(int fing_id);
    String reg_storefinger(int id);
    String check_finger(int fing_id);
    String check_finger();
    void start_fing_sen();

    bool available_finger();
};
#endif