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

//Example shows how to connect to Firebase RTDB and get stream connection

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define DATABASE_URL "URL" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "FIREBASE_DATABASE_SECRET"

#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

//Define Firebase data object
FirebaseData fbdo;

FirebaseData stream;

unsigned long sendDataPrevMillis = 0;

String path = "/test/stream";

int count = 0;

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

  if (!Firebase.beginStream(stream, path))
  {
    Serial.println("Can't connect stream, " + stream.errorReason());
    Serial.println();
  }
}

void loop()
{

  if (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)
  {
    sendDataPrevMillis = millis();
    count++;

    Serial.print("Set string... ");

    if (Firebase.setString(fbdo, path + "/string", "Hello World! " + String(count)))
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
      Serial.println("error, "+ fbdo.errorReason());
    }

    // clear internal memory used
    fbdo.clear();

    Serial.println();
  }

  if (!Firebase.readStream(stream))
  {
    Serial.println("Can't read stream, "+ stream.errorReason());
  }

  if (stream.streamTimeout())
  {
    Serial.println("Stream timed out, resuming...");
  }

  if (stream.streamAvailable())
  {
    count++;
    if (stream.dataType() == "null")
      count = 0;

    Serial.println("Stream data received... ");
    Serial.println("stream path: " + stream.streamPath());
    Serial.println("event path: " + stream.dataPath());
    Serial.println("data type: " + stream.dataType());
    Serial.println("event type: " + stream.eventType());
    Serial.print("value: ");
    if (stream.dataType() == "int")
      Serial.println(stream.intData());
    if (stream.dataType() == "int64")
      Serial.println(stream.int64Data());
    if (stream.dataType() == "uint64")
      Serial.println(stream.uint64Data());
    else if (stream.dataType() == "double")
      Serial.println(stream.doubleData());
    else if (stream.dataType() == "float")
      Serial.println(stream.floatData());
    else if (stream.dataType() == "boolean")
      Serial.println(stream.boolData() == 1 ? "true" : "false");
    else if (stream.dataType() == "string")
      Serial.println(stream.stringData());
    else if (stream.dataType() == "json")
      Serial.println(stream.jsonData());
    else if (stream.dataType() == "array")
      Serial.println(stream.arrayData());
    Serial.println();

    // clear internal memory used
    stream.clear();
  }
}