/*
* Google's Firebase Realtime Database Arduino Library for ARM/AVR WIFI Dev Boards based on WiFiNINA library, version 1.1.2
* 
*
* This library required WiFiNINA Library to be installed.
* https://github.com/arduino-libraries/WiFiNINA
* 
* March 8, 2020
* 
* Feature Added:
* 
* Feature Fixed:
* - No stream event triggering bug when the child node value of parent node changes.
* - FirebaseJson and FirebaseJsonArray data are not assigned when reading from the stream.
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
  static const uint8_t TIMESTAMP = 10;
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
  _host =host;
  _auth = auth;
  _ssid = wifiSSID;
 _psw=wifiPSW;
  _port = FIEBASE_PORT;
}

void Firebase_Arduino_WiFiNINA::reconnectWiFi(bool reconnect)
{
  _reconnectWiFi = reconnect;
}

bool Firebase_Arduino_WiFiNINA::pushInt(FirebaseData &dataObj, const String &path, int intValue)
{

  char *buf = getIntString(intValue);
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::INTEGER, buf);
  delPtr(buf);
  return res;
}

bool Firebase_Arduino_WiFiNINA::pushFloat(FirebaseData &dataObj, const String &path, float floatValue)
{
  char *buf = getFloatString(floatValue);
  trimDouble(buf);
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::FLOAT, buf);
  delPtr(buf);
  return res;
}

bool Firebase_Arduino_WiFiNINA::pushBool(FirebaseData &dataObj, const String &path, bool boolValue)
{
  char *buf = getBoolString(boolValue);
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::BOOLEAN, buf);
  delPtr(buf);
  return res;
}

bool Firebase_Arduino_WiFiNINA::pushString(FirebaseData &dataObj, const String &path, const String &stringValue)
{
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::STRING, stringValue.c_str());
}

bool Firebase_Arduino_WiFiNINA::pushJSON(FirebaseData &dataObj, const String &path, const String &jsonString)
{
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::pushTimestamp(FirebaseData &dataObj, const String &path)
{
  char *buf = getPGMString(C_STR_113);
  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::POST, FirebaseDataType::TIMESTAMP, buf);
  delPtr(buf);
  return flag;
}

bool Firebase_Arduino_WiFiNINA::setInt(FirebaseData &dataObj, const String &path, int intValue)
{
  char *buf = getIntString(intValue);
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::INTEGER, buf);
  delPtr(buf);
  return res;
}

bool Firebase_Arduino_WiFiNINA::setFloat(FirebaseData &dataObj, const String &path, float floatValue)
{
  char *buf = getFloatString(floatValue);
  trimDouble(buf);
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::FLOAT, buf);
  delPtr(buf);
  return res;
}

bool Firebase_Arduino_WiFiNINA::setBool(FirebaseData &dataObj, const String &path, bool boolValue)
{
  char *buf = getBoolString(boolValue);
  bool res = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::BOOLEAN, buf);
  delPtr(buf);
  return res;
}

bool Firebase_Arduino_WiFiNINA::setString(FirebaseData &dataObj, const String &path, const String &stringValue)
{
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::STRING, stringValue.c_str());
}

bool Firebase_Arduino_WiFiNINA::setJSON(FirebaseData &dataObj, const String &path, const String &jsonString)
{
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::setTimestamp(FirebaseData &dataObj, const String &path)
{
  char *buf = getPGMString(C_STR_113);
  bool flag = sendRequest(dataObj, path.c_str(), FirebaseMethod::PUT, FirebaseDataType::TIMESTAMP, buf);
  delPtr(buf);
  return flag;
}

bool Firebase_Arduino_WiFiNINA::updateNode(FirebaseData &dataObj, const String path, const String jsonString)
{
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PATCH, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::updateNodeSilent(FirebaseData &dataObj, const String &path, const String &jsonString)
{
  return sendRequest(dataObj, path.c_str(), FirebaseMethod::PATCH_SILENT, FirebaseDataType::JSON, jsonString.c_str());
}

bool Firebase_Arduino_WiFiNINA::getInt(FirebaseData &dataObj, const String &path)
{
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
  if (query._orderBy !="")
  {
    dataObj.queryFilter._orderBy = query._orderBy;
    dataObj.queryFilter._limitToFirst=query._limitToFirst;
    dataObj.queryFilter._limitToLast=query._limitToLast;
    dataObj.queryFilter._startAt=query._startAt;
    dataObj.queryFilter._endAt=query._endAt;
    dataObj.queryFilter._equalTo=query._equalTo;
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
  dataObj._streamPath ="";
  forceEndHTTP(dataObj);
  flag = dataObj._http.http_connected();
  if (!flag)
  {
    dataObj._isStream = false;
    dataObj._streamStop = true;
  }
  return !flag;
}

bool Firebase_Arduino_WiFiNINA::apConnected(FirebaseData &dataObj)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
    return false;
  }
  return true;
}

int Firebase_Arduino_WiFiNINA::firebaseConnect(FirebaseData &dataObj, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{
   dataObj._firebaseError="";

   if (dataObj._pause)
    return 0;

  if (!apConnected(dataObj))
    return HTTPC_ERROR_CONNECTION_LOST;

  if (strlen(path) == 0 || _host.length() == 0 || _auth.length() == 0)
  {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return _HTTP_CODE_BAD_REQUEST;
  }

  bool httpConnected = false;
  int httpCode = HTTPC_ERROR_CONNECTION_REFUSED;

  //init the firebase data
  resetFirebasedataFlag(dataObj);
 
  dataObj._path="";

  if (method == FirebaseMethod::STREAM)
  {
    //stream path change? reset the current (keep alive) connection
    if (strcmp(path, dataObj._streamPath.c_str()) != 0)
      dataObj._streamPathChanged = true;
    if (!dataObj._isStream || dataObj._streamPathChanged)
    {
      if (dataObj._http.http_connected())
        forceEndHTTP(dataObj);
    }

    dataObj._streamPath = "";

    if (strlen(path) > 0)
      if (path[0] != '/')
        dataObj._streamPath = "/";

    dataObj._streamPath +=path;
  }
  else
  {
    //last requested method was stream?, reset the connection
    if (dataObj._isStream)
      forceEndHTTP(dataObj);

    if (strlen(path) > 0){
      if (path[0] != '/')
        dataObj._path = "/";
    }

    dataObj._path += path;
    dataObj._isStreamTimeout = false;
  }


  if (!reconnect(dataObj))
    return HTTPC_ERROR_CONNECTION_LOST;

  httpConnected = dataObj._http.http_begin(_host.c_str(), _port);

  if (!httpConnected)
  {
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_REFUSED;
    return HTTPC_ERROR_CONNECTION_REFUSED;
  }

  if (!reconnect(dataObj))
    return HTTPC_ERROR_CONNECTION_LOST;

  bool hasPayload =  (method != FirebaseMethod::GET && method != FirebaseMethod::STREAM && method != FirebaseMethod::DELETE);
  bool isString = dataType == FirebaseDataType::STRING && hasPayload;
  uint16_t len = isString? strlen(payload) + 2 : strlen(payload);
 
  String req;

  buildFirebaseRequest(req, dataObj, _host.c_str(), method, path, _auth.c_str(), len);

  if(isString)
  {
   char *t = getPGMString( C_STR_3);
   req+=t;
   delPtr(t);
  }
    
  req += payload;

  if(isString)
  {
   char *t = getPGMString( C_STR_3);
   req+=t;
   delPtr(t);
  }



  httpCode = dataObj._http.http_sendRequest(req.c_str(),"");


  if (method == FirebaseMethod::PATCH_SILENT)
    dataObj._isSilentResponse = true;
  
  return httpCode;
  
}

bool Firebase_Arduino_WiFiNINA::reconnect(FirebaseData &dataObj)
{
  bool flag = reconnect();
  if (!flag)
    dataObj._httpCode = HTTPC_ERROR_CONNECTION_LOST;
  return flag;
}

bool Firebase_Arduino_WiFiNINA::reconnect()
{
  if (_reconnectWiFi && WiFi.status() != WL_CONNECTED)
  {
    if (_lastReconnectMillis == 0)
    {
      autoConnectWiFi();
      _lastReconnectMillis = millis();
    }
    if (WiFi.status() != WL_CONNECTED)
    {
      if (millis() - _lastReconnectMillis > _reconnectTimeout)
        _lastReconnectMillis = 0;
      return false;
    }
    else
    {
      _lastReconnectMillis = 0;
    }
  }
  return WiFi.status() == WL_CONNECTED;
}

void Firebase_Arduino_WiFiNINA::autoConnectWiFi()
{
  if (_reconnectWiFi && WiFi.status() != WL_CONNECTED && _ssid !=""  && _psw !="")
  {
    uint8_t tryCount = 0;
    int status = WL_IDLE_STATUS;
    while (status != WL_CONNECTED)
    {
      tryCount++;
      status = WiFi.begin(_ssid.c_str(), _psw.c_str());
      delay(250);
      if (tryCount > 20)
        break;
    }
  }
}

bool Firebase_Arduino_WiFiNINA::sendRequest(FirebaseData &dataObj, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{
  

  bool flag = false;
  dataObj._firebaseError= "";

  if (dataObj._pause)
    return true;

  if (strlen(path) == 0 || _host == "" || _auth =="")
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

        if (dataObj._http.http_connected())
        {

          forceEndHTTP(dataObj);
          if (dataObj._http.http_connected())
            if (!dataObj._isStream)
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
  dataObj._redirectURL ="";
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
   
      dataObj._path = path;
      flag = getServerResponse(dataObj);
      dataObj._dataAvailable = dataObj._data !="";
    }

    if (!flag)
      forceEndHTTP(dataObj);
  }
  else
  {
    //can't establish connection
    dataObj._httpCode = httpCode;
    dataObj._httpConnected = false;
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

  if (!dataObj._http.http_connected() || dataObj._interruptRequest)
    return cancelCurrentResponse(dataObj);
  if (!handleNetClientNotConnected(dataObj) || !dataObj._httpConnected)
    return false;

  bool flag = false;

  dataObj._data="";

  char *lineBuf = newPtr(FIREBASE_RESPONSE_SIZE);
  char *tmp = nullptr;
  char *tmp2 = nullptr;
  char *eventType = newPtr(30);

  char c;
  int p1, p2;
  bool isStream = false;
  dataObj._httpCode = -1000;
  dataObj._contentLength = -1;
  dataObj._bufferOverflow = false;
  dataObj._pushName ="";

  bool hasEvent = false;
  bool hasEventData = false;
  bool payLoadBegin = false;

  unsigned long dataTime = millis();

  uint16_t lfCount = 0;
  uint16_t charPos = 0;

  if (!dataObj._isStream)
    while (dataObj._http.client.connected() && !dataObj._http.client.available() && millis() - dataTime < dataObj._http.netClientTimeout)
      delay(0);

  dataTime = millis();

  if (dataObj._http.client.connected() && dataObj._http.client.available())
  {
    while (dataObj._http.client.available())
    {

      if (dataObj._interruptRequest)
        return cancelCurrentResponse(dataObj);

      c = dataObj._http.client.read();

      if (payLoadBegin && dataObj._contentLength > 0)
      {
        if (charPos % 128 == 0)
        {
          dataTime = millis();
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
          tmp = getPGMString(C_STR_5);
          p1 = strpos(lineBuf, tmp, 0);
          delPtr(tmp);

          if (p1 != -1)
          {
            tmp = newPtr(strlen(lineBuf) - p1 - 9);
            strncpy(tmp, lineBuf + p1 + 9, strlen(lineBuf) - p1 - 9);
            dataObj._httpCode = atoi(tmp);
            delPtr(tmp);
          }

          if (dataObj._httpCode == _HTTP_CODE_TEMPORARY_REDIRECT)
          {
            tmp = getPGMString(C_STR_95);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {
              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_95));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_95), strlen(lineBuf) - p1 - strlen_P(C_STR_95));
              dataObj._redirectURL = tmp;
              delPtr(tmp);
              int res = firebaseConnect(dataObj, dataObj._redirectURL.c_str(), dataObj._r_method, dataObj._r_dataType, "");

              if (res == 0)
                goto EXIT_4;

              goto EXIT_3;
            }
          }

          if (dataObj._httpCode == _HTTP_CODE_NO_CONTENT)
            continue;

            tmp = getPGMString(C_STR_7);
            bool  flag = strpos(lineBuf, tmp, 0) != -1;
            delPtr(tmp);
           
          if (flag)
          {
            tmp = getPGMString(C_STR_102);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {
              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_102));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_102) + 1, strlen(lineBuf) - p1 - strlen_P(C_STR_102));
              tmp2 = newPtr(strlen(tmp) - 1);
              strncpy(tmp2, tmp, strlen(tmp) - 1);
              dataObj._firebaseError = tmp2;
              delPtr(tmp2);
              delPtr(tmp);
            }

            tmp = getPGMString(C_STR_8);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {
              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_8));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_8), strlen(lineBuf) - p1 - strlen_P(C_STR_8));

              tmp2 = getPGMString(C_STR_9);
              if (strcmp(tmp, tmp2) == 0)
              {
                isStream = true;
              }
                
              delPtr(tmp2);
              delPtr(tmp);
              
            }

            tmp = getPGMString(C_STR_10);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {
              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_10));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_10), strlen(lineBuf) - p1 - strlen_P(C_STR_10));
              tmp2 = getPGMString(C_STR_11);
              if (strcmp(tmp, tmp2) == 0)
                dataObj._keepAlive = true;
              else
                dataObj._keepAlive = false;
              delPtr(tmp2);
              delPtr(tmp);
            }

            tmp = getPGMString(C_STR_12);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {

              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_12));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_12), strlen(lineBuf) - p1 - strlen_P(C_STR_12));
              dataObj._contentLength = atoi(tmp);
              delPtr(tmp);
            }

            tmp = getPGMString(C_STR_13);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {
              eventType = newPtr(eventType, strlen(lineBuf) - p1 - strlen_P(C_STR_13));
              strncpy(eventType, lineBuf + p1 + strlen_P(C_STR_13), strlen(lineBuf) - p1 - strlen_P(C_STR_13));
              hasEvent = true;
              isStream = true;
              dataObj._httpCode = _HTTP_CODE_OK;
              memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
            }

            tmp = getPGMString(C_STR_14);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1)
            {
              hasEventData = true;
              isStream = true;
              dataObj._httpCode = _HTTP_CODE_OK;
              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_14));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_14), strlen(lineBuf) - p1 - strlen_P(C_STR_14));
              memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
              strcpy(lineBuf, tmp);
              delPtr(tmp);
              break;
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
          tmp = getPGMString(C_STR_15);
          m |= strpos(eventType, tmp, 0) != -1;
          delPtr(tmp);

          tmp = getPGMString(C_STR_16);
          m |= strpos(eventType, tmp, 0) != -1;
          delPtr(tmp);

          if (m)
          {
            dataObj._eventType = eventType;
            bool samePath = true;

            //Parses json response for path
            tmp = getPGMString(C_STR_17);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1 && p1 < FIREBASE_RESPONSE_SIZE)
            {
              tmp = getPGMString(C_STR_3);
              p2 = strpos(lineBuf, tmp, p1 + strlen_P(C_STR_17));
              delPtr(tmp);
              if (p2 != -1)
              {
                tmp = newPtr(p2 - p1 - strlen_P(C_STR_17));
                strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_17), p2 - p1 - strlen_P(C_STR_17));
                samePath = strcmp(tmp, dataObj._path.c_str()) == 0;
                dataObj._path = tmp;
                delPtr(tmp);
              }
            }

            //Parses json response for data
            tmp = getPGMString(C_STR_18);
            p1 = strpos(lineBuf, tmp, 0);
            delPtr(tmp);
            if (p1 != -1 && p1 < FIREBASE_RESPONSE_SIZE)
            {
              tmp = newPtr(strlen(lineBuf) - p1 - strlen_P(C_STR_18) - 1);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_18), strlen(lineBuf) - p1 - strlen_P(C_STR_18) - 1);
              dataObj._data = tmp;
              delPtr(tmp);

              setDataType(dataObj, dataObj._data.c_str());
              bool sameData = dataObj._data == dataObj._data2;

              //Any stream update?
              if (!samePath || (samePath && !sameData && !dataObj._streamPathChanged))
              {
                dataObj._streamDataChanged = true;
                dataObj._data2 = dataObj._data;
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
            tmp = getPGMString(C_STR_11);
            if (strcmp(eventType, tmp) == 0)
            {
              dataObj._isStreamTimeout = false;
              dataObj._dataMillis = millis();

            }
            delPtr(tmp);

            //Firebase cancel and auth_revoked events
            tmp = getPGMString(C_STR_109);
            bool m2 = strcmp(eventType, tmp) == 0;
            delPtr(tmp);
            tmp = getPGMString(C_STR_110);
            m2 |= strcmp(eventType, tmp) == 0;
            delPtr(tmp);

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
        dataObj._data = lineBuf;
        setDataType(dataObj, lineBuf);

        //Push (POST) data?
        if (dataObj._r_method == FirebaseMethod::POST)
        {
          tmp = getPGMString(C_STR_20);
          p1 = strpos(lineBuf, tmp, 0);
          delPtr(tmp);
          if (p1 != -1)
          {
            tmp = getPGMString(C_STR_3);
            p2 = strpos(lineBuf, tmp, p1 + strlen_P(C_STR_20));
            delPtr(tmp);
            if (p2 != -1)
            {
              tmp =newPtr(p2 - p1 - strlen_P(C_STR_20));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_20), p2 - p1 - strlen_P(C_STR_20));
              dataObj._pushName=tmp;
              delPtr(tmp);
              dataObj._dataType = 0;
              dataObj._dataType2 = 0;
              dataObj._data ="";
            }
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
          dataObj._path="";
          dataObj._data="";
          dataObj._pushName="";
          dataObj._dataType = 0;
          dataObj._dataType2 = 0;
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

  if (dataObj._httpCode == -1000 && dataObj._r_method != FirebaseMethod::STREAM)
    flag = true;

  dataObj._httpConnected = false;
  dataObj._streamMillis = millis();
  delPtr(lineBuf);
  delPtr(eventType);

  return flag;

EXIT_2:

  delPtr(lineBuf);
  delPtr(eventType);

  if (dataObj._httpCode == HTTPC_ERROR_READ_TIMEOUT)
    return false;
  return dataObj._httpCode == _HTTP_CODE_OK || dataObj._httpCode == -1000;

EXIT_3:

  delPtr(lineBuf);
  delPtr(eventType);
  return true;

EXIT_4:
  delPtr(lineBuf);
  delPtr(eventType);
  return getServerResponse(dataObj);
}

bool Firebase_Arduino_WiFiNINA::firebaseConnectStream(FirebaseData &dataObj, const char *path)
{

  if (dataObj._pause)
    return true;

  dataObj._streamStop = false;

  if (!dataObj._isStreamTimeout && dataObj._isStream && strcmp(path, dataObj._streamPath.c_str())==0)
    return true;

  if (strlen(path) == 0 || _host =="" || _auth =="")
  {
    dataObj._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }


  bool flag;
  flag = dataObj._streamPath == "";
  flag |= firebaseConnect(dataObj, path, FirebaseMethod::STREAM, FirebaseDataType::STRING, "") == 0;
  dataObj._dataMillis = millis();
  return flag;
}

bool Firebase_Arduino_WiFiNINA::getServerStreamResponse(FirebaseData &dataObj)
{
   bool res = false;

  if (dataObj._pause || dataObj._streamStop)
    return true;

  unsigned long ml = millis();
  if (dataObj._streamMillis == 0)
    dataObj._streamMillis = ml;
  if (dataObj._streamResetMillis == 0)
    dataObj._streamResetMillis = ml;


  if (ml - dataObj._streamMillis > 0)
  {

    dataObj._streamMillis = ml;
    String path = "";
    
    //Stream timeout
    if (dataObj._dataMillis > 0 && millis() - dataObj._dataMillis > KEEP_ALIVE_TIMEOUT)
    {
      dataObj._dataMillis = millis();
      dataObj._isStreamTimeout = true;
      path = dataObj._streamPath;

      autoConnectWiFi();

      firebaseConnectStream(dataObj, path.c_str());
      res = getServerResponse(dataObj);

      if (!dataObj._httpConnected)
        dataObj._httpCode = HTTPC_ERROR_NOT_CONNECTED;
      return res;
    }

    //last connection was not close
    if (dataObj._httpConnected)
      return true;

    dataObj._httpConnected = true;
    resetFirebasedataFlag(dataObj);

    if (dataObj._http.client.connected() && !dataObj._isStream)
      forceEndHTTP(dataObj);

    if (!dataObj._http.client.connected())
    {
      path = dataObj._streamPath;
      firebaseConnectStream(dataObj, path.c_str());
    }

    res = getServerResponse(dataObj);

    if (!dataObj._httpConnected)
      dataObj._httpCode = HTTPC_ERROR_NOT_CONNECTED;

    return res;
  }

  return true;
}

void Firebase_Arduino_WiFiNINA::forceEndHTTP(FirebaseData &dataObj)
{
  if (dataObj._http.client.available() > 0)
  {
    dataObj._http.client.read();
  }
  dataObj._http.client.stop();
}



void Firebase_Arduino_WiFiNINA::delPtr(char * p)
{
  if (p != nullptr)
    delete[] p;
    p = nullptr;
}

char *Firebase_Arduino_WiFiNINA::newPtr(size_t len)
{
  char *p = new char[len + 1];
  memset(p, 0, len + 1);
  return p;
}

char *Firebase_Arduino_WiFiNINA::newPtr(char *p, size_t len)
{
  delPtr(p);
  p = newPtr(len);
  return p;
}

char *Firebase_Arduino_WiFiNINA::newPtr(char *p, size_t len, char *d)
{
  delPtr(p);
  p = newPtr(len);
  strcpy(p, d);
  return p;
}


char *Firebase_Arduino_WiFiNINA::getPGMString(PGM_P pgm)
{
  size_t len = strlen_P(pgm) + 1;
  char *buf = newPtr(len);
  strcat_P(buf, pgm);
  return buf;
}

void Firebase_Arduino_WiFiNINA::getPGMString(char *buf, PGM_P pgm, bool empty)
{
  if (empty)
    memset(buf, 0, strlen(buf));
  strcat_P(buf, pgm);
}

char *Firebase_Arduino_WiFiNINA::getFloatString(float value)
{
  char *buf = newPtr(36);
  dtostrf(value, 7, 6, buf);
  return buf;
}

char *Firebase_Arduino_WiFiNINA::getIntString(int value)
{
  char *buf = newPtr(36);
  itoa(value, buf, 10);
  return buf;
}

char *Firebase_Arduino_WiFiNINA::getBoolString(bool value)
{
  char *buf = nullptr;
  if (value)
    buf = getPGMString(C_STR_107);
  else
    buf = getPGMString(C_STR_106);
  return buf;
}

void Firebase_Arduino_WiFiNINA::trimDouble(char *buf)
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

void Firebase_Arduino_WiFiNINA::buildFirebaseRequest(String &req, FirebaseData &dataObj, const char *host, uint8_t method, const char *path, const char *auth, int payloadLength)
{
  char *buf = newPtr(400);
  if (method == FirebaseMethod::STREAM)
  {
    getPGMString(buf, C_STR_22);
    dataObj._isStream = true;
  }
  else
  {
    if (method == FirebaseMethod::PUT || method == FirebaseMethod::PUT_SILENT)
      getPGMString(buf, C_STR_23);
    else if (method == FirebaseMethod::POST)
      getPGMString(buf, C_STR_24);
    else if (method == FirebaseMethod::GET)
      getPGMString(buf, C_STR_25);
    else if (method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT)
      getPGMString(buf, C_STR_26);
    else if (method == FirebaseMethod::DELETE)
      getPGMString(buf, C_STR_27);
    getPGMString(buf, C_STR_6);

    dataObj._isStream = false;
  }

  if (strlen(path) > 0)
  {
    if (path[0] != '/')
      getPGMString(buf, C_STR_1);
  }

  strcat(buf,path);

  if (method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT)
    getPGMString(buf, C_STR_1);

  getPGMString(buf, C_STR_2);

  strcat(buf, auth);

  if (method == FirebaseMethod::GET && dataObj.queryFilter._orderBy !="")
  {
    getPGMString(buf, C_STR_96);
    strcat(buf, dataObj.queryFilter._orderBy.c_str());

    if (method == FirebaseMethod::GET && dataObj.queryFilter._limitToFirst !="")
    {
      getPGMString(buf, C_STR_97);
      strcat(buf, dataObj.queryFilter._limitToFirst.c_str());
    }

    if (method == FirebaseMethod::GET && dataObj.queryFilter._limitToLast !="")
    {
      getPGMString(buf, C_STR_98);
      strcat(buf, dataObj.queryFilter._limitToLast.c_str());
    }

    if (method == FirebaseMethod::GET && dataObj.queryFilter._startAt != "")
    {
      getPGMString(buf, C_STR_99);
      strcat(buf, dataObj.queryFilter._startAt.c_str());
    }

    if (method == FirebaseMethod::GET && dataObj.queryFilter._endAt !="")
    {

      getPGMString(buf, C_STR_100);
      strcat(buf, dataObj.queryFilter._endAt.c_str());
    }

    if (method == FirebaseMethod::GET && dataObj.queryFilter._equalTo !="")
    {
      getPGMString(buf, C_STR_101);
      strcat(buf, dataObj.queryFilter._equalTo.c_str());
    }
  }

  if (method == FirebaseMethod::PUT_SILENT || method == FirebaseMethod::PATCH_SILENT)
    getPGMString(buf, C_STR_29);

  getPGMString(buf, C_STR_30);
  getPGMString(buf, C_STR_31);

  strcat(buf, host);

  getPGMString(buf, C_STR_21);
  getPGMString(buf, C_STR_32);

  if (method == FirebaseMethod::STREAM)
  {
    getPGMString(buf, C_STR_34);
    getPGMString(buf, C_STR_35);
  }
  else
  {
    getPGMString(buf, C_STR_36);
    getPGMString(buf, C_STR_37);
  }

    getPGMString(buf, C_STR_38);

  if (method == FirebaseMethod::PUT || method == FirebaseMethod::PUT_SILENT || method == FirebaseMethod::POST || method == FirebaseMethod::PATCH || method == FirebaseMethod::PATCH_SILENT)
  {

    getPGMString(buf, C_STR_12);
    char *t = getIntString(payloadLength);
    strcat(buf, t);
    delete[] t;
  }

  getPGMString(buf, C_STR_21);
  getPGMString(buf, C_STR_21);

  req = buf;
  delete[] buf;

}


bool Firebase_Arduino_WiFiNINA::cancelCurrentResponse(FirebaseData &dataObj)
{
  forceEndHTTP(dataObj);
  dataObj._isStream = false;
  dataObj._streamDataChanged = false;
  dataObj._dataMillis = millis();
  dataObj._data2 = "";
  dataObj._dataAvailable = false;
  dataObj._isStreamTimeout = false;
  dataObj._httpCode = HTTPC_ERROR_CONNECTION_REFUSED;
  return false;
}


void Firebase_Arduino_WiFiNINA::setDataType(FirebaseData &dataObj, const char *data)
{

  bool typeSet = false;

  if (strlen(data) > 0)
  {
    if (!typeSet && data[0] == '{')
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::JSON;
    }

    char *t = getPGMString(C_STR_106);
    char *u = getPGMString(C_STR_107);

    if (!typeSet)
    {
      if (strcmp(data, t) == 0 || strcmp(data, u) == 0)
      {
        typeSet = true;
        dataObj._dataType = FirebaseDataType::BOOLEAN;
      }
    }
    delPtr(t);
    delPtr(u);

    if (!typeSet && data[0] == '"')
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::STRING;
    }

    t = getPGMString(C_STR_4);
    u = getPGMString(C_STR_19);

    if (!typeSet && strpos(data, t, 0) != -1)
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::FLOAT;
    }
    else if (!typeSet && strcmp(data, u) == 0)
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::NULL_;
    }

    if (!typeSet)
    {
      typeSet = true;
      dataObj._dataType = FirebaseDataType::INTEGER;
    }

    if (strcmp(data, u) == 0 && dataObj.queryFilter._orderBy == "")
    {
      dataObj._data="";
    }
    else if (strcmp(data, u) == 0 && dataObj.queryFilter._orderBy =="")
      dataObj._dataType = FirebaseDataType::JSON;

    delPtr(t);
    delPtr(u);
  }
  else
  {
    dataObj._dataType = FirebaseDataType::NULL_;
  }

  dataObj._dataTypeNum = dataObj._dataType;
}

void Firebase_Arduino_WiFiNINA::resetFirebasedataFlag(FirebaseData &dataObj)
{
  dataObj._bufferOverflow = false;
  dataObj._streamDataChanged = false;
  dataObj._streamPathChanged = false;
  dataObj._dataAvailable = false;
  dataObj._pushName = "";
}
bool Firebase_Arduino_WiFiNINA::handleNetClientNotConnected(FirebaseData &dataObj)
{
  if (!dataObj._http.http_connected())
  {
    dataObj._contentLength = -1;
    dataObj._dataType = FirebaseDataType::NULL_;
    dataObj._httpCode = HTTPC_ERROR_NOT_CONNECTED;
    dataObj._data ="";
    dataObj._path ="";
    resetFirebasedataFlag(dataObj);
    return false;
  }
  return true;
}

char * Firebase_Arduino_WiFiNINA::errorToString(int httpCode)
{
  char *buf = nullptr;
  switch (httpCode)
  {
  case HTTPC_ERROR_CONNECTION_REFUSED:
    buf = getPGMString(C_STR_39);
    break;
  case HTTPC_ERROR_SEND_HEADER_FAILED:
    buf = getPGMString(C_STR_40);
    break;
  case HTTPC_ERROR_SEND_PAYLOAD_FAILED:
    buf = getPGMString(C_STR_41);
    break;
  case HTTPC_ERROR_NOT_CONNECTED:
    buf = getPGMString(C_STR_42);
    break;
  case HTTPC_ERROR_CONNECTION_LOST:
    buf = getPGMString(C_STR_43);
    break;
  case HTTPC_ERROR_NO_HTTP_SERVER:
    buf = getPGMString(C_STR_44);
    break;
  case _HTTP_CODE_BAD_REQUEST:
    buf = getPGMString(C_STR_45);
    break;
  case _HTTP_CODE_NON_AUTHORITATIVE_INFORMATION:
    buf = getPGMString(C_STR_46);
    break;
  case _HTTP_CODE_NO_CONTENT:
    buf = getPGMString(C_STR_47);
    break;
  case _HTTP_CODE_MOVED_PERMANENTLY:
    buf = getPGMString(C_STR_48);
    break;
  case _HTTP_CODE_USE_PROXY:
    buf = getPGMString(C_STR_49);
    break;
  case _HTTP_CODE_TEMPORARY_REDIRECT:
    buf = getPGMString(C_STR_50);
    break;
  case _HTTP_CODE_PERMANENT_REDIRECT:
    buf = getPGMString(C_STR_51);
    break;
  case _HTTP_CODE_UNAUTHORIZED:
    buf = getPGMString(C_STR_52);
    break;
  case _HTTP_CODE_FORBIDDEN:
    buf = getPGMString(C_STR_53);
    break;
  case _HTTP_CODE_NOT_FOUND:
    buf = getPGMString(C_STR_54);
    break;
  case _HTTP_CODE_METHOD_NOT_ALLOWED:
    buf = getPGMString(C_STR_55);
    break;
  case _HTTP_CODE_NOT_ACCEPTABLE:
    buf = getPGMString(C_STR_56);
    break;
  case _HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED:
    buf = getPGMString(C_STR_57);
    break;
  case _HTTP_CODE_REQUEST_TIMEOUT:
    buf = getPGMString(C_STR_58);
    break;
  case _HTTP_CODE_LENGTH_REQUIRED:
    buf = getPGMString(C_STR_59);
    break;
  case _HTTP_CODE_TOO_MANY_REQUESTS:
    buf = getPGMString(C_STR_60);
    break;
  case _HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE:
    buf = getPGMString(C_STR_61);
    break;
  case _HTTP_CODE_INTERNAL_SERVER_ERROR:
    buf = getPGMString(C_STR_62);
    break;
  case _HTTP_CODE_BAD_GATEWAY:
    buf = getPGMString(C_STR_63);
    break;
  case _HTTP_CODE_SERVICE_UNAVAILABLE:
    buf = getPGMString(C_STR_64);
    break;
  case _HTTP_CODE_GATEWAY_TIMEOUT:
    buf = getPGMString(C_STR_65);
    break;
  case _HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED:
    buf = getPGMString(C_STR_66);
    break;
  case _HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED:
    buf = getPGMString(C_STR_67);
    break;
  case HTTPC_ERROR_READ_TIMEOUT:
    buf = getPGMString(C_STR_68);
    break;
  case FIREBASE_ERROR_DATA_TYPE_MISMATCH:
    buf = getPGMString(C_STR_69);
    break;
  case FIREBASE_ERROR_PATH_NOT_EXIST:
    buf = getPGMString(C_STR_71);
    break;
  case HTTPC_ERROR_CONNECTION_INUSED:
    buf = getPGMString(C_STR_94);
    break;
  case FIREBASE_ERROR_BUFFER_OVERFLOW:
    buf = getPGMString(C_STR_68);
    break;
  default:
    break;
  }
  return buf;
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
  size_t len = strlen(haystack);
  size_t len2 = strlen(needle);
  if (len == 0 || len < len2 || len2 == 0)
    return -1;
  char *_haystack = newPtr(len);
  strncpy(_haystack, haystack + offset, len - offset);
  char *p = strstr(_haystack, needle);
  int r = -1;
  if (p)
    r = p - _haystack + offset;
  delPtr(_haystack);
  return r;
}

int Firebase_Arduino_WiFiNINA::rstrpos(const char *haystack, const char *needle, int offset)
{
  size_t len = strlen(haystack);
  size_t len2 = strlen(needle);
  if (len == 0 || len < len2 || len2 == 0)
    return -1;
  char *_haystack = newPtr(len);
  strncpy(_haystack, haystack + offset, len - offset);
  char *p = rstrstr(_haystack, needle);
  int r = -1;
  if (p)
    r = p - _haystack + offset;
  delPtr(_haystack);
  return r;
}

char *Firebase_Arduino_WiFiNINA::rstrstr(const char *haystack, const char *needle)
{
  size_t needle_length = strlen(needle);
  const char *haystack_end = haystack + strlen(haystack) - needle_length;
  const char *p;
  size_t i;
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
  _path="";
  _data="";
  _data2="";
  _streamPath="";
  _pushName="";
  _redirectURL="";
  _firebaseError="";
  _eventType="";
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
      _http.client.read();
    }
    _http.client.stop();
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
  char *buf =nullptr;
  if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::JSON)
    buf = Firebase.getPGMString(C_STR_74);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::STRING)
    buf = Firebase.getPGMString(C_STR_75);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::FLOAT)
    buf = Firebase.getPGMString(C_STR_76);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::BOOLEAN)
    buf = Firebase.getPGMString(C_STR_105);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::INTEGER)
    buf = Firebase.getPGMString(C_STR_77);
  else if (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::NULL_)
    buf = Firebase.getPGMString(C_STR_78);
  String res = buf;
  Firebase.delPtr(buf);
  return res;
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
  if (_data !="" && (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::INTEGER || _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::FLOAT))
    return atoi(_data.c_str());
  else
    return 0;
}

float FirebaseData::floatData()
{
  if (_data !=""  && (_dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::INTEGER || _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::FLOAT))
    return atof(_data.c_str());
  else
    return 0.0;
}

bool FirebaseData::boolData()
{
  bool res = false;
  if (_data !="" && _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::BOOLEAN)
    res = _data == "true";
  return res;
}

String FirebaseData::stringData()
{
  if (_data !="" && _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::STRING)
  {
    return _data.substring(1, _data.length() -1);
  }
  else
    return String();
}

String FirebaseData::jsonData()
{
  if (_data !="" && _dataType == Firebase_Arduino_WiFiNINA::FirebaseDataType::JSON)
    return _data;
  else
    return String();
}

String FirebaseData::pushName()
{
    return _pushName;
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

String FirebaseData::payload()
{
  return _data;
}

String FirebaseData::errorReason()
{
 
  if (_httpCode == _HTTP_CODE_OK)
  {
    if (_bufferOverflow)
      _httpCode = FIREBASE_ERROR_BUFFER_OVERFLOW;
    else if (_mismatchDataType)
      _httpCode = FIREBASE_ERROR_DATA_TYPE_MISMATCH;
    else if (_pathNotExist)
      _httpCode = FIREBASE_ERROR_PATH_NOT_EXIST;
  }

  char *e = Firebase.errorToString(_httpCode);
  String res = e;
  delete[] e;
  if (_firebaseError !="")
  {
    res += ", ";
    res += _firebaseError;
  }
  return res;
}

int FirebaseData::httpCode()
{
  return _httpCode;
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
 clearQuery();
}

void QueryFilter::clearQuery()
{
  _orderBy="";
  _limitToFirst="";
  _limitToLast="";
  _limitToLast="";
  _startAt="";
  _endAt="";
  _equalTo="";
}

void QueryFilter::orderBy(const String &val)
{
  _orderBy = "\"";
  _orderBy += val;
  _orderBy += "\"";
}
void QueryFilter::limitToFirst(int val)
{
  char *t = Firebase.getIntString(val);
  _limitToFirst = t;
  Firebase.delPtr(t);
}

void QueryFilter::limitToLast(int val)
{
  char *t = Firebase.getIntString(val);
  _limitToLast = t;
  Firebase.delPtr(t);
}

void QueryFilter::startAt(int val)
{
  char *t = Firebase.getIntString(val);
  _startAt = t;
  Firebase.delPtr(t);
}

void QueryFilter::endAt(int val)
{
 char *t = Firebase.getIntString(val);
  _endAt = t;
  Firebase.delPtr(t);
}

void QueryFilter::startAt(const String &val)
{
  _startAt = "\"";
  _startAt += val;
  _startAt += "\"";
}

void QueryFilter::endAt(const String &val)
{
  _endAt = "\"";
  _endAt += val;
  _endAt += "\"";
}

void QueryFilter::equalTo(int val)
{
 char *t = Firebase.getIntString(val);
  _equalTo = t;
  Firebase.delPtr(t);
}

void QueryFilter::equalTo(const String &val)
{
  _equalTo = "\"";
  _equalTo += val;
  _equalTo += "\"";
}


Firebase_Arduino_WiFiNINA Firebase = Firebase_Arduino_WiFiNINA();

#endif
