/**
 * Firebase.cpp, version 1.0.1
 * 
 * 
 * Created: October 20, 2021
 * 
 * This library provides ARM/AVR WIFI Development Boards to perform REST API by GET PUT, POST, PATCH, DELETE data from/to with Google's Firebase database using get, set, update
 * and delete calls.
 * 
 * The library was test and work well with ESP32s based module and add support for multiple stream event path.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2021 K. Suwatchai (Mobizt)
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

#ifndef Firebase_Arduino_WiFi_CPP
#define Firebase_Arduino_WiFi_CPP

#include "Firebase.h"

enum firebase_data_type
{
  firebase_data_type_any,
  firebase_data_type_null,
  firebase_data_type_double,
  firebase_data_type_integer,
  firebase_data_type_integer64,
  firebase_data_type_unsigned_integer64,
  firebase_data_type_float,
  firebase_data_type_boolean,
  firebase_data_type_string,
  firebase_data_type_json,
  firebase_data_type_array,
  firebase_data_type_timestamp
};

enum firebase_method
{
  firebase_method_put,
  firebase_method_put_silent,
  firebase_method_post,
  firebase_method_get,
  firebase_method_stream,
  firebase_method_patch,
  firebase_method_patch_silent,
  firebase_method_delete
};

Firebase_Class::Firebase_Class() {}
Firebase_Class::~Firebase_Class() {}

void Firebase_Class::begin(const String &host, const String &auth, const String &wifiSSID, const String &wifiPSW)
{
  _host = host;
  _auth = auth;
  _ssid = wifiSSID;
  _psw = wifiPSW;
  _port = FIEBASE_PORT;
}

void Firebase_Class::reconnectWiFi(bool reconnect)
{
  _reconnectWiFi = reconnect;
}

bool Firebase_Class::pushInt(FirebaseData &fbdo, const String &path, int intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::pushDouble(FirebaseData &fbdo, const String &path, double dblValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_double, NumToString(dblValue).get());
}

bool Firebase_Class::pushFloat(FirebaseData &fbdo, const String &path, float floatValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_float, NumToString(floatValue).get());
}

bool Firebase_Class::pushBool(FirebaseData &fbdo, const String &path, bool boolValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_boolean, NumToString(boolValue).get());
}

bool Firebase_Class::pushString(FirebaseData &fbdo, const String &path, const String &stringValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_string, stringValue.c_str());
}

bool Firebase_Class::pushJSON(FirebaseData &fbdo, const String &path, const String &jsonString)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_json, jsonString.c_str());
}

bool Firebase_Class::pushArray(FirebaseData &fbdo, const String &path, const String &arrayString)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_array, arrayString.c_str());
}

bool Firebase_Class::pushTimestamp(FirebaseData &fbdo, const String &path)
{
  char *buf = strP(C_STR_0);
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_timestamp, buf);
  delS(buf);
  return flag;
}

bool Firebase_Class::setDouble(FirebaseData &fbdo, const String &path, double dblValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_double, NumToString(dblValue).get());
}

bool Firebase_Class::setInt(FirebaseData &fbdo, const String &path, int intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::setInt(FirebaseData &fbdo, const String &path, unsigned int intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::setInt(FirebaseData &fbdo, const String &path, long intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::setInt(FirebaseData &fbdo, const String &path, unsigned long intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::setInt(FirebaseData &fbdo, const String &path, long long intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::setInt(FirebaseData &fbdo, const String &path, unsigned long long intValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_integer, NumToString(intValue).get());
}

bool Firebase_Class::setFloat(FirebaseData &fbdo, const String &path, float floatValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_float, NumToString(floatValue).get());
}

bool Firebase_Class::setBool(FirebaseData &fbdo, const String &path, bool boolValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_boolean, NumToString(boolValue).get());
}

bool Firebase_Class::setString(FirebaseData &fbdo, const String &path, const String &stringValue)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_string, stringValue.c_str());
}

bool Firebase_Class::setJSON(FirebaseData &fbdo, const String &path, const String &jsonString)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_json, jsonString.c_str());
}

bool Firebase_Class::setArray(FirebaseData &fbdo, const String &path, const String &arrayString)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_array, arrayString.c_str());
}

bool Firebase_Class::setTimestamp(FirebaseData &fbdo, const String &path)
{
  char *buf = strP(C_STR_0);
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_timestamp, buf);
  delS(buf);
  return flag;
}

bool Firebase_Class::updateNode(FirebaseData &fbdo, const String path, const String jsonString)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_patch, firebase_data_type_json, jsonString.c_str());
}

bool Firebase_Class::updateNodeSilent(FirebaseData &fbdo, const String &path, const String &jsonString)
{
  return sendRequest(fbdo, path.c_str(), firebase_method_patch_silent, firebase_data_type_json, jsonString.c_str());
}

bool Firebase_Class::get(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  return sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_any, "");
}

bool Firebase_Class::getInt(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_integer, "");
  if (fbdo._dataType != firebase_data_type_integer && fbdo._dataType != firebase_data_type_integer64 && fbdo._dataType != firebase_data_type_unsigned_integer64 && fbdo._dataType != firebase_data_type_double && fbdo._dataType != firebase_data_type_float)
    flag = false;
  return flag;
}

bool Firebase_Class::getFloat(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_float, "");
  if (fbdo._dataType != firebase_data_type_integer && fbdo._dataType != firebase_data_type_integer64 && fbdo._dataType != firebase_data_type_unsigned_integer64 && fbdo._dataType != firebase_data_type_double && fbdo._dataType != firebase_data_type_float)
    flag = false;
  return flag;
}

bool Firebase_Class::getDouble(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_double, "");
  if (fbdo._dataType != firebase_data_type_integer && fbdo._dataType != firebase_data_type_integer64 && fbdo._dataType != firebase_data_type_unsigned_integer64 && fbdo._dataType != firebase_data_type_double && fbdo._dataType != firebase_data_type_float)
    flag = false;
  return flag;
}

bool Firebase_Class::getBool(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_boolean, "");
  if (fbdo._dataType != firebase_data_type_boolean)
    flag = false;
  return flag;
}

bool Firebase_Class::getString(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_string, "");
  if (fbdo._dataType != firebase_data_type_string)
    flag = false;
  return flag;
}

bool Firebase_Class::getJSON(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_json, "");
  if (fbdo._dataType != firebase_data_type_json && fbdo._dataType != firebase_data_type_array)
    flag = false;
  return flag;
}

bool Firebase_Class::getJSON(FirebaseData &fbdo, const String &path, QueryFilter &query)
{
  fbdo.queryFilter.clearQuery();
  if (query._orderBy != "")
  {
    fbdo.queryFilter._orderBy = query._orderBy;
    fbdo.queryFilter._limitToFirst = query._limitToFirst;
    fbdo.queryFilter._limitToLast = query._limitToLast;
    fbdo.queryFilter._startAt = query._startAt;
    fbdo.queryFilter._endAt = query._endAt;
    fbdo.queryFilter._equalTo = query._equalTo;
  }
  return getJSON(fbdo, path);
}

bool Firebase_Class::getArray(FirebaseData &fbdo, const String &path)
{
  fbdo.queryFilter.clearQuery();
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_get, firebase_data_type_array, "");
  if (fbdo._dataType != firebase_data_type_array && fbdo._dataType != firebase_data_type_json)
    flag = false;
  return flag;
}

bool Firebase_Class::getArray(FirebaseData &fbdo, const String &path, QueryFilter &query)
{
  fbdo.queryFilter.clearQuery();
  if (query._orderBy != "")
  {
    fbdo.queryFilter._orderBy = query._orderBy;
    fbdo.queryFilter._limitToFirst = query._limitToFirst;
    fbdo.queryFilter._limitToLast = query._limitToLast;
    fbdo.queryFilter._startAt = query._startAt;
    fbdo.queryFilter._endAt = query._endAt;
    fbdo.queryFilter._equalTo = query._equalTo;
  }
  return getArray(fbdo, path);
}

bool Firebase_Class::deleteNode(FirebaseData &fbdo, const String path)
{
  fbdo.queryFilter.clearQuery();
  return sendRequest(fbdo, path.c_str(), firebase_method_delete, firebase_data_type_string, "");
}

bool Firebase_Class::beginStream(FirebaseData &fbdo, const String path)
{
  return firebaseConnectStream(fbdo, path.c_str());
}

bool Firebase_Class::readStream(FirebaseData &fbdo)
{
  if (fbdo._streamStop)
    return true;
  return getServerStreamResponse(fbdo);
}

bool Firebase_Class::endStream(FirebaseData &fbdo)
{
  bool flag = false;
  fbdo._streamPath = "";
  forceEndHTTP(fbdo);
  flag = fbdo._wcs.connected();
  if (!flag)
  {
    fbdo._isStream = false;
    fbdo._streamStop = true;
  }
  return !flag;
}

bool Firebase_Class::apConnected(FirebaseData &fbdo)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    fbdo._httpCode = TCP_ERROR_CONNECTION_LOST;
    return false;
  }
  return true;
}

int Firebase_Class::firebaseConnect(FirebaseData &fbdo, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{
  fbdo._firebaseError = "";

  if (fbdo._pause)
    return 0;

  if (!apConnected(fbdo))
    return TCP_ERROR_CONNECTION_LOST;

  if (strlen(path) == 0 || _host.length() == 0 || _auth.length() == 0)
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return _HTTP_CODE_BAD_REQUEST;
  }

  bool httpConnected = false;
  int httpCode = TCP_ERROR_CONNECTION_REFUSED;

  //init the firebase data
  resetFirebasedataFlag(fbdo);

  fbdo._path = "";

  if (method == firebase_method_stream)
  {
    //stream path change? reset the current (keep alive) connection
    if (strcmp(path, fbdo._streamPath.c_str()) != 0)
      fbdo._streamPathChanged = true;
    if (!fbdo._isStream || fbdo._streamPathChanged)
    {
      if (fbdo._wcs.connected())
        forceEndHTTP(fbdo);
    }

    fbdo._streamPath = "";

    if (strlen(path) > 0)
      if (path[0] != '/')
        fbdo._streamPath = "/";

    fbdo._streamPath += path;
  }
  else
  {
    //last requested method was stream?, reset the connection
    if (fbdo._isStream)
      forceEndHTTP(fbdo);

    if (strlen(path) > 0)
    {
      if (path[0] != '/')
        fbdo._path = "/";
    }

    fbdo._path += path;
    fbdo._isStreamTimeout = false;
  }

  if (!reconnect(fbdo))
    return TCP_ERROR_CONNECTION_LOST;

  httpConnected = fbdo._wcs.begin(_host.c_str(), _port);

  if (!httpConnected)
  {
    fbdo._httpCode = TCP_ERROR_CONNECTION_REFUSED;
    return TCP_ERROR_CONNECTION_REFUSED;
  }

  if (!reconnect(fbdo))
    return TCP_ERROR_CONNECTION_LOST;

  bool hasPayload = (method != firebase_method_get && method != firebase_method_stream && method != firebase_method_delete);
  bool isString = dataType == firebase_data_type_string && hasPayload;
  uint16_t len = isString ? strlen(payload) + 2 : strlen(payload);

  String req;

  buildFirebaseRequest(req, fbdo, _host.c_str(), method, path, _auth.c_str(), len);

  if (isString)
  {
    char *t = strP(C_STR_3);
    req += t;
    delS(t);
  }

  req += payload;

  if (isString)
  {
    char *t = strP(C_STR_3);
    req += t;
    delS(t);
  }

  httpCode = fbdo._wcs.send(req.c_str());

  if (method == firebase_method_patch_silent)
    fbdo._isSilentResponse = true;

  return httpCode;
}

bool Firebase_Class::reconnect(FirebaseData &fbdo)
{
  bool flag = reconnect();
  if (!flag)
    fbdo._httpCode = TCP_ERROR_CONNECTION_LOST;
  return flag;
}

bool Firebase_Class::reconnect()
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

void Firebase_Class::autoConnectWiFi()
{
  if (_reconnectWiFi && WiFi.status() != WL_CONNECTED && _ssid != "" && _psw != "")
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

bool Firebase_Class::sendRequest(FirebaseData &fbdo, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{

  bool flag = false;
  fbdo._firebaseError = "";

  if (fbdo._pause)
    return true;

  if (strlen(path) == 0 || _host == "" || _auth == "")
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  if ((method == firebase_method_put || method == firebase_method_post || method == firebase_method_patch || method == firebase_method_patch_silent) && strlen(payload) == 0 && dataType != firebase_data_type_string)
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  //Try to reconnect WiFi if lost connection
  autoConnectWiFi();

  //If WiFi is not connected, return false
  if (WiFi.status() != WL_CONNECTED)
  {
    fbdo._httpCode = TCP_ERROR_CONNECTION_LOST;
    return false;
  }

  //Get the current WiFi client from current firebase data
  //Check for connection status
  if (fbdo._wcs.connected())
    fbdo._httpConnected = true;
  else
    fbdo._httpConnected = false;

  if (fbdo._httpConnected)
  {
    if (method == firebase_method_stream)
    {
      fbdo._streamMillis = millis();
      return false;
    }
    else
    {
      if (!fbdo._keepAlive)
      {
        fbdo._streamMillis = millis() + 50;
        fbdo._interruptRequest = true;

        if (fbdo._wcs.connected())
        {

          forceEndHTTP(fbdo);
          if (fbdo._wcs.connected())
            if (!fbdo._isStream)
              return false;
        }
        fbdo._httpConnected = false;
      }
    }
  }

  if (!fbdo._keepAlive && fbdo._httpConnected)
    return false;

  fbdo._httpConnected = true;
  fbdo._interruptRequest = false;
  fbdo._redirectURL = "";
  fbdo._r_method = method;
  fbdo._r_dataType = dataType;

  int httpCode = firebaseConnect(fbdo, path, method, dataType, payload);

  if (httpCode == 0)
  {

    fbdo._dataType2 = dataType;

    if (method == firebase_method_stream)
    {
      fbdo._dataMillis = millis();
      flag = getServerStreamResponse(fbdo);
      if (!flag)
        forceEndHTTP(fbdo);
    }
    else
    {

      fbdo._path = path;
      flag = getServerResponse(fbdo);
      fbdo._dataAvailable = fbdo._data != "";
    }

    if (!flag)
      forceEndHTTP(fbdo);
  }
  else
  {
    //can't establish connection
    fbdo._httpCode = httpCode;
    fbdo._httpConnected = false;
    return false;
  }

  return flag;
}

bool Firebase_Class::getServerResponse(FirebaseData &fbdo)
{

  if (fbdo._pause)
    return true;

  if (WiFi.status() != WL_CONNECTED)
  {
    fbdo._httpCode = TCP_ERROR_CONNECTION_LOST;
    return false;
  }

  if (!fbdo._wcs.connected() || fbdo._interruptRequest)
    return cancelCurrentResponse(fbdo);
  if (!handleNetClientNotConnected(fbdo) || !fbdo._httpConnected)
    return false;

  bool flag = false;

  fbdo._data = "";

  char *lineBuf = newS(FIREBASE_RESPONSE_SIZE);
  char *tmp = nullptr;
  char *tmp2 = nullptr;
  char *eventType = newS(30);

  char c;
  int p1, p2;
  bool isStream = false;
  fbdo._httpCode = -1000;
  fbdo._contentLength = -1;
  fbdo._bufferOverflow = false;
  fbdo._pushName = "";

  bool hasEvent = false;
  bool hasEventData = false;
  bool payLoadBegin = false;

  unsigned long dataTime = millis();

  uint16_t lfCount = 0;
  uint16_t charPos = 0;

  if (!fbdo._isStream)
    while (fbdo._wcs.client.connected() && !fbdo._wcs.client.available() && millis() - dataTime < fbdo._wcs.client_timeout)
      delay(0);

  dataTime = millis();

  if (fbdo._wcs.client.connected() && fbdo._wcs.client.available())
  {
    while (fbdo._wcs.client.available())
    {

      if (fbdo._interruptRequest)
        return cancelCurrentResponse(fbdo);

      c = fbdo._wcs.client.read();

      if (payLoadBegin && fbdo._contentLength > 0)
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
        fbdo._bufferOverflow = true;
        memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
      }

      if (c == '\n')
      {
        dataTime = millis();

        if (strlen(lineBuf) == 0 && lfCount > 0)
          payLoadBegin = true;

        if (strlen(lineBuf) > 0)
        {
          tmp = strP(C_STR_5);
          p1 = strpos(lineBuf, tmp, 0);
          delS(tmp);

          if (p1 != -1)
          {
            tmp = newS(strlen(lineBuf) - p1 - 9);
            strncpy(tmp, lineBuf + p1 + 9, strlen(lineBuf) - p1 - 9);
            fbdo._httpCode = atoi(tmp);
            delS(tmp);
          }

          if (fbdo._httpCode == _HTTP_CODE_TEMPORARY_REDIRECT)
          {
            tmp = strP(C_STR_95);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {
              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_95));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_95), strlen(lineBuf) - p1 - strlen_P(C_STR_95));
              fbdo._redirectURL = tmp;
              delS(tmp);
              int res = firebaseConnect(fbdo, fbdo._redirectURL.c_str(), fbdo._r_method, fbdo._r_dataType, "");

              if (res == 0)
                goto EXIT_4;

              goto EXIT_3;
            }
          }

          if (fbdo._httpCode == _HTTP_CODE_NO_CONTENT)
            continue;

          tmp = strP(C_STR_7);
          bool flag = strpos(lineBuf, tmp, 0) != -1;
          delS(tmp);

          if (flag)
          {
            tmp = strP(C_STR_102);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {
              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_102));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_102) + 1, strlen(lineBuf) - p1 - strlen_P(C_STR_102));
              tmp2 = newS(strlen(tmp) - 1);
              strncpy(tmp2, tmp, strlen(tmp) - 1);
              fbdo._firebaseError = tmp2;
              delS(tmp2);
              delS(tmp);
            }

            tmp = strP(C_STR_8);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {
              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_8));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_8), strlen(lineBuf) - p1 - strlen_P(C_STR_8));

              tmp2 = strP(C_STR_9);
              if (strcmp(tmp, tmp2) == 0)
              {
                isStream = true;
              }

              delS(tmp2);
              delS(tmp);
            }

            tmp = strP(C_STR_10);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {
              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_10));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_10), strlen(lineBuf) - p1 - strlen_P(C_STR_10));
              tmp2 = strP(C_STR_11);
              if (strcmp(tmp, tmp2) == 0)
                fbdo._keepAlive = true;
              else
                fbdo._keepAlive = false;
              delS(tmp2);
              delS(tmp);
            }

            tmp = strP(C_STR_12);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {

              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_12));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_12), strlen(lineBuf) - p1 - strlen_P(C_STR_12));
              fbdo._contentLength = atoi(tmp);
              delS(tmp);
            }

            tmp = strP(C_STR_13);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {
              eventType = newS(eventType, strlen(lineBuf) - p1 - strlen_P(C_STR_13));
              strncpy(eventType, lineBuf + p1 + strlen_P(C_STR_13), strlen(lineBuf) - p1 - strlen_P(C_STR_13));
              hasEvent = true;
              isStream = true;
              fbdo._httpCode = _HTTP_CODE_OK;
              memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
            }

            tmp = strP(C_STR_14);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1)
            {
              hasEventData = true;
              isStream = true;
              fbdo._httpCode = _HTTP_CODE_OK;
              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_14));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_14), strlen(lineBuf) - p1 - strlen_P(C_STR_14));
              memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);
              strcpy(lineBuf, tmp);
              delS(tmp);
              break;
            }
          }
        }

        if (!hasEventData || !hasEvent)
          memset(lineBuf, 0, FIREBASE_RESPONSE_SIZE);

        lfCount++;
        charPos = 0;
      }

      if (millis() - dataTime > fbdo._wcs.client_timeout)
      {
        fbdo._httpCode = TCP_ERROR_READ_TIMEOUT;
        break;
      }
    }

    if (fbdo._httpCode == _HTTP_CODE_OK)
    {
      //JSON stream data?
      if (isStream)
      {
        if (hasEventData && hasEvent)
        {
          bool m = false;
          tmp = strP(C_STR_15);
          m |= strpos(eventType, tmp, 0) != -1;
          delS(tmp);

          tmp = strP(C_STR_16);
          m |= strpos(eventType, tmp, 0) != -1;
          delS(tmp);

          if (m)
          {
            fbdo._eventType = eventType;
            bool samePath = true;

            //Parses json response for path
            tmp = strP(C_STR_17);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1 && p1 < FIREBASE_RESPONSE_SIZE)
            {
              tmp = strP(C_STR_3);
              p2 = strpos(lineBuf, tmp, p1 + strlen_P(C_STR_17));
              delS(tmp);
              if (p2 != -1)
              {
                tmp = newS(p2 - p1 - strlen_P(C_STR_17));
                strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_17), p2 - p1 - strlen_P(C_STR_17));
                samePath = strcmp(tmp, fbdo._path.c_str()) == 0;
                fbdo._path = tmp;
                delS(tmp);
              }
            }

            //Parses json response for data
            tmp = strP(C_STR_18);
            p1 = strpos(lineBuf, tmp, 0);
            delS(tmp);
            if (p1 != -1 && p1 < FIREBASE_RESPONSE_SIZE)
            {
              tmp = newS(strlen(lineBuf) - p1 - strlen_P(C_STR_18) - 1);
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_18), strlen(lineBuf) - p1 - strlen_P(C_STR_18) - 1);
              fbdo._data = tmp;
              delS(tmp);

              setDataType(fbdo, fbdo._data.c_str());
              bool sameData = fbdo._data == fbdo._data2;

              //Any stream update?
              if (!samePath || (samePath && !sameData && !fbdo._streamPathChanged))
              {
                fbdo._streamDataChanged = true;
                fbdo._data2 = fbdo._data;
              }
              else
                fbdo._streamDataChanged = false;

              fbdo._dataMillis = millis();
              flag = true;
              fbdo._dataAvailable = flag;
              fbdo._isStreamTimeout = false;
            }

            fbdo._streamPathChanged = false;
          }
          else
          {
            //Firebase keep alive data
            tmp = strP(C_STR_11);
            if (strcmp(eventType, tmp) == 0)
            {
              fbdo._isStreamTimeout = false;
              fbdo._dataMillis = millis();
            }
            delS(tmp);

            //Firebase cancel and auth_revoked events
            tmp = strP(C_STR_84);
            bool m2 = strcmp(eventType, tmp) == 0;
            delS(tmp);
            tmp = strP(C_STR_83);
            m2 |= strcmp(eventType, tmp) == 0;
            delS(tmp);

            if (m2)
            {
              fbdo._isStreamTimeout = false;
              fbdo._dataMillis = millis();
              fbdo._eventType = eventType;
              //make stream available status
              fbdo._streamDataChanged = true;
              fbdo._dataAvailable = true;
            }
          }
        }
        fbdo._streamMillis = millis();
      }
      else
      {
        //Just text payload
        fbdo._data = lineBuf;
        setDataType(fbdo, lineBuf);

        //Push (POST) data?
        if (fbdo._r_method == firebase_method_post)
        {
          tmp = strP(C_STR_20);
          p1 = strpos(lineBuf, tmp, 0);
          delS(tmp);
          if (p1 != -1)
          {
            tmp = strP(C_STR_3);
            p2 = strpos(lineBuf, tmp, p1 + strlen_P(C_STR_20));
            delS(tmp);
            if (p2 != -1)
            {
              tmp = newS(p2 - p1 - strlen_P(C_STR_20));
              strncpy(tmp, lineBuf + p1 + strlen_P(C_STR_20), p2 - p1 - strlen_P(C_STR_20));
              fbdo._pushName = tmp;
              delS(tmp);
              fbdo._dataType = 0;
              fbdo._dataType2 = 0;
              fbdo._data = "";
            }
          }
        }
      }
    }
    else
    {
      if (fbdo._isSilentResponse)
      {
        if (fbdo._httpCode == _HTTP_CODE_NO_CONTENT)
        {
          fbdo._httpCode = _HTTP_CODE_OK;
          fbdo._path = "";
          fbdo._data = "";
          fbdo._pushName = "";
          fbdo._dataType = 0;
          fbdo._dataType2 = 0;
          fbdo._dataAvailable = false;
        }
      }
      else
        fbdo._contentLength = -1;
    }

    if (fbdo._dataType == firebase_data_type_null)
    {
      fbdo._pathNotExist = true;
    }
    else
    {
      fbdo._pathNotExist = false;
      bool _n1 = fbdo._dataType == firebase_data_type_float || fbdo._dataType == firebase_data_type_double || fbdo._dataType == firebase_data_type_integer;
      bool _n2 = fbdo._dataType2 == firebase_data_type_float || fbdo._dataType2 == firebase_data_type_double || fbdo._dataType2 == firebase_data_type_integer;

      if (fbdo._dataType2 == firebase_data_type_any || fbdo._dataType2 == fbdo._dataType || (_n1 && _n2))
        fbdo._mismatchDataType = false;
      else
        fbdo._mismatchDataType = true;
    }

    if (!fbdo._httpCode)
    {
      fbdo._contentLength = -1;
      fbdo._httpCode = TCP_ERROR_NO_HTTP_SERVER;
    }
    fbdo._httpConnected = false;
    fbdo._streamMillis = millis();

    goto EXIT_2;
  }

  if (fbdo._httpCode == -1000 && fbdo._r_method != firebase_method_stream)
    flag = true;

  fbdo._httpConnected = false;
  fbdo._streamMillis = millis();
  delS(lineBuf);
  delS(eventType);

  return flag;

EXIT_2:

  delS(lineBuf);
  delS(eventType);

  if (fbdo._httpCode == TCP_ERROR_READ_TIMEOUT)
    return false;

  return fbdo._httpCode == _HTTP_CODE_OK || fbdo._httpCode == -1000;

EXIT_3:

  delS(lineBuf);
  delS(eventType);
  return true;

EXIT_4:
  delS(lineBuf);
  delS(eventType);
  return getServerResponse(fbdo);
}

bool Firebase_Class::firebaseConnectStream(FirebaseData &fbdo, const char *path)
{

  if (fbdo._pause)
    return true;

  fbdo._streamStop = false;

  if (!fbdo._isStreamTimeout && fbdo._isStream && strcmp(path, fbdo._streamPath.c_str()) == 0)
    return true;

  if (strlen(path) == 0 || _host == "" || _auth == "")
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  bool flag;
  flag = fbdo._streamPath == "";
  flag |= firebaseConnect(fbdo, path, firebase_method_stream, firebase_data_type_string, "") == 0;
  fbdo._dataMillis = millis();
  return flag;
}

bool Firebase_Class::getServerStreamResponse(FirebaseData &fbdo)
{
  bool res = false;

  if (fbdo._pause || fbdo._streamStop)
    return true;

  unsigned long ml = millis();
  if (fbdo._streamMillis == 0)
    fbdo._streamMillis = ml;
  if (fbdo._streamResetMillis == 0)
    fbdo._streamResetMillis = ml;

  if (ml - fbdo._streamMillis > 0)
  {

    fbdo._streamMillis = ml;
    String path = "";

    //Stream timeout
    if (fbdo._dataMillis > 0 && millis() - fbdo._dataMillis > KEEP_ALIVE_TIMEOUT)
    {
      fbdo._dataMillis = millis();
      fbdo._isStreamTimeout = true;
      path = fbdo._streamPath;

      autoConnectWiFi();

      firebaseConnectStream(fbdo, path.c_str());
      res = getServerResponse(fbdo);

      if (!fbdo._httpConnected)
        fbdo._httpCode = TCP_ERROR_NOT_CONNECTED;
      return res;
    }

    //last connection was not close
    if (fbdo._httpConnected)
      return true;

    fbdo._httpConnected = true;
    resetFirebasedataFlag(fbdo);

    if (fbdo._wcs.client.connected() && !fbdo._isStream)
      forceEndHTTP(fbdo);

    if (!fbdo._wcs.client.connected())
    {
      path = fbdo._streamPath;
      firebaseConnectStream(fbdo, path.c_str());
    }

    res = getServerResponse(fbdo);

    if (!fbdo._httpConnected)
      fbdo._httpCode = TCP_ERROR_NOT_CONNECTED;

    return res;
  }

  return true;
}

void Firebase_Class::forceEndHTTP(FirebaseData &fbdo)
{
  if (fbdo._wcs.client.available() > 0)
  {
    fbdo._wcs.client.read();
  }
  fbdo._wcs.client.stop();
}

void Firebase_Class::delS(char *p)
{
  if (p != nullptr)
    delete[] p;
  p = nullptr;
}

char *Firebase_Class::newS(size_t len)
{
  char *p = new char[len + 1];
  memset(p, 0, len + 1);
  return p;
}

char *Firebase_Class::newS(char *p, size_t len)
{
  delS(p);
  p = newS(len);
  return p;
}

char *Firebase_Class::newS(char *p, size_t len, char *d)
{
  delS(p);
  p = newS(len);
  strcpy(p, d);
  return p;
}

char *Firebase_Class::strP(PGM_P pgm)
{
  size_t len = strlen_P(pgm) + 1;
  char *buf = newS(len);
  strcat_P(buf, pgm);
  return buf;
}

void Firebase_Class::strP(char *buf, PGM_P pgm, bool empty)
{
  if (empty)
    memset(buf, 0, strlen(buf));
  strcat_P(buf, pgm);
}

void Firebase_Class::buildFirebaseRequest(String &req, FirebaseData &fbdo, const char *host, uint8_t method, const char *path, const char *auth, int payloadLength)
{
  char *buf = newS(400);
  if (method == firebase_method_stream)
  {
    strP(buf, C_STR_22);
    fbdo._isStream = true;
  }
  else
  {
    if (method == firebase_method_put || method == firebase_method_put_silent)
      strP(buf, C_STR_23);
    else if (method == firebase_method_post)
      strP(buf, C_STR_24);
    else if (method == firebase_method_get)
      strP(buf, C_STR_25);
    else if (method == firebase_method_patch || method == firebase_method_patch_silent)
      strP(buf, C_STR_26);
    else if (method == firebase_method_delete)
      strP(buf, C_STR_27);
    strP(buf, C_STR_6);

    fbdo._isStream = false;
  }

  if (strlen(path) > 0)
  {
    if (path[0] != '/')
      strP(buf, C_STR_1);
  }

  strcat(buf, path);

  if (method == firebase_method_patch || method == firebase_method_patch_silent)
    strP(buf, C_STR_1);

  strP(buf, C_STR_2);

  strcat(buf, auth);

  if (method == firebase_method_get && fbdo.queryFilter._orderBy != "")
  {
    strP(buf, C_STR_96);
    strcat(buf, fbdo.queryFilter._orderBy.c_str());

    if (method == firebase_method_get && fbdo.queryFilter._limitToFirst != "")
    {
      strP(buf, C_STR_97);
      strcat(buf, fbdo.queryFilter._limitToFirst.c_str());
    }

    if (method == firebase_method_get && fbdo.queryFilter._limitToLast != "")
    {
      strP(buf, C_STR_98);
      strcat(buf, fbdo.queryFilter._limitToLast.c_str());
    }

    if (method == firebase_method_get && fbdo.queryFilter._startAt != "")
    {
      strP(buf, C_STR_99);
      strcat(buf, fbdo.queryFilter._startAt.c_str());
    }

    if (method == firebase_method_get && fbdo.queryFilter._endAt != "")
    {

      strP(buf, C_STR_100);
      strcat(buf, fbdo.queryFilter._endAt.c_str());
    }

    if (method == firebase_method_get && fbdo.queryFilter._equalTo != "")
    {
      strP(buf, C_STR_101);
      strcat(buf, fbdo.queryFilter._equalTo.c_str());
    }
  }

  if (method == firebase_method_put_silent || method == firebase_method_patch_silent)
    strP(buf, C_STR_29);

  strP(buf, C_STR_30);
  strP(buf, C_STR_31);

  strcat(buf, host);

  strP(buf, C_STR_21);
  strP(buf, C_STR_32);

  if (method == firebase_method_stream)
  {
    strP(buf, C_STR_34);
    strP(buf, C_STR_35);
  }
  else
  {
    strP(buf, C_STR_36);
    strP(buf, C_STR_37);
  }

  strP(buf, C_STR_38);

  if (method == firebase_method_put || method == firebase_method_put_silent || method == firebase_method_post || method == firebase_method_patch || method == firebase_method_patch_silent)
  {

    strP(buf, C_STR_12);
    strcat(buf, NumToString(payloadLength).get());
  }

  strP(buf, C_STR_21);
  strP(buf, C_STR_21);

  req = buf;
  delete[] buf;
}

bool Firebase_Class::cancelCurrentResponse(FirebaseData &fbdo)
{
  forceEndHTTP(fbdo);
  fbdo._isStream = false;
  fbdo._streamDataChanged = false;
  fbdo._dataMillis = millis();
  fbdo._data2 = "";
  fbdo._dataAvailable = false;
  fbdo._isStreamTimeout = false;
  fbdo._httpCode = TCP_ERROR_CONNECTION_REFUSED;
  return false;
}

void Firebase_Class::setDataType(FirebaseData &fbdo, const char *data)
{

  bool typeSet = false;

  if (strlen(data) > 0)
  {
    if (!typeSet && data[0] == '{')
    {
      typeSet = true;
      fbdo._dataType = firebase_data_type_json;
    }

    if (!typeSet && data[0] == '[')
    {
      typeSet = true;
      fbdo._dataType = firebase_data_type_array;
    }

    char *t = strP(C_STR_87);
    char *u = strP(C_STR_85);

    if (!typeSet)
    {
      if (strcmp(data, t) == 0 || strcmp(data, u) == 0)
      {
        typeSet = true;
        fbdo._dataType = firebase_data_type_boolean;
      }
    }
    delS(t);
    delS(u);

    if (!typeSet && data[0] == '"')
    {
      typeSet = true;
      fbdo._dataType = firebase_data_type_string;
    }

    t = strP(C_STR_4);
    u = strP(C_STR_19);

    if (!typeSet && strcmp(data, u) == 0)
    {
      typeSet = true;
      fbdo._dataType = firebase_data_type_null;
    }

    if (!typeSet)
    {
      typeSet = true;

      if (strpos(data, t, 0) != -1)
      {
        if (strlen(data) <= 7)
        {
          fbdo._dataType = firebase_data_type_float;
        }
        else
        {
          fbdo._dataType = firebase_data_type_double;
        }
      }
      else
      {
        char *eptr;

        unsigned long long v1 = (data[0] == '-') ? strtoull(&data[1], &eptr, 10) : strtoull(data, &eptr, 10);

        unsigned long long v2 = (sizeof(int) == 2) ? 0xffff / 2 : 0xffffffff / 2;

        if (data[0] == '-')
          fbdo._dataType = (v1 > v2) ? firebase_data_type_integer64 : firebase_data_type_integer;
        else
          fbdo._dataType = (v1 > v2) ? firebase_data_type_unsigned_integer64 : firebase_data_type_integer;
      }
    }

    delS(t);
    delS(u);
  }
  else
  {
    fbdo._dataType = firebase_data_type_null;
  }

  fbdo._dataTypeNum = fbdo._dataType;
}

void Firebase_Class::resetFirebasedataFlag(FirebaseData &fbdo)
{
  fbdo._bufferOverflow = false;
  fbdo._streamDataChanged = false;
  fbdo._streamPathChanged = false;
  fbdo._dataAvailable = false;
  fbdo._pushName = "";
}
bool Firebase_Class::handleNetClientNotConnected(FirebaseData &fbdo)
{
  if (!fbdo._wcs.connected())
  {
    fbdo._contentLength = -1;
    fbdo._dataType = firebase_data_type_null;
    fbdo._httpCode = TCP_ERROR_NOT_CONNECTED;
    fbdo._data = "";
    fbdo._path = "";
    resetFirebasedataFlag(fbdo);
    return false;
  }
  return true;
}

char *Firebase_Class::errorToString(int httpCode)
{
  char *buf = nullptr;
  switch (httpCode)
  {
  case TCP_ERROR_CONNECTION_REFUSED:
    buf = strP(C_STR_39);
    break;
  case TCP_ERROR_SEND_DATA_FAILED:
    buf = strP(C_STR_40);
    break;
  case TCP_ERROR_NOT_CONNECTED:
    buf = strP(C_STR_42);
    break;
  case TCP_ERROR_CONNECTION_LOST:
    buf = strP(C_STR_43);
    break;
  case TCP_ERROR_NO_HTTP_SERVER:
    buf = strP(C_STR_44);
    break;
  case _HTTP_CODE_BAD_REQUEST:
    buf = strP(C_STR_45);
    break;
  case _HTTP_CODE_NON_AUTHORITATIVE_INFORMATION:
    buf = strP(C_STR_46);
    break;
  case _HTTP_CODE_NO_CONTENT:
    buf = strP(C_STR_47);
    break;
  case _HTTP_CODE_MOVED_PERMANENTLY:
    buf = strP(C_STR_48);
    break;
  case _HTTP_CODE_USE_PROXY:
    buf = strP(C_STR_49);
    break;
  case _HTTP_CODE_TEMPORARY_REDIRECT:
    buf = strP(C_STR_50);
    break;
  case _HTTP_CODE_PERMANENT_REDIRECT:
    buf = strP(C_STR_51);
    break;
  case _HTTP_CODE_UNAUTHORIZED:
    buf = strP(C_STR_52);
    break;
  case _HTTP_CODE_FORBIDDEN:
    buf = strP(C_STR_53);
    break;
  case _HTTP_CODE_NOT_FOUND:
    buf = strP(C_STR_54);
    break;
  case _HTTP_CODE_METHOD_NOT_ALLOWED:
    buf = strP(C_STR_55);
    break;
  case _HTTP_CODE_NOT_ACCEPTABLE:
    buf = strP(C_STR_56);
    break;
  case _HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED:
    buf = strP(C_STR_57);
    break;
  case _HTTP_CODE_REQUEST_TIMEOUT:
    buf = strP(C_STR_58);
    break;
  case _HTTP_CODE_LENGTH_REQUIRED:
    buf = strP(C_STR_59);
    break;
  case _HTTP_CODE_TOO_MANY_REQUESTS:
    buf = strP(C_STR_60);
    break;
  case _HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE:
    buf = strP(C_STR_61);
    break;
  case _HTTP_CODE_INTERNAL_SERVER_ERROR:
    buf = strP(C_STR_62);
    break;
  case _HTTP_CODE_BAD_GATEWAY:
    buf = strP(C_STR_63);
    break;
  case _HTTP_CODE_SERVICE_UNAVAILABLE:
    buf = strP(C_STR_64);
    break;
  case _HTTP_CODE_GATEWAY_TIMEOUT:
    buf = strP(C_STR_65);
    break;
  case _HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED:
    buf = strP(C_STR_66);
    break;
  case _HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED:
    buf = strP(C_STR_67);
    break;
  case TCP_ERROR_READ_TIMEOUT:
    buf = strP(C_STR_69);
    break;
  case FIREBASE_ERROR_DATA_TYPE_MISMATCH:
    buf = strP(C_STR_70);
    break;
  case FIREBASE_ERROR_PATH_NOT_EXIST:
    buf = strP(C_STR_71);
    break;
  case TCP_ERROR_CONNECTION_INUSED:
    buf = strP(C_STR_94);
    break;
  case FIREBASE_ERROR_BUFFER_OVERFLOW:
    buf = strP(C_STR_68);
    break;
  default:
    break;
  }
  return buf;
}

void Firebase_Class::strcat_c(char *str, char c)
{
  for (; *str; str++)
    ;
  *str++ = c;
  *str++ = 0;
}

int Firebase_Class::strpos(const char *haystack, const char *needle, int offset)
{
  if (!haystack || !needle)
    return -1;

  int hlen = strlen(haystack);
  int nlen = strlen(needle);

  if (hlen == 0 || nlen == 0)
    return -1;

  int hidx = offset, nidx = 0;
  while ((*(haystack + hidx) != '\0') && (*(needle + nidx) != '\0') && hidx < hlen)
  {
    if (*(needle + nidx) != *(haystack + hidx))
    {
      hidx++;
      nidx = 0;
    }
    else
    {
      nidx++;
      hidx++;
      if (nidx == nlen)
        return hidx - nidx;
    }
  }

  return -1;
}

int Firebase_Class::rstrpos(const char *haystack, const char *needle, int offset)
{
  if (!haystack || !needle)
    return -1;

  int hlen = strlen(haystack);
  int nlen = strlen(needle);

  if (hlen == 0 || nlen == 0)
    return -1;

  int hidx = hlen - 1, nidx = nlen - 1;
  while (offset < hidx)
  {
    if (*(needle + nidx) != *(haystack + hidx))
    {
      hidx--;
      nidx = nlen - 1;
    }
    else
    {
      nidx--;
      hidx--;
      if (nidx == 0)
        return hidx + nidx;
    }
  }

  return -1;
}

FirebaseData::FirebaseData() {}

FirebaseData ::~FirebaseData()
{
  end();
}

void FirebaseData::end()
{
  _path = "";
  _data = "";
  _data2 = "";
  _streamPath = "";
  _pushName = "";
  _redirectURL = "";
  _firebaseError = "";
  _eventType = "";
}

WiFiSSLClient FirebaseData::getWiFiClient()
{
  return _wcs.client;
}

bool FirebaseData::pauseFirebase(bool pause)
{

  if (_wcs.connected() && pause != _pause)
  {
    if (_wcs.client.available() > 0)
    {
      _wcs.client.read();
    }
    _wcs.client.stop();
    if (!_wcs.connected())
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
  char *buf = nullptr;
  if (_dataType == firebase_data_type_json)
    buf = Firebase.strP(C_STR_74);
  if (_dataType == firebase_data_type_array)
    buf = Firebase.strP(C_STR_103);
  else if (_dataType == firebase_data_type_string)
    buf = Firebase.strP(C_STR_75);
  else if (_dataType == firebase_data_type_double)
    buf = Firebase.strP(C_STR_92);
  else if (_dataType == firebase_data_type_float)
    buf = Firebase.strP(C_STR_76);
  else if (_dataType == firebase_data_type_boolean)
    buf = Firebase.strP(C_STR_91);
  else if (_dataType == firebase_data_type_integer)
    buf = Firebase.strP(C_STR_77);
  else if (_dataType == firebase_data_type_integer64)
    buf = Firebase.strP(C_STR_41);
  else if (_dataType == firebase_data_type_unsigned_integer64)
    buf = Firebase.strP(C_STR_93);
  else if (_dataType == firebase_data_type_null)
    buf = Firebase.strP(C_STR_78);
  String res = buf;
  Firebase.delS(buf);
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
  if (_data != "" && (_dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
    return atoi(_data.c_str());
  else
    return 0;
}

unsigned long long FirebaseData::uint64Data()
{
  if (_data != "" && (_dataType == firebase_data_type_unsigned_integer64 || _dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
  {
    char *eptr;
    unsigned long long v = strtoull(_data.c_str(), &eptr, 10);
    return v;
  }
  else
    return 0;
}

long long FirebaseData::int64Data()
{
  if (_data != "" && (_dataType == firebase_data_type_integer64 || _dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
  {
    char *eptr;
    long long v = strtoll(_data.c_str(), &eptr, 10);
    return v;
  }
  else
    return 0;
}

double FirebaseData::doubleData()
{

  if (_data != "" && (_dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
    return atof(_data.c_str());
  else
    return 0.0;
}

float FirebaseData::floatData()
{
  if (_data != "" && (_dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
    return atof(_data.c_str());
  else
    return 0.0;
}

bool FirebaseData::boolData()
{
  bool res = false;
  if (_data != "" && _dataType == firebase_data_type_boolean)
    res = _data == "true";
  return res;
}

String FirebaseData::stringData()
{
  if (_data != "" && _dataType == firebase_data_type_string)
  {
    return _data.substring(1, _data.length() - 1);
  }
  else
    return String();
}

String FirebaseData::jsonData()
{
  if (_data != "" && _dataType == firebase_data_type_json)
    return _data;
  else
    return String();
}

String FirebaseData::arrayData()
{
  if (_data != "" && _dataType == firebase_data_type_array)
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
  if (_firebaseError != "")
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
  _orderBy = "";
  _limitToFirst = "";
  _limitToLast = "";
  _limitToLast = "";
  _startAt = "";
  _endAt = "";
  _equalTo = "";
}

void QueryFilter::orderBy(const String &val)
{
  _orderBy = "\"";
  _orderBy += val;
  _orderBy += "\"";
}
void QueryFilter::limitToFirst(int val)
{
  _limitToFirst = NumToString(val).get();
}

void QueryFilter::limitToLast(int val)
{
  _limitToLast = NumToString(val).get();
}

void QueryFilter::startAt(int val)
{
  _startAt = NumToString(val).get();
}

void QueryFilter::endAt(int val)
{
  _endAt = NumToString(val).get();
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
  _equalTo = NumToString(val).get();
}

void QueryFilter::equalTo(const String &val)
{
  _equalTo = "\"";
  _equalTo += val;
  _equalTo += "\"";
}

Firebase_Class Firebase = Firebase_Class();

#endif
