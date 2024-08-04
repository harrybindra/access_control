#include "json_edit_config.h"

String path = "/littlefs/config.json";

String LSreadFile(String path)
{
  LittleFS.begin(false);
  File file = LittleFS.open(path.c_str(), FILE_READ);
  if (!file)
  {
    return "nop";
  }

  String data = file.readString();

  file.close();
  return data;
}
bool LSwriteFile(String path, String message)
{
  LittleFS.begin(false, "/");
  File file = LittleFS.open(path.c_str(), FILE_WRITE);
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

void json_edit_w(int data, String json_key, String w_path = path)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
};
void json_edit_w(bool data, String json_key, String w_path = path)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
};
void json_edit_w(signed char data, String json_key, String w_path = path)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
};
void json_edit_w(String data, String json_key, String w_path = path)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
}
String json_edit_r(String json_key, String r_path = path)
{
  String ans = LSreadFile(r_path);
  JsonDocument doc;
  deserializeJson(doc, ans);

  return doc[json_key];
}

// {
//                 "type": "",
//                 "start_time": {
//                     "date": 0,
//                     "month": 0,
//                     "year": 0,
//                     "hour": 0,
//                     "min": 0
//                 },
//                 "end_time": {
//                     "date": 0,
//                     "month": 0,
//                     "year": 0,
//                     "hour": 0,
//                     "min": 0
//                 }
//             }
String json_edit_config::GetBufferSchedule()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonDocument doc_times;
  doc_times["times"] = doc["buffer_schedule"]["times"];
  doc_times["name"] = doc["buffer_schedule"]["s_name"];
  String times_obj;
  serializeJson(doc_times, times_obj);
  return times_obj;
};

String json_edit_config::GetBufferScheduleMapKey(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String key = doc["buffer_schedule"]["buffer_schedule_map"][index];
  return key;
}

void json_edit_config::SetBufferScheduleIndex(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["buffer_schedule_index"] = index;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
int json_edit_config::GetBufferScheduleIndex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int index = doc["buffer_schedule"]["buffer_schedule_index"];
  return index;
}

void json_edit_config::SetBufferScheduleSendIndex(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["buffer_schedule_send_index"] = index;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
int json_edit_config::GetBufferScheduleSendIndex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int index = doc["buffer_schedule"]["buffer_schedule_send_index"];
  return index;
}

int json_edit_config::GetBufferScheduleTimesIndex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int num_of_times = doc["buffer_schedule"]["buffer_schedule_size"];
  return num_of_times;
};

void json_edit_config::SetBufferScheduleTimesIndex(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["buffer_schedule_size"] = index;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
String json_edit_config::GetBufferScheduleName()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String user = doc["buffer_schedule"]["s_name"];
  return user;
};
void json_edit_config::SetBufferScheduleName(String name)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["s_name"] = name;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

// entry/no_entry
String json_edit_config::GetBufferScheduleTime_type()
{
  int index = GetBufferScheduleTimesIndex();

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String user = doc["buffer_schedule"]["times"][index]["type"];
  return user;
};
// entry/no_entry
void json_edit_config::SetBufferScheduleTime_type(String type)
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();

  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["times"][index]["type"] = type;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

String json_edit_config::GetBufferScheduleTime_day()
{
  int index = GetBufferScheduleTimesIndex();

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String user = doc["buffer_schedule"]["times"][index]["day"];

  return user;
}
int json_edit_config::GetBufferScheduleTime_day_size()
{
  int index = GetBufferScheduleTimesIndex();
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int size = doc["buffer_schedule"]["times"][index]["day"].size();

  return size;
}
void json_edit_config::SetBufferScheduleTime_day(String day)
{

  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();

  JsonDocument doc;
  deserializeJson(doc, ans);
  int size = GetBufferScheduleTime_day_size();

  doc["buffer_schedule"]["times"][index]["day"][size] = day;

  serializeJson(doc, ans);

  LSwriteFile(path, ans);
};

void json_edit_config::ResetBufferScheduleTime_day()
{

  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();

  JsonDocument doc;
  deserializeJson(doc, ans);
  int size = GetBufferScheduleTime_day_size();

  doc["buffer_schedule"]["times"][index]["day"].clear();

  serializeJson(doc, ans);

  LSwriteFile(path, ans);
};

