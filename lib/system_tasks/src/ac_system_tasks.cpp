
#include <ac_system_tasks.h>
time_config time_config_system_tasks;
json_edit_config json_config_system_tasks;
screen_compo screen_system_tasks;
sd_edit_config sd_config_system_tasks;
fingerprint_leb finger_system_tasks;
String session_map_mode_select = "mode_select";
String session_map_pin_enter = "pin_enter";
String session_map_finger_print = "finger_print";
String session_map_permissions_select = "permissions_select";
String session_map_finish = "finish";
String action_normel = "normel";
String action_config = "config";

void sho_hide_pin(String pin_to_show, bool show)
{
    Serial.println(show);
    for (int i = 0; i < pin_to_show.length(); i++)
    {
        screen_system_tasks.keypadscreen_update_pin(true, true, show, String(pin_to_show[i]), i);
    }
    screen_system_tasks.keypadscreen_update_eye(true, true, show);
}

void del_pin(String pin, bool show, int count_pin = 1)
{
    pin.remove(0);
    json_config_system_tasks.SetSessionPin("");

    screen_system_tasks.keypadscreen_update_pin(false, true, show, pin, 0);
}

void ac_system_tasks::restart(String perpous)
{
    Serial.println(perpous);
    // make loge
    ESP.restart();
}
void ac_system_tasks::fingreprint_register(int index){
screen_system_tasks.finger_screen(true,false,false);
start:
finger_system_tasks.set_sensor_color(FINGERPRINT_LED_BLUE);
while (!finger_system_tasks.available_finger())
{
Serial.println(".");
}
if (finger_system_tasks.reg_storefinger(index)=="true")
{
finger_system_tasks.set_sensor_color(4);
vTaskDelay(1000);
screen_system_tasks.finger_screen(false,false,false);
finger_system_tasks.set_sensor_color(FINGERPRINT_LED_OFF);


}

}

