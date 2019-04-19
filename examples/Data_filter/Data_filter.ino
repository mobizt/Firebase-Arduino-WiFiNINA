/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 *
*/

//Example shows how to connect to Firebase RTDB and construct queries to filter data

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define FIREBASE_HOST "YOUR_FIREBASE_PROJECT.firebaseio.com"
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET"
#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

//Define Firebase Data object
FirebaseData firebaseData;

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
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Provide the autntication data
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  String jsonStr = "";

  Serial.println("------------------------------------");
  Serial.println("Push JSON test...");

  for (uint8_t i = 0; i < 30; i++)
  {

    jsonStr = "{\"Data1\":" + String(i + 1) + ",\"Data2\":\"" + String(i + 100) + "\"}";

    if (Firebase.pushJSON(firebaseData, "/Test/Int", jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  QueryFilter query;

  //Clear query parameters
  query.clearQuery();


  query.orderBy("Data2");
  //query.orderBy("Data1");
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

    "Test":{
      "Int":{
        ".indexOn":"Data2"
        //".indexOn":"Data1"
      }
    }
    }

  */

  Serial.println("------------------------------------");
  Serial.println("Data Filtering test...");

  if (Firebase.getJSON(firebaseData, "/Test/Int", query))
  {

    Serial.println("PASSED");
    Serial.println("JSON DATA: ");
    Serial.println(firebaseData.jsonData());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  //Release memory used by query object
  query.end();
}

void loop()
{
}
