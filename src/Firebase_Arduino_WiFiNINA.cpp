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

#ifndef Firebase_Arduino_WiFiNINA_CPP
#define Firebase_Arduino_WiFiNINA_CPP

#include "Firebase_Arduino_WiFiNINA.h"

struct Firebase_Arduino_WiFiNINA::FirebaseDataType
{
  static const uint8_t NULL_ = 1;
  static const uint8_t INTEGER = 2;
  static const uint8_t FLOAT = 3;
  static const uint8_t BOOLEAN = 4;
  static const uint8_t STRING = 5;
  static const uint8_t JSON = 6;
};

struct Firebase_Arduino_WiFiNINA::FirebaseMethod
{
  static const uint8_t PUT = 0;
  static const uint8_t PUT_SILENT = 1;
  static const uint8_t POST = 2;
  static const uint8_t GET = 3;
  static const uint8_t STREAM = 4;
  static const uint8_t PATCH = 5;
  static const uint8_t PATCH_SILENT = 6;
  static const uint8_t DELETE = 7;
};

Firebase_Arduino_WiFiNINA::Firebase_Arduino_WiFiNINA() {}
Firebase_Arduino_WiFiNINA::~Firebase_Arduino_WiFiNINA() {}

void Firebase_Arduino_WiFiNINA::begin(const String &host, const String &auth, const String &wifiSSID, const String &wifiPSW)
{
  strCopy(_host, (char*)host.c_str(), true, FB_HOST_LENGTH);
  strCopy(_auth, (char*)auth.c_str(), true, FB_AUTH_LENGTH);
  strCopy(_ssid, (char*)wifiSSID.c_str(), true, FB_SSID_LENGTH);
  strCopy(_psw, (char*)wifiPSW.c_str(), true, FB_PSW_LENGTH);
  _port = FIEBASE_PORT;
}

void Firebase_Arduino_WiFiNINA::reconnectWiFi(bool reconnect)
{
  _reconnectWiFi = reconnect;
}


bool Firebase_Arduino_WiFiNINA::pushInt(FirebaseData &dataObj, const String &path, int intValue)
{

  char *buf = new char[50];
  intBuf(buf, intValue, true, 50);
  dataObj.queryFilter.clearQuery();
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::INTEGER, buf);
  delete[] buf;
  return res;
}

bool Firebase_Arduino_WiFiNINA::pushFloat(FirebaseData &dataObj, const String &path, float floatValue)
{
  char *buf = new char[50];
  floatBuf(buf, floatValue, true, 50);
  dataObj.queryFilter.clearQuery();
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::FLOAT, buf);
  delete[] buf;
  return res;
}

bool Firebase_Arduino_WiFiNINA::pushBool(FirebaseData &dataObj, const String &path, bool boolValue)
{
  char *buf = new char[60];
  if (boolValue)
    strCopy_T(buf, 107, true, 60);
  else
    strCopy_T(buf, 106, true, 60);

  dataObj.queryFilter.clearQuery();
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::BOOLEAN, buf);
  delete[] buf;
  return res;
}

bool Firebase_Arduino_WiFiNINA::pushString(FirebaseData &dataObj, const String &path, const String &stringValue)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::STRING, stringValue.c_str());
}

bool Firebase_Arduino_WiFiNINA::pushJSON(FirebaseData &dataObj, const String &path, const String &jsonString)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::setInt(FirebaseData &dataObj, const String &path, int intValue)
{
  char *buf = new char[50];
  intBuf(buf, intValue, true, 50);
  dataObj.queryFilter.clearQuery();
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::INTEGER, buf);
  delete[] buf;
  return res;
}

bool Firebase_Arduino_WiFiNINA::setFloat(FirebaseData &dataObj, const String &path, float floatValue)
{
  uint8_t bufSize = 50;
  char *buf = new char[bufSize];
  floatBuf(buf, floatValue, true, bufSize);
  dataObj.queryFilter.clearQuery();
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::FLOAT, buf);
  delete[] buf;
  return res;
}

bool Firebase_Arduino_WiFiNINA::setBool(FirebaseData &dataObj, const String &path, bool boolValue)
{
  uint8_t bufSize = 50;
  char *buf = new char[bufSize];
  if (boolValue)
    strCopy_T(buf, 107, true, bufSize);
  else
    strCopy_T(buf, 106, true, bufSize);

  dataObj.queryFilter.clearQuery();
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::BOOLEAN, buf);
  delete[] buf;
  return res;
}

bool Firebase_Arduino_WiFiNINA::setString(FirebaseData &dataObj, const String &path, const String &stringValue)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::STRING, stringValue.c_str());
}

bool Firebase_Arduino_WiFiNINA::setJSON(FirebaseData &dataObj, const String &path, const String &jsonString)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::updateNode(FirebaseData &dataObj, const String path, const String jsonString)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PATCH, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::updateNodeSilent(FirebaseData &dataObj, const String &path, const String &jsonString)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PATCH_SILENT, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::getInt(FirebaseData &dataObj, const String &path)
{
  dataObj.queryFilter.clearQuery();
  return getFloat(dataObj, path);
}

bool Firebase_Arduino_WiFiNINA::getFloat(FirebaseData &dataObj, const String &path)
{
  dataObj.queryFilter.clearQuery();
  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::GET, FirebaseDataType::FLOAT, "");
  if (dataObj._dataType != FirebaseDataType::INTEGER && dataObj._dataType != FirebaseDataType::FLOAT)
    flag = false;
  return flag;
}

bool Firebase_Arduino_WiFiNINA::getBool(FirebaseData &dataObj, const String &path)
{
  dataObj.queryFilter.clearQuery();
  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::GET, FirebaseDataType::BOOLEAN, "");
  if (dataObj._dataType != FirebaseDataType::BOOLEAN)
    flag = false;
  return flag;
}

bool Firebase_Arduino_WiFiNINA::getString(FirebaseData &dataObj, const String &path)
{
  dataObj.queryFilter.clearQuery();
  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::GET, FirebaseDataType::STRING, "");
  if (dataObj._dataType != FirebaseDataType::STRING)
    flag = false;
  return flag;
}

bool Firebase_Arduino_WiFiNINA::getJSON(FirebaseData &dataObj, const String &path)
{
  dataObj.queryFilter.clearQuery();
  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::GET, FirebaseDataType::JSON, "");
  if (dataObj._dataType != FirebaseDataType::JSON)
    flag = false;
  return flag;
}

