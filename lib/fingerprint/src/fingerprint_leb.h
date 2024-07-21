#include <Adafruit_Fingerprint.h>

class fingerprint_leb
{
private:
    /* data */
public:
    void del_finger(int fing_id);
    String reg_storefinger(int id);
    String check_finger(int fing_id);
        String check_finger();

    void start_fing_sen();
    bool available_finger();
};
