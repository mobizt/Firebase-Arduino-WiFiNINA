/**
 * Firebase.cpp, version 1.0.4
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
  char *buf = strP(fb_esp_pgm_str_0);
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_post, firebase_data_type_timestamp, buf);
  delP(buf);
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
  char *buf = strP(fb_esp_pgm_str_0);
  bool flag = sendRequest(fbdo, path.c_str(), firebase_method_put, firebase_data_type_timestamp, buf);
  delP(buf);
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

void Firebase_Class::setQuery(FirebaseData &fbdo, QueryFilter &query)
{
  fbdo.queryFilter.clearQuery();
  if (query._orderBy.length() > 0)
    fbdo.queryFilter = query;
}

bool Firebase_Class::getJSON(FirebaseData &fbdo, const String &path, QueryFilter &query)
{
  setQuery(fbdo, query);
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
  setQuery(fbdo, query);
  return getArray(fbdo, path);
}

bool Firebase_Class::deleteNode(FirebaseData &fbdo, const String path)
{
  fbdo.queryFilter.clearQuery();
  return sendRequest(fbdo, path.c_str(), firebase_method_delete, firebase_data_type_string, "");
}

bool Firebase_Class::beginStream(FirebaseData &fbdo, const String path)
{
  fbdo._paused = false;
  return connectStream(fbdo, path.c_str());
}

bool Firebase_Class::readStream(FirebaseData &fbdo)
{
  return handleStream(fbdo);
}

bool Firebase_Class::endStream(FirebaseData &fbdo)
{
  closeTCP(fbdo);
  fbdo._isStream = false;
  clearStr(fbdo._streamPath);
  return !fbdo._tcpClient.connected();
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

int Firebase_Class::connect(FirebaseData &fbdo, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{
  clearStr(fbdo._firebaseError);

  // return 0 if paused
  if (fbdo._paused)
  {
    closeTCP(fbdo);
    return 0;
  }

  if (!apConnected(fbdo))
    return TCP_ERROR_CONNECTION_LOST;

  if (strlen(path) == 0 || _host.length() == 0 || _auth.length() == 0)
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return _HTTP_CODE_BAD_REQUEST;
  }

  int httpCode = TCP_ERROR_CONNECTION_REFUSED;

  // init the firebase data
  clearFlag(fbdo);

  clearStr(fbdo._path);

  if (method == firebase_method_stream)
  {
    // stream path change? reset the current (keep alive) connection
    if (strcmp(path, fbdo._streamPath.c_str()) != 0)
      fbdo._streamPathChanged = true;
    if (!fbdo._isStream || fbdo._streamPathChanged)
    {
      if (fbdo._tcpClient.connected())
        closeTCP(fbdo);
    }

    clearStr(fbdo._streamPath);

    if (strlen(path) > 0)
      if (path[0] != '/')
        fbdo._streamPath = "/";

    fbdo._streamPath += path;
  }
  else
  {
    // last requested method was stream?, reset the connection
    if (fbdo._isStream)
      closeTCP(fbdo);

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

  fbdo._tcpClient.begin(_host.c_str(), _port);

  bool hasPayload = (method != firebase_method_get && method != firebase_method_stream && method != firebase_method_delete);
  bool isString = dataType == firebase_data_type_string && hasPayload;
  uint16_t len = isString ? strlen(payload) + 2 : strlen(payload);

  String req;

  buildFirebaseRequest(req, fbdo, _host.c_str(), method, path, _auth.c_str(), len);

  if (isString)
  {
    char *t = strP(fb_esp_pgm_str_3);
    req += t;
    delP(t);
  }

  req += payload;

  if (isString)
  {
    char *t = strP(fb_esp_pgm_str_3);
    req += t;
    delP(t);
  }

  httpCode = fbdo._tcpClient.send(req.c_str());

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
  if (_reconnectWiFi && WiFi.status() != WL_CONNECTED && _ssid.length() > 0 && _psw.length() > 0)
  {
    WiFi.begin(_ssid.c_str(), _psw.c_str());
  }
}

void Firebase_Class::clearStr(String &s)
{
  s.remove(0, s.length());
}

bool Firebase_Class::sendRequest(FirebaseData &fbdo, const char *path, const uint8_t method, uint8_t dataType, const char *payload)
{

  fbdo._paused = false;

  bool flag = false;

  clearStr(fbdo._firebaseError);

  if (strlen(path) == 0 || _host.length() == 0 || _auth.length() == 0)
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  if ((method == firebase_method_put || method == firebase_method_post || method == firebase_method_patch || method == firebase_method_patch_silent) && strlen(payload) == 0 && dataType != firebase_data_type_string)
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  // Try to reconnect WiFi if lost connection
  autoConnectWiFi();

  // If WiFi is not connected, return false
  if (WiFi.status() != WL_CONNECTED)
  {
    fbdo._httpCode = TCP_ERROR_CONNECTION_LOST;
    return false;
  }

  if ((method == firebase_method_stream && fbdo._r_method != method) || (method != firebase_method_stream && fbdo._r_method == firebase_method_stream))
    closeTCP(fbdo);

  if (fbdo._tcpClient.connected() && method == firebase_method_stream)
    return true;

  clearStr(fbdo._redirectURL);
  fbdo._r_method = method;
  fbdo._r_dataType = dataType;

  int httpCode = connect(fbdo, path, method, dataType, payload);

  if (httpCode == 0 && fbdo._tcpClient.connected())
  {

    fbdo._last_dataType = dataType;

    if (method == firebase_method_stream)
    {
      fbdo._dataMillis = millis();
      flag = handleStream(fbdo);
    }
    else
    {

      fbdo._path = path;
      flag = handleResponse(fbdo);
      fbdo._dataAvailable = fbdo._payload.length() > 0;
    }
  }
  else
  {
    // can't establish connection
    fbdo._httpCode = httpCode;
  }

  if (!flag)
    closeTCP(fbdo);

  return flag;
}

uint16_t Firebase_Class::calCRC(const char *buf)
{
  uint8_t x;
  uint16_t crc = 0xFFFF;

  int length = (int)strlen(buf);

  while (length--)
  {
    x = crc >> 8 ^ *buf++;
    x ^= x >> 4;
    crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x << 5)) ^ ((uint16_t)x);
  }
  return crc;
}

int Firebase_Class::strposP(const char *haystack, PGM_P needle, int index)
{
  char *tmp = strP(needle);
  int p1 = strpos(haystack, tmp, index);
  delP(tmp);
  return p1;
}

void Firebase_Class::getHeader(const char *buf, String &out, PGM_P hdr)
{
  out.remove(0, out.length());
  int p1 = strposP(buf, hdr);
  if (p1 != -1)
  {
    char *tmp = newP(strlen(buf) - p1 - strlen_P(hdr));
    if (tmp)
    {
      strncpy(tmp, buf + p1 + strlen_P(hdr), strlen(buf) - p1 - strlen_P(hdr));
      out = tmp;
      delP(tmp);
    }
  }
}

bool Firebase_Class::handleResponse(FirebaseData &fbdo)
{

  if (WiFi.status() != WL_CONNECTED)
  {
    fbdo._httpCode = TCP_ERROR_CONNECTION_LOST;
    return false;
  }

  clearStr(fbdo._payload);

  int p1, p2;
  bool isStream = false;
  fbdo._httpCode = 0;
  fbdo._contentLength = 0;
  fbdo._bufferOverflow = false;
  clearStr(fbdo._pushName);

  bool hasEvent = false;
  bool hasEventData = false;

  unsigned long dataTime = millis();

  uint16_t charPos = 0;

  if (!fbdo._isStream)
  {
    // There is an issue of current Arduino's WiFiSSLClient that
    // reports the connected state instead of disconnected state
    // when the connection timeout reached.
    // Then we need to wait for response until it reached the timeout.

    while (fbdo._tcpClient.connected() && !fbdo._tcpClient.available() && millis() - dataTime < fbdo._tcpClient.client_timeout)
      delay(0);

    if (millis() - dataTime >= fbdo._tcpClient.client_timeout)
    {
      fbdo._httpCode = TCP_ERROR_READ_TIMEOUT;
      return false;
    }
  }

  dataTime = millis();

  if (fbdo._tcpClient.connected() && fbdo._tcpClient.available())
  {

    String respBuf;
    String tmp;
    String eventType;
    bool isHeader = false;

    while (fbdo._tcpClient.available())
    {

      int r = fbdo._tcpClient.read();

      if (r > -1)
      {
        if (r != '\r' && r != '\n' && charPos < FIREBASE_RESPONSE_SIZE)
          respBuf += (char)r;
        charPos++;
      }

      if (respBuf.length() > FIREBASE_RESPONSE_SIZE)
      {
        fbdo._bufferOverflow = true;
        respBuf.remove(0, respBuf.length());
      }

      if (r == '\n')
      {
        dataTime = millis();

        if (respBuf.length() == 0)
          isHeader = false;
        else
        {

          getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_5);
          if (tmp.length() > 0)
          {
            isHeader = true;
            fbdo._httpCode = atoi(tmp.c_str());
          }
          else
            isHeader = false;

          if (isHeader)
          {

            if (fbdo._httpCode == _HTTP_CODE_TEMPORARY_REDIRECT)
            {
              getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_95);
              if (tmp.length() > 0)
              {
                fbdo._redirectURL = tmp;
                int res = connect(fbdo, fbdo._redirectURL.c_str(), fbdo._r_method, fbdo._r_dataType, "");

                if (res == 0)
                  return handleResponse(fbdo);

                return true;
              }
            }

            if (fbdo._httpCode == _HTTP_CODE_NO_CONTENT)
              continue;

            if (strposP(respBuf.c_str(), fb_esp_pgm_str_7) != -1)
            {

              getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_8);
              if (tmp.length() > 0)
              {
                if (strcmp_P(tmp.c_str(), fb_esp_pgm_str_9) == 0)
                  isStream = true;
              }

              getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_12);
              if (tmp.length() > 0)
                fbdo._contentLength = atoi(tmp.c_str());
            }
          }
          else
          {

            getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_102);
            if (tmp.length() > 0)
            {
              tmp.remove(tmp.length() - 2, 2);
              fbdo._firebaseError = tmp;
            }

            getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_13);
            if (tmp.length() > 0)
            {
              eventType = tmp;
              hasEvent = true;
              isStream = true;
              fbdo._httpCode = _HTTP_CODE_OK;
              clearStr(respBuf);
            }

            getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_14);
            if (tmp.length() > 0)
            {
              hasEventData = true;
              isStream = true;
              fbdo._httpCode = _HTTP_CODE_OK;
              clearStr(respBuf);
              respBuf = tmp;
              break;
            }
          }
        }

        if (!hasEventData || !hasEvent)
          clearStr(respBuf);

        charPos = 0;
      }

      if (millis() - dataTime > fbdo._tcpClient.client_timeout)
      {
        fbdo._httpCode = TCP_ERROR_READ_TIMEOUT;
        break;
      }
    }

    if (fbdo._httpCode == _HTTP_CODE_OK)
    {
      // JSON stream data?
      if (isStream)
      {
        fbdo._isStreamTimeout = false;
        fbdo._dataMillis = millis();

        if (hasEventData && hasEvent)
        {

          if (strposP(eventType.c_str(), fb_esp_pgm_str_15) != -1 || strposP(eventType.c_str(), fb_esp_pgm_str_16) != -1)
          {
            fbdo._eventType = eventType;
            bool samePath = true;

            // Parses json response for path
            p1 = strposP(respBuf.c_str(), fb_esp_pgm_str_17);
            if (p1 != -1)
            {
              p2 = strposP(respBuf.c_str(), fb_esp_pgm_str_3, p1 + strlen_P(fb_esp_pgm_str_17));
              if (p2 != -1)
              {
                char *buf = newP(p2 - p1 - strlen_P(fb_esp_pgm_str_17));
                strncpy(buf, respBuf.c_str() + p1 + strlen_P(fb_esp_pgm_str_17), p2 - p1 - strlen_P(fb_esp_pgm_str_17));
                samePath = strcmp(buf, fbdo._path.c_str()) == 0;
                fbdo._path = buf;
                delP(buf);
              }
            }

            // Parses json response for data
            getHeader(respBuf.c_str(), tmp, fb_esp_pgm_str_18);
            if (tmp.length() > 0)
            {
              // trim last }
              tmp.remove(tmp.length() - 1, 1);

              fbdo._payload = tmp;
              clearStr(tmp);

              setDataType(fbdo, fbdo._payload.c_str());

              uint16_t crc = calCRC(fbdo._payload.c_str());
              bool sameData = crc == fbdo._payload_crc;
              fbdo._payload_crc = crc;

              // Any stream update?
              fbdo._streamDataChanged = !samePath || (samePath && !sameData && !fbdo._streamPathChanged);
              fbdo._dataAvailable = true;
            }

            fbdo._streamPathChanged = false;
          }
          else
          {
            // Firebase keep alive data
            if (strcmp_P(eventType.c_str(), fb_esp_pgm_str_11) == 0)
            {
              fbdo._isStreamTimeout = false;
              fbdo._dataMillis = millis();
            }

            // Firebase cancel and auth_revoked events
            if (strcmp_P(eventType.c_str(), fb_esp_pgm_str_83) == 0 || strcmp_P(eventType.c_str(), fb_esp_pgm_str_84) == 0)
            {
              fbdo._isStreamTimeout = false;
              fbdo._dataMillis = millis();
              fbdo._eventType = eventType;
              // make stream available status
              fbdo._streamDataChanged = true;
              fbdo._dataAvailable = true;
            }
          }
        }
      }
      else
      {
        // Just response payload
        fbdo._payload = respBuf;
        setDataType(fbdo, respBuf.c_str());

        // Push (POST) data?
        if (fbdo._r_method == firebase_method_post)
        {
          p1 = strposP(respBuf.c_str(), fb_esp_pgm_str_20);
          if (p1 != -1)
          {
            p2 = strposP(respBuf.c_str(), fb_esp_pgm_str_3, p1 + strlen_P(fb_esp_pgm_str_20));
            if (p2 != -1)
            {
              char *buf = newP(p2 - p1 - strlen_P(fb_esp_pgm_str_20));
              strncpy(buf, respBuf.c_str() + p1 + strlen_P(fb_esp_pgm_str_20), p2 - p1 - strlen_P(fb_esp_pgm_str_20));
              fbdo._pushName = buf;
              delP(buf);
              fbdo._dataType = 0;
              clearStr(fbdo._payload);
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
          clearStr(fbdo._path);
          clearStr(fbdo._payload);
          clearStr(fbdo._pushName);
          fbdo._dataType = 0;
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
      bool _c1 = fbdo._dataType == firebase_data_type_float || fbdo._dataType == firebase_data_type_double || fbdo._dataType == firebase_data_type_integer;
      bool _c2 = fbdo._last_dataType == firebase_data_type_float || fbdo._last_dataType == firebase_data_type_double || fbdo._last_dataType == firebase_data_type_integer;

      if (fbdo._last_dataType == firebase_data_type_any || fbdo._last_dataType == fbdo._dataType || (_c1 && _c2))
        fbdo._mismatchDataType = false;
      else
        fbdo._mismatchDataType = true;
    }

    return fbdo._httpCode == _HTTP_CODE_OK || fbdo._httpCode == 0;
  }

  if (fbdo._isStream)
    return true;

  return false;
}

bool Firebase_Class::connectStream(FirebaseData &fbdo, const char *path)
{

  // return true if paused
  if (fbdo._paused)
  {
    closeTCP(fbdo);
    return true;
  }

  if (fbdo._tcpClient.connected() && fbdo._isStream && strcmp(path, fbdo._streamPath.c_str()) == 0)
    return true;

  if (strlen(path) == 0 || _host.length() == 0 || _auth.length() == 0)
  {
    fbdo._httpCode = _HTTP_CODE_BAD_REQUEST;
    return false;
  }

  fbdo._dataMillis = millis();

  return connect(fbdo, path, firebase_method_stream, firebase_data_type_string, "") == 0;
}

bool Firebase_Class::handleStream(FirebaseData &fbdo)
{

  // return true if paused
  if (fbdo._paused)
  {
    closeTCP(fbdo);
    return true;
  }

  autoConnectWiFi();

  clearFlag(fbdo);

  String path = fbdo._streamPath;

  if (fbdo._isStreamTimeout)
  {
    fbdo._dataMillis = millis();
    fbdo._isStreamTimeout = false;
  }
  else
  {
    // Stream timed out
    if (fbdo._dataMillis > 0 && millis() - fbdo._dataMillis > KEEP_ALIVE_TIMEOUT)
    {
      fbdo._isStreamTimeout = true;
      // close connection
      closeTCP(fbdo);
    }
  }

  if (!fbdo._tcpClient.connected())
    connectStream(fbdo, path.c_str());

  bool ret = handleResponse(fbdo);

  if (!ret)
    closeTCP(fbdo);

  return ret;
}

void Firebase_Class::closeTCP(FirebaseData &fbdo)
{
  fbdo._tcpClient.close();
}

void Firebase_Class::delP(char *p)
{
  if (p != nullptr)
    delete[] p;
  p = nullptr;
}

char *Firebase_Class::newP(size_t len)
{
  char *p = new char[len + 1];
  memset(p, 0, len + 1);
  return p;
}

char *Firebase_Class::strP(PGM_P pgm)
{
  size_t len = strlen_P(pgm) + 1;
  char *buf = newP(len);
  strcat_P(buf, pgm);
  return buf;
}

void Firebase_Class::appendP(char *buf, PGM_P pgm, bool empty)
{
  if (empty)
    memset(buf, 0, strlen(buf));
  strcat_P(buf, pgm);
}

void Firebase_Class::buildFirebaseRequest(String &req, FirebaseData &fbdo, const char *host, uint8_t method, const char *path, const char *auth, int payloadLength)
{
  char *buf = newP(400);
  if (method == firebase_method_stream)
  {
    appendP(buf, fb_esp_pgm_str_22);
    fbdo._isStream = true;
  }
  else
  {
    if (method == firebase_method_put || method == firebase_method_put_silent)
      appendP(buf, fb_esp_pgm_str_23);
    else if (method == firebase_method_post)
      appendP(buf, fb_esp_pgm_str_24);
    else if (method == firebase_method_get)
      appendP(buf, fb_esp_pgm_str_25);
    else if (method == firebase_method_patch || method == firebase_method_patch_silent)
      appendP(buf, fb_esp_pgm_str_26);
    else if (method == firebase_method_delete)
      appendP(buf, fb_esp_pgm_str_27);
    appendP(buf, fb_esp_pgm_str_6);

    fbdo._isStream = false;
  }

  if (strlen(path) > 0)
  {
    if (path[0] != '/')
      appendP(buf, fb_esp_pgm_str_1);
  }

  strcat(buf, path);

  if (method == firebase_method_patch || method == firebase_method_patch_silent)
    appendP(buf, fb_esp_pgm_str_1);

  appendP(buf, fb_esp_pgm_str_2);

  strcat(buf, auth);

  if (method == firebase_method_get && fbdo.queryFilter._orderBy.length() > 0)
  {
    appendP(buf, fb_esp_pgm_str_96);
    strcat(buf, fbdo.queryFilter._orderBy.c_str());

    if (fbdo.queryFilter._limitToFirst.length() > 0)
    {
      appendP(buf, fb_esp_pgm_str_97);
      strcat(buf, fbdo.queryFilter._limitToFirst.c_str());
    }

    if (fbdo.queryFilter._limitToLast.length() > 0)
    {
      appendP(buf, fb_esp_pgm_str_98);
      strcat(buf, fbdo.queryFilter._limitToLast.c_str());
    }

    if (fbdo.queryFilter._startAt.length() > 0)
    {
      appendP(buf, fb_esp_pgm_str_99);
      strcat(buf, fbdo.queryFilter._startAt.c_str());
    }

    if (fbdo.queryFilter._endAt.length() > 0)
    {

      appendP(buf, fb_esp_pgm_str_100);
      strcat(buf, fbdo.queryFilter._endAt.c_str());
    }

    if (fbdo.queryFilter._equalTo.length() > 0)
    {
      appendP(buf, fb_esp_pgm_str_101);
      strcat(buf, fbdo.queryFilter._equalTo.c_str());
    }
  }

  if (method == firebase_method_put_silent || method == firebase_method_patch_silent)
    appendP(buf, fb_esp_pgm_str_29);

  appendP(buf, fb_esp_pgm_str_30);
  appendP(buf, fb_esp_pgm_str_31);

  strcat(buf, host);

  appendP(buf, fb_esp_pgm_str_21);
  appendP(buf, fb_esp_pgm_str_32);

  if (method == firebase_method_stream)
  {
    appendP(buf, fb_esp_pgm_str_34);
    appendP(buf, fb_esp_pgm_str_35);
  }
  else
  {
    appendP(buf, fb_esp_pgm_str_36);
    appendP(buf, fb_esp_pgm_str_37);
  }

  appendP(buf, fb_esp_pgm_str_38);

  if (method == firebase_method_put || method == firebase_method_put_silent || method == firebase_method_post || method == firebase_method_patch || method == firebase_method_patch_silent)
  {
    appendP(buf, fb_esp_pgm_str_12);
    strcat(buf, NumToString(payloadLength).get());
  }

  appendP(buf, fb_esp_pgm_str_21);
  appendP(buf, fb_esp_pgm_str_21);

  req = buf;
  delete[] buf;
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

    if (!typeSet)
    {
      if (strcmp_P(data, fb_esp_pgm_str_87) == 0 || strcmp(data, fb_esp_pgm_str_85) == 0)
      {
        typeSet = true;
        fbdo._dataType = firebase_data_type_boolean;
      }
    }

    if (!typeSet && data[0] == '"')
    {
      typeSet = true;
      fbdo._dataType = firebase_data_type_string;
    }

    if (!typeSet && strcmp_P(data, fb_esp_pgm_str_19) == 0)
    {
      typeSet = true;
      fbdo._dataType = firebase_data_type_null;
    }

    if (!typeSet)
    {
      typeSet = true;

      if (strposP(data, fb_esp_pgm_str_4) != -1)
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

#if defined(__AVR__)
        unsigned long long v1 = (data[0] == '-') ? wstrtoull(&data[1]) : wstrtoull(data);
#else
        char *eptr;
        unsigned long long v1 = (data[0] == '-') ? strtoull(&data[1], &eptr, 10) : strtoull(data, &eptr, 10);
#endif

        unsigned long long v2 = (sizeof(int) == 2) ? 0xffff / 2 : 0xffffffff / 2;

        if (data[0] == '-')
          fbdo._dataType = (v1 > v2) ? firebase_data_type_integer64 : firebase_data_type_integer;
        else
          fbdo._dataType = (v1 > v2) ? firebase_data_type_unsigned_integer64 : firebase_data_type_integer;
      }
    }
  }
  else
  {
    fbdo._dataType = firebase_data_type_null;
  }

  fbdo._dataTypeNum = fbdo._dataType;
}

unsigned long long Firebase_Class::wstrtoull(const char *s)
{
  unsigned long long y = 0;

  for (int i = 0; i < (int)strlen(s); i++)
  {
    char c = s[i];
    if (c < '0' || c > '9')
      break;
    y *= 10;
    y += (c - '0');
  }

  return y;
}

long long Firebase_Class::wstrtoll(const char *s)
{
  long long y = 0;

  int ofs = s[0] == '-' ? 1 : 0;

  for (int i = ofs; i < (int)strlen(s); i++)
  {
    char c = s[i];
    if (c < '0' || c > '9')
      break;
    y *= 10;
    y += (c - '0');
  }

  if (ofs == 1)
    y *= -1;

  return y;
}

void Firebase_Class::clearFlag(FirebaseData &fbdo)
{
  fbdo._bufferOverflow = false;
  fbdo._streamDataChanged = false;
  fbdo._streamPathChanged = false;
  fbdo._dataAvailable = false;
  clearStr(fbdo._pushName);
}

char *Firebase_Class::errorToString(int httpCode)
{
  char *buf = nullptr;
  switch (httpCode)
  {
  case TCP_ERROR_CONNECTION_REFUSED:
    buf = strP(fb_esp_pgm_str_39);
    break;
  case TCP_ERROR_SEND_DATA_FAILED:
    buf = strP(fb_esp_pgm_str_40);
    break;
  case TCP_ERROR_NOT_CONNECTED:
    buf = strP(fb_esp_pgm_str_42);
    break;
  case TCP_ERROR_CONNECTION_LOST:
    buf = strP(fb_esp_pgm_str_43);
    break;
  case TCP_ERROR_NO_HTTP_SERVER:
    buf = strP(fb_esp_pgm_str_44);
    break;
  case _HTTP_CODE_BAD_REQUEST:
    buf = strP(fb_esp_pgm_str_45);
    break;
  case _HTTP_CODE_NON_AUTHORITATIVE_INFORMATION:
    buf = strP(fb_esp_pgm_str_46);
    break;
  case _HTTP_CODE_NO_CONTENT:
    buf = strP(fb_esp_pgm_str_47);
    break;
  case _HTTP_CODE_MOVED_PERMANENTLY:
    buf = strP(fb_esp_pgm_str_48);
    break;
  case _HTTP_CODE_USE_PROXY:
    buf = strP(fb_esp_pgm_str_49);
    break;
  case _HTTP_CODE_TEMPORARY_REDIRECT:
    buf = strP(fb_esp_pgm_str_50);
    break;
  case _HTTP_CODE_PERMANENT_REDIRECT:
    buf = strP(fb_esp_pgm_str_51);
    break;
  case _HTTP_CODE_UNAUTHORIZED:
    buf = strP(fb_esp_pgm_str_52);
    break;
  case _HTTP_CODE_FORBIDDEN:
    buf = strP(fb_esp_pgm_str_53);
    break;
  case _HTTP_CODE_NOT_FOUND:
    buf = strP(fb_esp_pgm_str_54);
    break;
  case _HTTP_CODE_METHOD_NOT_ALLOWED:
    buf = strP(fb_esp_pgm_str_55);
    break;
  case _HTTP_CODE_NOT_ACCEPTABLE:
    buf = strP(fb_esp_pgm_str_56);
    break;
  case _HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED:
    buf = strP(fb_esp_pgm_str_57);
    break;
  case _HTTP_CODE_REQUEST_TIMEOUT:
    buf = strP(fb_esp_pgm_str_58);
    break;
  case _HTTP_CODE_LENGTH_REQUIRED:
    buf = strP(fb_esp_pgm_str_59);
    break;
  case _HTTP_CODE_TOO_MANY_REQUESTS:
    buf = strP(fb_esp_pgm_str_60);
    break;
  case _HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE:
    buf = strP(fb_esp_pgm_str_61);
    break;
  case _HTTP_CODE_INTERNAL_SERVER_ERROR:
    buf = strP(fb_esp_pgm_str_62);
    break;
  case _HTTP_CODE_BAD_GATEWAY:
    buf = strP(fb_esp_pgm_str_63);
    break;
  case _HTTP_CODE_SERVICE_UNAVAILABLE:
    buf = strP(fb_esp_pgm_str_64);
    break;
  case _HTTP_CODE_GATEWAY_TIMEOUT:
    buf = strP(fb_esp_pgm_str_65);
    break;
  case _HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED:
    buf = strP(fb_esp_pgm_str_66);
    break;
  case _HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED:
    buf = strP(fb_esp_pgm_str_67);
    break;
  case TCP_ERROR_READ_TIMEOUT:
    buf = strP(fb_esp_pgm_str_69);
    break;
  case FIREBASE_ERROR_DATA_TYPE_MISMATCH:
    buf = strP(fb_esp_pgm_str_70);
    break;
  case FIREBASE_ERROR_PATH_NOT_EXIST:
    buf = strP(fb_esp_pgm_str_71);
    break;
  case TCP_ERROR_CONNECTION_INUSED:
    buf = strP(fb_esp_pgm_str_94);
    break;
  case FIREBASE_ERROR_BUFFER_OVERFLOW:
    buf = strP(fb_esp_pgm_str_68);
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

void FirebaseData::clear()
{
  Firebase.clearStr(_path);
  Firebase.clearStr(_payload);
  if (!_isStream)
    Firebase.clearStr(_streamPath);
  Firebase.clearStr(_pushName);
  Firebase.clearStr(_redirectURL);
  Firebase.clearStr(_firebaseError);
  Firebase.clearStr(_eventType);
}

void FirebaseData::end()
{
  _tcpClient.close();
  _paused = true;
  clear();
}

WiFiSSLClient FirebaseData::getWiFiClient()
{
  return _tcpClient.client;
}

bool FirebaseData::pauseFirebase(bool pause)
{
  _paused = pause;
  _tcpClient.close();
  return !_tcpClient.connected();
}

String FirebaseData::dataType()
{
  char *buf = nullptr;
  if (_dataType == firebase_data_type_json)
    buf = Firebase.strP(fb_esp_pgm_str_74);
  if (_dataType == firebase_data_type_array)
    buf = Firebase.strP(fb_esp_pgm_str_103);
  else if (_dataType == firebase_data_type_string)
    buf = Firebase.strP(fb_esp_pgm_str_75);
  else if (_dataType == firebase_data_type_double)
    buf = Firebase.strP(fb_esp_pgm_str_92);
  else if (_dataType == firebase_data_type_float)
    buf = Firebase.strP(fb_esp_pgm_str_76);
  else if (_dataType == firebase_data_type_boolean)
    buf = Firebase.strP(fb_esp_pgm_str_91);
  else if (_dataType == firebase_data_type_integer)
    buf = Firebase.strP(fb_esp_pgm_str_77);
  else if (_dataType == firebase_data_type_integer64)
    buf = Firebase.strP(fb_esp_pgm_str_41);
  else if (_dataType == firebase_data_type_unsigned_integer64)
    buf = Firebase.strP(fb_esp_pgm_str_93);
  else if (_dataType == firebase_data_type_null)
    buf = Firebase.strP(fb_esp_pgm_str_78);
  String res = buf;
  Firebase.delP(buf);
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
  if (_payload.length() > 0 && (_dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
    return atoi(_payload.c_str());
  else
    return 0;
}

unsigned long long FirebaseData::uint64Data()
{
  if (_payload.length() > 0 && (_dataType == firebase_data_type_unsigned_integer64 || _dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
  {
#if defined(__AVR__)
    unsigned long long v = Firebase.wstrtoull(_payload.c_str());
#else
    char *eptr;
    unsigned long long v = strtoull(_payload.c_str(), &eptr, 10);
#endif

    return v;
  }
  return 0;
}

long long FirebaseData::int64Data()
{
  if (_payload.length() > 0 && (_dataType == firebase_data_type_integer64 || _dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
  {
#if defined(__AVR__)
    long long v = Firebase.wstrtoll(_payload.c_str());
#else
    char *eptr;
    long long v = strtoll(_payload.c_str(), &eptr, 10);
#endif
    return v;
  }

  return 0;
}

double FirebaseData::doubleData()
{

  if (_payload.length() > 0 && (_dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
    return atof(_payload.c_str());

  return 0.0;
}

float FirebaseData::floatData()
{
  if (_payload.length() > 0 && (_dataType == firebase_data_type_integer || _dataType == firebase_data_type_double || _dataType == firebase_data_type_float))
    return atof(_payload.c_str());

  return 0.0;
}

bool FirebaseData::boolData()
{
  bool res = false;
  if (_payload.length() > 0 && _dataType == firebase_data_type_boolean)
    res = _payload == "true";

  return res;
}

String FirebaseData::stringData()
{
  if (_payload.length() > 0 && _dataType == firebase_data_type_string)
    return _payload.substring(1, _payload.length() - 1);

  return String();
}

String FirebaseData::jsonData()
{
  if (_payload.length() > 0 && _dataType == firebase_data_type_json)
    return _payload;

  return String();
}

String FirebaseData::arrayData()
{
  if (_payload.length() > 0 && _dataType == firebase_data_type_array)
    return _payload;

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
  return _tcpClient.connected();
}

bool FirebaseData::streamTimeout()
{
  if (_paused)
    return false;

  return _isStreamTimeout;
}

bool FirebaseData::dataAvailable()
{
  return _dataAvailable;
}

bool FirebaseData::streamAvailable()
{
  return _dataAvailable && _streamDataChanged;
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
  return _payload;
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
  if (_firebaseError.length() > 0)
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
  Firebase.clearStr(_orderBy);
  Firebase.clearStr(_limitToFirst);
  Firebase.clearStr(_limitToLast);
  Firebase.clearStr(_limitToLast);
  Firebase.clearStr(_startAt);
  Firebase.clearStr(_endAt);
  Firebase.clearStr(_equalTo);
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
