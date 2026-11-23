#include "network/AccessPoint.h"

#include <WiFi.h>
#include "config/Secrets.h"

namespace AccessPoint {

    bool start() {
        WiFi.mode(WIFI_AP);

        return WiFi.softAP(AP_SSID, AP_PASSWORD);
    }

    void stop() {
        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_OFF);
    }

}