bool Firebase_Arduino_WiFiNINA::getJSON(FirebaseData &dataObj, const String &path, QueryFilter &query)
{
  dataObj.queryFilter.clearQuery();
  if (strlen(query._orderBy) > 0)
  {
    strcpy(dataObj.queryFilter._orderBy, query._orderBy);
    strcpy(dataObj.queryFilter._limitToFirst, query._limitToFirst);
    strcpy(dataObj.queryFilter._limitToLast, query._limitToLast);
    strcpy(dataObj.queryFilter._startAt, query._startAt);
    strcpy(dataObj.queryFilter._endAt, query._endAt);
    strcpy(dataObj.queryFilter._equalTo, query._equalTo);
  }

  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::GET, FirebaseDataType::JSON, "");
  if (dataObj._dataType != FirebaseDataType::JSON)
    flag = false;
  return flag;
}

bool Firebase_Arduino_WiFiNINA::deleteNode(FirebaseData &dataObj, const String path)
{
  dataObj.queryFilter.clearQuery();
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::DELETE, FirebaseDataType::STRING, "");
}

bool Firebase_Arduino_WiFiNINA::beginStream(FirebaseData &dataObj, const String path)
{
  return firebaseConnectStream(dataObj, path.c_str());
}

bool Firebase_Arduino_WiFiNINA::readStream(FirebaseData &dataObj)
{
  if (dataObj._streamStop)
    return true;
  return getServerStreamResponse(dataObj);
}

bool Firebase_Arduino_WiFiNINA::endStream(FirebaseData &dataObj)
{
  bool flag = false;
  memset(dataObj._streamPath, 0, FBDATA_STREAM_PATH_LENGTH);
  forceEndHTTP(dataObj);
  flag = dataObj._http.http_connected();
  if (!flag)
  {
    dataObj._isStream = false;
    dataObj._streamStop = true;
  }
  return !flag;
}

