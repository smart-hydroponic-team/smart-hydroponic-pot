#pragma once

#include <Arduino.h>

namespace Config
{
    struct ProvisioningConfig
    {
        String wifiSsid;
        String wifiPassword;
        String apiUsername;
        String apiPassword;
    };
}
