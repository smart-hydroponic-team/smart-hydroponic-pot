#pragma once

#include <Arduino.h>

namespace WiFiConnection
{
    void connect(const String& ssid, const String& password);
    void disconnect();
    bool isConnected();
    bool isConnecting();
}
