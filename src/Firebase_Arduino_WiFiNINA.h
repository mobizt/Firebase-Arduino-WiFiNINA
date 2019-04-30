/*
* Google's Firebase Realtime Database Arduino Library for ARM/AVR WIFI Development Boards based on WiFiNINA library, version 1.0.3
* 
*
* This library required WiFiNINA Library to be installed.
* https://github.com/arduino-libraries/WiFiNINA
* 
* April 30, 2019
* 
* Feature Added:
* - Add keywords
* 
* Feature Fixed:
* 
*
* This library provides ARM/AVR WIFI Development Boards to perform REST API by GET PUT, POST, PATCH, DELETE data from/to with Google's Firebase database using get, set, update
* and delete calls.
* 
 * The library was test and work well with ESP32s based module and add support for multiple stream event path.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person returning a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef Firebase_Arduino_WiFiNINA_H
#define Firebase_Arduino_WiFiNINA_H

#include <Arduino.h>

#include "Firebase_Arduino_WiFiNINA_HTTPClient.h"

#include <avr/pgmspace.h>
#if defined(__arm__) 
#include <avr/dtostrf.h>
#elif defined(__AVR__)
#else
#error Architecture or board not supported.
#endif


#define FIEBASE_PORT 443
#define FIREBASE_RESPONSE_SIZE 400
#define KEEP_ALIVE_TIMEOUT 30000

#define HTTPC_ERROR_CONNECTION_INUSED -16

#define DEF_STR_19 "null"
#define DEF_STR_4 "."
#define DEF_STR_106 "false"
#define DEF_STR_107 "true"

const char C_STR_0[] PROGMEM = "";
const char C_STR_1[] PROGMEM = "/";
const char C_STR_2[] PROGMEM = ".json?auth=";
const char C_STR_3[] PROGMEM = "\"";
const char C_STR_4[] PROGMEM = ".";
const char C_STR_5[] PROGMEM = "HTTP/1.1 ";
const char C_STR_6[] PROGMEM = " ";
const char C_STR_7[] PROGMEM = ":";
const char C_STR_8[] PROGMEM = "Content-Type: ";
const char C_STR_9[] PROGMEM = "text/event-stream";
const char C_STR_10[] PROGMEM = "Connection: ";
const char C_STR_11[] PROGMEM = "keep-alive";
const char C_STR_12[] PROGMEM = "Content-Length: ";
const char C_STR_13[] PROGMEM = "event: ";
const char C_STR_14[] PROGMEM = "data: ";
const char C_STR_15[] PROGMEM = "put";
const char C_STR_16[] PROGMEM = "patch";
const char C_STR_17[] PROGMEM = "\"path\":\"";
const char C_STR_18[] PROGMEM = "\"data\":";
const char C_STR_19[] PROGMEM = "null";
const char C_STR_20[] PROGMEM = "{\"name\":\"";
const char C_STR_21[] PROGMEM = "\r\n";
const char C_STR_22[] PROGMEM = "GET ";
const char C_STR_23[] PROGMEM = "PUT";
const char C_STR_24[] PROGMEM = "POST";
const char C_STR_25[] PROGMEM = "GET";
const char C_STR_26[] PROGMEM = "PATCH";
const char C_STR_27[] PROGMEM = "DELETE";
const char C_STR_28[] PROGMEM = "&download=";
const char C_STR_29[] PROGMEM = "&print=silent";
const char C_STR_30[] PROGMEM = " HTTP/1.1\r\n";
const char C_STR_31[] PROGMEM = "Host: ";
const char C_STR_32[] PROGMEM = "User-Agent: UNO WiFi\r\n";
const char C_STR_33[] PROGMEM = "X-Firebase-Decoding: 1\r\n";
const char C_STR_34[] PROGMEM = "Connection: close\r\n";
const char C_STR_35[] PROGMEM = "Accept: text/event-stream\r\n";
const char C_STR_36[] PROGMEM = "Connection: keep-alive\r\n";
const char C_STR_37[] PROGMEM = "Keep-Alive: timeout=30, max=100\r\n";
const char C_STR_38[] PROGMEM = "Accept-Encoding: identity;q=1,chunked;q=0.1,*;q=0\r\n";
const char C_STR_39[] PROGMEM = "connection refused";
const char C_STR_40[] PROGMEM = "send header failed";
const char C_STR_41[] PROGMEM = "send payload failed";
const char C_STR_42[] PROGMEM = "not connected";
const char C_STR_43[] PROGMEM = "connection lost";
const char C_STR_44[] PROGMEM = "no HTTP server";
const char C_STR_45[] PROGMEM = "bad request";
const char C_STR_46[] PROGMEM = "non-authoriative information";
const char C_STR_47[] PROGMEM = "no content";
const char C_STR_48[] PROGMEM = "moved permanently";
const char C_STR_49[] PROGMEM = "use proxy";
const char C_STR_50[] PROGMEM = "temporary redirect";
const char C_STR_51[] PROGMEM = "permanent redirect";
const char C_STR_52[] PROGMEM = "unauthorized";
const char C_STR_53[] PROGMEM = "forbidden";
const char C_STR_54[] PROGMEM = "not found";
const char C_STR_55[] PROGMEM = "method not allow";
const char C_STR_56[] PROGMEM = "not acceptable";
const char C_STR_57[] PROGMEM = "proxy authentication required";
const char C_STR_58[] PROGMEM = "request timeout";
const char C_STR_59[] PROGMEM = "length required";
const char C_STR_60[] PROGMEM = "too many requests";
const char C_STR_61[] PROGMEM = "request header fields too larg";
const char C_STR_62[] PROGMEM = "internal server error";
const char C_STR_63[] PROGMEM = "bad gateway";
const char C_STR_64[] PROGMEM = "service unavailable";
const char C_STR_65[] PROGMEM = "gateway timeout";
const char C_STR_66[] PROGMEM = "http version not support";
const char C_STR_67[] PROGMEM = "network authentication required";
const char C_STR_68[] PROGMEM = "data buffer overflow";
const char C_STR_69[] PROGMEM = "read Timeout";
const char C_STR_70[] PROGMEM = "data type mismatch";
const char C_STR_71[] PROGMEM = "path not exist";
const char C_STR_72[] PROGMEM = "task";
const char C_STR_73[] PROGMEM = "/esp.32";
const char C_STR_74[] PROGMEM = "json";
const char C_STR_75[] PROGMEM = "string";
const char C_STR_76[] PROGMEM = "float";
const char C_STR_77[] PROGMEM = "int";
const char C_STR_78[] PROGMEM = "null";
const char C_STR_79[] PROGMEM = ";";
const char C_STR_80[] PROGMEM = "Content-Disposition: ";
const char C_STR_81[] PROGMEM = "application/octet-stream";
const char C_STR_82[] PROGMEM = "attachment";
const char C_STR_83[] PROGMEM = "";
const char C_STR_84[] PROGMEM = "";
const char C_STR_85[] PROGMEM = "";
const char C_STR_86[] PROGMEM = "e";
const char C_STR_87[] PROGMEM = "";
const char C_STR_88[] PROGMEM = "Node path is not exist";
const char C_STR_89[] PROGMEM = ".json";
const char C_STR_90[] PROGMEM = "/root.json";
const char C_STR_91[] PROGMEM = "";
const char C_STR_92[] PROGMEM = "";
const char C_STR_93[] PROGMEM = "";
const char C_STR_94[] PROGMEM = "http connection was used by other process";
const char C_STR_95[] PROGMEM = "Location: ";
const char C_STR_96[] PROGMEM = "&orderBy=";
const char C_STR_97[] PROGMEM = "&limitToFirst=";
const char C_STR_98[] PROGMEM = "&limitToLast=";
const char C_STR_99[] PROGMEM = "&startAt=";
const char C_STR_100[] PROGMEM = "&endAt=";
const char C_STR_101[] PROGMEM = "&equalTo=";
const char C_STR_102[] PROGMEM = "\"error\" : ";
const char C_STR_103[] PROGMEM = "";
const char C_STR_104[] PROGMEM = "";
const char C_STR_105[] PROGMEM = "boolean";
const char C_STR_106[] PROGMEM = "false";
const char C_STR_107[] PROGMEM = "true";
const char C_STR_108[] PROGMEM = "";
const char C_STR_109[] PROGMEM = "cancel";
const char C_STR_110[] PROGMEM = "auth_revoked";
const char C_STR_111[] PROGMEM = "http://";
const char C_STR_112[] PROGMEM = "https://";

const char *const string_table[] PROGMEM = {
  C_STR_0,
  C_STR_1, C_STR_2, C_STR_3, C_STR_4, C_STR_5,
  C_STR_6, C_STR_7, C_STR_8, C_STR_9, C_STR_10,
  C_STR_11, C_STR_12, C_STR_13, C_STR_14, C_STR_15,
  C_STR_16, C_STR_17, C_STR_18, C_STR_19, C_STR_20,
  C_STR_21, C_STR_22, C_STR_23, C_STR_24, C_STR_25,
  C_STR_26, C_STR_27, C_STR_28, C_STR_29, C_STR_30,
  C_STR_31, C_STR_32, C_STR_33, C_STR_34, C_STR_35,
  C_STR_36, C_STR_37, C_STR_38, C_STR_39, C_STR_40,
  C_STR_41, C_STR_42, C_STR_43, C_STR_44, C_STR_45,
  C_STR_46, C_STR_47, C_STR_48, C_STR_49, C_STR_50,
  C_STR_51, C_STR_52, C_STR_53, C_STR_54, C_STR_55,
  C_STR_56, C_STR_57, C_STR_58, C_STR_59, C_STR_60,
  C_STR_61, C_STR_62, C_STR_63, C_STR_64, C_STR_65,
  C_STR_66, C_STR_67, C_STR_68, C_STR_69, C_STR_70,
  C_STR_71, C_STR_72, C_STR_73, C_STR_74, C_STR_75,
  C_STR_76, C_STR_77, C_STR_78, C_STR_79, C_STR_80,
  C_STR_81, C_STR_82, C_STR_83, C_STR_84, C_STR_85,
  C_STR_86, C_STR_87, C_STR_88, C_STR_89, C_STR_90,
  C_STR_91, C_STR_92, C_STR_93, C_STR_94, C_STR_95,
  C_STR_96, C_STR_97, C_STR_98, C_STR_99, C_STR_100,
  C_STR_101, C_STR_102, C_STR_103, C_STR_104, C_STR_105,
  C_STR_106, C_STR_107, C_STR_108, C_STR_109, C_STR_110,
  C_STR_111, C_STR_112
};

#define FBDATA_PATH_LENGTH 200
#define FBDATA_PATH2_LENGTH 200
#define FBDATA_DATA_LENGTH 200
#define FBDATA_DATA2_LENGTH 200
#define FBDATA_STREAM_PATH_LENGTH 200
#define FBDATA_PUSH_NAME_LENGTH 100
#define FBDATA_REDIRECTURL_LENGTH 100
#define FBDATA_ERROR_LENGTH 100
#define FBDATA_EVENT_TYPE_LENGTH 100

#define QUERY_ORDERBY_LENGTH 50
#define QUERY_LIMITTOFIRST_LENGTH 50
#define QUERY_LIMITTOLAST_LENGTH 50
#define QUERY_STARTAT_LENGTH 50
#define QUERY_ENDAT_LENGTH 50
#define QUERY_EQUALTO_LENGTH 50

#define FB_HOST_LENGTH 100
#define FB_AUTH_LENGTH 100
#define FB_SSID_LENGTH 32
#define FB_PSW_LENGTH 64
#define FB_JSON_RES_LENGTH 200

class FirebaseData;
class Firebase_Arduino_WiFiNINA;

class QueryFilter
{
  public:
    QueryFilter();
    ~QueryFilter();
    void orderBy(const String &);
    void limitToFirst(int);
    void limitToLast(int);
    void startAt(int);
    void endAt(int);
    void startAt(const String &);
    void endAt(const String &);
    void equalTo(int);
    void equalTo(const String &);

    //Clear all query
    void clearQuery();
    
    //Release memory used by QueryFilter object
    void end();
    
    
    friend Firebase_Arduino_WiFiNINA;

  protected:
    char *_orderBy = new char[QUERY_ORDERBY_LENGTH];
    char *_limitToFirst = new char[QUERY_LIMITTOFIRST_LENGTH];
    char *_limitToLast = new char[QUERY_LIMITTOLAST_LENGTH];
    char *_startAt = new char[QUERY_STARTAT_LENGTH];
    char *_endAt = new char[QUERY_ENDAT_LENGTH];
    char *_equalTo = new char[QUERY_EQUALTO_LENGTH];
    void strCopy_T(char *buf, uint16_t index, bool empty = false, uint16_t size = 0);


};

class Firebase_Arduino_WiFiNINA
{
  public:
    struct FirebaseDataType;
    struct FirebaseMethod;

    Firebase_Arduino_WiFiNINA();
    ~Firebase_Arduino_WiFiNINA();

    /*
        Store Firebase's authentication credentials.

        @param host - Your Firebase database project host without http:// or https:// protocol e.g. Your_ProjectID.firebaseio.com.
        @param auth - Your database secret.
        @param wifiSSID - Your WiFi AP SSID.
        @param wifiPSW - Your WiFi AP Password.

    */
    void begin(const String &host, const String &auth, const String &wifiSSID, const String &wifiPSW);

    /*
        Reconnect WiFi if lost connection.

        @param reconnect - The boolean to set/unset WiFi AP reconnection.

    */
    void reconnectWiFi(bool reconnect);


    /*
        Append new integer value to the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which integer value will be appended.
        @param intValue - The appended value.

        @return - Boolean type status indicates the success of operation.

        The new appended node's key will be stored in Firebase Data object,
        which its value can be accessed via function [FirebaseData object].pushName().

    */
    bool pushInt(FirebaseData &dataObj, const String &path, int intValue);

    /*
        Append new float value to the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which float value will be appended.
        @param floatValue - The appended value.

        @return - Boolean type status indicates the success of operation.

        The new appended node's key will be stored in Firebase Data object,
        which its value can be accessed via function [FirebaseData object].pushName().

    */
    bool pushFloat(FirebaseData &dataObj, const String &path, float floatValue);

    /*
        Append new Boolean value to the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which Boolean value will be appended.
        @param boolValue - The appended value.

        @return - Boolean type status indicates the success of operation.

        The new appended node's key will be stored in Firebase Data object,
        which its value can be accessed via function [FirebaseData object].pushName().

    */
    bool pushBool(FirebaseData &dataObj, const String &path, bool boolValue);

    /*
        Append new string (text) to the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which string will be appended.
        @param StringValue - The appended value.

        @return - Boolean type status indicates the success of operation.

        The new appended node's key stored in Firebase Data object,
        which can be accessed via function [FirebaseData object].pushName().

    */
    bool pushString(FirebaseData &dataObj, const String &path, const String &stringValue);

    /*
        Append new child nodes's key and value (using JSON data) to the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which key and value in JSON data will be appended.
        @param jsonString - The appended JSON string (should be valid JSON data).

        @return - Boolean type status indicates the success of operation.

        The new appended node's key will be stored in Firebase Data object,
        which its value can be accessed via function [FirebaseData object].pushName().

    */
    bool pushJSON(FirebaseData &dataObj, const String &path, const String &jsonString);

    /*
        Set integer data at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which integer data will be set.
        @param intValue - Integer value to set.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].intData will return the integer value of
        payload returned from server.

    */
    bool setInt(FirebaseData &dataObj, const String &path, int intValue);

    /*
        Set float data at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which float data will be set.
        @param floatValue - Float value to set.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].floatData will return the float value of
        payload returned from server.

    */
    bool setFloat(FirebaseData &dataObj, const String &path, float floatValue);

    /*
        Set Boolean data at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which Boolean data will be set.
        @param boolValue - Boolean value to set.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].boolData will return the Boolean value of
        payload returned from server.

    */
    bool setBool(FirebaseData &dataObj, const String &path, bool boolValue);

    /*
        Set string (text) at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which string data will be set.
        @param stringValue - String or text to set.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].stringData will return the string value of
        payload returned from server.

    */
    bool setString(FirebaseData &dataObj, const String &path, const String &stringValue);

    /*

        Set child nodes's key and value (using JSON data) to the defined database path.

        This will replace any child nodes inside the defined path with node' s key
        and value defined in JSON data.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which key and value in JSON data will be replaced or set.
        @param jsonString - The JSON string to set (should be valid JSON data).

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].jsonData will return the JSON string value of
        payload returned from server.

    */
    bool setJSON(FirebaseData &dataObj, const String &path, const String &jsonString);

    /*
        Update child nodes's key or exising key's value (using JSON data) under the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which key and value in JSON data will be update.
        @param jsonString - The JSON string use for update.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].jsonData will return the json string value of
        payload returned from server.

        To reduce the network data usage, use updateNodeSilent instead.

    */
    bool updateNode(FirebaseData &dataObj, const String path, const String jsonString);

    /*
        Update child nodes's key or exising key's value (using JSON data) under the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which key and value in JSON data will be update.
        @param jsonString - The JSON string use for update.

        @return - Boolean type status indicates the success of operation.

        Owing to the objective of this function to reduce the netwok data usage,
        no payload will be returned from server.

    */
    bool updateNodeSilent(FirebaseData &dataObj, const String &path, const String &jsonString);

    /*
        Update child nodes's key or exising key's value (using JSON data) under the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Target database path which key and value in JSON data will be update.
        @param jsonString - The JSON string use for update.

        @return - Boolean type status indicates the success of operation.

        Owing to the objective of this function to reduce the netwok data usage,
        no payload will be returned from server.

    */
    bool getInt(FirebaseData &dataObj, const String &path);

    /*
        Read the float value at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path which the float value is being read.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].floatData will return the float value of
        payload returned from server.

        If the payload returned from server is not integer or float type,
        the function [FirebaseData object].intData will return zero (0).

    */
    bool getFloat(FirebaseData &dataObj, const String &path);

    /*
        Read the Boolean value at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path which the Boolean value is being read.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].boolData will return the Boolean value of
        payload returned from server.

        If the payload returned from server is not Boolean type,
        the function [FirebaseData object].boolData will return false.

    */
    bool getBool(FirebaseData &dataObj, const String &path);

    /*
        Read the string or text at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path which the string value is being read.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].stringData will return the string value of
        payload returned from server.

        If the payload returned from server is not string type,
        the function [FirebaseData object].stringData will return empty string (String object).

    */
    bool getString(FirebaseData &dataObj, const String &path);

    /*
        Read the JSON string at the defined database path.
        The returned payload JSON string represents the child nodes and their value.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path which the string value is being read.

        @return - Boolean type status indicates the success of operation.

        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].jsonData will return the JSON string value of
        payload returned from server.

        If the payload returned from server is not json type,
        the function [FirebaseData object].jsonData will return empty string (String object).

    */
    bool getJSON(FirebaseData &dataObj, const String &path);

    /*
        Read the JSON string at the defined database path.
        The returned payload JSON string represents the child nodes and their value.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path which the string value is being read.
        @param query - QueryFilter class to set query parameters to filter data.

        @return - Boolean type status indicates the success of operation.

        Available query parameters for filtering the data are the following.

        QueryFilter.orderBy -       Required parameter to specify which data used for data filtering included child key, key and value.
                                  Use "$key" for filtering data by keys of all nodes at the defined database path.
                                  Use "$value" for filtering data by value of all nodes at the defined database path.
                                  Use "$priority" for filtering data by "virtual child" named .priority of all nodes.
                                  Use  any child key to filter by that key.


        QueryFilter.limitToFirst -  The total children (number) to filter from the first child.
        QueryFilter.limitToLast -   The total last children (number) to filter.
        QueryFilter.startAt -       Starting value of range (number or string) of query upon orderBy param.
        QueryFilter.endAt -         Ending value of range (number or string) of query upon orderBy param.
        QueryFilter.equalTo -       Value (number or string) matches the orderBy param


        Call [FirebaseData object].dataType to determine what type of data that successfully
        stores in database.

        Call [FirebaseData object].jsonData will return the JSON string value of
        payload returned from server.

        If the payload returned from server is not json type,
        the function [FirebaseData object].jsonData will return empty string (String object).

        [FirebaseData object].jsonData will return null when the filtered data is empty.

    */
    bool getJSON(FirebaseData &dataObj, const String &path, QueryFilter &query);

    /*
        Delete all child nodes at the defined database path.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path to be deleted.

        @return - Boolean type status indicates the success of operation.

    */
    bool deleteNode(FirebaseData &dataObj, const String path);

    /*
        Start monitoring the value changes at the defined path and its children.

        @param dataObj - Firebase Data Object to hold data and instances.
        @param path - Database path being monitor.

        @return - Boolean type status indicates the success of operation.

    */
    bool beginStream(FirebaseData &dataObj, const String path);

    /*
        Read the stream event data at defined database path.

        Once beginStream was called e.g. in setup(), the readStream function
        should call inside the loop function.

        @param dataObj - Firebase Data Object to hold data and instances.

        @return - Boolean type status indicates the success of operation.

        Using the same Firebase Data object for stream read/monitoring associated
        with getXXX, setXXX, pushXXX, updateNode and deleteNode will break or quit
        the current stream connection.

        The stream will be resumed or reconnected automatically when calling readStream.

    */
    bool readStream(FirebaseData &dataObj);

    /*
        End the stream connection at defined path.

        Can be restart again by calling beginStream.

        @param dataObj - Firebase Data Object to hold data and instances.

        @return - Boolean type status indicates the success of operation.

    */
    bool endStream(FirebaseData &dataObj);

    void errorToString(int httpCode, char *buf);

  protected:
    bool sendRequest(FirebaseData &dataObj, const char *path, const uint8_t method, uint8_t dataType, const char *payload);
    void sendFirebaseRequest(FirebaseData &dataObj, const char *host, uint8_t method, const char *path, const char *auth, uint16_t payloadLength);
    bool firebaseConnectStream(FirebaseData &dataObj, const char *path);
    bool getServerStreamResponse(FirebaseData &dataObj);
    bool getServerResponse(FirebaseData &dataObj);

    void sendHeader(FirebaseData &dataObj, const char *host, uint8_t _method, const char *path, const char *auth, uint16_t payloadLength);
    void resetFirebasedataFlag(FirebaseData &dataObj);
    bool handleNetClientNotConnected(FirebaseData &dataObj);
    void forceEndHTTP(FirebaseData &dataObj);
    int firebaseConnect(FirebaseData &dataObj, const char *path, const uint8_t method, uint8_t dataType, const char *payload);
    bool cancelCurrentResponse(FirebaseData &dataObj);
    void setDataType(FirebaseData &dataObj, const char *data);
    void strCopy(char *buf, char *p, bool empty = false, uint16_t size = 0);
    void strCopy_T(char *buf, uint16_t index, bool empty = false, uint16_t size = 0);
    void intBuf(char *buf, int val, bool empty = false, uint16_t size = 0);
    void floatBuf(char *buf, float val, bool empty = false, uint16_t size = 0);
    void autoConnectWiFi();

    bool sdTest();
    void createDirs(char *dirs);

    void strcat_c(char *str, char c);
    int strpos(const char *haystack, const char *needle, int offset);
    int rstrpos(const char *haystack, const char *needle, int offset);
    char *rstrstr(const char *haystack, const char *needle);

    char *_host = new char[FB_HOST_LENGTH];
    char *_auth = new char[FB_AUTH_LENGTH];
    char *_ssid = new char[FB_SSID_LENGTH];
    char *_psw = new char[FB_PSW_LENGTH];
    uint16_t _port;
    bool _reconnectWiFi;
};

