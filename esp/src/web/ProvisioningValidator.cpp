#include "web/ProvisioningValidator.h"

namespace ProvisioningValidator
{
    bool validate(
        const char* ssid,
        const char* wifiPassword,
        const char* username,
        const char* apiPassword
    )
    {
        return ssid && *ssid &&
               wifiPassword && *wifiPassword &&
               username && *username &&
               apiPassword && *apiPassword;
    }
}
