#include "web/ProvisioningServer.h"

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