class FirebaseData
{

  public:
    FirebaseData();
    ~FirebaseData();

    /*

        Get WiFi client instance.

        @return - WiFi client instance.

    */
    WiFiSSLClient getWiFiClient();

    /*

        Pause/Unpause WiFiClient from all Firebase operations.

        @param pause The boolean to set/unset pause operation.

        @return - Boolean type status indicates the success of operation.

    */
    bool pauseFirebase(bool pause);

    /*

        Determine the data type of payload returned from server.

        @return The one of these data type e.g. integer, float, string and json.

    */
    String dataType();

    /*
        Determine the event type of stream.

        @return The one of these event type e.g. put, patch, cancel, and auth_revoked.

        The event type "put" indicated that data at event path relative to stream path was completely changed. Event path can be determined from dataPath().

        The event type "patch" indicated that data at event path relative to stream path was updated. Event path can be determined from dataPath().

        The event type "cancel" indeicated something wrong and cancel by server.

        The event type "auth_revoked" indicated the provided Firebase Authentication Data (Database secret) is no longer valid.

    */
    String eventType();

    /*

        Determine the current stream path.

        @return The database streaming path.

    */
    String streamPath();

    /*

        Determine the current data path.

        @return The database path which belong to server's returned payload.

        The database path returned from this function in case of stream, also changed up on the child or parent's stream
        value changes.

    */
    String dataPath();

