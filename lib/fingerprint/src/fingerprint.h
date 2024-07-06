#include "./Adafruit-Fingerprint-Sensor-Library-master/Adafruit_Fingerprint.h"

class fingerprint
{
private:
    /* data */
public:
    void del_finger(int fing_id);
    String reg_storefinger(int id);
    String check_finger(int fing_id);
    void start_fing_sen();
};
