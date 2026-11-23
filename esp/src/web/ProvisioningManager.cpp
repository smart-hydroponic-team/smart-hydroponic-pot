#include "config/ProvisioningManager.h"

#include <ArduinoJson.h>

#ifdef ESP8266
#include <LittleFS.h>
#else
#include <LittleFS.h>
#endif

namespace ProvisioningManager
{
    namespace
    {
        constexpr const char* CONFIG_FILE = "/provisioning.json";

        bool isValid(const Config::ProvisioningConfig& config)
        {
            return config.wifiSsid.length() > 0 &&
                   config.wifiPassword.length() > 0 &&
                   config.apiUsername.length() > 0 &&
                   config.apiPassword.length() > 0;
        }
    }

    bool begin()
    {
        return LittleFS.begin();
    }

    bool saveConfig(const Config::ProvisioningConfig& config)
    {
        if (!isValid(config))
        {
            return false;
        }

        File file = LittleFS.open(CONFIG_FILE, "w");

        if (!file)
        {
            return false;
        }

        JsonDocument document;

        document["wifi"]["ssid"] = config.wifiSsid;
        document["wifi"]["password"] = config.wifiPassword;
        document["api"]["username"] = config.apiUsername;
        document["api"]["password"] = config.apiPassword;

        const size_t bytesWritten = serializeJson(document, file);

        file.close();

        return bytesWritten > 0;
    }

    bool loadConfig(Config::ProvisioningConfig& config)
    {
        if (!LittleFS.exists(CONFIG_FILE))
        {
            return false;
        }

        File file = LittleFS.open(CONFIG_FILE, "r");

        if (!file)
        {
            return false;
        }

        JsonDocument document;

        DeserializationError error = deserializeJson(document, file);

        file.close();

        if (error)
        {
            return false;
        }

        Config::ProvisioningConfig loadedConfig;

        loadedConfig.wifiSsid = document["wifi"]["ssid"].as<String>();
        loadedConfig.wifiPassword = document["wifi"]["password"].as<String>();
        loadedConfig.apiUsername = document["api"]["username"].as<String>();
        loadedConfig.apiPassword = document["api"]["password"].as<String>();

        if (!isValid(loadedConfig))
        {
            return false;
        }

        config = loadedConfig;

        return true;
    }

    bool hasConfig()
    {
        Config::ProvisioningConfig config;
        return loadConfig(config);
    }

    bool clearConfig()
    {
        if (!LittleFS.exists(CONFIG_FILE))
        {
            return true;
        }

        return LittleFS.remove(CONFIG_FILE);
    }
}
