#include "fingerprint_leb.h"  
#include <Adafruit_Fingerprint.h>


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

void fingerprint_leb::start_fing_sen()
{
  // finger print
  Serial2.begin(57600, SERIAL_8N1, 26, 27);

  finger.begin(57600);
 
}
// 420 to emptyDatabase
void fingerprint_leb::del_finger(int fing_id)
{
  if (fing_id == 420)
  {
    finger.emptyDatabase();
  }
  else
  {
    finger.deleteModel(fing_id);
  }
}
String fingerprint_leb::reg_storefinger(int id)
{
  // if you want to enroll fingerprint you have to get 2 images like this:
  // 1:-
  // finger.getImage();take the IMG with this function after this use following function
  // to convert the img :
  // finger.image2Tz(1);
  // 2:-and for now second img :
  // finger.getImage();
  // finger.image2Tz(2);
  // And after all of this use finger.createModel(); and finger.storeModel(1); to store
  // finger print in 1 slot
  int p = -1;
  int fing;
  if (id == 0)
  {
    return "you cant use this reg";
  }
  else if (id >= 127)
  {
    return "you only can save 127 fingerprints";
  }
  else
  {
    if (check_finger(id) == String(FINGERPRINT_NOTFOUND))
    {

      Serial.print("Waiting for valid finger to enroll as #");
      Serial.println(id);
      while (p != FINGERPRINT_OK)
      {
        p = finger.getImage();
        switch (p)
        {
        case FINGERPRINT_OK:
          Serial.println("Image taken");
          break;
        case FINGERPRINT_NOFINGER:
          Serial.println(".");
          break;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println("Communication error");
          break;
        case FINGERPRINT_IMAGEFAIL:
          Serial.println("Imaging error");
          break;
        default:
          Serial.println("Unknown error");
          break;
        }
      }

      // OK success!

      p = finger.image2Tz(1);
      switch (p)
      {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return String(p);
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return String(p);
      case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return String(p);
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return String(p);
      default:
        Serial.println("Unknown error");
        return String(p);
      }

      Serial.println("Remove finger");
      // delay(2000);
      // p = 0;
      // while (p != FINGERPRINT_NOFINGER) {
      //   p = finger.getImage();
      //}
      Serial.print("ID ");
      Serial.println(id);
      p = -1;
      Serial.println("Place same finger again");
      while (p != FINGERPRINT_OK)
      {
        p = finger.getImage();
        switch (p)
        {
        case FINGERPRINT_OK:
          Serial.println("Image taken");
          break;
        case FINGERPRINT_NOFINGER:
          Serial.print(".");
          break;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println("Communication error");
          break;
        case FINGERPRINT_IMAGEFAIL:
          Serial.println("Imaging error");
          break;
        default:
          Serial.println("Unknown error");
          break;
        }
      }

      // OK success!

      p = finger.image2Tz(2);
      switch (p)
      {
      case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;
      case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return String(p);
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return String(p);
      case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return String(p);
      case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return String(p);
      default:
        Serial.println("Unknown error");
        return String(p);
      }

      // OK converted!
      Serial.print("Creating model for #");
      Serial.println(id);

      p = finger.createModel();
      if (p == FINGERPRINT_OK)
      {
        Serial.println("Prints matched!");
      }
      else if (p == FINGERPRINT_PACKETRECIEVEERR)
      {
        Serial.println("Communication error");
        return String(p);
      }
      else if (p == FINGERPRINT_ENROLLMISMATCH)
      {
        Serial.println("Fingerprints did not match");
        return String(p);
      }
      else
      {
        Serial.println("Unknown error");
        return String(p);
      }

      Serial.print("ID ");
      Serial.println(id);
      p = finger.storeModel(id);
      if (p == FINGERPRINT_OK)
      {
        Serial.println("Stored!");
      }
      else if (p == FINGERPRINT_PACKETRECIEVEERR)
      {
        Serial.println("Communication error");
        return String(p);
      }
      else if (p == FINGERPRINT_BADLOCATION)
      {
        Serial.println("Could not store in that location");
        return String(p);
      }
      else if (p == FINGERPRINT_FLASHERR)
      {
        Serial.println("Error writing to flash");
        return String(p);
      }
      else
      {
        Serial.println("Unknown error");
        return String(p);
      }
      return "true";
    }
    else
    {
      return "Finger exist";
    }
  }
}
String fingerprint_leb::check_finger(){
  uint8_t p = finger.getImage();
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image taken");
    break;
  case FINGERPRINT_NOFINGER:
    Serial.println("No finger detected");
    return String(p);
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    return String(p);
  case FINGERPRINT_IMAGEFAIL:
    Serial.println("Imaging error");
    return String(p);
  default:
    Serial.println("Unknown error");
    return String(p);
  }

  // OK success!

  p = finger.image2Tz();
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image converted");
    break;
  case FINGERPRINT_IMAGEMESS:
    Serial.println("Image too messy");
    return String(p);
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    return String(p);
  case FINGERPRINT_FEATUREFAIL:
    Serial.println("Could not find fingerprint features");
    return String(p);
  case FINGERPRINT_INVALIDIMAGE:
    Serial.println("Could not find fingerprint features");
    return String(p);
  default:
    Serial.println("Unknown error");
    return String(p);
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println("Communication error");
    return String(p);
  }
  else if (p == FINGERPRINT_NOTFOUND)
  {
    Serial.println("Did not find a match");
    return String(p);
  }
  else
  {
    Serial.println("Unknown error");
    return String(p);
  }

  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);  
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);
  return String(finger.fingerID);


};

String fingerprint_leb::check_finger(int fing_id)
{
  uint8_t p = finger.getImage();
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image taken");
    break;
  case FINGERPRINT_NOFINGER:
    Serial.println("No finger detected");
    return String(p);
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    return String(p);
  case FINGERPRINT_IMAGEFAIL:
    Serial.println("Imaging error");
    return String(p);
  default:
    Serial.println("Unknown error");
    return String(p);
  }

  // OK success!

  p = finger.image2Tz();
  switch (p)
  {
  case FINGERPRINT_OK:
    Serial.println("Image converted");
    break;
  case FINGERPRINT_IMAGEMESS:
    Serial.println("Image too messy");
    return String(p);
  case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println("Communication error");
    return String(p);
  case FINGERPRINT_FEATUREFAIL:
    Serial.println("Could not find fingerprint features");
    return String(p);
  case FINGERPRINT_INVALIDIMAGE:
    Serial.println("Could not find fingerprint features");
    return String(p);
  default:
    Serial.println("Unknown error");
    return String(p);
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println("Communication error");
    return String(p);
  }
  else if (p == FINGERPRINT_NOTFOUND)
  {
    Serial.println("Did not find a match");
    return String(p);
  }
  else
  {
    Serial.println("Unknown error");
    return String(p);
  }

  // found a match!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);

  if (finger.fingerID == fing_id)
  {

    return "true";
  }
  else
  {
    return "false";
  }
}

bool fingerprint_leb::available_finger ()
{
   return finger.getImage()==FINGERPRINT_NOFINGER?false:true;
 
 }
