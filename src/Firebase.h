/**
 * Firebase.h, version 1.0.4
 *
 *
 * Created: March 3, 2022
 *
 * The MIT License (MIT)
 * Copyright (c) 2022 K. Suwatchai (Mobizt)
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

#ifndef Firebase_Arduino_WiFi_H
#define Firebase_Arduino_WiFi_H

#include <Arduino.h>

#include "Firebase_TCP_Client.h"

#include <avr/pgmspace.h>
#if defined(__arm__)
#include <avr/dtostrf.h>
#elif defined(__AVR__)
#else
#error Architecture or board not supported.
#endif
#define FIEBASE_PORT 443
#if defined(__arm__)
#define FIREBASE_RESPONSE_SIZE 4096
#elif defined(__AVR__)
#define FIREBASE_RESPONSE_SIZE 512
#endif
#define KEEP_ALIVE_TIMEOUT 40000

const char fb_esp_pgm_str_0[] PROGMEM = "{\".sv\": \"timestamp\"}";
const char fb_esp_pgm_str_1[] PROGMEM = "/";
const char fb_esp_pgm_str_2[] PROGMEM = ".json?auth=";
const char fb_esp_pgm_str_3[] PROGMEM = "\"";
const char fb_esp_pgm_str_4[] PROGMEM = ".";
const char fb_esp_pgm_str_5[] PROGMEM = "HTTP/1.1 ";
const char fb_esp_pgm_str_6[] PROGMEM = " ";
const char fb_esp_pgm_str_7[] PROGMEM = ":";
const char fb_esp_pgm_str_8[] PROGMEM = "Content-Type: ";
const char fb_esp_pgm_str_9[] PROGMEM = "text/event-stream";
const char fb_esp_pgm_str_10[] PROGMEM = "Connection: ";
const char fb_esp_pgm_str_11[] PROGMEM = "keep-alive";
const char fb_esp_pgm_str_12[] PROGMEM = "Content-Length: ";
const char fb_esp_pgm_str_13[] PROGMEM = "event: ";
const char fb_esp_pgm_str_14[] PROGMEM = "data: ";
const char fb_esp_pgm_str_15[] PROGMEM = "put";
const char fb_esp_pgm_str_16[] PROGMEM = "patch";
const char fb_esp_pgm_str_17[] PROGMEM = "\"path\":\"";
const char fb_esp_pgm_str_18[] PROGMEM = "\"data\":";
const char fb_esp_pgm_str_19[] PROGMEM = "null";
const char fb_esp_pgm_str_20[] PROGMEM = "{\"name\":\"";
const char fb_esp_pgm_str_21[] PROGMEM = "\r\n";
const char fb_esp_pgm_str_22[] PROGMEM = "GET ";
const char fb_esp_pgm_str_23[] PROGMEM = "PUT";
const char fb_esp_pgm_str_24[] PROGMEM = "POST";
const char fb_esp_pgm_str_25[] PROGMEM = "GET";
const char fb_esp_pgm_str_26[] PROGMEM = "PATCH";
const char fb_esp_pgm_str_27[] PROGMEM = "DELETE";
const char fb_esp_pgm_str_28[] PROGMEM = "&download=";
const char fb_esp_pgm_str_29[] PROGMEM = "&print=silent";
const char fb_esp_pgm_str_30[] PROGMEM = " HTTP/1.1\r\n";
const char fb_esp_pgm_str_31[] PROGMEM = "Host: ";
const char fb_esp_pgm_str_32[] PROGMEM = "User-Agent: UNO WiFi\r\n";
const char fb_esp_pgm_str_34[] PROGMEM = "Connection: close\r\n";
const char fb_esp_pgm_str_35[] PROGMEM = "Accept: text/event-stream\r\n";
const char fb_esp_pgm_str_36[] PROGMEM = "Connection: keep-alive\r\n";
const char fb_esp_pgm_str_37[] PROGMEM = "Keep-Alive: timeout=30, max=100\r\n";
const char fb_esp_pgm_str_38[] PROGMEM = "Accept-Encoding: identity;q=1,chunked;q=0.1,*;q=0\r\n";
const char fb_esp_pgm_str_39[] PROGMEM = "connection refused";
const char fb_esp_pgm_str_40[] PROGMEM = "send data failed";
const char fb_esp_pgm_str_41[] PROGMEM = "int64";
const char fb_esp_pgm_str_42[] PROGMEM = "not connected";
const char fb_esp_pgm_str_43[] PROGMEM = "connection lost";
const char fb_esp_pgm_str_44[] PROGMEM = "no HTTP server";
const char fb_esp_pgm_str_45[] PROGMEM = "bad request";
const char fb_esp_pgm_str_46[] PROGMEM = "non-authoriative information";
const char fb_esp_pgm_str_47[] PROGMEM = "no content";
const char fb_esp_pgm_str_48[] PROGMEM = "moved permanently";
const char fb_esp_pgm_str_49[] PROGMEM = "use proxy";
const char fb_esp_pgm_str_50[] PROGMEM = "temporary redirect";
const char fb_esp_pgm_str_51[] PROGMEM = "permanent redirect";
const char fb_esp_pgm_str_52[] PROGMEM = "unauthorized";
const char fb_esp_pgm_str_53[] PROGMEM = "forbidden";
const char fb_esp_pgm_str_54[] PROGMEM = "not found";
const char fb_esp_pgm_str_55[] PROGMEM = "method not allow";
const char fb_esp_pgm_str_56[] PROGMEM = "not acceptable";
const char fb_esp_pgm_str_57[] PROGMEM = "proxy authentication required";
const char fb_esp_pgm_str_58[] PROGMEM = "request timeout";
const char fb_esp_pgm_str_59[] PROGMEM = "length required";
const char fb_esp_pgm_str_60[] PROGMEM = "too many requests";
const char fb_esp_pgm_str_61[] PROGMEM = "request header fields too larg";
const char fb_esp_pgm_str_62[] PROGMEM = "internal server error";
const char fb_esp_pgm_str_63[] PROGMEM = "bad gateway";
const char fb_esp_pgm_str_64[] PROGMEM = "service unavailable";
const char fb_esp_pgm_str_65[] PROGMEM = "gateway timeout";
const char fb_esp_pgm_str_66[] PROGMEM = "http version not support";
const char fb_esp_pgm_str_67[] PROGMEM = "network authentication required";
const char fb_esp_pgm_str_68[] PROGMEM = "data buffer overflow";
const char fb_esp_pgm_str_69[] PROGMEM = "read Timeout";
const char fb_esp_pgm_str_70[] PROGMEM = "data type mismatch";
const char fb_esp_pgm_str_71[] PROGMEM = "path not exist";
const char fb_esp_pgm_str_72[] PROGMEM = "task";
const char fb_esp_pgm_str_73[] PROGMEM = "/esp.32";
const char fb_esp_pgm_str_74[] PROGMEM = "json";
const char fb_esp_pgm_str_75[] PROGMEM = "string";
const char fb_esp_pgm_str_76[] PROGMEM = "float";
const char fb_esp_pgm_str_77[] PROGMEM = "int";
const char fb_esp_pgm_str_78[] PROGMEM = "null";
const char fb_esp_pgm_str_79[] PROGMEM = ";";
const char fb_esp_pgm_str_80[] PROGMEM = "Content-Disposition: ";
const char fb_esp_pgm_str_81[] PROGMEM = "application/octet-stream";
const char fb_esp_pgm_str_82[] PROGMEM = "attachment";
const char fb_esp_pgm_str_83[] PROGMEM = "auth_revoked";
const char fb_esp_pgm_str_84[] PROGMEM = "cancel";
const char fb_esp_pgm_str_85[] PROGMEM = "true";
const char fb_esp_pgm_str_86[] PROGMEM = "e";
const char fb_esp_pgm_str_87[] PROGMEM = "false";
const char fb_esp_pgm_str_88[] PROGMEM = "Node path is not exist";
const char fb_esp_pgm_str_89[] PROGMEM = ".json";
const char fb_esp_pgm_str_90[] PROGMEM = "/root.json";
const char fb_esp_pgm_str_91[] PROGMEM = "boolean";
const char fb_esp_pgm_str_92[] PROGMEM = "double";
const char fb_esp_pgm_str_93[] PROGMEM = "uint64";
const char fb_esp_pgm_str_94[] PROGMEM = "http connection was used by other process";
const char fb_esp_pgm_str_95[] PROGMEM = "Location: ";
const char fb_esp_pgm_str_96[] PROGMEM = "&orderBy=";
const char fb_esp_pgm_str_97[] PROGMEM = "&limitToFirst=";
const char fb_esp_pgm_str_98[] PROGMEM = "&limitToLast=";
const char fb_esp_pgm_str_99[] PROGMEM = "&startAt=";
const char fb_esp_pgm_str_100[] PROGMEM = "&endAt=";
const char fb_esp_pgm_str_101[] PROGMEM = "&equalTo=";
const char fb_esp_pgm_str_102[] PROGMEM = "\"error\" : ";
const char fb_esp_pgm_str_103[] PROGMEM = "array";
class FirebaseData;
class Firebase_Class;

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

    friend Firebase_Class;

private:
    String _orderBy;
    String _limitToFirst;
    String _limitToLast;
    String _startAt;
    String _endAt;
    String _equalTo;
};

class Firebase_Class
{
    friend class FirebaseData;
    friend class QueryFilter;

public:
    struct FirebaseDataType;
    struct FirebaseMethod;

    Firebase_Class();
    ~Firebase_Class();

    /**
     * Store Firebase's authentication credentials.
     * @param host Firebase database project url e.g. <databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
     * @param auth database secret.
     * @param wifiSSID Your WiFi AP SSID.
     * @param wifiPSW Your WiFi AP Password.
    */
    void begin(const String &host, const String &auth, const String &wifiSSID, const String &wifiPSW);

    /**
     * Reconnect WiFi if lost connection.
     * @param reconnect The boolean to set/unset WiFi AP reconnection.
    */
    void reconnectWiFi(bool reconnect);

    /**
     * Append new integer value to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which integer value will be appended.
     * @param intValue The appended value.
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushInt(FirebaseData &fbdo, const String &path, int intValue);

    /**
     * Append new double value to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which double value will be appended.
     * @param dblValue The appended value.
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushDouble(FirebaseData &fbdo, const String &path, double dblValue);

    /**
     * Append new float value to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which float value will be appended.
     * @param floatValue The appended value.
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushFloat(FirebaseData &fbdo, const String &path, float floatValue);

    /**
     * Append new Boolean value to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which Boolean value will be appended.
     * @param boolValue The appended value.
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushBool(FirebaseData &fbdo, const String &path, bool boolValue);

    /**
     * Append new string (text) to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which string will be appended.
     * @param StringValue The appended value.

     * @return Boolean type status indicates the success of operation.

        The new appended node's key stored in Firebase Data object,
        which can be accessed via function <firebase data object>.pushName().

    */
    bool pushString(FirebaseData &fbdo, const String &path, const String &stringValue);

    /**
     * Append new child nodes's key and value (using JSON data) to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which key and value in JSON data will be appended.
     * @param jsonString The appended JSON string (should be valid JSON data).
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushJSON(FirebaseData &fbdo, const String &path, const String &jsonString);

    /**
     * Append new child nodes's key and value (using JSON array data) to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which key and value in JSON data will be appended.
     * @param arrayString The appended JSON array string (should be valid JSON array data).
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushArray(FirebaseData &fbdo, const String &path, const String &arrayString);

    /**
     * Append new Firebase server's timestamp to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which timestamp will be appended.
     * @return Boolean type status indicates the success of operation.
     * 
     * The new appended node's key will be stored in Firebase Data object,
     * which its value can be accessed via function <firebase data object>.pushName().
    */
    bool pushTimestamp(FirebaseData &fbdo, const String &path);

    /**
     * Set double data at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which integer data will be set.
     * @param dblValue Double value to set.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.doubleData will return the double value of payload returned from server.
    */
    bool setDouble(FirebaseData &fbdo, const String &path, double dblValue);

    /**
     * Set integer data at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which integer data will be set.
     * @param intValue Integer value to set.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.intData will return the integer value of payload returned from server.
    */
    bool setInt(FirebaseData &fbdo, const String &path, int intValue);
    bool setInt(FirebaseData &fbdo, const String &path, unsigned int intValue);
    bool setInt(FirebaseData &fbdo, const String &path, long intValue);
    bool setInt(FirebaseData &fbdo, const String &path, unsigned long intValue);
    bool setInt(FirebaseData &fbdo, const String &path, long long intValue);
    bool setInt(FirebaseData &fbdo, const String &path, unsigned long long intValue);

    /** 
     * Set float data at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which float data will be set.
     * @param floatValue Float value to set.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.floatData will return the float value of payload returned from server.
    */
    bool setFloat(FirebaseData &fbdo, const String &path, float floatValue);

    /**
     * Set Boolean data at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which Boolean data will be set.
     * @param boolValue Boolean value to set.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.boolData will return the Boolean value of
     * payload returned from server.
    */
    bool setBool(FirebaseData &fbdo, const String &path, bool boolValue);

    /**
     * Set string (text) at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which string data will be set.
     * @param stringValue String or text to set.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.stringData will return the string value of payload returned from server.
    */
    bool setString(FirebaseData &fbdo, const String &path, const String &stringValue);

    /**
     * Set child nodes's key and value (using JSON data) to the defined database path.
     * 
     * This will replace any child nodes inside the defined path with node' s key and value defined in JSON data.
     * 
     * @param fbdo Firebase Data Object.
     * @param path Target database path which key and value in JSON data will be replaced or set.
     * @param jsonString The JSON string to set (should be valid JSON data).
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.jsonData will return the JSON string value of payload returned from server.
    */
    bool setJSON(FirebaseData &fbdo, const String &path, const String &jsonString);

    /**
     * Set child nodes's key and value (using JSON array data) to the defined database path.
     * 
     * This will replace any child nodes inside the defined path with node' s key and value defined in JSON array data.
     * 
     * @param fbdo Firebase Data Object.
     * @param path Target database path which key and value in JSON data will be replaced or set.
     * @param arrayString The JSON string to set (should be valid JSON array data).
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.arrayData or  <firebase data object>.jsonData will return the JSON array string value of payload returned from server.
    */
    bool setArray(FirebaseData &fbdo, const String &path, const String &arrayString);

    /**
     * Set Firebase server's timestamp to the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which timestamp will be set.
     * @return Boolean type status indicates the success of operation.
     * Call <firebase data object>.intData will return the integer value of timestamp returned from server.
   */

    bool setTimestamp(FirebaseData &fbdo, const String &path);

    /**
     * Update child nodes's key or exising key's value (using JSON data) under the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which key and value in JSON data will be update.
     * @param jsonString The JSON string use for update.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.jsonData will return the json string value of payload returned from server.
     * 
     * To reduce the network data usage, use updateNodeSilent instead.
    */
    bool updateNode(FirebaseData &fbdo, const String path, const String jsonString);

    /**
     * Update child nodes's key or exising key's value (using JSON data) under the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Target database path which key and value in JSON data will be update.
     * @param jsonString The JSON string use for update.
     * @return Boolean type status indicates the success of operation.
     * 
     * Owing to the objective of this function to reduce the netwok data usage, no payload will be returned from server.
    */
    bool updateNodeSilent(FirebaseData &fbdo, const String &path, const String &jsonString);

    /**
     * Read the value at the defined database path.
     * The returned payload JSON string represents the child nodes and their value.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the string value is being read.
     * @return Boolean type status indicates the success of operation.
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
    */
    bool get(FirebaseData &fbdo, const String &path);

    /**
     * Read the int value at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the float value is being read.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.intData, <firebase data object>.int64Data or
     * <firebase data object>.uint64Data will return the integer value of payload returned from server.
     * 
     * If the payload returned from server is not integer, float or double type, 
     * the function <firebase data object>.intData will return zero (0).
     * 
     * If the payload returned from server is float or double type, 
     * the function <firebase data object>.intData will return rounded integer value.
    */
    bool getInt(FirebaseData &fbdo, const String &path);

    /**
     * ead the float value at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the float value is being read.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully stores in database.
     * 
     * Call <firebase data object>.floatData will return the float value of payload returned from server.
     * 
     * If the payload returned from server is not integer, float or double type, 
     * the function <firebase data object>.floatData will return zero (0).
    */
    bool getFloat(FirebaseData &fbdo, const String &path);

    /**
     * Read the double value at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the float value is being read.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.floatData will return the float value of
     * payload returned from server.
     * 
     * If the payload returned from server is not integer, float or double type, 
     * the function <firebase data object>.doubleData will return zero (0).
    */
    bool getDouble(FirebaseData &fbdo, const String &path);

    /**
     * Read the Boolean value at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the Boolean value is being read.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.boolData will return the Boolean value of
     * payload returned from server.
     * 
     * If the payload returned from server is not Boolean type,
     * the function <firebase data object>.boolData will return false.
    */
    bool getBool(FirebaseData &fbdo, const String &path);

    /**
     * Read the string or text at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the string value is being read.
     * @return Boolean type status indicates the success of operation.
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.stringData will return the string value of
     * payload returned from server.
     * 
     * If the payload returned from server is not string type, 
     * the function <firebase data object>.stringData will return empty string (String object).
    */
    bool getString(FirebaseData &fbdo, const String &path);

    /**
     * Read the JSON string at the defined database path.
     * The returned payload JSON string represents the child nodes and their value.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the string value is being read.
     * @return Boolean type status indicates the success of operation.
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.jsonData will return the JSON string value of
     * payload returned from server.
     * 
     * If the payload returned from server is not json or array type,
     * the function <firebase data object>.jsonData will return empty string (String object).
    */
    bool getJSON(FirebaseData &fbdo, const String &path);

    /**
     * Read the JSON string at the defined database path.
     * The returned payload JSON string represents the child nodes and their value.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the string value is being read.
     * @param query QueryFilter class to set query parameters to filter data.
     * @return Boolean type status indicates the success of operation.
     * 
     * Available query parameters for filtering the data are the following.
     * 
     * QueryFilter.orderBy       Required parameter to specify which data used for data filtering included child key, key and value.
     *                           Use "$key" for filtering data by keys of all nodes at the defined database path.
     *                           Use "$value" for filtering data by value of all nodes at the defined database path.
     *                           Use "$priority" for filtering data by "virtual child" named .priority of all nodes.
     *                           Use  any child key to filter by that key.
     * 
     * QueryFilter.limitToFirst  The total children (number) to filter from the first child.
     * QueryFilter.limitToLast   The total last children (number) to filter.
     * QueryFilter.startAt       Starting value of range (number or string) of query upon orderBy param.
     * QueryFilter.endAt         Ending value of range (number or string) of query upon orderBy param.
     * QueryFilter.equalTo       Value (number or string) matches the orderBy param
     * 
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.jsonData will return the JSON string value of payload returned from server.
     * 
     * If the payload returned from server is not json or array type, 
     * the function <firebase data object>.jsonData will return empty string (String object).
     * 
     * <firebase data object>.jsonData will return null when the filtered data is empty.
    */
    bool getJSON(FirebaseData &fbdo, const String &path, QueryFilter &query);

    /**
     * Read the JSON array string at the defined database path.
     * The returned payload JSON string represents the child nodes and their value.
     * @param fbdo Firebase Data Object.
     * @param path Database path which the string value is being read.
     * @param query QueryFilter class to set query parameters to filter data.
     * @return Boolean type status indicates the success of operation.
     * Call <firebase data object>.dataType to determine what type of data that successfully
     * stores in database.
     * 
     * Call <firebase data object>.arrayData will return the JSON array string value of
     * payload returned from server.
     * 
     * If the payload returned from server is not json or array type,
     * the function <firebase data object>.arrayData will return empty string (String object).
    */
    bool getArray(FirebaseData &fbdo, const String &path);

    bool getArray(FirebaseData &fbdo, const String &path, QueryFilter &query);

    /**
     * Delete all child nodes at the defined database path.
     * @param fbdo Firebase Data Object.
     * @param path Database path to be deleted.
     * @return Boolean type status indicates the success of operation.
    */
    bool deleteNode(FirebaseData &fbdo, const String path);

    /**
     * Start monitoring the value changes at the defined path and its children.
     * @param fbdo Firebase Data Object.
     * @param path Database path being monitor.
     * @return Boolean type status indicates the success of operation.
    */
    bool beginStream(FirebaseData &fbdo, const String path);

    /**
     * Read the stream event data at defined database path.
     * Once beginStream was called e.g. in setup(), the readStream function should call inside the loop function.
     * @param fbdo Firebase Data Object.
     * @return Boolean type status indicates the success of operation.
     * 
     * Using the same Firebase Data object for stream read/monitoring associated with getXXX, setXXX, pushXXX, updateNode and deleteNode will break or quit 
     * the current stream connection.
     * The stream will be resumed or reconnected automatically when calling readStream.
    */
    bool readStream(FirebaseData &fbdo);

    /**
     * End the stream connection at defined path.
     * 
     * Can be restart again by calling beginStream.
     * @param fbdo Firebase Data Object.
     * @return Boolean type status indicates the success of operation.
    */
    bool endStream(FirebaseData &fbdo);

    char *errorToString(int httpCode);

