#include <sd_edit_config.h>
ac_system_tasks ac_system_tasks_sd_edit;
json_edit_config configC_sd_edit;
SdFat sd;
time_config time_sd_edit;

String system_name = configC_sd_edit.GetSystemName();
String path_schedule = system_name + "/schedule";
String path_schedule_config = path_schedule + "/config.json";

String path_logs = system_name + "/logs";

int const SDA_PIN = 21;
int const SCL_PIN = 22;
int const SS_PIN = 5;    // 5
int const MOSI_PIN = 23; // 23
int const MISO_PIN = 19; // 19
int const SCK_PIN = 18;  // 18

String sdreadFile(String path)
{
    FsFile file = sd.open(path.c_str(), O_RDWR);
    if (!file)
    {
        return "nop";
    }

    String data = file.readString();

    file.close();
    return data;
}
bool sdwriteFile(String path, String message)
{
    FsFile file = sd.open(path.c_str(), O_RDWR);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return (false);
    }
    if (file.print(message))
    {
        file.close();
        return (true);
    }
    else
    {
        file.close();
        return (false);
    } // Make sure the CREATE and LASTWRITE times are different
}

void json_edit_w_config(String data, String w_path = path_schedule_config)
{
    FsFile make_schedule_file_r = sd.open(w_path, O_READ);
    String ans = make_schedule_file_r.readString();
    make_schedule_file_r.close();
    JsonDocument doc;
    deserializeJson(doc, ans);
    int size_index = doc.size();
    doc[size_index] = data;
    serializeJson(doc, ans);
    FsFile make_schedule_file_w = sd.open(w_path, O_WRITE);
    make_schedule_file_w.println(ans);
    make_schedule_file_w.close();
}
String json_edit_r_config(String r_path = path_schedule_config)
{
  
    FsFile make_schedule_file = sd.open(r_path, O_READ);
    String data = make_schedule_file.readString();
    make_schedule_file.close();
    return data;
}

void sd_edit_config::start_sd()
{
    Serial.println("----------------------");

    Serial.println(path_schedule);
    Serial.println(path_logs);

    int sd_begin_time_wait = configC_sd_edit.GetSdBeginTimeWait();
    int time_passed = 0;
    while (sd.begin(SdSpiConfig(SS_PIN, 3, SPI_CLOCK_DIV2)) == 0)
    {
        Serial.println("sd.begin:");
        Serial.print(sd.begin(SdSpiConfig(SS_PIN, 3, SPI_CLOCK_DIV2)));

        if (time_passed == sd_begin_time_wait)
        {
            ac_system_tasks_sd_edit.restart("Sd Failure");
        }
        time_passed++;
        delay(1000);
    }

    if (sd.exists(system_name) == 0)
    {
        FsFile make_file_system_root = sd.open(system_name, O_CREAT);
        make_file_system_root.close();
        // schedule
        FsFile make_file_system_schedule = sd.open(path_schedule, O_CREAT);
        make_file_system_schedule.close();
        FsFile make_file_system_schedule_config = sd.open(path_schedule_config, O_WRITE | O_CREAT);
        make_file_system_schedule_config.println("[]");
        make_file_system_schedule.close();

        // logs
        FsFile make_file_system_logs = sd.open(path_logs, O_CREAT);
        make_file_system_logs.close();
    }
}
void sd_edit_config::make_schedule(String user_json_oject)
{
    Serial.println(user_json_oject);
    JsonDocument doc;
    deserializeJson(doc, user_json_oject);
    String schedule_name = doc["name"];
    String path = path_schedule + "/" + schedule_name + ".json";
    FsFile make_schedule_file = sd.open(path, O_WRITE | O_CREAT);
    make_schedule_file.println(user_json_oject);
    make_schedule_file.close();
    json_edit_w_config(schedule_name);
}
bool sd_edit_config::exists_schedule(String name)
{
    name.toUpperCase();
    String path = path_schedule_config;
    FsFile make_schedule_file = sd.open(path_schedule_config, O_READ);
    String data = make_schedule_file.readString();
    make_schedule_file.close();
    if (data.indexOf(name) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
String sd_edit_config::list_schedule()
{
    return json_edit_r_config();
}
bool sd_edit_config::is_allow_to_enter(String id_name)
{
time_sd_edit.GetTime();
    return "hello";
}