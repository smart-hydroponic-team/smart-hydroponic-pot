#include "network/WiFiConnection.h"

#include "config/Secrets.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

namespace
{
    bool connectionAttemptStarted = false;
    unsigned long connectionStartTime = 0;
    const unsigned long CONNECTION_TIMEOUT = 15000;
}

namespace WiFiConnection
{
    void connect(const String& ssid, const String& password)
    {
        WiFi.mode(WIFI_AP_STA);

        String macAddress = WiFi.macAddress();
        macAddress.replace(":", "");

        String hostname = "SmartPot-" +
                          macAddress.substring(macAddress.length() - 6);

#ifdef ESP8266
        WiFi.hostname(hostname.c_str());
#else
        WiFi.setHostname(hostname.c_str());
#endif

        IPAddress apIp;
        apIp.fromString(AP_IP);

        WiFi.softAPConfig(
            apIp,
            apIp,
            IPAddress(255, 255, 255, 0)
        );

        WiFi.begin(ssid.c_str(), password.c_str());

        connectionAttemptStarted = true;
        connectionStartTime = millis();
    }

    void disconnect()
    {
        WiFi.disconnect();
        connectionAttemptStarted = false;
    }

    bool isConnected()
    {
        return WiFi.status() == WL_CONNECTED;
    }

    bool isConnecting()
    {
        if (!connectionAttemptStarted)
        {
            return false;
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            connectionAttemptStarted = false;
            return false;
        }

        if (WiFi.status() == WL_CONNECT_FAILED ||
            WiFi.status() == WL_NO_SSID_AVAIL ||
            millis() - connectionStartTime >= CONNECTION_TIMEOUT)
        {
            connectionAttemptStarted = false;
            return false;
        }

        return true;
    }
}