private:
    void clearStr(String &s);
    bool sendRequest(FirebaseData &fbdo, const char *path, const uint8_t method, uint8_t dataType, const char *payload);
    void buildFirebaseRequest(String &req, FirebaseData &fbdo, const char *host, uint8_t method, const char *path, const char *auth, int payloadLength);
    bool connectStream(FirebaseData &fbdo, const char *path);
    bool handleStream(FirebaseData &fbdo);
    uint16_t calCRC(const char *buf);
    void getHeader(const char *buf, String &out, PGM_P hdr);
    int strposP(const char *haystack, PGM_P needle, int index = 0);
    bool handleResponse(FirebaseData &fbdo);
    bool reconnect();
    bool reconnect(FirebaseData &fbdo);

    void delP(char *p);
    char *newP(size_t len);
    char *strP(PGM_P pgm);
    void appendP(char *buf, PGM_P pgm, bool empty = false);
    unsigned long long wstrtoull(const char *s);
    long long wstrtoll(const char *s);
    void sendHeader(FirebaseData &fbdo, const char *host, uint8_t _method, const char *path, const char *auth, uint16_t payloadLength);
    void clearFlag(FirebaseData &fbdo);
    void closeTCP(FirebaseData &fbdo);
    void setQuery(FirebaseData &fbdo, QueryFilter &query);
    int connect(FirebaseData &fbdo, const char *path, const uint8_t method, uint8_t dataType, const char *payload);
    void setDataType(FirebaseData &fbdo, const char *data);
    void autoConnectWiFi();
    bool apConnected(FirebaseData &fbdo);

    bool sdTest();
    void createDirs(char *dirs);

    void strcat_c(char *str, char c);
    int strpos(const char *haystack, const char *needle, int offset);
    int rstrpos(const char *haystack, const char *needle, int offset);

    String _host;
    String _auth;
    String _ssid;
    String _psw;
    uint16_t _port;
    bool _reconnectWiFi;
    unsigned long _lastReconnectMillis = 0;
    uint16_t _reconnectTimeout = 10000;
};

