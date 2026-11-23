#include "web/ProvisioningValidator.h"

namespace ProvisioningValidator
{
    bool validate(const Config::ProvisioningConfig& config)
    {
        return config.wifiSsid.length() > 0 &&
               config.wifiPassword.length() > 0 &&
               config.apiUsername.length() > 0 &&
               config.apiPassword.length() > 0;
    }
}
