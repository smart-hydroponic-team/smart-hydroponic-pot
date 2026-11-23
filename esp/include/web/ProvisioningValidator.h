#pragma once

namespace ProvisioningValidator {
    bool validate(
        const char* ssid,
        const char* wifiPassword,
        const char* username,
        const char* apiPassword
    );
}