class NumToString
{
public:
    NumToString() { nullStr(); }
    NumToString(unsigned long long value) { uint64Str(value); }
    NumToString(unsigned long value) { uint32Str(value); }
    NumToString(long long value) { int64Str(value); }
    NumToString(signed long value) { int32Str(value); }
    NumToString(unsigned int value) { uint32Str(value); }
    NumToString(int value) { int32Str(value); }
    NumToString(bool value) { boolStr(value); }
    NumToString(float value, int precision = 5) { floatStr(value, precision); }
    NumToString(double value, int precision = 9) { doubleStr(value, precision); }
    ~NumToString() { delP(buf); }
    const char *get() const { return buf; }

private:
    /** dtostrf function is taken from 
     * https://github.com/stm32duino/Arduino_Core_STM32/blob/master/cores/arduino/avr/dtostrf.c
    */

    /***
     * dtostrf Emulation for dtostrf function from avr-libc
     * Copyright (c) 2013 Arduino.  All rights reserved.
     * Written by Cristian Maglie <c.maglie@arduino.cc>
     * This library is free software; you can redistribute it and/or
     * modify it under the terms of the GNU Lesser General Public
     * License as published by the Free Software Foundation; either
     * version 2.1 of the License, or (at your option) any later version.
     * This library is distributed in the hope that it will be useful,
     * but WITHOUT ANY WARRANTY; without even the implied warranty of
     * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     * Lesser General Public License for more details.
     * You should have received a copy of the GNU Lesser General Public
     * License along with this library; if not, write to the Free Software
     * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
    */

