/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2022 mobizt
 *
*/

//Example shows how to connect to Firebase RTDB and construct queries to filter data

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define DATABASE_URL "URL" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "FIREBASE_DATABASE_SECRET"

#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

//Define Firebase Data object
FirebaseData fbdo;

void setup()
{

  Serial.begin(115200);
  delay(100);
  Serial.println();

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Provide the autntication data
  Firebase.begin(DATABASE_URL, DATABASE_SECRET, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  String jsonStr = "";

  for (uint8_t i = 0; i < 30; i++)
  {
    Serial.print("Push json... ");

    jsonStr = "{\"data1\":" + String(i + 1) + ",\"data2\":\"" + String(i + 100) + "\"}";

    if (Firebase.pushJSON(fbdo, "/test/int", jsonStr))
    {
      Serial.println("ok");
      Serial.println("path: " + fbdo.dataPath());
      Serial.print("push name: ");
      Serial.println(fbdo.pushName());
    }
    else
    {
      Serial.println("error, " + fbdo.errorReason());
    }

    Serial.println();
  }

  QueryFilter query;

  //Clear query parameters
  query.clearQuery();


  query.orderBy("data2");
  //query.orderBy("data1");
  query.startAt("110");
  //query.startAt(5);
  query.endAt("115");
  //query.endAt(20);
  query.limitToLast(3);

  /*

    Begin data filtering test

    Add the following rules in Firebase Database Rules Dashboard

    "rules": {
    ...
    ...
    ,

    "test":{
      "int":{
        ".indexOn":"data2"
        //".indexOn":"data1"
      }
    }

  */

  Serial.print("Data filtering... ");

  if (Firebase.getJSON(fbdo, "/test/int", query))
  {

    Serial.println("ok");
    Serial.println(fbdo.jsonData());
  }
  else
  {
    Serial.println("error, " + fbdo.errorReason());
  }

  Serial.println();

  //Release memory used by query object
  query.end();

  // clear internal memory used
  fbdo.clear();
}

void loop()
{
}
