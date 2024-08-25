#include "web_server_lis.h"
sd_edit_config web_server_sd_edit;
json_edit_config web_server_json_edit;
AsyncWebServer server(80);
ac_system_tasks web_server_system_tasks;
time_config web_server_time_config;
networking_config web_server_network;

// initial state
char *GetInitialState_Path = "/get_initial_state";

// users
char *GetUserList_Path = "/get_user_list";
char *AddUser_Path = "/add_user";
char *DeleteUserList_Path = "/remove_user";
char *RegisterUserFingerprint_Path = "/register_user_fingerprint";
char *ExistUserName_Path = "/exist_user_name";
char *ExistUserPin_Path = "/exist_user_pin";
// logs
char *GetLogList_Path = "/get_log_list";

// temp_users
char *GetTempUserList_Path = "/get_temp_user_list";
char *AddTempUser_Path = "/add_temp_user";
char *DeleteTempUserList_Path = "/remove_temp_user";
char *ExistTempUserName_Path = "/exist_temp_user_name";
char *ExistTempUserPin_Path = "/exist_temp_user_pin";

// schedule
char *GetScheduleUserList_Path = "/get_schedule_list";
char *AddScheduleUser_Path = "/add_schedule";
char *DeleteScheduleUserList_Path = "/remove_schedule";
char *ExistScheduleUserName_Path = "/exist_schedule_user_name";

// Config
char *GetConfig_Path = "/get_config";
char *EditConfig_Path = "/edit_config";
char *WiFiListConfig_Path = "/wifi_list_config";

//system task

const char *paths_arry[] = {
    GetInitialState_Path,
    GetUserList_Path,
    AddUser_Path,
    DeleteUserList_Path,
    RegisterUserFingerprint_Path,
    ExistUserName_Path,
    ExistUserPin_Path,
    GetLogList_Path,
    GetTempUserList_Path,
    AddTempUser_Path,
    DeleteTempUserList_Path,
    ExistTempUserName_Path,
    ExistTempUserPin_Path,
    GetScheduleUserList_Path,
    AddScheduleUser_Path,
    DeleteScheduleUserList_Path,
    ExistScheduleUserName_Path,
    GetConfig_Path,
    EditConfig_Path};

