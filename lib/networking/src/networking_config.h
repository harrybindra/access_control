#include <leb.h>
#include <json_edit_config.h>
#ifndef NETWORKING_CONFIG_H
#define NETWORKING_CONFIG_H
class networking_config
{
private:
    /* data */
public:
    
    void mack_ap(String ap_ssid,String ap_pass);
    String genretepass();
bool connect_wifi(String ssid,String pass);
String wifi_list();

};


#endif