int Firebase_Arduino_WiFiNINA::firebaseConnect(FirebaseData &dataObj, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{
  memset(dataObj._firebaseError, 0, FBDATA_ERROR_LENGTH);

  if (dataObj._pause)
    return 0;

  if (WiFi.status() != WL_CONNECTED)
  {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
    return -1;
  }

  if (strlen(path) == 0 || strlen(_host) == 0 || strlen(_auth) == 0)
  {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return _HTTP_CODE_BAD_REQUEST;
  }

  uint16_t bufSize = 32;
  char *buf = new char[bufSize];

  uint16_t tempSize = 200;
  char *temp = new char[tempSize];

  int len = 0;
  uint16_t toRead = 0;
  bool httpConnected = false;

  uint16_t payloadStrSize = strlen(payload) + 10;

  char *payloadStr = new char[payloadStrSize];
  memset(payloadStr, 0, payloadStrSize);

  int httpCode = -1;

  //init the firebase data
  resetFirebasedataFlag(dataObj);
  memset(dataObj._path, 0, FBDATA_PATH_LENGTH);

  if (method == FirebaseMethod::STREAM)
  {
    //stream path change? reset the current (keep alive) connection
    if (strcmp(path, dataObj._streamPath) != 0)
      dataObj._streamPathChanged = true;
    if (!dataObj._isStream || dataObj._streamPathChanged)
    {
      if (dataObj._http.http_connected())
        forceEndHTTP(dataObj);
    }

    memset(dataObj._streamPath, 0, FBDATA_STREAM_PATH_LENGTH);

    if (strlen(path) > 0)
      if (path[0] != '/')
        strCopy_T(dataObj._streamPath, 1);

    strcat(dataObj._streamPath, path);
  }
  else
  {
    //last requested method was stream?, reset the connection
    if (dataObj._isStream)
      forceEndHTTP(dataObj);

    memset(dataObj._path, 0, FBDATA_PATH_LENGTH);

    if (strlen(path) > 0)
      if (path[0] != '/')
        strCopy_T(dataObj._path, 1);

    strcat(dataObj._path, path);

    dataObj._isStreamTimeout = false;
  }


  httpConnected = dataObj._http.http_begin(_host, _port);

  if (!httpConnected)
  {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_REFUSED;
    goto EXIT_1;
  }
  
    

  //Prepare for string and JSON payloads
  if (method != FirebaseMethod::GET && method != FirebaseMethod::STREAM &&
      method != FirebaseMethod::DELETE)
  {
    memset(payloadStr, 0, payloadStrSize);
    if (dataType == FirebaseDataType::STRING)
      strCopy_T(payloadStr, 3);
    strcat(payloadStr, payload);
    if (dataType == FirebaseDataType::STRING)
      strCopy_T(payloadStr, 3);
  }
  

  //Prepare request header

  sendFirebaseRequest(dataObj, _host, method, path, _auth, strlen(payloadStr));

  if (method == FirebaseMethod::PATCH_SILENT)
    dataObj._isSilentResponse = true;

  //Send request w/wo payload
  httpCode = dataObj._http.http_sendRequest("", payloadStr);

  delete[] payloadStr;
  delete[] buf;
  delete[] temp;
  return httpCode;

EXIT_1:

  delete[] payloadStr;
  delete[] buf;
  delete[] temp;
  return -1;
}

bool Firebase_Arduino_WiFiNINA::sendRequest(FirebaseData &dataObj, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{

  bool flag = false;
  memset(dataObj._firebaseError, 0, FBDATA_ERROR_LENGTH);

  if (dataObj._pause)
    return true;

  if (strlen(path) == 0 || strlen(_host) == 0 || strlen(_auth) == 0)
  {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  if ((method == FirebaseMethod::PUT || method == FirebaseMethod::POST || method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT) && strlen(payload) == 0 && dataType != FirebaseDataType::STRING)
  {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  //Try to reconnect WiFi if lost connection
  autoConnectWiFi();

  //If WiFi is not connected, return false
  if (WiFi.status() != WL_CONNECTED)
  {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
    return false;
  }

  //Get the current WiFi client from current firebase data
  //Check for connection status
  if (dataObj._http.http_connected())
    dataObj._httpConnected = true;
  else
    dataObj._httpConnected = false;

  if (dataObj._httpConnected)
  {
    if (method == FirebaseMethod::STREAM)
    {
      dataObj._streamMillis = millis();
      return false;
    }
    else
    {
      if (!dataObj._keepAlive)
      {
        dataObj._streamMillis = millis() + 50;
        dataObj._interruptRequest = true;
        delay(20);
        if (dataObj._http.http_connected())
        {

          delay(20);
          forceEndHTTP(dataObj);
          if (dataObj._http.http_connected())
            if(!dataObj._isStream)
              return false;
        }
        dataObj._httpConnected = false;
      }
    }
  }

  if (!dataObj._keepAlive && dataObj._httpConnected)
    return false;

  dataObj._httpConnected = true;
  dataObj._interruptRequest = false;
  memset(dataObj._redirectURL, 0, FBDATA_REDIRECTURL_LENGTH);
  dataObj._r_method = method;
  dataObj._r_dataType = dataType;

  int httpCode = firebaseConnect(dataObj, path, method, dataType, payload);

  if (httpCode == 0)
  {

    dataObj._dataType2 = dataType;

    if (method == FirebaseMethod::STREAM)
    {
      dataObj._dataMillis = millis();
      flag = getServerStreamResponse(dataObj);
      if (!flag)
        forceEndHTTP(dataObj);
    }
    else
    {
      strCopy(dataObj._path, (char*)path, true, FBDATA_PATH_LENGTH);
      flag = getServerResponse(dataObj);
      dataObj._dataAvailable = strlen(dataObj._data) > 0;
    }

    if (!flag)
      forceEndHTTP(dataObj);
  }
  else
  {
    //can't establish connection
    dataObj._httpCode = httpCode;
    dataObj._httpConnected = false;
    delay(100);
    return false;
  }

  return flag;
}

bool Firebase_Arduino_WiFiNINA::getServerResponse(FirebaseData &dataObj)
{

  if (dataObj._pause)
    return true;

  if (WiFi.status() != WL_CONNECTED)
  {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
    return false;
  }

  WiFiSSLClient client = dataObj._http.client;

  if (!dataObj._http.http_connected() || dataObj._interruptRequest)
    return cancelCurrentResponse(dataObj);
  if (!handleNetClientNotConnected(dataObj) || !dataObj._httpConnected)
    return false;

  bool flag = false;

  memset(dataObj._data, 0, FBDATA_DATA_LENGTH);

  char *jsonRes = new char[FB_JSON_RES_LENGTH];
  memset(jsonRes, 0, FB_JSON_RES_LENGTH);

  char *lineBuf = new char[FIREBASE_RESPONSE_SIZE];
  memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);

  uint16_t tempBufSize = FIREBASE_RESPONSE_SIZE;
  char *tmp = new char[tempBufSize];
  memset(tmp, 0, tempBufSize);

  uint16_t eventTypeSize = 30;
  char *eventType = new char[eventTypeSize];
  memset(eventType, 0, eventTypeSize);

  char *fstr = new char[60];
  memset(fstr, 0, 60);

  char c;
  int p1, p2;
  bool isStream = false;
  dataObj._httpCode = -1000;
  dataObj._contentLength = -1;
  dataObj._bufferOverflow = false;
  memset(dataObj._pushName, 0, FBDATA_PUSH_NAME_LENGTH);

  bool hasEvent = false;
  bool hasEventData = false;
  bool payLoadBegin = false;

  unsigned long dataTime = millis();

  uint16_t lfCount = 0;
  uint16_t charPos = 0;

  if (!dataObj._isStream)
    while (client.connected() && !client.available() && millis() - dataTime < dataObj._http.netClientTimeout)
      delay(1);

  dataTime = millis();
  if (client.connected() && client.available())
  {
    while (client.available())
    {

      if (dataObj._interruptRequest)
        return cancelCurrentResponse(dataObj);

      c = client.read();

      if (payLoadBegin && dataObj._contentLength > 0)
      {
        if (charPos % 128 == 0)
        {
          dataTime = millis();
          delayMicroseconds(10);
        }
      }

      if (c < 0xff && c != '\r' && c != '\n' && charPos <= FIREBASE_RESPONSE_SIZE)
        strcat_c(lineBuf, c);

      if (c < 0xff)
        charPos++;

      if (strlen(lineBuf) > FIREBASE_RESPONSE_SIZE)
      {
        dataObj._bufferOverflow = true;
        memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
      }

      if (c == '\n')
      {
        dataTime = millis();

        if (strlen(lineBuf) == 0 && lfCount > 0)
          payLoadBegin = true;

        if (strlen(lineBuf) > 0)
        {
          strCopy_T(fstr, 5, true, 60);
          p1 = strpos(lineBuf, fstr, 0);
          if (p1 != -1)
          {
            memset(tmp, 0, tempBufSize);
            strncpy(tmp, lineBuf + p1 + 9, strlen(lineBuf) - p1 - 9);
            dataObj._httpCode = atoi(tmp);
          }

          if (dataObj._httpCode == _HTTP_CODE_TEMPORARY_REDIRECT)
          {
            strCopy_T(fstr, 95, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {
              memset(tmp, 0, tempBufSize);
              memset(dataObj._redirectURL, 0, FBDATA_REDIRECTURL_LENGTH);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_95), strlen(lineBuf) - p1 - strlen_P(C_STR_95));
              strcpy(dataObj._redirectURL, tmp);
              int res = firebaseConnect(dataObj, dataObj._redirectURL, dataObj._r_method, dataObj._r_dataType, "");

              if (res == 0)
                goto EXIT_4;

              goto EXIT_3;
            }
          }

          if (dataObj._httpCode == _HTTP_CODE_NO_CONTENT)
            continue;

          strCopy_T(fstr, 7, true, 60);
          if (strpos(lineBuf, fstr, 0) != -1)
          {
            strCopy_T(fstr, 102, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {
              memset(dataObj._firebaseError, 0, FBDATA_ERROR_LENGTH);
              memset(tmp, 0, tempBufSize);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_102) + 1, strlen(lineBuf) - p1 - strlen_P(C_STR_102));
              strncpy(dataObj._firebaseError, tmp, strlen(tmp) - 1);
            }

            strCopy_T(fstr, 8, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {
              memset(tmp, 0, tempBufSize);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_8), strlen(lineBuf) - p1 - strlen_P(C_STR_8));

              strCopy_T(fstr, 9, true, 60);
              if (strcmp(tmp, fstr) == 0)
                isStream = true;
            }

            strCopy_T(fstr, 10, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {
              memset(tmp, 0, tempBufSize);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_10), strlen(lineBuf) - p1 - strlen_P(C_STR_10));

              strCopy_T(fstr, 11, true, 60);
              if (strcmp(tmp, fstr) == 0)
                dataObj._keepAlive = true;
              else
                dataObj._keepAlive = false;
            }

            strCopy_T(fstr, 12, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {

              memset(tmp, 0, tempBufSize);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_12), strlen(lineBuf) - p1 - strlen_P(C_STR_12));

              dataObj._contentLength = atoi(tmp);
            }

            strCopy_T(fstr, 13, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {
              memset(eventType, 0, eventTypeSize);
              strncpy(eventType, lineBuf + p1 + strlen_P(C_STR_13), strlen(lineBuf) - p1 - strlen_P(C_STR_13));

              hasEvent = true;
              isStream = true;
              dataObj._httpCode = _HTTP_CODE_OK;
            }

            strCopy_T(fstr, 14, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1)
            {
              hasEventData = true;
              isStream = true;
              dataObj._httpCode = _HTTP_CODE_OK;

              memset(tmp, 0, tempBufSize);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_14), strlen(lineBuf) - p1 - strlen_P(C_STR_14));
              memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
              strcpy(lineBuf, tmp);
            }
          }
        }


        if (!hasEventData || !hasEvent)
          memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);

        lfCount++;
        charPos = 0;
      }

      if (millis() - dataTime > dataObj._http.netClientTimeout)
      {
        //cancelCurrentResponse(dataObj);
        dataObj._httpCode = HTTPC_ERROR_READ_TIMEOUT;
        break;
      }
    }

    if (dataObj._httpCode == _HTTP_CODE_OK)
    {

      //JSON stream data?
      if (isStream)
      {
        if (hasEventData && hasEvent)
        {
          bool m = false;
          strCopy_T(fstr, 15, true, 60);
          m |= strpos(eventType, fstr, 0) != -1;

          strCopy_T(fstr, 16, true, 60);
          m |= strpos(eventType, fstr, 0) != -1;

          if (m)
          {
            strCopy(dataObj._eventType, eventType, true, FBDATA_EVENT_TYPE_LENGTH);

            //Parses json response for path
            strCopy_T(fstr, 17, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1 && p1 < FIREBASE_RESPONSE_SIZE)
            {
              strCopy_T(fstr, 3, true, 60);
              p2 = strpos(lineBuf, fstr, p1 + strlen_P(C_STR_17));
              if (p2 != -1)
              {
                memset(tmp, 0, tempBufSize);
                strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_17), p2 - p1 - strlen_P(C_STR_17));
                strCopy(dataObj._path, tmp, true, FBDATA_PATH_LENGTH);
              }
            }

            //Parses json response for data
            strCopy_T(fstr, 18, true, 60);
            p1 = strpos(lineBuf, fstr, 0);
            if (p1 != -1 && p1 < FIREBASE_RESPONSE_SIZE)
            {
              memset(tmp, 0, tempBufSize);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_18), strlen(lineBuf) - p1 - strlen_P(C_STR_18) - 1);
              strCopy(dataObj._data, tmp, true, FBDATA_DATA_LENGTH);

              setDataType(dataObj, dataObj._data);
              bool samePath = dataObj._path == dataObj._path2;
              strCopy_T(fstr, 1, true, 60);
              bool rootPath = strcmp(dataObj._path, fstr) == 0;
              bool emptyPath = strlen(dataObj._path2) == 0;
              bool sameData = strcmp(dataObj._data, dataObj._data2) == 0;

              //Any stream update?
              if ((!samePath && (!rootPath || emptyPath)) || (samePath && !sameData && !dataObj._streamPathChanged))
              {
                dataObj._streamDataChanged = true;
                strCopy(dataObj._data2, dataObj._data, true, FBDATA_DATA2_LENGTH);
                strCopy(dataObj._path2, dataObj._path, true, FBDATA_PATH2_LENGTH);
              }
              else
                dataObj._streamDataChanged = false;

              dataObj._dataMillis = millis();
              flag = true;
              dataObj._dataAvailable = flag;
              dataObj._isStreamTimeout = false;
            }

            dataObj._streamPathChanged = false;
          }
          else
          {
            //Firebase keep alive data
            strCopy_T(fstr, 11, true, 60);
            if (strcmp(eventType, fstr) == 0)
            {
              dataObj._isStreamTimeout = false;
              dataObj._dataMillis = millis();

              //if (dataObj._timeoutCallback)
              //  dataObj._timeoutCallback(false);
            }

            //Firebase cancel and auth_revoked events
            strCopy_T(fstr, 109, true, 60);
            bool m2 = strcmp(eventType, fstr) == 0;
            strCopy_T(fstr, 110, true, 60);
            m2 |= strcmp(eventType, fstr) == 0;

            if (m2)
            {
              dataObj._isStreamTimeout = false;
              dataObj._dataMillis = millis();
              dataObj._eventType = eventType;
              //make stream available status
              dataObj._streamDataChanged = true;
              dataObj._dataAvailable = true;
            }
          }
        }
        dataObj._streamMillis = millis();
      }
      else
      {
        //Just text payload
        strCopy(dataObj._data, lineBuf, true, FBDATA_DATA_LENGTH);
        setDataType(dataObj, lineBuf);

        //Push (POST) data?
        strCopy_T(fstr, 20, true, 60);
        p1 = strpos(lineBuf, fstr, 0);
        if (p1 != -1)
        {
          strCopy_T(fstr, 3, true, 60);
          p2 = strpos(lineBuf, fstr, p1 + strlen_P(C_STR_20));
          if (p2 != -1)
          {
            memset(tmp, 0, tempBufSize);
            strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_20), p2 - p1 - strlen_P(C_STR_20));
            strCopy(dataObj._pushName, tmp, true, FBDATA_PUSH_NAME_LENGTH);
            dataObj._dataType = -1;
            dataObj._dataType2 = -1;
            memset(dataObj._data, 0, FBDATA_DATA_LENGTH);
          }
        }
      }
    }
    else
    {
      if (dataObj._isSilentResponse)
      {
        if (dataObj._httpCode == _HTTP_CODE_NO_CONTENT)
        {
          dataObj._httpCode = _HTTP_CODE_OK;
          memset(dataObj._path, 0, FBDATA_PATH_LENGTH);
          memset(dataObj._data, 0, FBDATA_DATA_LENGTH);
          memset(dataObj._pushName, 0, FBDATA_PUSH_NAME_LENGTH);
          dataObj._dataType = -1;
          dataObj._dataType2 = -1;
          dataObj._dataAvailable = false;
        }
      }
      else
        dataObj._contentLength = -1;
    }

    if (dataObj._dataType == FirebaseDataType::NULL_)
    {
      dataObj._pathNotExist = true;
    }
    else
    {
      dataObj._pathNotExist = false;
      bool _n1 = dataObj._dataType == FirebaseDataType::FLOAT || dataObj._dataType == FirebaseDataType::INTEGER;
      bool _n2 = dataObj._dataType2 == FirebaseDataType::FLOAT || dataObj._dataType2 == FirebaseDataType::INTEGER;

      if (dataObj._dataType2 == dataObj._dataType || (_n1 && _n2))
        dataObj._mismatchDataType = false;
      else
        dataObj._mismatchDataType = true;
    }

    if (!dataObj._httpCode)
    {
      dataObj._contentLength = -1;
      dataObj._httpCode = HTTPC_ERROR_NO_HTTP_SERVER;
    }
    dataObj._httpConnected = false;
    dataObj._streamMillis = millis();

    goto EXIT_2;
  }

  if (dataObj._httpCode == -1000)
    flag = true;

  dataObj._httpConnected = false;
  dataObj._streamMillis = millis();
  delete[] lineBuf;
  delete[] tmp;
  delete[] eventType;
  delete[] jsonRes;
  delete[] fstr;

  return flag;

