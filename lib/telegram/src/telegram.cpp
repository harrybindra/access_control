#include <telegram.h>

#include <json_edit_config.h>
HTTPClient http_teligram;
TimerEvent timer_teligram;
sd_edit_config sd_edit_teligram;
json_edit_config configC_teligram;
String comand_key_add_user = "add_user";
String comand_key_locke_unlock = "locke_unlock";
String comand_key_schedule = "schedule";
String comand_key_shutedown = "shutedown";
bool isvalededate(int date0, int month0, int year0, int date1, int month1, int year1)
{
  if (date0 > date1)
  {
    Serial.println("date0");
    return false;
  }
  else if (month0 > month1)
  {    Serial.println("month0");

    return false;
  }
  else if (year0 > year1)
  {    Serial.println("year0");

    return false;
  }
  
    return true;
  
}
bool isvaledehour(int hour0, int min0, int hour1, int min1)
{
  if (hour0 > hour1)
  {
    return false;
  }
  else if (min0 > min1)
  {
    return false;
  }
  else
  {
    return true;
  }
}
String days_render()
{
  String days = configC_teligram.GetBufferScheduleTime_day();

  Serial.println(configC_teligram.GetBufferScheduleTime_day());

  JsonDocument doc;
  doc["inline_keyboard"][0][0]["text"] = days.indexOf("monday") == -1 ? "MONDAY" : "\xE2\x9C\x85 MONDAY";
  doc["inline_keyboard"][0][0]["callback_data"] = "monday";
  doc["inline_keyboard"][1][0]["text"] = days.indexOf("tuesday") == -1 ? "TUESDAY" : "\xE2\x9C\x85	TUESDAY";
  doc["inline_keyboard"][1][0]["callback_data"] = "tuesday";

  doc["inline_keyboard"][2][0]["text"] = days.indexOf("wednesday") == -1 ? "WEDNESDAY" : "\xE2\x9C\x85	WEDNESDAY";
  doc["inline_keyboard"][2][0]["callback_data"] = "wednesday";

  doc["inline_keyboard"][3][0]["text"] = days.indexOf("thursday") == -1 ? "THURSDAY" : "\xE2\x9C\x85	THURSDAY";
  doc["inline_keyboard"][3][0]["callback_data"] = "thursday";

  doc["inline_keyboard"][4][0]["text"] = days.indexOf("friday") == -1 ? "FRIDAY" : "\xE2\x9C\x85 FRIDAY";
  doc["inline_keyboard"][4][0]["callback_data"] = "friday";

  doc["inline_keyboard"][5][0]["text"] = days.indexOf("saturday") == -1 ? "SATURDAY" : "\xE2\x9C\x85	SATURDAY";
  doc["inline_keyboard"][5][0]["callback_data"] = "saturday";

  doc["inline_keyboard"][6][0]["text"] = days.indexOf("sunday") == -1 ? "SUNDAY" : "\xE2\x9C\x85 SUNDAY";
  doc["inline_keyboard"][6][0]["callback_data"] = "sunday";

  doc["inline_keyboard"][7][0]["text"] = "DONE";
  doc["inline_keyboard"][7][0]["callback_data"] = "s_days";

  doc["inline_keyboard"][7][1]["text"] = "RESET";
  doc["inline_keyboard"][7][1]["callback_data"] = "r_days";
  String data;
  serializeJson(doc, data);
  return data;
}
// GetChatId
// GetTelToken
bool has_letters(String data)
{
  int data_int = data.toInt();
  if (String(data_int).length() == data.length())
  {
    return false;
  }
  else
  {
    return true;
  }
}
void telegram::send_text(String text, String object, bool update)
{

  String chatid = configC_teligram.GetChatId();
  String token = configC_teligram.GetTelToken();
  int bot_mess_id = configC_teligram.GetTeligramBotId();

  String is_update = update && bot_mess_id != 0 ? "editMessageText" : "sendMessage";
  String path = "https://api.telegram.org/bot" + token + "/" + is_update;

  JsonDocument doc_pak;
  doc_pak["chat_id"] = chatid;
  doc_pak["text"] = text;
  doc_pak["reply_markup"] = object;
  doc_pak["message_id"] = bot_mess_id;
  String paquet = "{\"chat_id\":\"" + chatid + "\",\"text\":\"" + text + "\",\"reply_markup\": " + object + ",\"message_id\":" + bot_mess_id + "}";
  //
  // serializeJson(doc_pak, Serial);

  http_teligram.begin(path);
  Serial.println(http_teligram.connected());
  http_teligram.addHeader("Host", "api.telegram.org");
  http_teligram.addHeader("Content-Type", "application/json");
  http_teligram.addHeader("Content-Length", "42");

  int respons = http_teligram.POST(paquet);
  String paylode = http_teligram.getString();
  if (respons == 400)
  {
    Serial.println(paylode);
  }

  JsonDocument doc;
  deserializeJson(doc, paylode);
  int mess_id = doc["result"]["message_id"];
  configC_teligram.SetTeligramBotId(mess_id);

  http_teligram.end();
}

