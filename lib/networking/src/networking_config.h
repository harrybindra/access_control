#include <leb.h>

class networking_config
{
private:
    /* data */
public:
    
    void mack_ap(String ap_ssid,String ap_pass);
    String genretepass();
bool connect_wifi(String ssid,String pass);
};