EXIT_2:

  delete[] lineBuf;
  delete[] tmp;
  delete[] eventType;
  delete[] jsonRes;
  delete[] fstr;

  if (dataObj._httpCode == HTTPC_ERROR_READ_TIMEOUT)
    return false;
  return dataObj._httpCode == _HTTP_CODE_OK;

EXIT_3:

  delete[] lineBuf;
  delete[] tmp;
  delete[] eventType;
  delete[] jsonRes;
  delete[] fstr;
  return true;

EXIT_4:
  delete[] lineBuf;
  delete[] tmp;
  delete[] eventType;
  delete[] jsonRes;
  delete[] fstr;
  return getServerResponse(dataObj);
}

bool Firebase_Arduino_WiFiNINA::firebaseConnectStream(FirebaseData &dataObj, const char *path)
{

  if (dataObj._pause)
    return true;

  dataObj._streamStop = false;

  if (dataObj._isStream && path == dataObj._streamPath)
    return true;

  if (strlen(path) == 0 || strlen(_host) == 0 || strlen(_auth) == 0)
  {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  if (millis() - dataObj._streamResetMillis > 50)
    delay(50);

  bool flag;
  flag = strlen(dataObj._streamPath) == 0;
  flag |= firebaseConnect(dataObj, path, FirebaseMethod::STREAM, FirebaseDataType::STRING, "") == 0;
  dataObj._dataMillis = millis();
  return flag;
}

bool Firebase_Arduino_WiFiNINA::getServerStreamResponse(FirebaseData &dataObj)
{

  if (dataObj._pause || dataObj._streamStop)
    return true;

  unsigned long ml = millis();
  if (dataObj._streamMillis == 0)
    dataObj._streamMillis = ml;
  if (dataObj._streamResetMillis == 0)
    dataObj._streamResetMillis = ml;

  //Reset firebase data every 50 ms and extend delay for 50 ms before stream response checking
  //to allow other http connection that may happen
  if (ml - dataObj._streamResetMillis > 50)
  {
    dataObj._streamResetMillis = ml;
    dataObj._streamDataChanged = false;
    memset(dataObj._data2, 0, FBDATA_DATA2_LENGTH);
    memset(dataObj._path2, 0, FBDATA_PATH2_LENGTH);
    dataObj._dataAvailable = false;
    dataObj._isStreamTimeout = false;

    delay(50);
    return true;
  }

  if (ml - dataObj._streamMillis > 50)
  {

    dataObj._streamMillis = ml;
    char *path = new char[strlen(dataObj._streamPath)];
    memset(path, 0, strlen(dataObj._streamPath));

    //Stream timeout
    if (dataObj._dataMillis > 0 && millis() - dataObj._dataMillis > KEEP_ALIVE_TIMEOUT)
    {
      dataObj._dataMillis = millis();
      dataObj._isStreamTimeout = true;
      strcpy(path, dataObj._streamPath);

      autoConnectWiFi();

      firebaseConnectStream(dataObj, path);
      return getServerResponse(dataObj);
    }

    //last connection was not close
    if (dataObj._httpConnected)
      return true;

    dataObj._httpConnected = true;
    resetFirebasedataFlag(dataObj);

    WiFiSSLClient client = dataObj._http.client;

    if (client.connected() && !dataObj._isStream)
      forceEndHTTP(dataObj);
    if (!client.connected())
    {
      strcpy(path, dataObj._streamPath);
      firebaseConnectStream(dataObj, path);
    }

    delete[] path;

    return getServerResponse(dataObj);
  }

  return true;
}

void Firebase_Arduino_WiFiNINA::forceEndHTTP(FirebaseData &dataObj)
{
  WiFiSSLClient client = dataObj._http.client;

  if (client.available() > 0)
  {
    client.flush();
    delay(50);
  }
  client.stop();
  delay(50);
}

void Firebase_Arduino_WiFiNINA::sendFirebaseRequest(FirebaseData &dataObj, const char *host, uint8_t method, const char *path, const char *auth, uint16_t payloadLength)
{

  uint8_t retryCount = 0;
  uint8_t maxRetry = 5;

  uint16_t headerSize = 400;
  char *request = new char[headerSize];
  memset(request, 0, headerSize);
 

  uint16_t numBufSize = 50;

  char *contentLength = new char[numBufSize];

  memset(contentLength, 0, numBufSize);

  char *num = new char[numBufSize];

  if (method == FirebaseMethod::STREAM)
  {
    strCopy_T(request, 22);
    dataObj._isStream = true;
  }
  else
  {

    if (method == FirebaseMethod::PUT || method == FirebaseMethod::PUT_SILENT)
      strCopy_T(request, 23);
    else if (method == FirebaseMethod::POST)
      strCopy_T(request, 24);
    else if (method == FirebaseMethod::GET)
      strCopy_T(request, 25);
    else if (method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT)
      strCopy_T(request, 26);
    else if (method == FirebaseMethod::DELETE)
      strCopy_T(request, 27);
    strCopy_T(request, 6);

    dataObj._isStream = false;
  }

  retryCount = 0;
  while (dataObj._http.http_sendRequest(request, "") != 0)
  {
      retryCount++;
      if (retryCount > maxRetry)
          break;
  }


  if (strlen(path) > 0)
  {
    if (path[0] != '/')
    {
      strCopy_T(request, 1, true, headerSize);
      dataObj._http.http_sendRequest(request, "");
    }
  }

  dataObj._http.http_sendRequest(path, "");

  memset(request, 0, headerSize);

  if (method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT)
    strCopy_T(request, 1);

  strCopy_T(request, 2);

  strcat(request, auth);

  if (method == FirebaseMethod::GET && strlen(dataObj.queryFilter._orderBy) > 0)
  {
    strCopy_T(request, 96);
    strcat(request, dataObj.queryFilter._orderBy);

    if (method == FirebaseMethod::GET && strlen(dataObj.queryFilter._limitToFirst) > 0)
    {
      strCopy_T(request, 97);
      strcat(request, dataObj.queryFilter._limitToFirst);
    }

    if (method == FirebaseMethod::GET && strlen(dataObj.queryFilter._limitToLast) > 0)
    {
      strCopy_T(request, 98);
      strcat(request, dataObj.queryFilter._limitToLast);
    }

    if (method == FirebaseMethod::GET && strlen(dataObj.queryFilter._startAt) > 0)
    {
      strCopy_T(request, 99);
      strcat(request, dataObj.queryFilter._startAt);
    }

    if (method == FirebaseMethod::GET && strlen(dataObj.queryFilter._endAt) > 0)
    {

      strCopy_T(request, 100);
      strcat(request, dataObj.queryFilter._endAt);
    }

    if (method == FirebaseMethod::GET && strlen(dataObj.queryFilter._equalTo) > 0)
    {
      strCopy_T(request, 101);
      strcat(request, dataObj.queryFilter._equalTo);
    }
  }

  if (method == FirebaseMethod::PUT_SILENT || method == FirebaseMethod::PATCH_SILENT)
    strCopy_T(request, 29);

  strCopy_T(request, 30);
  strCopy_T(request, 31);

  strcat(request, host);

  strCopy_T(request, 21);
  strCopy_T(request, 32);
  strCopy_T(request, 33);

  if (method == FirebaseMethod::STREAM)
  {
    strCopy_T(request, 34);
    strCopy_T(request, 35);
  }
  else
  {

    strCopy_T(request, 36);
    strCopy_T(request, 37);
  }

  if (method == FirebaseMethod::PUT || method == FirebaseMethod::PUT_SILENT || method == FirebaseMethod::POST || method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT)
  {

    strCopy_T(request, 12);
    itoa(payloadLength, contentLength, 10);
    strcat(request, contentLength);
  }

  strCopy_T(request, 21);
  strCopy_T(request, 21);

  dataObj._http.http_sendRequest(request, "");

  delete[] contentLength;
  delete[] num;
  delete[] request;
}

bool Firebase_Arduino_WiFiNINA::cancelCurrentResponse(FirebaseData &dataObj)
{
  forceEndHTTP(dataObj);
  dataObj._isStream = false;
  dataObj._streamDataChanged = false;
  dataObj._dataMillis = millis();
  memset(dataObj._data2, 0, FBDATA_DATA2_LENGTH);
  memset(dataObj._path2, 0, FBDATA_PATH2_LENGTH);
  dataObj._dataAvailable = false;
  dataObj._isStreamTimeout = false;
  dataObj._httpCode = HTTPC_ERROR_CONNECTION_REFUSED;
  return false;
}

void Firebase_Arduino_WiFiNINA::setDataType(FirebaseData &dataObj, const char *data)
{

  uint16_t len = 32;
  char *temp = new char[len];
  bool typeSet = false;

  if (strlen(data) > 0)
  {
    if (!typeSet && data[0] == '{')
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::JSON;
    }

    if (!typeSet)
    {

      if (strcmp(data, DEF_STR_106) == 0 || strcmp(data, DEF_STR_107) == 0)
      {
        typeSet = true;
        dataObj._dataType = FirebaseDataType::BOOLEAN;
      }
    }

    if (!typeSet && data[0] == '"')
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::STRING;
    }

    if (!typeSet && strpos(data, DEF_STR_4, 0) != -1)
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::FLOAT;
    }

    else if (!typeSet && strcmp(data, DEF_STR_19) == 0)
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::NULL_;
    }

    if (!typeSet)
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::INTEGER;
    }

    if (strcmp(data, DEF_STR_19) == 0 && strlen(dataObj.queryFilter._orderBy) == 0)
      memset(dataObj._data, 0, FBDATA_DATA_LENGTH);
    else if (strcmp(data, DEF_STR_19) == 0 && strlen(dataObj.queryFilter._orderBy) > 0)
      dataObj._dataType = FirebaseDataType::JSON;
  }
  else
  {
    dataObj._dataType = FirebaseDataType::NULL_;
  }

  dataObj._dataTypeNum = dataObj._dataType;

  delete[] temp;
}