void telegram::remove_mass(int mass_id)
{

  String chatid = configC_teligram.GetChatId();
  String token = configC_teligram.GetTelToken();
  String path = "https://api.telegram.org/bot" + token + "/deleteMessage";

  JsonDocument doc_pak;
  doc_pak["chat_id"] = chatid;
  doc_pak["message_id"] = mass_id;
  String paquet;
  serializeJson(doc_pak, paquet);
  http_teligram.begin(path);
  http_teligram.addHeader("Host", "api.telegram.org");
  http_teligram.addHeader("Content-Type", "application/json");
  http_teligram.addHeader("Content-Length", "42");

  Serial.println(http_teligram.POST(paquet));

  String paylode = http_teligram.getString();

  http_teligram.end();
}

//
// text and id
// GetTelToken
// GetLastUpdateId
// GetChatId
String telegram::get_last_mass()
{

  String token = configC_teligram.GetTelToken();
  String lastupdateid = configC_teligram.GetLastUpdateId();
  String chatid = configC_teligram.GetChatId();
  http_teligram.begin("https://api.telegram.org/bot" + token + "/getUpdates");
  http_teligram.addHeader("Host", "telegram.org");
  JsonDocument doc_pak;
  doc_pak["offset"] = lastupdateid.toInt() + 1;
  doc_pak["timeout"] = 0;

  String paquet;

  serializeJson(doc_pak, paquet);
  Serial.println(paquet);

  if (http_teligram.POST(paquet) == HTTP_CODE_OK)
  {
    String mass_arry = http_teligram.getString();
    JsonDocument doc;
    deserializeJson(doc, mass_arry);
    String result = doc["result"];
    if (result == "[]")
    {

      return "false";
    }
    int index = doc["result"].size() - 1;
    bool callback_query = doc["result"][index].containsKey("callback_query");
    String id = doc["result"][index]["update_id"];

    String text = doc["result"][index]["message"]["text"];
    String chat_id = doc["result"][index]["message"]["chat"]["id"];
    String cb_text = doc["result"][index]["callback_query"]["data"];
    String cb_chat_id = doc["result"][index]["callback_query"]["message"]["chat"]["id"];
    String resulet;
    String idD = doc["result"][index];
    Serial.println(text);
    Serial.println(cb_text);

    if (id == lastupdateid)
    {

      return "false";
    }

    else
    {
      if (chatid != chat_id || chatid == "null")
      {
        configC_teligram.SetChatId(callback_query ? cb_chat_id : chat_id);
      }
      if (chatid == "")
      {
        configC_teligram.SetChatId(callback_query ? cb_chat_id : chat_id);
      }
      else
      {

        JsonDocument resu;
        resu["text"] = callback_query ? cb_text : text;
        resu["id"] = id;
        configC_teligram.SetLastUpdateId(id);
        serializeJson(resu, resulet);
        return resulet;
      }
      return "false";
    }
  }
}

