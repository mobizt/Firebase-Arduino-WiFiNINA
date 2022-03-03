/**
 * Google's Firebase Realtime Database Arduino Library for ARM/AVR WIFI Dev Boards based on WiFiNINA library, version 1.2.5
 *
 * This library required WiFiNINA Library to be installed.
 * https://github.com/arduino-libraries/WiFiNINA
 *
 * Created: March 3, 2022
 *
 * Updates:
 * - Reduced program size.
 * - Improve stabilities.
 *
 *
 * This library provides ARM/AVR WIFI Development Boards to perform REST API by GET PUT, POST, PATCH, DELETE data from/to with Google's Firebase database using get, set, update
 * and delete calls.
 *
 * The library was test and work well with ESP32s based module and add support for multiple stream event path.
 *
 * The MIT License (MIT)
 *
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

#include <SPI.h>
#include <WiFiNINA.h>
#include "Firebase.h"