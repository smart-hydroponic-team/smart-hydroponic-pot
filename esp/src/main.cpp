
#include <Arduino.h>

#include "network/AccessPoint.h"
#include "web/ProvisioningServer.h"
#include "config/ProvisioningManager.h"

void setup()
{
    Serial.begin(9600);

    if (!AccessPoint::start())
    {
        Serial.println("Failed to start Access Point");
        return;
    }

    Serial.println("Access Point started");
    Serial.println(AccessPoint::getIpAddress());

    if (!ProvisioningManager::begin())
    {
        Serial.println("Failed to initialize LittleFS");
        return;
    }

    Serial.println("LittleFS initialized");

    Config::ProvisioningConfig config;

    if (ProvisioningManager::loadConfig(config))
    {
        Serial.println("Provisioning configuration loaded");
    }
    else
    {
        Serial.println("No valid provisioning configuration found");
    }

    ProvisioningServer::start();
    Serial.println("Provisioning server started");
}

void loop()
{
    ProvisioningServer::handleClient();
}