    #if defined (__arm__)

        char *dtostrf(double val, signed char width, unsigned char prec, char *sout)
        {
            //Commented code is the original version
            /***
          char fmt[20];
          sprintf(fmt, "%%%d.%df", width, prec);
          sprintf(sout, fmt, val);
          return sout;
        */

            // Handle negative numbers
            uint8_t negative = 0;
            if (val < 0.0)
            {
                negative = 1;
                val = -val;
            }

            // Round correctly so that print(1.999, 2) prints as "2.00"
            double rounding = 0.5;
            for (int i = 0; i < prec; ++i)
            {
                rounding /= 10.0;
            }

            val += rounding;

            // Extract the integer part of the number
            unsigned long int_part = (unsigned long)val;
            double remainder = val - (double)int_part;

            if (prec > 0)
            {
                // Extract digits from the remainder
                unsigned long dec_part = 0;
                double decade = 1.0;
                for (int i = 0; i < prec; i++)
                {
                    decade *= 10.0;
                }
                remainder *= decade;
                dec_part = (int)remainder;

                if (negative)
                {
                    sprintf(sout, "-%ld.%0*ld", int_part, prec, dec_part);
                }
                else
                {
                    sprintf(sout, "%ld.%0*ld", int_part, prec, dec_part);
                }
            }
            else
            {
                if (negative)
                {
                    sprintf(sout, "-%ld", int_part);
                }
                else
                {
                    sprintf(sout, "%ld", int_part);
                }
            }
            // Handle minimum field width of the output string
            // width is signed value, negative for left adjustment.
            // Range -128,127
            char fmt[129] = "";
            unsigned int w = width;
            if (width < 0)
            {
                negative = 1;
                w = -width;
            }
            else
            {
                negative = 0;
            }

            if (strlen(sout) < w)
            {
                memset(fmt, ' ', 128);
                fmt[w - strlen(sout)] = '\0';
                if (negative == 0)
                {
                    char *tmp = (char *)malloc(strlen(sout) + 1);
                    strcpy(tmp, sout);
                    strcpy(sout, fmt);
                    strcat(sout, tmp);
                    free(tmp);
                }
                else
                {
                    // left adjustment
                    strcat(sout, fmt);
                }
            }

            return sout;
        }