void Firebase_Arduino_WiFiNINA::resetFirebasedataFlag(FirebaseData &dataObj)
{
  dataObj._bufferOverflow = false;
  dataObj._streamDataChanged = false;
  dataObj._streamPathChanged = false;
  dataObj._dataAvailable = false;
  memset(dataObj._pushName, 0, FBDATA_PUSH_NAME_LENGTH);
}
bool Firebase_Arduino_WiFiNINA::handleNetClientNotConnected(FirebaseData &dataObj)
{
  if (!dataObj._http.http_connected())
  {
    dataObj._contentLength = -1;
    dataObj._dataType = FirebaseDataType::NULL_;
    dataObj._httpCode = HTTPC_ERROR_NOT_CONNECTED;
    memset(dataObj._data, 0, FBDATA_DATA_LENGTH);
    memset(dataObj._path, 0, FBDATA_PATH_LENGTH);
    resetFirebasedataFlag(dataObj);
    return false;
  }
  return true;
}

void Firebase_Arduino_WiFiNINA::errorToString(int httpCode, char *buf)
{
  switch (httpCode)
  {
    case HTTPC_ERROR_CONNECTION_REFUSED:
      strCopy_T(buf, 39, true, sizeof(buf));
      return;
    case HTTPC_ERROR_SEND_HEADER_FAILED:
      strCopy_T(buf, 40, true, sizeof(buf));
      return;
    case HTTPC_ERROR_SEND_PAYLOAD_FAILED:
      strCopy_T(buf, 41, true, sizeof(buf));
      return;
    case HTTPC_ERROR_NOT_CONNECTED:
      strCopy_T(buf, 42, true, sizeof(buf));
      return;
    case HTTPC_ERROR_CONNECTION_LOST:
      strCopy_T(buf, 43, true, sizeof(buf));
      return;
    case HTTPC_ERROR_NO_HTTP_SERVER:
      strCopy_T(buf, 44, true, sizeof(buf));
      return;
    case _HTTP_CODE_BAD_REQUEST:
      strCopy_T(buf, 45, true, sizeof(buf));
      return;
    case _HTTP_CODE_NON_AUTHORITATIVE_INFORMATION:
      strCopy_T(buf, 46, true, sizeof(buf));
      return;
    case _HTTP_CODE_NO_CONTENT:
      strCopy_T(buf, 47, true, sizeof(buf));
      return;
    case _HTTP_CODE_MOVED_PERMANENTLY:
      strCopy_T(buf, 48, true, sizeof(buf));
      return;
    case _HTTP_CODE_USE_PROXY:
      strCopy_T(buf, 49, true, sizeof(buf));
      return;
    case _HTTP_CODE_TEMPORARY_REDIRECT:
      strCopy_T(buf, 50, true, sizeof(buf));
      return;
    case _HTTP_CODE_PERMANENT_REDIRECT:
      strCopy_T(buf, 51, true, sizeof(buf));
      return;
    case _HTTP_CODE_UNAUTHORIZED:
      strCopy_T(buf, 52, true, sizeof(buf));
      return;
    case _HTTP_CODE_FORBIDDEN:
      strCopy_T(buf, 53, true, sizeof(buf));
      return;
    case _HTTP_CODE_NOT_FOUND:
      strCopy_T(buf, 54, true, sizeof(buf));
      return;
    case _HTTP_CODE_METHOD_NOT_ALLOWED:
      strCopy_T(buf, 55, true, sizeof(buf));
      return;
    case _HTTP_CODE_NOT_ACCEPTABLE:
      strCopy_T(buf, 56, true, sizeof(buf));
      return;
    case _HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED:
      strCopy_T(buf, 57, true, sizeof(buf));
      return;
    case _HTTP_CODE_REQUEST_TIMEOUT:
      strCopy_T(buf, 58, true, sizeof(buf));
      return;
    case _HTTP_CODE_LENGTH_REQUIRED:
      strCopy_T(buf, 59, true, sizeof(buf));
      return;
    case _HTTP_CODE_TOO_MANY_REQUESTS:
      strCopy_T(buf, 60, true, sizeof(buf));
      return;
    case _HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE:
      strCopy_T(buf, 61, true, sizeof(buf));
      return;
    case _HTTP_CODE_INTERNAL_SERVER_ERROR:
      strCopy_T(buf, 62, true, sizeof(buf));
      return;
    case _HTTP_CODE_BAD_GATEWAY:
      strCopy_T(buf, 63, true, sizeof(buf));
      return;
    case _HTTP_CODE_SERVICE_UNAVAILABLE:
      strCopy_T(buf, 64, true, sizeof(buf));
      return;
    case _HTTP_CODE_GATEWAY_TIMEOUT:
      strCopy_T(buf, 65, true, sizeof(buf));
      return;
    case _HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED:
      strCopy_T(buf, 66, true, sizeof(buf));
      return;
    case _HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED:
      strCopy_T(buf, 67, true, sizeof(buf));
      return;
    case HTTPC_ERROR_READ_TIMEOUT:
      strCopy_T(buf, 68, true, sizeof(buf));
      return;
    case FIREBASE_ERROR_DATA_TYPE_MISMATCH:
      strCopy_T(buf, 69, true, sizeof(buf));
      return;
    case FIREBASE_ERROR_PATH_NOT_EXIST:
      strCopy_T(buf, 71, true, sizeof(buf));
      return;
    case HTTPC_ERROR_CONNECTION_INUSED:
      strCopy_T(buf, 94, true, sizeof(buf));
      return;
    case FIREBASE_ERROR_BUFFER_OVERFLOW:
      strCopy_T(buf, 68, true, sizeof(buf));
      return;
    default:
      return;
  }
}

