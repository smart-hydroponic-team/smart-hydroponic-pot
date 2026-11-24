#pragma once

#include "config/ProvisioningConfig.h"

namespace ProvisioningManager
{
    bool begin();
    bool saveConfig(const Config::ProvisioningConfig& config);
    bool loadConfig(Config::ProvisioningConfig& config);
    bool hasConfig();
    bool clearConfig();
}