    #endif

    void init(size_t sz)
    {
        delP(buf);
        buf = newP(sz + 1);
    }

    char *newP(size_t len)
    {
        char *p = new char[len];
        memset(p, 0, len);
        return p;
    }

    void delP(char *p)
    {
        if (p != nullptr)
            delete[] p;
        p = nullptr;
    }

    char *intStr(int value)
    {
        char *t = newP(36);
        sprintf(t, "%d", value);
        return t;
    }

    void int32Str(signed long value)
    {
        init(64);
        sprintf(buf, "%ld", value);
    }

    void uint32Str(unsigned long value)
    {
        init(64);
        sprintf(buf, "%lu", value);
    }

    char *ullToString(char *b, unsigned long long value, bool flag)
    {
        int i = 126;
        char *out = NULL;
        while (value != 0)
        {
            b[i--] = (value % 10) + '0';
            value /= 10;
        }

        if (flag)
            b[i--] = '-';

        out = b + i + 1;
        return out;
    }

    void int64Str(long long value)
    {
        init(128);
        char *in = newP(128);
        unsigned long long v = (value < 0) ? value * -1 : value;
        char *out = ullToString(in, v, value < 0);
        strcpy(buf, out);
        delP(in);
    }

    void uint64Str(unsigned long long value)
    {
        init(128);
        char *in = newP(128);
        char *out = ullToString(in, value, false);
        strcpy(buf, out);
        delP(in);
    }