void web_server_lis::web_server_start()
{
  // char * name = web_server_json_edit.GetSystemName();
  Serial.println("web_server_start");
  Serial.println(sizeof(paths_arry));

  // char * path = (name + "/web/").c_str();

  // web_server_sd_edit.start_sd();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text.html", "heloo"); });
  // initial state
  server.on(GetInitialState_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text.html", "heloo"); });
  // users
  server.on(GetUserList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String UserList = web_server_json_edit.user_list_names();
              request->send(200, "text.html", UserList); });
  server.on(AddUser_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String data = request->arg("data");
              Serial.println(data);
              JsonDocument doc;
              deserializeJson(doc, data);
              String name = doc["name"];
              int findex = doc["findex"];
              String pin = doc["pin"];
              bool permissionsnormal = doc["permissions"]["normal"];
              bool permissionsconfig = doc["permissions"]["config"];
              String timeid = doc["timeid"];
              String error = "";
              if (web_server_json_edit.user_name_exist(name))
              {
                error.concat("invalid Name\n");
              }
              if (web_server_json_edit.user_pin_exist(pin))
              {
                error.concat("invalid Pin\n");
              }
              if (web_server_json_edit.user_findex_exist(findex))
              {
                error.concat("invalid findex\n");
              }
              if (timeid=="")
              {
                error.concat("invalid timeid\n");
              }
              if (error == "")
              {
                web_server_json_edit.make_user(name,findex,pin,timeid,false,permissionsnormal,permissionsconfig);
                request->send(200, "text.html", "ok");
              }
              else
              {
                request->send(400, "text.html", error);
              } });
  server.on(DeleteUserList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String name = request->arg("data");
              if (web_server_json_edit.user_name_exist(name))
              {
                String pin = web_server_json_edit.user_pin(name);
                int findex = web_server_json_edit.user_findex(pin);
                web_server_json_edit.remove_user(name, findex, pin);

                request->send(200, "text.html", "ok");
              }
              else
              {
                request->send(200, "text.html", "user does not exist");
              } });

  server.on(RegisterUserFingerprint_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              int index = web_server_json_edit.user_last_findex();
              web_server_system_tasks.fingreprint_register(index);
              request->send(200, "text.html", String(index)); });
  server.on(ExistUserName_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String name = request->arg("data");
              bool exsist = web_server_json_edit.user_name_exist(name);
              request->send(200, "text.html", String(exsist)); });

  server.on(ExistUserPin_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String pin = request->arg("data");
              bool exsist = web_server_json_edit.user_pin_exist(pin);
              request->send(200, "text.html", String(exsist)); });

  // logs
  server.on(GetLogList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text.html", "heloo"); });

  // temp_users
  server.on(GetTempUserList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String TempUserList = web_server_json_edit.user_temp_list_names();
              request->send(200, "text.html", TempUserList); });
  server.on(AddTempUser_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {   String data = request->arg("data");
              Serial.println(data);
              JsonDocument doc;
              deserializeJson(doc, data);
              String name = doc["name"];
              String pin = doc["pin"];
              bool permissionsnormal = doc["permissions"]["normal"];
              bool permissionsconfig = doc["permissions"]["config"];
              String timeid = doc["timeid"];
              String error = "";
              if (web_server_json_edit.user_name_exist(name))
              {
                error.concat("invalid Name\n");
              }
              if (web_server_json_edit.user_pin_exist(pin))
              {
                error.concat("invalid Pin\n");
              }
             if (timeid=="")
              {
                error.concat("invalid timeid\n");
              }
              if (error == "")
              {
                web_server_json_edit.make_temp_user(name,pin,timeid,permissionsnormal,permissionsconfig);
                request->send(200, "text.html", "ok");
              }
              else
              {
                request->send(400, "text.html", error);
              } });
  server.on(DeleteTempUserList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String name = request->arg("data");
              if (web_server_json_edit.user_temp_name_exist(name))
              {
                web_server_json_edit.remove_temp_user(name);

                request->send(200, "text.html", "ok");
              }
              else
              {
                request->send(200, "text.html", "user does not exist");
              } });
  server.on(ExistTempUserName_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            { String name = request->arg("data");
              bool exsist = web_server_json_edit.user_temp_name_exist(name);
              request->send(200, "text.html", String(exsist)); });

  server.on(ExistTempUserPin_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {     String pin = request->arg("data");
              bool exsist = web_server_json_edit.user_temp_pin_exist(pin);
              request->send(200, "text.html", String(exsist)); });

  // schedule
  server.on(GetScheduleUserList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {    
               String ScheduleUserList = web_server_sd_edit.list_schedule();
              request->send(200, "text.html", ScheduleUserList); });
  server.on(AddScheduleUser_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              // "name" : "",
              //          "times":
              // {
              //   "type" : "",
              //    "days":[],
              //            "start_time" : {
              //              "date" : 0,
              //              "month" : 0,
              //              "year" : 0,
              //              "hour" : 0,
              //              "min" : 0
              //            },
              //  "end_time":
              //   {
              //     "date" : 0,
              //         "month" : 0,
              //         "year" : 0,
              //         "hour" : 0,
              //         "min" : 0
              //   }
              // }
              String data = request->arg("data");
              JsonDocument doc;
              deserializeJson(doc, data);
              String error = "";

              if (!doc.containsKey("name"))
              {
                error.concat("name not found in obj\n");
              }
              else
              {
                String name = doc["name"];

                if (web_server_sd_edit.exists_schedule(name))
                {
                  error.concat(name + " already being used\n");
                }
              }
              if (!doc.containsKey("times"))
              {
                error.concat("times not found in obj\n");
              }
              else
              {
                int size = doc["times"].size();

                for (int i = 0; i < size; i++)
                {
                  for (int l = 0; l < 1; l++)
                  {
                    String time_start_end = l == 0 ? "start_time" : "end_time";
                    if (!doc["times"][i].containsKey("type"))
                    {
                      error.concat(String(i) + ":type not found in obj\n");
                    }
                    else
                    {
                      String type =doc["times"][i]["type"]; 
                      Serial.println(type);
                      if (!(type == "no_entry"||type=="entry"))
                      {                       
                        error.concat(String(i) + ":invalid type \n");
                      }
                      
                      
                    }
                     if (!doc["times"][i].containsKey("day"))
                    {
                      error.concat(String(i) + ":day not found in obj\n");
                    }else
                    {
                     int day_size =doc["times"][i]["day"].size(); 
                      if (day_size==0)
                      {
                        error.concat(String(i) + ":invalid days\n");
                      }
                      

                    }
                    if (!doc["times"][i].containsKey("start_time"))
                    {
                      error.concat(String(i) + ":start_time not found in obj\n");
                    }
                    if (!doc["times"][i][time_start_end].containsKey("date"))
                    {
                      error.concat(String(i) + ":date not found in obj\n");
                    }
                    if (!doc["times"][i][time_start_end].containsKey("month"))
                    {
                      error.concat(String(i) + ":date not found in obj\n");
                    }
                    if (!doc["times"][i][time_start_end].containsKey("year"))
                    {
                      error.concat(String(i) + ":year not found in obj\n");
                    }
                    if (!doc["times"][i][time_start_end].containsKey("hour"))
                    {
                      error.concat(String(i) + ":hour not found in obj\n");
                    }
                    if (!doc["times"][i][time_start_end].containsKey("min"))
                    {
                      error.concat(String(i) + ":min not found in obj\n");
                    }
                  }
                }
              }

              int size = doc["times"].size();
              for (int i = 0; i < size; i++)
              {
                int start_time_date = doc["times"][i]["start_time"]["date"];
                int start_time_month = doc["times"][i]["start_time"]["month"];
                int start_time_year = doc["times"][i]["start_time"]["year"];
                int start_time_hour = doc["times"][i]["start_time"]["hour"];
                int start_time_min = doc["times"][i]["start_time"]["min"];

                int end_time_date = doc["times"][i]["end_time"]["date"];
                int end_time_month = doc["times"][i]["end_time"]["month"];
                int end_time_year = doc["times"][i]["end_time"]["year"];
                int end_time_hour = doc["times"][i]["end_time"]["hour"];
                int end_time_min = doc["times"][i]["end_time"]["min"];

                if (
                    !web_server_time_config.isvalededate(true, start_time_date, start_time_month, start_time_year, 0, 0, 0) &&
                    !web_server_time_config.isvalededate(false, start_time_date, start_time_month, start_time_year, end_time_date, end_time_month, end_time_year))
                {

                  error.concat(String(i) + ":invalid date\n");
                }
                if (!web_server_time_config.isvaledehour(true, start_time_hour, start_time_min, end_time_hour, end_time_min))
                {

                  error.concat(String(i) + ":invalid hour\n");
                }

                if (error == "")
                {
                  web_server_sd_edit.make_schedule(data);
                  request->send(200, "text.html", "ok");
                }
                else
                {
                  request->send(400, "text.html", error);
                }
              } });
  server.on(DeleteScheduleUserList_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String name = request->arg("data");

              if (web_server_sd_edit.remove_schedule(name))
              {
                request->send(200, "text.html", "ok");
              }
              else
              {
                request->send(400, "text.html", "cant do it");
              } });
  server.on(ExistScheduleUserName_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String name = request->arg("data");
              bool ExistSchedule = web_server_sd_edit.exists_schedule(name);
              request->send(200, "text.html", String(ExistSchedule)); });

  // Config

  server.on(GetConfig_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text.html", "heloo"); });
            
  server.on(WiFiListConfig_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String data = web_server_network.wifi_list();
              web_server_json_edit.SetWiFiList(data);

               request->send(200, "text.html", data); 
                           Serial.println(data);

            });
  server.on(EditConfig_Path, HTTP_GET, [](AsyncWebServerRequest *request)
            { 
              //wifi 
              //teligram
              //user
              //
              String error ="";
              String data =request->arg("data");
              JsonDocument doc;
              deserializeJson(doc, data);
              if (!doc.containsKey("ssid"))
              {
                error.concat("ssid not found in obj\n");
              }
               if (!doc.containsKey("pass"))
              {
                error.concat("pass not found in obj\n");

              } if (!doc.containsKey("tb-token"))
              {
                error.concat("tb-token not found in obj\n");

              }
              if (error=="")
              {
                 
             String ssid= doc["ssid"];
             String pass= doc["pass"];
             String teligram_token = doc["tb-token"];
             web_server_json_edit.SetSsid(ssid);
             web_server_json_edit.SetApPass(pass);
             web_server_json_edit.SetTelToken(teligram_token);
             request->send(200, "text.html", "ok"); 
             
              }else{
             request->send(400, "text.html", error); 



              } });
  server.begin();
};