    /*

        Determine the error reason String from process.

        @return The error description string (String object).

    */
    String errorReason();

    /*

        Return the ineger data of server returned payload.

        @return Integer value.

    */
    int intData();

    /*

        Return the float data of server returned payload.

        @return Float value.

    */
    float floatData();

    /*

        Return the Boolean data of server returned payload.

        @return Boolean value.

    */
    bool boolData();

    /*

        Return the String data of server returned payload.

        @return String (String object).

    */
    String stringData();

    /*

        Return the JSON String data of server returned payload.

        @return String (String object).

    */
    String jsonData();

    /*

        Return the new appended node's name or key of server returned payload when calling pushXXX function.

        @return String (String object).

    */
    String pushName();

    /*

        Determine the stream connection status.

        @return Boolean type status indicates whether the Firebase Data object is working with stream or not.

    */
    bool isStream();

    /*

        Determine the server connection status.

        @return Boolean type status indicates whether the Firebase Data object is connected to server or not.

    */
    bool httpConnected();

    /*

        Determine the timeout event of server's stream (30 sec is default).

        Nothing to do when stream connection timeout, the stream connection will be automatic resumed.

        @return Boolean type status indicates whether the stream was timeout or not.

    */
    bool streamTimeout();

    /*

        Determine the availability of data or paylaod returned from server.

        @return Boolean type status indicates whether the server return back the new payload or not.

    */
    bool dataAvailable();

