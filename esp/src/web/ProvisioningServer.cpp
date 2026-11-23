
#include "web/ProvisioningServer.h"
#include "web/ProvisioningValidator.h"

#include <ArduinoJson.h>

#ifdef ESP8266
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif

namespace ProvisioningServer
{
#ifdef ESP8266
    ESP8266WebServer server(80);
#else
    WebServer server(80);
#endif

    void start()
    {
        server.on("/api/health", HTTP_GET, []()
                  { server.send(200, "application/json", "{\"status\":\"ok\"}"); });

        server.on("/api/provision", HTTP_POST, []()
                  {
            JsonDocument document;

            DeserializationError error = deserializeJson(document, server.arg("plain"));

            if (error) {
                server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
                return;
            }

            const char* ssid = document["wifi"]["ssid"];
            const char* wifiPassword = document["wifi"]["password"];
            const char* username = document["api"]["username"];
            const char* apiPassword = document["api"]["password"];

            if (!ProvisioningValidator::validate(
                    ssid, wifiPassword, username, apiPassword)) {
                server.send(400, "application/json", "{\"error\":\"Missing or empty fields\"}");
                return;
            }

            server.send(200, "application/json", "{\"status\":\"received\"}");
        });

        server.begin();
    }

    void stop()
    {
        server.stop();
    }

    void handleClient()
    {
        server.handleClient();
    }
}