void json_edit_config::ResetBufferScheduleTime()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonArray array = doc["buffer_schedule"]["times"].to<JsonArray>();

  // array[0]["type"] = "";
  // array[0]["start_time"]["date"] = 0;
  // array[0]["start_time"]["month"] = 0;
  // array[0]["start_time"]["year"] = 0;
  // array[0]["start_time"]["hour"] = 0;
  // array[0]["start_time"]["min"] = 0;
  // array[0]["end_time"]["date"] = 0;
  // array[0]["end_time"]["month"] = 0;
  // array[0]["end_time"]["year"] = 0;
  // array[0]["end_time"]["hour"] = 0;
  // array[0]["end_time"]["min"] = 0;

  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

String json_edit_config::GetBufferScheduleTime_starTime()
{
  int index = GetBufferScheduleTimesIndex();

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String user = doc["buffer_schedule"]["times"][index]["start_time"];

  return user;
}

String json_edit_config::GetBufferScheduleTime_starTime_date()
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonDocument doc_starTime_date;
  doc_starTime_date["date"] = doc["buffer_schedule"]["times"][index]["start_time"]["date"];
  doc_starTime_date["month"] = doc["buffer_schedule"]["times"][index]["start_time"]["month"];
  doc_starTime_date["year"] = doc["buffer_schedule"]["times"][index]["start_time"]["year"];

  String starTime_date;
  serializeJson(doc_starTime_date, starTime_date);
  return starTime_date;
};

void json_edit_config::SetBufferScheduleTime_starTime_date(int date, int month, int year)
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();

  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["times"][index]["start_time"]["date"] = date;
  doc["buffer_schedule"]["times"][index]["start_time"]["month"] = month;
  doc["buffer_schedule"]["times"][index]["start_time"]["year"] = year;

  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
void json_edit_config::SetBufferScheduleTime_starTime_hour(int hour, int min)
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["times"][index]["start_time"]["hour"] = hour;
  doc["buffer_schedule"]["times"][index]["start_time"]["min"] = min;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

String json_edit_config::GetBufferScheduleTime_starTime_hour()
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonDocument doc_starTime_hour;
  doc_starTime_hour["hour"] = doc["buffer_schedule"]["times"][index]["start_time"]["hour"];
  doc_starTime_hour["min"] = doc["buffer_schedule"]["times"][index]["start_time"]["min"];

  String starTime_hour;
  serializeJson(doc_starTime_hour, starTime_hour);
  return starTime_hour;
};

String json_edit_config::GetBufferScheduleTime_endTime_hour()
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonDocument doc_endTime_hour;
  doc_endTime_hour["hour"] = doc["buffer_schedule"]["times"][index]["end_time"]["hour"];
  doc_endTime_hour["min"] = doc["buffer_schedule"]["times"][index]["end_time"]["min"];
  String endTime_hour;
  serializeJson(doc_endTime_hour, endTime_hour);
  return endTime_hour;
};

String json_edit_config::GetBufferScheduleTime_endTime()
{
  int index = GetBufferScheduleTimesIndex();

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String user = doc["buffer_schedule"]["times"][index]["end_time"];

  return user;
};
void json_edit_config::SetBufferScheduleTime_endTime_date(int date, int month, int year)
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["times"][index]["end_time"]["date"] = date;
  doc["buffer_schedule"]["times"][index]["end_time"]["month"] = month;
  doc["buffer_schedule"]["times"][index]["end_time"]["year"] = year;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
void json_edit_config::SetBufferScheduleTime_endTime_hour(int hour, int min)
{
  String ans = LSreadFile(path);
  int index = GetBufferScheduleTimesIndex();
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_schedule"]["times"][index]["end_time"]["hour"] = hour;
  doc["buffer_schedule"]["times"][index]["end_time"]["min"] = min;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

//"telegram_bot_id":0,
void json_edit_config::SetTeligramBotId(int id)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["telegram_bot_id"] = id;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
int json_edit_config::GetTeligramBotId()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int index = doc["telegram_bot_id"];
  return index;
}

// "telegram_comand_index": -1,
// "telegram_comand_keys": [
//         "add_user",
//         "locke_unlock",
//         "no_entry_time",
//         "shutedown"
//     ],

