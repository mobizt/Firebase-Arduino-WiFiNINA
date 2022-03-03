#ifndef FIREBASE_WIFI_CLIENT_CONFIG_H
#define FIREBASE_WIFI_CLIENT_CONFIG_H

#if __has_include(<WiFiNINA.h>)
#include <WiFiNINA.h>
#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#endif

#endif