void telegram::conand_map(String comand)
{
  Serial.println(comand);
  Serial.println(comand_key_add_user);
  Serial.println(comand_key_locke_unlock);
  Serial.println(comand_key_schedule);
  Serial.println(comand_key_shutedown);

  comand.trim();
  if (comand == "/start")
  {

    JsonDocument doc;
    doc["inline_keyboard"][0][0]["text"] = "ADD USER";
    doc["inline_keyboard"][0][0]["callback_data"] = "add_user";
    doc["inline_keyboard"][0][1]["text"] = "LOCK/UNLOCKE";
    doc["inline_keyboard"][0][1]["callback_data"] = "locke_unlock";

    doc["inline_keyboard"][1][0]["text"] = "SCHEDULE";
    doc["inline_keyboard"][1][0]["callback_data"] = "schedule";

    doc["inline_keyboard"][1][1]["text"] = "SHUTEDOWN";
    doc["inline_keyboard"][1][1]["callback_data"] = "shutedown";

    String data;
    serializeJson(doc, data);
    configC_teligram.SetBufferUserIndex(0);
    configC_teligram.SetBufferUserSendIndex(-1);
    configC_teligram.SetBufferUserPin("");
    configC_teligram.SetBufferUserName("");
    configC_teligram.SetBufferUserPermissionsNormal(false);
    configC_teligram.SetBufferUserPermissionsConfig(false);

    configC_teligram.SetBufferScheduleIndex(0);
    configC_teligram.SetBufferScheduleSendIndex(-1);

    configC_teligram.SetTeligramComandIndex(-1);

    send_text("select", data, false);
  }
  else if (comand == comand_key_add_user /*add_user*/)
  {

    configC_teligram.SetBufferUserIndex(0);
    configC_teligram.SetBufferUserSendIndex(-1);
    configC_teligram.SetBufferUserPin("");
    configC_teligram.SetBufferUserName("");
    configC_teligram.SetBufferUserPermissionsNormal(false);
    configC_teligram.SetBufferUserPermissionsConfig(false);

    // setting comand index

    configC_teligram.SetTeligramComandIndex(0);
  }
  else if (comand == comand_key_locke_unlock /*locke_unlock*/)
  {
    JsonDocument doc;
    doc["inline_keyboard"][0][0]["text"] = "LOCK";
    doc["inline_keyboard"][0][0]["callback_data"] = "lock";
    doc["inline_keyboard"][0][1]["text"] = "UNLOCK";
    doc["inline_keyboard"][0][1]["callback_data"] = "unlock";
    String data;
    serializeJson(doc, data);
    send_text("select", data, true);
    // setting comand index
    configC_teligram.SetTeligramComandIndex(1);
  }
  else if (comand == comand_key_schedule /*schedule*/)
  {
    configC_teligram.ResetBufferScheduleTime();

    configC_teligram.SetBufferScheduleIndex(0);
    configC_teligram.SetBufferScheduleSendIndex(-1);

    configC_teligram.SetBufferScheduleTimesIndex(0);

    configC_teligram.SetTeligramComandIndex(2);
  }
  else if (comand == comand_key_shutedown /*shutedown*/)
  {
    configC_teligram.SetTeligramComandIndex(3);
  }

  String comand_key = configC_teligram.GetTeligramComandKey();

  if (comand_key == comand_key_add_user)
  {
  add_userstart:

    String buffer_user_map[] = {"name", "pin", "permissions", "timeallow"};
    String key = configC_teligram.GetTeligramComandKey();
    String key_send = configC_teligram.GetTeligramComandKey();

    if (key == "name")
    {

      if (key_send != "name")
      {

        send_text("Name", "{}", true);
        configC_teligram.SetBufferUserSendIndex(0);
      }
      else if (key_send == "name" && comand != "null")
      {

        if (configC_teligram.user_temp_name_exist(comand))
        {
          send_text("Name " + comand + " is already in use", "{}", true);
        }
        else
        {
          configC_teligram.SetBufferUserName(comand);
          // remove_mass(configC_teligram.GetLastUpdateId().toInt());
          configC_teligram.SetBufferUserIndex(1);
          goto add_userstart;
        }
      }
    }
    if (key == "pin")
    {
      if (key_send == "name")
      {
        send_text("Pin(7):", "{}", true);
        configC_teligram.SetBufferUserSendIndex(1);
      }
      else if (key_send == "pin" && comand != "null")
      {
        if (configC_teligram.user_temp_pin_exist(comand))
        {
          send_text("Pin " + comand + " is already in use", "{}", true);
        }
        else if (comand.length() > 7)
        {
          send_text("Pin only can have 7 digits", "{}", true);
        }
        else if (has_letters(comand))
        {
          send_text("Pin cant have Letters", "{}", true);
        }
        else
        {
          configC_teligram.SetBufferUserPin(comand);
          // remove_mass(configC_teligram.GetLastUpdateId().toInt());
          configC_teligram.SetBufferUserIndex(2);
          goto add_userstart;
        }
      }
    }
    if (key == "permissions")
    {
      if (key_send == "pin")
      {
        JsonDocument doc;
        doc["inline_keyboard"][0][0]["text"] = "NORMEL";
        doc["inline_keyboard"][0][0]["callback_data"] = "permiten_2";
        doc["inline_keyboard"][0][1]["text"] = "CONFIG";
        doc["inline_keyboard"][0][1]["callback_data"] = "permiten_1";
        doc["inline_keyboard"][0][2]["text"] = "BOTH";
        doc["inline_keyboard"][0][2]["callback_data"] = "permiten_3";
        String data;
        serializeJson(doc, data);
        send_text("permissions", data, true);
        configC_teligram.SetBufferUserSendIndex(2);
      }
      if (key_send == "permissions" && comand != "null")
      {
        if (comand == "permiten_1")
        {
          configC_teligram.SetBufferUserPermissionsNormal(false);
          configC_teligram.SetBufferUserPermissionsConfig(true);
        }
        else if (comand == "permiten_2")
        {
          configC_teligram.SetBufferUserPermissionsNormal(true);
          configC_teligram.SetBufferUserPermissionsConfig(false);
        }
        else if (comand == "permiten_3")
        {
          configC_teligram.SetBufferUserPermissionsNormal(true);
          configC_teligram.SetBufferUserPermissionsConfig(true);
        }
        configC_teligram.SetBufferUserIndex(3);
        goto add_userstart;
      }
      if (key_send == "permissions" && comand != "null")
      {
        configC_teligram.SetTeligramComandIndex(-1);
      }
    }
  }
  else if (comand_key == comand_key_locke_unlock)
  {
    configC_teligram.SetTeligramComandIndex(-1);

    if (comand == "lock")
    {
      send_text("lock", "{}", true);
    }
    if (comand == "unlock")
    {
      send_text("lock", "{}", true);
    }
  }
  else if (comand_key == comand_key_schedule)
  {
  schedule_start:
    /*{
       "s_name",
        "permission",
        "start_time_date",
        "end_time_date",
        "start_time_hour",
        "end_time_hour",
        "time_days",
        "finish"
  };*/
    String key = configC_teligram.GetBufferScheduleMapKey(configC_teligram.GetBufferScheduleIndex());
    String key_send = configC_teligram.GetBufferScheduleMapKey(configC_teligram.GetBufferScheduleSendIndex());
    if (key == "s_name")
    {

      //-1
      if (key_send != "s_name")
      {
        send_text("Name:", "{}", true);
        configC_teligram.SetBufferScheduleSendIndex(0);
      }
      // check if name exist
      // else if (configC_teligram.ExistBufferScheduleTime_day(comand))
      //  {
      //    send_text(comand+" name already exists", "{}", true);
      //  }
      else
      {
        configC_teligram.SetBufferScheduleName(comand);
        configC_teligram.SetBufferScheduleIndex(1);
        goto schedule_start;
      }
    }
    if (key == "permission")
    {
      if (key_send != "permission")
      {
        JsonDocument doc;
        doc["inline_keyboard"][0][0]["text"] = "ENTRY";
        doc["inline_keyboard"][0][0]["callback_data"] = "entry";
        doc["inline_keyboard"][0][1]["text"] = "NO ENTRY";
        doc["inline_keyboard"][0][1]["callback_data"] = "no_entry";

        String data;
        serializeJson(doc, data);
        send_text("Permissions", data, true);
        configC_teligram.SetBufferScheduleSendIndex(1);
      }
      else
      {
        configC_teligram.SetBufferScheduleTime_type(comand);
        configC_teligram.SetBufferScheduleIndex(2);
        goto schedule_start;
      }
    }
    if (key == "start_time_date")
    {
      if (key_send != "start_time_date")
      {
        send_text("Start Time(dd/MM/YYYY)", "{}", true);
        configC_teligram.SetBufferScheduleSendIndex(2);
      }
      else if (comand != "null" && comand.length() != 10)
      {
        send_text("Incorrect Time Formet(" + comand + "):", "{}", true);
      }
      else
      {

        String data = comand;
        // date month year hour min

        String date;
        String month;
        String year;
        String temp_var = "";
        int temp_index = 0;
        for (int i = 0; i < 10; i++)
        {
          temp_var.concat(data[i]);

          if (data[i] == '/' || i == 9)
          {
            temp_var.replace("/", "");
            temp_var.replace("-", "");
            temp_var.replace(":", "");

            if (temp_index == 0)
            {
              date = temp_var;
            }
            if (temp_index == 1)
            {
              month = temp_var;
            }
            if (temp_index == 2)
            {
              year = temp_var;
            }

            temp_var = "";
            temp_index++;
          }
        }

        configC_teligram.SetBufferScheduleTime_starTime_date(date.toInt(), month.toInt(), year.toInt());

        configC_teligram.SetBufferScheduleIndex(3);
        goto schedule_start;
      }
    }
    if (key == "end_time_date")
    {
      if (key_send != "end_time_date")
      {
        send_text("End Time(dd/MM/YYYY)", "{}", true);
        configC_teligram.SetBufferScheduleSendIndex(3);
      }
      else if (comand != "null" && comand.length() != 10)
      {
        send_text("Incorrect Time Formet(" + comand + "):", "{}", true);
      }
      else
      {

        String data = comand;
        // date month year hour min

        String date1;
        String month1;
        String year1;

        String temp_var = "";
        int temp_index = 0;
        for (int i = 0; i < 10; i++)
        {
          temp_var.concat(data[i]);

          if (data[i] == '/' || i == 9)
          {
            temp_var.replace("/", "");

            if (temp_index == 0)
            {
              date1 = temp_var;
            }
            if (temp_index == 1)
            {
              month1 = temp_var;
            }
            if (temp_index == 2)
            {
              year1 = temp_var;
            }

            temp_var = "";
            temp_index++;
          }
        }
        JsonDocument doc_starTime;
        deserializeJson(doc_starTime, configC_teligram.GetBufferScheduleTime_starTime_date());
        int starTime_date_date0 = doc_starTime["date"];
        int starTime_date_month0 = doc_starTime["month"];
        int starTime_date_year0 = doc_starTime["year"];
        Serial.println(starTime_date_date0);
        Serial.println(starTime_date_month0);
        Serial.println(starTime_date_year0);
         Serial.println(date1);
        Serial.println(month1);
        Serial.println(year1);
        Serial.println(isvalededate(starTime_date_date0, starTime_date_month0, starTime_date_year0, date1.toInt(), month1.toInt(), year1.toInt()));
        if (isvalededate(starTime_date_date0, starTime_date_month0, starTime_date_year0, date1.toInt(), month1.toInt(), year1.toInt())==false)
        {
          send_text("Invalid Time(" + comand + "):", "{}", true);
        }
        else
        {
          send_text("valid Time(" + comand + "):", "{}", true);

          configC_teligram.SetBufferScheduleTime_endTime_date(date1.toInt(), month1.toInt(), year1.toInt());
          configC_teligram.SetBufferScheduleIndex(4);
          goto schedule_start;
        }
      }
    }
    if (key == "start_time_hour")
    {
      if (key_send != "start_time_hour")
      {
        send_text("Start Time(HH:MM)", "{}", true);
        configC_teligram.SetBufferScheduleSendIndex(4);
      }
      else if (comand != "null" && comand.length() != 5)
      {
        send_text("Incorrect Time Formet(" + comand + "):", "{}", true);
      }
      else
      {

        String data = comand;
        // date month year hour min

        String hour;
        String min;
        String temp_var = "";
        int temp_index = 0;
        for (int i = 0; i < 5; i++)
        {
          temp_var.concat(data[i]);

          if (data[i] == ':' || i == 4)
          {

            temp_var.replace(":", "");

            if (temp_index == 0)
            {
              hour = temp_var;
            }
            if (temp_index == 1)
            {
              min = temp_var;
            }

            temp_var = "";
            temp_index++;
          }
        }

        if (hour.toInt() > 24 || min.toInt() > 59)
        {
          send_text("Incorrect Time value(" + comand + "):", "{}", true);
        }
        else
        {

          configC_teligram.SetBufferScheduleTime_starTime_hour(hour.toInt(), min.toInt());

          configC_teligram.SetBufferScheduleIndex(5);
          goto schedule_start;
        }
      }
    }
    if (key == "end_time_hour")
    {
      if (key_send != "end_time_hour")
      {
        send_text("End Time(HH:MM)", "{}", true);
        configC_teligram.SetBufferScheduleSendIndex(5);
      }
      else if (comand != "null" && comand.length() != 5)
      {
        send_text("Incorrect Time Formet(" + comand + "):", "{}", true);
      }
      else
      {
        String data = comand;
        String hour1;
        String min1;
        String temp_var = "";
        int temp_index = 0;
        for (int i = 0; i < 5; i++)
        {
          temp_var.concat(data[i]);

          if (data[i] == ':' || i == 4)
          {

            temp_var.replace(":", "");

            if (temp_index == 0)
            {
              hour1 = temp_var;
            }
            if (temp_index == 1)
            {
              min1 = temp_var;
            }

            temp_var = "";
            temp_index++;
          }
        }
        JsonDocument doc_starTime;
        deserializeJson(doc_starTime, configC_teligram.GetBufferScheduleTime_starTime_hour());
        int hour0 = doc_starTime["hour"];
        int min0 = doc_starTime["min"];
        if (!isvaledehour(hour0, min0, hour1.toInt(), min1.toInt()))
        {
          send_text("Invalid Time(" + comand + "):", "{}", true);
        }
        else if (hour1.toInt() > 24 || hour1.toInt() > 59)
        {
          send_text("Invalid Time(" + comand + "):", "{}", true);
        }
        else
        {

          send_text("correct Time(" + comand + "):", "{}", true);

          configC_teligram.SetBufferScheduleTime_endTime_hour(hour1.toInt(), min1.toInt());

          configC_teligram.SetBufferScheduleIndex(6);
          goto schedule_start;
        }
      }
    }
    if (key == "time_days")
    {
      if (key_send != "time_days")
      {

        send_text("Days:", days_render(), true);

        configC_teligram.SetBufferScheduleSendIndex(6);
      }
      else if (comand == "s_days")
      {
        configC_teligram.SetBufferScheduleIndex(7);
        goto schedule_start;
      }
      else if (comand == "r_days")
      {
        configC_teligram.ResetBufferScheduleTime_day();
        send_text("Days:", days_render(), true);
      }
      else
      {
        configC_teligram.SetBufferScheduleTime_day(comand);

        send_text("Days:", days_render(), true);
      }
    }
    if (key == "finish")
    {
      if (key_send != "finish")
      {

        JsonDocument doc;
        doc["inline_keyboard"][0][0]["text"] = "ADD MORE TIME";
        doc["inline_keyboard"][0][0]["callback_data"] = "s_add_more_time";
        doc["inline_keyboard"][1][0]["text"] = "CANCEL";
        doc["inline_keyboard"][1][0]["callback_data"] = "s_cancel";

        doc["inline_keyboard"][1][1]["text"] = "SAVE";
        doc["inline_keyboard"][1][1]["callback_data"] = "s_save";
        String data;

        serializeJson(doc, data);
        send_text("Do You want to save it:", data, true);
        configC_teligram.SetBufferScheduleSendIndex(7);
      }
      else if (comand == "s_cancel")
      {
      }
      else if (comand == "s_add_more_time")
      {
        configC_teligram.SetBufferScheduleIndex(1);
        configC_teligram.SetBufferScheduleSendIndex(0);
        configC_teligram.SetBufferScheduleTimesIndex(configC_teligram.GetBufferScheduleIndex() + 1);

        goto schedule_start;
      }
      else if (comand == "s_save")
      {
        configC_teligram.SetBufferScheduleIndex(0);
        configC_teligram.SetBufferScheduleSendIndex(-1);
        configC_teligram.SetTeligramComandIndex(-1);
        String object = configC_teligram.GetBufferSchedule();
        sd_edit_teligram.make_schedule(object);
        send_text("Use /start to configer:", "{}", true);
      }
    }
    //  configC_teligram.SetTeligramComandIndex(-1);
  }
  else if (comand_key == comand_key_shutedown)
  {
    configC_teligram.SetTeligramComandIndex(-1);
  }
}
