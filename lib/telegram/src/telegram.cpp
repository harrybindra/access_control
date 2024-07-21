#include "telegram.h"

void telegram::send_text( String text )
{
  
  String chatid = configC.GetChatId();
  String token = configC.GetTelToken();
  String paquet = "{\"chat_id\":\"" + chatid + "\",\"text\":\"" + text + "\"}";
  http.begin("https://api.telegram.org/bot" + token + "/sendMessage");
  Serial.println(http.connected());
  http.addHeader("Host", "api.telegram.org");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Content-Length", "42");

  Serial.println(http.POST(paquet));
  http.end();
}
// no new text
// text and id
String telegram::get_last_mass(String token)
{
  http.begin("https://api.telegram.org/bot" + token + "/getUpdates");
  http.addHeader("Host", "telegram.org");
  if (http.GET() == HTTP_CODE_OK)
  {
    String mass_arry = http.getString();
    // Serial.println(mass_arry);

    JsonDocument doc;
    deserializeJson(doc, mass_arry);
    if (doc["result"].isNull() == 1)
    {
      return "no new text";
    }

    int i = 0;
    bool get_laast_ind = true;
    while (get_laast_ind)
    {
      String loopf = doc["result"][i];
      int h = doc["result"][i].isNull();
      // Serial.println(loopf);
      if (h == 1)
      {
        get_laast_ind = false;
      }
      else
      {

        i++;
      }
    }

    Serial.println(i);
    String id = doc["result"][i - 1]["update_id"];
    String text = doc["result"][i - 1]["message"]["text"];
    String chat_id = doc["result"][i - 1]["message"]["from"]["id"];
    String resulet;

    if (id == get_config("lastupdateid"))
    {
      return "no new text";
    }
    else
    {
      if (get_config("lastupdateid") == "")
      {

        set_config("lastupdateid", id);
      }
      if (get_config("chatid") == "")
      {
        set_config("chatid", chat_id);
      }

      else
      {
        JsonObject object = doc.to<JsonObject>();
        object["text"] = text;
        object["id"] = id;
        set_config("lastupdateid", id);

        serializeJson(doc, resulet);
        Serial.println(resulet);
        return resulet;
      }
    }
  }
}
