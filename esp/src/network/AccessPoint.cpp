#include "network/AccessPoint.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include "config/Secrets.h"

namespace AccessPoint
{

    bool start()
    {
        WiFi.mode(WIFI_AP);

        return WiFi.softAP(AP_SSID, AP_PASSWORD);
    }

    void stop()
    {
        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_OFF);
    }

    String getIpAddress()
    {
        return WiFi.softAPIP().toString();
    }

}