void json_edit_config::SetTeligramComandIndex(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["telegram_comand_index"] = index;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
int json_edit_config::GetTeligramComandIndex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int index = doc["telegram_comand_index"];
  return index;
}
String json_edit_config::GetTeligramComandKey()
{
  int index = GetBufferScheduleTimesIndex();

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String key = doc["telegram_comand_keys"][index];
  return key;
}

// "buffer_user": {
//         "buffer_user_index": 0,
//         "buffer_user_map": [
//             "name",
//             "pin",
//             "permissions",
//             "timeallow"
//         ],
//         "user": {
//             "name": "",
//             "pin": "",
//             "permissions": {
//                 "normal": true,
//                 "config": true
//             },
//             "timeallow": ""
//         }
//     }

void json_edit_config::SetBufferUserIndex(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["buffer_user_index"] = index;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
int json_edit_config::GetBufferUserIndex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int index = doc["buffer_user"]["buffer_user_index"];
  return index;
}

void json_edit_config::SetBufferUserSendIndex(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["buffer_user_send_index"] = index;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
int json_edit_config::GetBufferUserSendIndex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int index = doc["buffer_user"]["buffer_user_send_index"];
  return index;
}

String json_edit_config::GetBufferMapKey(int index)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String key = doc["buffer_user"]["buffer_user_map"][index];
  return key;
}
String json_edit_config::GetBufferUserName()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String user = doc["buffer_user"]["user"]["name"];
  return user;
};
void json_edit_config::SetBufferUserName(String name)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["user"]["name"] = name;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

String json_edit_config::GetBufferUserPin()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String pin = doc["buffer_user"]["user"]["pin"];
  return pin;
};
void json_edit_config::SetBufferUserPin(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["user"]["pin"] = pin;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
bool json_edit_config::GetBufferUserPermissionsNormal()
{

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  bool permis = doc["buffer_user"]["user"]["permissions"]["normal"];
  return permis;
};
bool json_edit_config::GetBufferUserPermissionsConfig()
{

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  bool permis = doc["buffer_user"]["user"]["permissions"]["config"];
  return permis;
};
void json_edit_config::SetBufferUserPermissionsNormal(bool permissions_normal)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["user"]["permissions"]["config"] = permissions_normal;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
void json_edit_config::SetBufferUserPermissionsConfig(bool permissions_config)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["user"]["permissions"]["config"] = permissions_config;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
String json_edit_config::GetBufferUserTimeId()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  String id = doc["buffer_user"]["user"]["timeallow"];
  return id;
};
void json_edit_config::SetBufferUserTimeId(String id)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["buffer_user"]["user"]["timeallow"] = id;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};

// {
//     "name":"",
//     "findex":"",
//     "pin":"",
//     "locked":false
//     "permissions":{
//         "normal":true,
//         "config":true
//     },
//     "timeallow":""
// }
json_edit_config::json_edit_config()
{
}
void json_edit_config::make_user(String name, int findex, String pin, int timeid, bool locked, bool permissions_normal, bool permissions_config)
{
  name.toUpperCase();
  name.trim();

  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size() == 0 ? 0 : doc["users"].size();
  doc["users"][user_count]["name"] = name;
  doc["users"][user_count]["findex"] = findex;
  doc["users"][user_count]["pin"] = pin;
  doc["users"][user_count]["locked"] = locked;
  doc["users"][user_count]["permissions"]["normal"] = permissions_normal;
  doc["users"][user_count]["permissions"]["config"] = permissions_config;
  doc["users"][user_count]["timeallow"] = timeid;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
void json_edit_config::remove_user(String name, int findex, String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["pin"] == pin && doc["users"][i]["findex"] == findex && doc["users"][i]["name"] == name)
    {
      doc["users"].remove(i);
      break;
    }
  }
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
};
bool json_edit_config::user_pin_exist(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["pin"] == pin)
    {
      return true;
    }
  }
  return false;
}
bool json_edit_config::user_name_exist(String name)
{
  name.toUpperCase();

  name.trim();
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["name"] == name)
    {
      return true;
    }
  }
  return false;
}
bool json_edit_config::user_findex_exist(int findex)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["findex"] == findex)
    {
      return true;
    }
  }
  return false;
}
int json_edit_config::user_last_findex()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 1; i < user_count; i++)
  {
    if (doc["users"][i]["findex"] != i)
    {
      return i;
    }
  }
  return -1;
}

