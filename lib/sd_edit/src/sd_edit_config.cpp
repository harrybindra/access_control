#include <sd_edit_config.h>
json_edit_config configC_sd_edit;
SdFat sd;
time_config time_sd_edit;
String system_name;
String path_schedule;
String path_schedule_config;

String path_logs;
String path_logs_config;

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
    Serial.println(data);
    make_schedule_file.close();
    return data;
}

void sd_edit_config::start_sd()
{
    system_name = configC_sd_edit.GetSystemName();
    path_schedule = system_name + "/schedule";
    path_schedule_config = path_schedule + "/config.json";
    path_logs = system_name + "/logs";
    path_logs_config = path_logs + "/config.json";
    Serial.println("----------------------");
    Serial.println(system_name);
    Serial.println(path_schedule);
    Serial.println(path_logs);
    Serial.println(path_schedule_config);

    int sd_begin_time_wait = configC_sd_edit.GetSdBeginTimeWait();
    int time_passed = 0;
    while (sd.begin(SdSpiConfig(SS_PIN, 3, SPI_CLOCK_DIV2)) == 0)
    {
        Serial.println("sd.begin:");
        Serial.print(sd.begin(SdSpiConfig(SS_PIN, 3, SPI_CLOCK_DIV2)));

        if (time_passed == sd_begin_time_wait)
        {
            ESP.restart();
            break;
        }
        time_passed++;
        delay(1000);
    }

    if (sd.exists(system_name) == 0)
    {
        sd.mkdir(system_name, O_WRITE | O_CREAT | O_TRUNC);
        // schedule
        sd.mkdir(path_schedule, O_WRITE | O_CREAT | O_TRUNC);
        FsFile make_file_system_schedule_config = sd.open(path_schedule_config, O_WRITE | O_CREAT | O_TRUNC);
        make_file_system_schedule_config.println("[]");
        make_file_system_schedule_config.close();
        // logs
        sd.mkdir(path_logs, O_WRITE | O_CREAT | O_TRUNC);
        FsFile make_file_system_log_config = sd.open(path_logs_config, O_WRITE | O_CREAT | O_TRUNC);
        make_file_system_log_config.println("[]");
        make_file_system_log_config.close();
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
    String data = json_edit_r_config();
    return data;
}

String sd_edit_config::get_schedule(String name)
{
    String path = path_schedule + "/" + name + ".json";
    FsFile file = sd.open(path, O_READ);
    String resulet = file.readString();
    return resulet;
}

bool sd_edit_config::remove_schedule(String name)
{
    String path = path_schedule + "/" + name + ".json";
    FsFile file = sd.open(path, O_WRITE);
    file.print("");
    Serial.println(file.readString());
    file.close();
    bool rem = sd.remove(path);
    String config_schedule = json_edit_r_config(path_schedule_config);

    JsonDocument doc;
    deserializeJson(doc, config_schedule);
    for (int i = 0; i < doc.size(); i++)
    {
        if (doc[i] == name)
        {
            Serial.println(name);

            doc.remove(i);
        }
    }
    serializeJson(doc, config_schedule);
    Serial.println(config_schedule);
    FsFile make_schedule_file_w = sd.open(path_schedule_config, O_WRITE);
    make_schedule_file_w.println(config_schedule);
    make_schedule_file_w.close();
    return rem;
}
bool sd_edit_config::is_allow_to_enter(String id_name)
{
    bool is_alowed_to_enter;
    String path = path_schedule + "/" + id_name + ".json";
    FsFile file = sd.open(path, O_READ);
    String resulet = file.readString();
    JsonDocument doc;
    deserializeJson(doc, resulet);
    int times_size = doc["times"].size();
    String day = time_sd_edit.Getday();
    int date = time_sd_edit.Getdate();
    int month = time_sd_edit.Getmonth();
    int year = time_sd_edit.Getyear();
    int hour = time_sd_edit.Gethour();
    int min = time_sd_edit.Getmin();

    for (int i = 0; i < times_size; i++)
    {
        String schedule_day = doc["times"][i]["day"];
        int schedule_date_start = doc["times"][i]["start_time"]["date"];
        int schedule_month_start = doc["times"][i]["start_time"]["month"];
        int schedule_year_start = doc["times"][i]["start_time"]["year"];
        int schedule_hour_start = doc["times"][i]["start_time"]["hour"];
        int schedule_min_start = doc["times"][i]["start_time"]["min"];

        int schedule_date_end = doc["times"][i]["end_time"]["date"];
        int schedule_month_end = doc["times"][i]["end_time"]["month"];
        int schedule_year_end = doc["times"][i]["end_time"]["year"];
        int schedule_hour_end = doc["times"][i]["end_time"]["hour"];
        int schedule_min_end = doc["times"][i]["end_time"]["min"];

        if (
            schedule_day.indexOf(day) != -1 &&
            schedule_date_start >= date &&
            schedule_month_start >= month &&
            schedule_year_start >= year &&
            schedule_hour_start >= hour &&
            schedule_min_start >= min &&

            schedule_date_end <= date &&
            schedule_month_end <= month &&
            schedule_year_end <= year &&
            schedule_hour_end <= hour &&
            schedule_min_end <= min)
        {
            return true;
        }
    }
    return false;
}