    void boolStr(bool value)
    {
        init(8);
        value ? strcpy(buf, "true") : strcpy(buf, "false");
    }

    void floatStr(float value, int precision)
    {
        init(32);
        dtostrf(value, (precision + 2), precision, buf);
        trim();
    }

    void doubleStr(double value, int precision)
    {
        init(64);
        dtostrf(value, (precision + 2), precision, buf);
        trim();
    }

    void nullStr()
    {
        init(6);
        strcpy(buf, "null");
    }

    void trim()
    {
        size_t i = strlen(buf) - 1;
        while (buf[i] == '0' && i > 0)
        {
            if (buf[i - 1] == '.')
            {
                i--;
                break;
            }
            if (buf[i - 1] != '0')
                break;
            i--;
        }
        if (i < strlen(buf) - 1)
            buf[i] = '\0';
    }

    char *buf = nullptr;
};

class FirebaseData
{

public:
    FirebaseData();
    ~FirebaseData();

    /**
     * Get WiFi client instance.
     * @return WiFi client instance.
    */
    WiFiSSLClient getWiFiClient();

    /**
     * Pause/Unpause WiFiClient from all Firebase operations.
     * @param pause The boolean to set/unset pause operation.
     * @return Boolean type status indicates the success of operation.
    */
    bool pauseFirebase(bool pause);