    /*

        Determine the availability of stream event-data paylaod returned from server.

        @return Boolean type status indicates whether the server return back the stream event-data
        payload or not.

    */
    bool streamAvailable();

    /*

        Determine the matching between data type that intend to get from/store to database and the server's return payload data type.

        @return Boolean type status indicates whether the type of data being get from/store to database
        and server's returned payload are matched or not.

    */
    bool mismatchDataType();

    /*

        Determine the http status code return from server.

        @return integer number of HTTP status.

    */
    int httpCode();

    /*

        Check overflow of the returned payload data buffer.

        @return The overflow status.

        Default buffer size is 400 bytes, assigned via FIREBASE_RESPONSE_SIZE macro in Firebase_Arduino_WiFiNINA.h

    */
    bool bufferOverflow();

    /*

        Release memory used by Firebase Data object.

    */
    void end();

    /*
        Return the server's payload data.

        @return Payload string (String object).

    */
    String payload();

    QueryFilter queryFilter;

  protected:
    bool _isStreamTimeout;
    bool _isStream;
    bool _streamStop;
    bool _isSilentResponse;

    bool _bufferOverflow;
    bool _streamDataChanged;
    bool _streamPathChanged;
    bool _dataAvailable;
    bool _keepAlive;
    bool _httpConnected;
    bool _interruptRequest;
    bool _mismatchDataType;
    bool _pathNotExist;
    bool _pause;
    int _dataType;
    int _dataType2;
    uint8_t _dataTypeNum;
    uint8_t _connectionStatus;

    uint8_t _r_method = 0;
    uint8_t _r_dataType;

    char *_path = new char[FBDATA_PATH_LENGTH];
    char *_path2 = new char[FBDATA_PATH2_LENGTH];
    char *_data = new char[FBDATA_DATA_LENGTH];
    char *_data2 = new char[FBDATA_DATA2_LENGTH];
    char *_streamPath = new char[FBDATA_STREAM_PATH_LENGTH];
    char *_pushName = new char[FBDATA_PUSH_NAME_LENGTH];
    char *_redirectURL = new char[FBDATA_REDIRECTURL_LENGTH];
    char *_firebaseError = new char[FBDATA_ERROR_LENGTH];
    char *_eventType = new char[FBDATA_EVENT_TYPE_LENGTH];

    int _httpCode;
    int _contentLength;

    unsigned long _dataMillis;
    unsigned long _streamMillis;
    unsigned long _streamResetMillis;

    FirebaseHTTPClient _http;

    void strCopy_T(char *buf, uint16_t index, bool empty = false, uint16_t size = 0);

    friend Firebase_Arduino_WiFiNINA;
};

extern Firebase_Arduino_WiFiNINA Firebase;

#endif
