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
  {  file.close();
    return(true);
  }
  else
  {  file.close();
    return(false);
  } // Make sure the CREATE and LASTWRITE times are different

}

void json_edit_w(int data, String json_key, String w_path = path){
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
};
void json_edit_w(bool data, String json_key, String w_path = path){
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
};
void json_edit_w(signed char data, String json_key, String w_path = path){
  String ans = LSreadFile(path);
  JsonDocument doc;
  deserializeJson(doc, ans);
  doc[json_key] = data;
  serializeJson(doc, ans);
  LSwriteFile(w_path, ans);
};
void json_edit_w( String data, String json_key, String w_path = path)
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

String json_edit_config::GetTelToken()
{
  return json_edit_r("teltoken");
}

void json_edit_config::SetTelToken(String data)
{
  json_edit_w(data, "teltoken");
}

String json_edit_config::GetChatId()
{
  return json_edit_r("chatid");
}
void json_edit_config::SetChatId(String data)
{
  json_edit_w(data, "chatid");
}

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