void Firebase_Arduino_WiFiNINA::strCopy(char *buf, char *p, bool empty, uint16_t size)
{
  if (empty)
    memset(buf, 0, size);
  strcat(buf, p);
}

void Firebase_Arduino_WiFiNINA::strCopy_T(char *buf, uint16_t index, bool empty, uint16_t size)
{
  if (empty)
    memset(buf, 0, size);
  strcat_P(buf, (char *)pgm_read_word(&(string_table[index])));
}

void Firebase_Arduino_WiFiNINA::intBuf(char *buf, int val, bool empty, uint16_t size)
{
  if (empty)
    memset(buf, 0, size);
  itoa(val, buf, 10);
}

void Firebase_Arduino_WiFiNINA::floatBuf(char *buf, float val, bool empty, uint16_t size)
{
  if (empty)
    memset(buf, 0, size);
  dtostrf(val, 7, 6, buf);
}

void Firebase_Arduino_WiFiNINA::autoConnectWiFi()
{
  if (_reconnectWiFi && WiFi.status() != WL_CONNECTED && strlen(_ssid) > 0 && strlen(_psw) > 0)
  {
    uint8_t tryCount = 0;
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED)
    {
      tryCount++;
      status = WiFi.begin(_ssid, _psw);
      delay(500);
      if (tryCount > 10)
        break;
    }
  }
}