    /**
     * Determine the data type of payload returned from server.
     * @return The one of these data type e.g. integer, float, string and json.
    */
    String dataType();

    /**
     * Determine the event type of stream.
     * @return The one of these event type e.g. put, patch, cancel, and auth_revoked.
     * 
     * The event type "put" indicated that data at event path relative to stream path was completely changed. Event path can be determined from dataPath().
     * The event type "patch" indicated that data at event path relative to stream path was updated. Event path can be determined from dataPath().
     * The event type "cancel" indeicated something wrong and cancel by server.
     * The event type "auth_revoked" indicated the provided Firebase Authentication Data (Database secret) is no longer valid.
    */
    String eventType();

    /**
     * Determine the current stream path.
     * @return The database streaming path.
    */
    String streamPath();

    /**
     * Determine the current data path.
     * @return The database path which belong to server's returned payload.
     * The database path returned from this function in case of stream, also changed up on the child or parent's stream
     * value changes.
    */
    String dataPath();

    /**
     * Determine the error reason String from process.
     * @return The error description string (String object).
    */
    String errorReason();

    /**
     * Return the ineger data of server returned payload.
     * @return Integer value.
    */
    int intData();
    long long int64Data();
    unsigned long long uint64Data();

    /**
     * Return the float data of server returned payload.
     * @return Float value.
    */
    double doubleData();

