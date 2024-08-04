#include <leb.h>
#include "FS.h"
#include <LittleFS.h>
#include <SPIFFS.h>
//  String LSreadFile( String *path) {}
// void LSlistDir( String *dirname) {}
// void LSwriteFile( String *path,  String *message) {}
#ifndef JSON_EDIT_CONFIG_H

#define JSON_EDIT_CONFIG_H
class json_edit_config
{
private:
  /* data */
public:
  json_edit_config(/* args */);

  String GetBufferSchedule();

  void SetBufferScheduleTime_starTime_hour(int hour, int min);
  void SetBufferScheduleTime_endTime_hour(int hour, int min);
  String GetBufferScheduleTime_starTime_hour();
  String GetBufferScheduleTime_endTime_hour();

void ResetBufferScheduleTime_day();
  int GetBufferScheduleTime_day_size();
  void SetBufferScheduleTime_day(String day);
  String GetBufferScheduleTime_day();

  void ResetBufferScheduleTime();

  String GetBufferScheduleMapKey(int index);

  void SetBufferScheduleIndex(int index);
  int GetBufferScheduleIndex();

  void SetBufferScheduleSendIndex(int index);
  int GetBufferScheduleSendIndex();

  int GetBufferScheduleTimesIndex();
  void SetBufferScheduleTimesIndex(int index);

  String GetBufferScheduleName();

  String GetBufferScheduleTime_type();
  void SetBufferScheduleTime_type(String type);

  String GetBufferScheduleTime_starTime();
  String GetBufferScheduleTime_starTime_date();

  void SetBufferScheduleTime_starTime_date(int date, int month, int year);

  String GetBufferScheduleTime_endTime();
  void SetBufferScheduleTime_endTime_date(int date, int month, int year);

  void SetBufferScheduleName(String name);
  void SetTeligramBotId(int id);
  int GetTeligramBotId();
  int GetTeligramComandIndex();
  void SetTeligramComandIndex(int index);
  String GetTeligramComandKey();

  String GetBufferMapKey(int index);

  int GetBufferUserIndex();
  void SetBufferUserIndex(int index);

  int GetBufferUserSendIndex();
  void SetBufferUserSendIndex(int index);

  String GetBufferUserName();
  void SetBufferUserName(String name);

  String GetBufferUserPin();
  void SetBufferUserPin(String pin);

  bool GetBufferUserPermissionsNormal();
  bool GetBufferUserPermissionsConfig();

  void SetBufferUserPermissionsNormal(bool permissions_normal);
  void SetBufferUserPermissionsConfig(bool permissions_config);

  String GetBufferUserTimeId();
  void SetBufferUserTimeId(String id);

  void make_user(String name, int findex, String pin, int timeid, bool locked, bool permissions_normal, bool permissions_config);
  void remove_user(String name, int findex, String pin);
  bool user_pin_exist(String pin);
  bool user_name_exist(String name);
  bool user_findex_exist(int findex);
  int user_last_findex();
  int user_findex(String pin);
  String user_name(String pin);
  int user_timeid(String pin);
  bool user_permissions_normal(String pin);
  bool user_permissions_config(String pin);
  String user_pin(String name);
  String user_list_names();

  void make_temp_user(String name, String pin, int timeid, bool permissions_normal, bool permissions_config);
  bool user_temp_pin_exist(String pin);
  bool user_temp_name_exist(String name);
  String user_temp_name(String pin);
  int user_temp_timeid(String pin);
  bool user_temp_permissions_normal(String pin);
  bool user_temp_permissions_config(String pin);
  String user_temp_pin(String name);
  String user_temp_list_names();

  String GetApSsid();
  void SetApSsid(String data);

  String GetApPass();
  void SetApPass(String data);
  String GetTelToken();
  void SetTelToken(String data);

  String GetChatId();
  void SetChatId(String data);

  String GetLastUpdateId();
  void SetLastUpdateId(String data);

  bool GetIsNegtiveTimeOffset();
  void SetIsNegtiveTimeOffset(bool data);

  int GetTimeOffset();
  void SetTimeOffset(int data);

  bool GetSetup();
  void SetSetup(bool data);

  int GetPinTrys();
  void SetPinTrys(int data);

  int GetFingTrys();
  void SetFingTrys(int data);

  bool GetOverTrys();
  void SetOverTrys(bool data);

  bool GetErrorCom();
  void SetErrorCom(bool data);

  String GetSsid();
  void SetSsid(String data);

  String GetPass();
  void SetPass(String data);
  int GetSdBeginTimeWait();
  void SetSdBeginTimeWait(int data);

  void SetSystemName(String data);
String GetSystemName();

 void SetPublicIp(String data);
String GetPublicIp();

void SetTimeZone(String data);
String GetTimeZone();

void SetCurrentTime(int date,int month,int year,int hour,int min,String day);
String GetCurrentTime();
};
#endif
