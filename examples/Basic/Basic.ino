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

//Example shows how to connect to Firebase RTDB and perform basic operation for set, get, push and update data to database

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define DATABASE_URL "URL" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "FIREBASE_DATABASE_SECRET"
#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

//Define Firebase data object
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

  String path = "/test";
  String jsonStr;

  Serial.print("Set int... ");

  unsigned long long val = 1634631042000;

  if (Firebase.setInt(fbdo, path + "/int/data", val)) //support large number
  {
    Serial.println("ok");
    Serial.println("path: " + fbdo.dataPath());
    Serial.println("type: " + fbdo.dataType());
    Serial.print("value: ");
    if (fbdo.dataType() == "int")
      Serial.println(fbdo.intData());
    if (fbdo.dataType() == "int64")
      Serial.println(fbdo.int64Data());
    if (fbdo.dataType() == "uint64")
      Serial.println(fbdo.uint64Data());
    else if (fbdo.dataType() == "double")
      Serial.println(fbdo.doubleData());
    else if (fbdo.dataType() == "float")
      Serial.println(fbdo.floatData());
    else if (fbdo.dataType() == "boolean")
      Serial.println(fbdo.boolData() == 1 ? "true" : "false");
    else if (fbdo.dataType() == "string")
      Serial.println(fbdo.stringData());
    else if (fbdo.dataType() == "json")
      Serial.println(fbdo.jsonData());
    else if (fbdo.dataType() == "array")
      Serial.println(fbdo.arrayData());
  }
  else
  {
    Serial.println("error, " + fbdo.errorReason());
  }

  Serial.println();

  Serial.print("Get int... ");

  if (Firebase.getInt(fbdo, path + "/int/data")) // also can use Firebase.get(fbdo, path)
  {
    Serial.println("ok");
    Serial.println("path: " + fbdo.dataPath());
    Serial.println("type: " + fbdo.dataType());
    Serial.print("value: ");
    if (fbdo.dataType() == "int")
      Serial.println(fbdo.intData());
    if (fbdo.dataType() == "int64")
      Serial.println(fbdo.int64Data());
    if (fbdo.dataType() == "uint64")
      Serial.println(fbdo.uint64Data());
    else if (fbdo.dataType() == "double")
      Serial.println(fbdo.doubleData());
    else if (fbdo.dataType() == "float")
      Serial.println(fbdo.floatData());
    else if (fbdo.dataType() == "boolean")
      Serial.println(fbdo.boolData() == 1 ? "true" : "false");
    else if (fbdo.dataType() == "string")
      Serial.println(fbdo.stringData());
    else if (fbdo.dataType() == "json")
      Serial.println(fbdo.jsonData());
    else if (fbdo.dataType() == "array")
      Serial.println(fbdo.arrayData());
  }
  else
  {
    Serial.println("error, " + fbdo.errorReason());
  }

  Serial.println();

  Serial.print("Push double... ");

  if (Firebase.pushDouble(fbdo, path + "/push/double", 1234.56789))
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

  Serial.print("Push json... ");

  jsonStr = "{\"title\":{\"index\":0,\"text\":{\"us\":\"abc\"},\"ts\":{\".sv\":\"timestamp\"}}}";

  if (Firebase.pushJSON(fbdo, path + "/push/json", jsonStr))
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

  Serial.print("Update node... ");

  jsonStr = "{\"jp\":\"def\",\"sg\":\"ghi\"}";

  if (Firebase.updateNode(fbdo, path + "/push/json/" + fbdo.pushName() + "/title/text", jsonStr))
  {
    Serial.println("ok");
    Serial.println("path: " + fbdo.dataPath());
    Serial.println("type: " + fbdo.dataType());
    Serial.print("value: ");
    if (fbdo.dataType() == "int")
      Serial.println(fbdo.intData());
    if (fbdo.dataType() == "int64")
      Serial.println(fbdo.int64Data());
    if (fbdo.dataType() == "uint64")
      Serial.println(fbdo.uint64Data());
    else if (fbdo.dataType() == "double")
      Serial.println(fbdo.doubleData());
    else if (fbdo.dataType() == "float")
      Serial.println(fbdo.floatData());
    else if (fbdo.dataType() == "boolean")
      Serial.println(fbdo.boolData() == 1 ? "true" : "false");
    else if (fbdo.dataType() == "string")
      Serial.println(fbdo.stringData());
    else if (fbdo.dataType() == "json")
      Serial.println(fbdo.jsonData());
    else if (fbdo.dataType() == "array")
      Serial.println(fbdo.arrayData());
    
  }
  else
  {
    Serial.println("error, " + fbdo.errorReason());
  }
  Serial.println();

  // clear internal memory used
  fbdo.clear();
}

void loop()
{
}