void Firebase_Arduino_WiFiNINA::strcat_c(char *str, char c)
{
  for (; *str; str++)
    ;
  *str++ = c;
  *str++ = 0;
}
int Firebase_Arduino_WiFiNINA::strpos(const char *haystack, const char *needle, int offset)
{
  char _haystack[strlen(haystack)];
  strncpy(_haystack, haystack + offset, strlen(haystack) - offset);
  char *p = strstr(_haystack, needle);
  if (p)
    return p - _haystack + offset;
  return -1;
}

int Firebase_Arduino_WiFiNINA::rstrpos(const char *haystack, const char *needle, int offset)
{
  char _haystack[strlen(haystack)];
  strncpy(_haystack, haystack + offset, strlen(haystack) - offset);
  char *p = rstrstr(_haystack, needle);
  if (p)
    return p - _haystack + offset;
  return -1;
}
char *Firebase_Arduino_WiFiNINA::rstrstr(const char *haystack, const char *needle)
{
  uint16_t needle_length = strlen(needle);
  const char *haystack_end = haystack + strlen(haystack) - needle_length;
  const char *p;
  uint16_t i;
  for (p = haystack_end; p >= haystack; --p)
  {
    for (i = 0; i < needle_length; ++i)
    {
      if (p[i] != needle[i])
        goto next;
    }
    return (char *)p;
next:;
  }
  return 0;
}

FirebaseData::FirebaseData() {}

FirebaseData ::~FirebaseData()
{
  end();
}

void FirebaseData::end()
{
  delete[] _path;
  delete[] _path2;
  delete[] _data;
  delete[] _data2;
  delete[] _streamPath;
  delete[] _pushName;
  delete[] _redirectURL;
  delete[] _firebaseError;
  delete[] _eventType;
}

WiFiSSLClient FirebaseData::getWiFiClient()
{
  return _http.client;
}

bool FirebaseData::pauseFirebase(bool pause)
{

  if (_http.http_connected() && pause != _pause)
  {
    if (_http.client.available() > 0)
    {
      _http.client.flush();
      delay(50);
    }
    _http.client.stop();
    delay(50);
    if (!_http.http_connected())
    {
      _pause = pause;
      return true;
    }
    return false;
  }
  else
  {
    _pause = pause;
    return true;
  }
}

String FirebaseData::dataType()
{
  char buf[50];
  if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::JSON)
    strCopy_T(buf, 74, true, 50);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::STRING)
    strCopy_T(buf, 75, true, 50);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::FLOAT)
    strCopy_T(buf, 76, true, 50);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::BOOLEAN)
    strCopy_T(buf, 105, true, 50);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::INTEGER)
    strCopy_T(buf, 77, true, 50);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::NULL_)
    strCopy_T(buf, 78, true, 50);
  return buf;
}

