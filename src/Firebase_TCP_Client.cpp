/*
 * Firebase TCP Client library, version 1.0.1
 *
 *
 * Created: March 3, 2022
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

#ifndef Firebase_TCP_Client_CPP
#define Firebase_TCP_Client_CPP

#include "Firebase_TCP_Client.h"

Firebase_TCP_Client::Firebase_TCP_Client()
{
}

Firebase_TCP_Client::~Firebase_TCP_Client()
{
  client.stop();
  host.remove(0, host.length());
}

bool Firebase_TCP_Client::begin(const char *host, uint16_t port)
{
  this->host = host;
  this->port = port;
  client.setTimeout(client_timeout);
  return true;
}

bool Firebase_TCP_Client::connected()
{
  return client.connected();
}

int Firebase_TCP_Client::send(const char *data)
{
  size_t size = strlen(data);

  if (!connect())
    return TCP_ERROR_CONNECTION_REFUSED;

  if (size > 0)
  {
    if (client.print(data) == size)
      return 0;
  }
  
  return TCP_ERROR_SEND_DATA_FAILED;
}

bool Firebase_TCP_Client::connect(void)
{
  if (connected())
  {
    while (client.available() > 0)
      client.read();
    return true;
  }

  if (!client.connect(host.c_str(), port))
    return false;

  return connected();
}

int Firebase_TCP_Client::available()
{
  return client.available();
}

int Firebase_TCP_Client::read()
{
  return client.read();
}

void Firebase_TCP_Client::close()
{
  if (client.connected())
  {
    while (client.available())
    {
      client.read();
    }
    client.stop();
  }

  host.remove(0, host.length());
}

#endif