int json_edit_config::user_findex(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["pin"] == pin)
    {
      return doc["users"][i]["findex"];
    }
  }
  return NULL;
}
String json_edit_config::user_name(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["pin"] == pin)
    {
      return doc["users"][i]["name"];
    }
  }
  return "";
}
int json_edit_config::user_timeid(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["pin"] == pin)
    {
      return doc["users"][i]["timeallow"];
    }
  }
  return NULL;
}
bool json_edit_config::user_permissions_normal(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["pin"] == pin)
    {
      return doc["users"][i]["permissions"]["normal"];
    }
  }
  return false;
}
bool json_edit_config::user_permissions_config(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {

    if (doc["users"][i]["pin"] == pin)
    {
      return doc["users"][i]["permissions"]["config"];
    }
  }
  return false;
}
String json_edit_config::user_pin(String name)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["users"][i]["name"] == name)
    {
      return doc["users"][i]["pin"];
    }
  }
  return "";
}
String json_edit_config::user_list_names()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonDocument user_list;

  int user_count = doc["users"].size();
  for (int i = 0; i < user_count; i++)
  {
    user_list[i] = doc["users"][i]["name"];
  }
  serializeJson(user_list, ans);
  return ans;
}

// {
//   "name" : "",
//            "pin" : "",
//                    "permissions" : {
//                      "normal" : true,
//                      "config" : true
//                    },
//                                    "timeallow" : ""
// }
void json_edit_config::make_temp_user(String name, String pin, int timeid, bool permissions_normal, bool permissions_config)
{
  name.toUpperCase();
  name.trim();
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size() == 0 ? 0 : doc["temp_user"].size();
  doc["temp_user"][user_count]["name"] = name;
  doc["temp_user"][user_count]["pin"] = pin;
  doc["temp_user"][user_count]["permissions"]["normal"] = permissions_normal;
  doc["temp_user"][user_count]["permissions"]["config"] = permissions_config;
  doc["temp_user"][user_count]["timeallow"] = timeid;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
bool json_edit_config::user_temp_pin_exist(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {

    if (doc["temp_user"][i]["pin"] == pin)
    {
      return true;
    }
  }
  return false;
}
bool json_edit_config::user_temp_name_exist(String name)
{
  name.toUpperCase();
  name.trim();
  String ans = LSreadFile(path);
  JsonDocument doc;

  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {

    if (doc["temp_user"][i]["name"] == name)
    {
      return true;
    }
  }
  return false;
}
String json_edit_config::user_temp_name(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["temp_user"][i]["pin"] == pin)
    {
      return doc["temp_user"][i]["name"];
    }
  }
  return "";
}
int json_edit_config::user_temp_timeid(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["temp_user"][i]["pin"] == pin)
    {
      return doc["temp_user"][i]["timeallow"];
    }
  }
  return NULL;
}
bool json_edit_config::user_temp_permissions_normal(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {

    if (doc["temp_user"][i]["pin"] == pin)
    {
      return doc["temp_user"][i]["permissions"]["normal"];
    }
  }
  return false;
}
bool json_edit_config::user_temp_permissions_config(String pin)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {

    if (doc["temp_user"][i]["pin"] == pin)
    {
      return doc["temp_user"][i]["permissions"]["config"];
    }
  }
  return false;
}
String json_edit_config::user_temp_pin(String name)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {
    if (doc["temp_user"][i]["name"] == name)
    {
      return doc["temp_user"][i]["pin"];
    }
  }
  return "";
}
String json_edit_config::user_temp_list_names()
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  JsonDocument user_list;

  int user_count = doc["temp_user"].size();
  for (int i = 0; i < user_count; i++)
  {
    user_list[i] = doc["temp_user"][i]["name"];
  }
  serializeJson(user_list, ans);
  return ans;
}

String json_edit_config::GetApSsid()
{
  return json_edit_r("ap_ssid");
};
void json_edit_config::SetApSsid(String data)
{
  json_edit_w(data, "ap_ssid");
};

String json_edit_config::GetApPass()
{
  return json_edit_r("ap_pass");
};
void json_edit_config::SetApPass(String data)
{
  json_edit_w(data, "ap_pass");
};

String json_edit_config::GetTelToken()
{
  return json_edit_r("teltoken");
}