String FirebaseData::eventType()
{
  return _eventType;
}

String FirebaseData::streamPath()
{
  return _streamPath;
}

String FirebaseData::dataPath()
{
  return _path;
}

int FirebaseData::intData()
{
  if (strlen(_data) > 0 && (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::INTEGER || _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::FLOAT))
    return atoi(_data);
  else
    return 0;
}

float FirebaseData::floatData()
{
  if (strlen(_data) > 0 && (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::INTEGER || _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::FLOAT))
    return atof(_data);
  else
    return 0.0;
}

bool FirebaseData::boolData()
{
  bool res;
  char *str = new char[10];
  strCopy_T(str, 107, true, 10);
  if (strlen(_data) > 0 && _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::BOOLEAN)
    res = strcmp(_data, str) == 0;
  delete[] str;
  return res;
}

String FirebaseData::stringData()
{
  if (strlen(_data) > 0 && _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::STRING)
  {
    char *buf = new char[strlen(_data)];
    memset(buf, 0, strlen(_data));
    strncpy(buf, _data + 1, strlen(_data) - 2);
    return buf;
  }
  else
    return String();
}

String FirebaseData::jsonData()
{
  if (strlen(_data) > 0 && _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::JSON)
    return _data;
  else
    return String();
}

String FirebaseData::pushName()
{
  if (strlen(_pushName) > 0)
    return _pushName;
  else
    return String();
}

bool FirebaseData::isStream()
{
  return _isStream;
}

bool FirebaseData::httpConnected()
{
  return _httpConnected;
}

bool FirebaseData::streamTimeout()
{
  return _isStreamTimeout;
}

bool FirebaseData::dataAvailable()
{
  return _dataAvailable;
}

bool FirebaseData::streamAvailable()
{
  return !_httpConnected && _dataAvailable && _streamDataChanged;
}

bool FirebaseData::mismatchDataType()
{
  return _mismatchDataType;
}
bool FirebaseData::bufferOverflow()
{
  return _bufferOverflow;
}

String FirebaseData::errorReason()
{
  char *buf = new char[FBDATA_ERROR_LENGTH];
  memset(buf, 0, FBDATA_ERROR_LENGTH);

  if (_httpCode == _HTTP_CODE_OK)
  {
    if (_bufferOverflow)
      _httpCode = FIREBASE_ERROR_BUFFER_OVERFLOW;
    else if (_mismatchDataType)
      _httpCode = FIREBASE_ERROR_DATA_TYPE_MISMATCH;
    else if (_pathNotExist)
      _httpCode = FIREBASE_ERROR_PATH_NOT_EXIST;
  }

  Firebase.errorToString(_httpCode, buf);

  if (strlen(_firebaseError) > 0)
  {
    strcat(buf, ", ");
    strcat(buf, _firebaseError);
  }

  return buf;
}

int FirebaseData::httpCode()
{
  return _httpCode;
}

void FirebaseData::strCopy_T(char *buf, uint16_t index, bool empty, uint16_t size)
{
  if (empty)
    memset(buf, 0, size);
  strcat_P(buf, (char *)pgm_read_word(&(string_table[index])));
}

QueryFilter::QueryFilter()
{
  clearQuery();
}

QueryFilter::~QueryFilter()
{
  end();
}

void QueryFilter::end()
{
  if (_orderBy)
    delete[] _orderBy;

  if (_limitToFirst)
    delete[] _limitToFirst;

  if (_limitToFirst)
    delete[] _limitToFirst;

  if (_limitToLast)
    delete[] _limitToLast;

  if (_startAt)
    delete[] _startAt;

  if (_endAt)
    delete[] _endAt;

  if (_equalTo)
    delete[] _equalTo;
}

void QueryFilter::clearQuery()
{

  if (_orderBy)
    memset(_orderBy, 0, QUERY_ORDERBY_LENGTH);

  if (_limitToFirst)
    memset(_limitToFirst, 0, QUERY_LIMITTOFIRST_LENGTH);

  if (_limitToLast)
    memset(_limitToLast, 0, QUERY_LIMITTOLAST_LENGTH);

  if (_startAt)
    memset(_startAt, 0, QUERY_STARTAT_LENGTH);

  if (_endAt)
    memset(_endAt, 0, QUERY_ENDAT_LENGTH);

  if (_equalTo)
    memset(_equalTo, 0, QUERY_EQUALTO_LENGTH);

}

void QueryFilter::orderBy(const String &val)
{
  strCopy_T(_orderBy, 3, true, QUERY_ORDERBY_LENGTH);
  strcat(_orderBy, val.c_str());
  strCopy_T(_orderBy, 3);
}
void QueryFilter::limitToFirst(int val)
{
  memset(_limitToFirst, 0, QUERY_LIMITTOFIRST_LENGTH);
  itoa(val, _limitToFirst, 10);
}

void QueryFilter::limitToLast(int val)
{
  memset(_limitToFirst, 0, QUERY_LIMITTOLAST_LENGTH);
  itoa(val, _limitToLast, 10);
}

void QueryFilter::startAt(int val)
{
  memset(_startAt, 0, QUERY_STARTAT_LENGTH);
  itoa(val, _startAt, 10);
}

void QueryFilter::endAt(int val)
{
  memset(_endAt, 0, QUERY_ENDAT_LENGTH);
  itoa(val, _endAt, 10);
}

void QueryFilter::startAt(const String &val)
{
  strCopy_T(_startAt, 3, true, QUERY_STARTAT_LENGTH);
  strcat(_startAt, val.c_str());
  strCopy_T(_startAt, 3);
}

void QueryFilter::endAt(const String &val)
{
  strCopy_T(_endAt, 3, true, QUERY_ENDAT_LENGTH);
  strcat(_endAt, val.c_str());
  strCopy_T(_endAt, 3);
}

void QueryFilter::equalTo(int val)
{
  memset(_equalTo, 0, QUERY_EQUALTO_LENGTH);
  itoa(val, _equalTo, 10);
}

void QueryFilter::equalTo(const String &val)
{
  strCopy_T(_equalTo, 3, QUERY_EQUALTO_LENGTH);
  strcat(_equalTo, val.c_str());
  strCopy_T(_equalTo, 3);
}

void QueryFilter::strCopy_T(char *buf, uint16_t index, bool empty, uint16_t size)
{
  if (empty)
    memset(buf, 0, size);
  strcat_P(buf, (char *)pgm_read_word(&(string_table[index])));
}

Firebase_Arduino_WiFiNINA Firebase = Firebase_Arduino_WiFiNINA();

#endif
