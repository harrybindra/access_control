
#include "FS.h"
#include "SPIFFS.h"
#include "./ArduinoJson.h"
//  String LSreadFile( String *path) {}
// void LSlistDir( String *dirname) {}
// void LSwriteFile( String *path,  String *message) {}


class json_edit_config
{
private:
    /* data */
public:
      String GetTelToken(  );
    void SetTelToken( String data);
   String GetChatId(  );
    void SetChatId( String data);

    String GetLastUpdateId(  );
    void SetLastUpdateId( String data);

    bool GetIsNegtiveTimeOffset(  );
    void SetIsNegtiveTimeOffset(bool data);

    int GetTimeOffset(  );
    void SetTimeOffset(int data);

    bool GetSetup(  );
    void SetSetup(bool data);

    int GetPinTrys(  );
    void SetPinTrys(int data);

    int GetFingTrys(  );
    void SetFingTrys(int data);

    bool GetOverTrys(  );
    void SetOverTrys(bool data);

    bool GetErrorCom(  );
    void SetErrorCom(bool data);

    String GetSsid(  );
    void SetSsid( String data);

     String GetPass(  );
    void SetPass( String data);
};


   