void json_edit_config::SetTelToken(String data)
{
  json_edit_w(data, "teltoken");
}
// chat id(every user has 1 id)
String json_edit_config::GetChatId()
{
  return json_edit_r("chatid");
}
// chat id(every user has 1 id)
void json_edit_config::SetChatId(String data)
{
  json_edit_w(data, "chatid");
}
// Update Id(every new chat has 1 id)
String json_edit_config::GetLastUpdateId()
{

  return json_edit_r("lastupdate_id");
}
void json_edit_config::SetLastUpdateId(String data)
{

  json_edit_w(data, "lastupdate_id");
}

bool json_edit_config::GetIsNegtiveTimeOffset()
{
  return json_edit_r("isnegtivetimeoffset");
}
void json_edit_config::SetIsNegtiveTimeOffset(bool data)
{

  json_edit_w(data, "isnegtivetimeoffset");
}

int json_edit_config::GetTimeOffset()
{

  return json_edit_r("timeoffset").toInt();
}
void json_edit_config::SetTimeOffset(int data)
{
  json_edit_w(data, "timeoffset");
}

bool json_edit_config::GetSetup()
{

  return json_edit_r("setup") == "true" || "1" ? true : false;
}
void json_edit_config::SetSetup(bool data)
{
  json_edit_w(data, "setup");
}

int json_edit_config::GetPinTrys()
{

  return json_edit_r("pintrys").toInt();
}
void json_edit_config::SetPinTrys(int data)
{
  json_edit_w(data, "pintrys");
}

int json_edit_config::GetFingTrys()
{
  return json_edit_r("fingtrys").toInt();
}
void json_edit_config::SetFingTrys(int data)
{
  json_edit_w(data, "fingtrys");
}

bool json_edit_config::GetOverTrys()
{
  return json_edit_r("overtrys") == "true" || "1" ? true : false;
}
void json_edit_config::SetOverTrys(bool data)
{
  json_edit_w(data, "overtrys");
}

bool json_edit_config::GetErrorCom()
{
  return json_edit_r("errorcom") == "true" || "1" ? true : false;
}
void json_edit_config::SetErrorCom(bool data)
{
  json_edit_w(data, "errorcom");
}

String json_edit_config::GetSsid()
{

  return json_edit_r("ssid");
}

void json_edit_config::SetSsid(String data)
{
  json_edit_w(data, "ssid");
}

String json_edit_config::GetPass()
{
  return json_edit_r("pass");
}

void json_edit_config::SetPass(String data)
{
  json_edit_w(data, "pass");
}
int json_edit_config::GetSdBeginTimeWait()
{
  return json_edit_r("sd_begin_time_wait").toInt();
}

void json_edit_config::SetSdBeginTimeWait(int data)
{
  json_edit_w(data, "sd_begin_time_wait");
}

void json_edit_config::SetSystemName(String data)
{
  json_edit_w(data, "system_name");
}

String json_edit_config::GetSystemName()
{
  return json_edit_r("system_name");
}

void json_edit_config::SetPublicIp(String data)
{
  json_edit_w(data, "public_ip");
}
String json_edit_config::GetPublicIp()
{
  return json_edit_r("public_ip");
}

void json_edit_config::SetTimeZone(String data)
{
  json_edit_w(data, "time_zone");
}
String json_edit_config::GetTimeZone()
{
  return json_edit_r("time_zone");
}

void json_edit_config::SetCurrentTime(int date,int month,int year,int hour,int min,String day)
{
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc["current_time"]["date"] = date;
  doc["current_time"]["month"] = month;
  doc["current_time"]["year"] = year;
  doc["current_time"]["hour"] = hour;
  doc["current_time"]["min"] = min;
  doc["current_time"]["day"] = day;
  serializeJson(doc, ans);
  LSwriteFile(path, ans);
}
String json_edit_config::GetCurrentTime()
{
 
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
    JsonDocument doc_current_time;
doc_current_time["date"]=doc["current_time"]["date"] ;
doc_current_time["month"]=doc["current_time"]["month"] ;
doc_current_time["year"]=doc["current_time"]["year"] ;
doc_current_time["hour"]=doc["current_time"]["hour"] ;
doc_current_time["min"]=doc["current_time"]["min"] ;
doc_current_time["day"]=doc["current_time"]["day"] ;

  serializeJson(doc, ans);
  return ans;
}