void ac_system_tasks::verification_reset()
{
    json_config_system_tasks.SetSessionPin("");
    json_config_system_tasks.SetSessionUserMapIndex(0);
    json_config_system_tasks.SetSessionUserMapSendIndex(-1);
    json_config_system_tasks.SetSessionUserPermissions(false, false);
    json_config_system_tasks.SetSessionUserAction("");
    json_config_system_tasks.SetSessionIsOn(false);
    json_config_system_tasks.SetSessionShowPin(false);
    json_config_system_tasks.SetSessionName("");
    json_config_system_tasks.SetSessionFindex(0);
    json_config_system_tasks.SetSessionUserTimeId("");
    json_config_system_tasks.SetSessionUserTime(0, 0, 0, 0, 0);
    json_config_system_tasks.SetSessionUserCountDown(0);
}
void ac_system_tasks::verification(String input)
{
    String key = input;
Start_verification:
    String map_key = json_config_system_tasks.GetSessionMapKey(json_config_system_tasks.GetSessionUserMapIndex());
    String map_show_key = json_config_system_tasks.GetSessionMapKey(json_config_system_tasks.GetSessionUserMapSendIndex());
    Serial.println(map_key);
    Serial.println(map_show_key);

    if (map_key == session_map_mode_select)
    {
        if (map_show_key != session_map_mode_select)
        {
            Serial.println(key);
            screen_system_tasks.selectscreen(true, "Normel", false, 60, 90, "Mode", "A");
            screen_system_tasks.selectscreen(true, "Temp", false, 60, 190, "Mode", "B");
            json_config_system_tasks.SetSessionIsOn(true);
            json_config_system_tasks.SetSessionUserMapSendIndex(0);
        }
        else
        {
            int inusemapeindex = 0;
            int mapeindex = 0;

            if (key == "A")
            {
                inusemapeindex = 0;
                mapeindex = 1;
            }
            if (key == "B")
            {
                inusemapeindex = 1;
                mapeindex = 1;
            }
            if (key == "A" || key == "B")
            {
                json_config_system_tasks.SetSessionUserInUseMap(inusemapeindex);
                json_config_system_tasks.SetSessionUserMapIndex(mapeindex);
                screen_system_tasks.selectscreen(false, "Normel", false, 60, 90, "Mode", "A");
                screen_system_tasks.selectscreen(false, "Temp", false, 60, 190, "Mode", "B");
                goto Start_verification;
            }
        }
    }
    if (map_key == session_map_pin_enter)
    {

        if (map_show_key != session_map_pin_enter)
        {
            Serial.println(key);
            screen_system_tasks.keypadscreen(true, json_config_system_tasks.GetSessionShowPin(), "no error", true, true);
            json_config_system_tasks.SetSessionUserMapSendIndex(1);
        }
        else
        {
            String c_pin = json_config_system_tasks.GetSessionPin();
            if (key == "A")
            {
                if (c_pin.length() < 8)
                {
                    screen_system_tasks.keypadscreen(true, json_config_system_tasks.GetSessionShowPin(), "Retriving Data...", true, true);
                    // Get Session Map
                    if (json_config_system_tasks.GetSessionUserInUseMap() == 0)
                    {
                        // check if pin exist
                        if (json_config_system_tasks.user_pin_exist(c_pin))
                        { // if pin exist
                            String name = json_config_system_tasks.user_name(c_pin);
                            int f_index = json_config_system_tasks.user_findex(c_pin);
                            String timeid = json_config_system_tasks.user_timeid(c_pin);
                            bool permissions_config = json_config_system_tasks.user_permissions_config(c_pin);
                            bool permissions_normel = json_config_system_tasks.user_permissions_config(c_pin);
                            json_config_system_tasks.SetSessionName(name);
                            json_config_system_tasks.SetSessionFindex(f_index);
                            json_config_system_tasks.SetSessionUserTimeId(timeid);
                            json_config_system_tasks.SetSessionUserTime(time_config_system_tasks.Getdate(), time_config_system_tasks.Getmonth(), time_config_system_tasks.Getyear(), time_config_system_tasks.Gethour(), time_config_system_tasks.Getmin());
                            json_config_system_tasks.SetPinTrys(0);
                            json_config_system_tasks.SetSessionUserMapIndex(2);
                            json_config_system_tasks.SetSessionUserPermissions(permissions_normel, permissions_config);

                            screen_system_tasks.keypadscreen(false, json_config_system_tasks.GetSessionShowPin(), "no error", true, true);
                            screen_system_tasks.correct(true, false);
                            screen_system_tasks.correct(false, true);
                        }
                        else
                        { // if pin does not exist
                            screen_system_tasks.keypadscreen(true, json_config_system_tasks.GetSessionShowPin(), "Pin Does not exist", true, true);
                            json_config_system_tasks.SetSessionPin("");
                            json_config_system_tasks.SetPinTrys(json_config_system_tasks.GetPinTrys() + 1);
                            json_config_system_tasks.SetSessionUserMapSendIndex(0);
                            json_config_system_tasks.SetSessionUserMapIndex(1);
                        }
                        goto Start_verification;
                    }
                    else if (json_config_system_tasks.GetSessionUserInUseMap() == 1)
                    {
                        // check if pin exist
                        if (json_config_system_tasks.user_temp_pin_exist(c_pin))
                        { // if pin exist
                            String name = json_config_system_tasks.user_temp_name(c_pin);
                            String timeid = json_config_system_tasks.user_temp_timeid(c_pin);

                            bool permissions_config = json_config_system_tasks.user_temp_permissions_config(c_pin);
                            bool permissions_normel = json_config_system_tasks.user_temp_permissions_normal(c_pin);
                            json_config_system_tasks.SetSessionName(name);
                            json_config_system_tasks.SetSessionUserTimeId(timeid);
                            json_config_system_tasks.SetSessionUserPermissions(permissions_normel, permissions_config);
                            json_config_system_tasks.SetSessionUserTime(time_config_system_tasks.Getdate(), time_config_system_tasks.Getmonth(), time_config_system_tasks.Getyear(), time_config_system_tasks.Gethour(), time_config_system_tasks.Getmin());
                            json_config_system_tasks.SetPinTrys(0);
                            json_config_system_tasks.SetSessionUserMapIndex(2);

                            screen_system_tasks.keypadscreen(false, json_config_system_tasks.GetSessionShowPin(), "no error", true, true);
                            screen_system_tasks.correct(true, false);
                            screen_system_tasks.correct(false, true);
                        }
                        else
                        { // if pin does not exist
                            screen_system_tasks.keypadscreen(true, json_config_system_tasks.GetSessionShowPin(), "Pin Does not exist", true, true);
                            json_config_system_tasks.SetSessionPin("");
                            json_config_system_tasks.SetPinTrys(json_config_system_tasks.GetPinTrys() + 1);
                            json_config_system_tasks.SetSessionUserMapSendIndex(0);
                            json_config_system_tasks.SetSessionUserMapIndex(1);
                        }
                        goto Start_verification;
                    }
                }
                else
                {

                    screen_system_tasks.keypadscreen(true, json_config_system_tasks.GetSessionShowPin(), "Invalid Pin...", true, true);
                }
            }
            else if (key == "B")
            {
                screen_system_tasks.keypadscreen(false, json_config_system_tasks.GetSessionShowPin(), "no error", true, true);

                json_config_system_tasks.SetSessionPin("");
                json_config_system_tasks.SetSessionUserInUseMap(0);
                json_config_system_tasks.SetSessionUserMapSendIndex(-1);
                json_config_system_tasks.SetSessionUserMapIndex(0);
                goto Start_verification;
            }
            else if (key == "C")
            {
                //  screen_system_tasks.keypadscreen(true, !show, "no error", true, true);
                json_config_system_tasks.SetSessionShowPin(!json_config_system_tasks.GetSessionShowPin());

                sho_hide_pin(c_pin.c_str(), json_config_system_tasks.GetSessionShowPin());
            }
            else if (key == "D")
            {
                del_pin(c_pin, json_config_system_tasks.GetSessionShowPin());
            }
            else
            {
                Serial.println(c_pin);

                if (c_pin.length() < 8)
                {

                    c_pin.concat(key);
                    json_config_system_tasks.SetSessionPin(c_pin);
                    screen_system_tasks.keypadscreen_update_pin(true, false, json_config_system_tasks.GetSessionShowPin(), key, c_pin.length() - 1);

                    Serial.println(c_pin);
                    Serial.println(c_pin.length());
                }
            }
        }
    }
    if (map_key == session_map_finger_print)
    {

        if (map_show_key != session_map_finger_print)
        {
            Serial.println(key);
            screen_system_tasks.finger_screen(true, false, false);

            finger_system_tasks.set_sensor_color(true, 0);
            json_config_system_tasks.SetSessionUserMapSendIndex(2);
        }
        else
        {
            int timer = 0;
            while (!finger_system_tasks.available_finger())
            {
                if (json_config_system_tasks.GetFingerTimeWait() * 1000 == timer)
                {
                    // reset
                    json_config_system_tasks.SetSessionPin("");
                    json_config_system_tasks.SetSessionUserInUseMap(0);
                    json_config_system_tasks.SetSessionUserMapSendIndex(-1);
                    json_config_system_tasks.SetSessionUserMapIndex(0);
                }

                delay(1);
            }
            int finger_index = json_config_system_tasks.GetSessionFindex();
            if (finger_system_tasks.check_finger(finger_index) == "true")
            {
                finger_system_tasks.set_sensor_color(true, 4);

                json_config_system_tasks.SetSessionUserMapSendIndex(3);
                screen_system_tasks.finger_screen(false, false, false);
                screen_system_tasks.correct(true, true);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                screen_system_tasks.correct(false, true);
            }
            else
            {
                finger_system_tasks.set_sensor_color(true, 1);
                json_config_system_tasks.SetSessionUserMapSendIndex(1);
                json_config_system_tasks.SetFingTrys(json_config_system_tasks.GetFingTrys() + 1);

                finger_system_tasks.set_sensor_color(false, 1);
                screen_system_tasks.finger_screen(false, false, false);
                screen_system_tasks.incorrect(true, true);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                screen_system_tasks.incorrect(false, true);
            }
            goto Start_verification;
        }
    }
    if (map_key == session_map_permissions_select)
    {

        if (map_show_key != session_map_permissions_select)
        {
            bool permissions_config = json_config_system_tasks.GetSessionUserPermissionsConfig();
            bool permissions_normel = json_config_system_tasks.GetSessionUserPermissionsNormal();
            if (permissions_config)
            {
                screen_system_tasks.selectscreen(true, "Unlocke", false, 60, 90, "Action", "A");
            }
            if (permissions_normel)
            {
                screen_system_tasks.selectscreen(true, "Config", false, 60, 190, "Action", "B");
            }
            json_config_system_tasks.SetSessionUserMapSendIndex(3);
        }
        else
        {
            String action = "";
            if (key == "A")
            {
                action = action_normel;
            }
            if (key == "B")
            {
                action = action_config;
            }
            if (key == "A" || key == "B")
            {
                json_config_system_tasks.SetSessionUserAction(action);
                json_config_system_tasks.SetSessionUserMapIndex(4);
            }
        }
    }
    if (map_key == session_map_finish)
    {

        if (map_show_key != session_map_finish)
        {
            String action = json_config_system_tasks.GetSessionUserAction();
            if (action == action_normel)
            {
                //open door
                //make log
                verification_reset();
            }
            if (action == action_config)
            {
                //open ap
                //make log
                verification_reset();
            }
        }
    }
}