    /**
     * Return the float data of server returned payload.
     * @return Float value.
    */
    float floatData();

    /**
     * Return the Boolean data of server returned payload.
     * @return Boolean value.
    */
    bool boolData();

    /**
     * Return the String data of server returned payload.
     * @return String (String object).
    */
    String stringData();

    /**
     * Return the JSON String data of server returned payload.
     * @return String (String object).
    */
    String jsonData();

    /**
     * Return the JSON array String data of server returned payload.
     * @return String (String object).
    */
    String arrayData();

    /**
     * Return the new appended node's name or key of server returned payload when calling pushXXX function.
     * @return String (String object).
    */
    String pushName();

    /**
     * Determine the stream connection status.
     * @return Boolean type status indicates whether the Firebase Data object is working with stream or not.
    */
    bool isStream();

    /**
     * Determine the server connection status.
     * @return Boolean type status indicates whether the Firebase Data object is connected to server or not.
    */
    bool httpConnected();

    /**
     * Determine the timeout event of server's stream (30 sec is default).
     * Nothing to do when stream connection timeout, the stream connection will be automatic resumed.
     * @return Boolean type status indicates whether the stream was timeout or not.
    */
    bool streamTimeout();

    /**
     * Determine the availability of data or paylaod returned from server.
     * @return Boolean type status indicates whether the server return back the new payload or not.
    */
    bool dataAvailable();

    /**
     * Determine the availability of stream event-data paylaod returned from server.
     * @return Boolean type status indicates whether the server return back the stream event-data
        payload or not.
    */
    bool streamAvailable();

    /**
     * Determine the matching between data type that intend to get from/store to database and the server's return payload data type.
     * @return Boolean type status indicates whether the type of data being get from/store to database
     * and server's returned payload are matched or not.
    */
    bool mismatchDataType();

    /**
     * Determine the http status code return from server.
     * @return integer number of HTTP status.
    */
    int httpCode();

    /**
     * Check overflow of the returned payload data buffer.
     * @return The overflow status.
     * Default buffer size is 400 bytes, assigned via FIREBASE_RESPONSE_SIZE macro in Firebase_Class.h
    */
    bool bufferOverflow();

    /**
     * Return the server's payload data.
     * @return Payload string (String object).
    */
    String payload();

    /**
     * Clear internal memory included payload without closing the TCP connection.
     */
    void clear();

    /**
     * Close socket connection, free all resources.
     */
    void end();

    QueryFilter queryFilter;

private:
    bool _isStreamTimeout;
    bool _isStream;
    bool _isSilentResponse;

    bool _bufferOverflow;
    bool _streamDataChanged;
    bool _streamPathChanged;
    bool _dataAvailable;
    bool _tcpConnected;
    bool _mismatchDataType;
    bool _pathNotExist;
    bool _paused;
    int _dataType;
    int _last_dataType;
    uint8_t _dataTypeNum;
    uint8_t _connectionStatus;

    uint8_t _r_method = 0;
    uint8_t _r_dataType = 0;

    uint16_t _payload_crc = 0;

    String _path;
    String _payload;
    String _streamPath;
    String _pushName;
    String _redirectURL;
    String _firebaseError;
    String _eventType;

    int _httpCode;
    int _contentLength;

    unsigned long _dataMillis;
    Firebase_TCP_Client _tcpClient;
   

    friend Firebase_Class;
};

extern Firebase_Class Firebase;

#endif
