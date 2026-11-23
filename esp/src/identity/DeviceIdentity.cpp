
#include "identity/DeviceIdentity.h"

#include <Arduino.h>

#ifdef ESP8266
#include <LittleFS.h>
#include <user_interface.h>
#else
#include <LittleFS.h>
#include <esp_system.h>
#endif

namespace DeviceIdentity
{
    namespace
    {
        constexpr const char* DEVICE_ID_FILE = "/device-id.txt";

        String deviceId;

        uint32_t getRandomValue()
        {
#ifdef ESP8266
            return os_random();
#else
            return esp_random();
#endif
        }

        String generateUuid()
        {
            uint8_t bytes[16];

            for (int i = 0; i < 16; i += 4)
            {
                uint32_t randomValue = getRandomValue();

                bytes[i] = randomValue >> 24;
                bytes[i + 1] = randomValue >> 16;
                bytes[i + 2] = randomValue >> 8;
                bytes[i + 3] = randomValue;
            }

            bytes[6] = (bytes[6] & 0x0F) | 0x40;
            bytes[8] = (bytes[8] & 0x3F) | 0x80;

            char uuid[37];

            snprintf(
                uuid,
                sizeof(uuid),
                "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                bytes[0], bytes[1], bytes[2], bytes[3],
                bytes[4], bytes[5],
                bytes[6], bytes[7],
                bytes[8], bytes[9],
                bytes[10], bytes[11], bytes[12],
                bytes[13], bytes[14], bytes[15]);

            return String(uuid);
        }
    }

    bool begin()
    {

        if (LittleFS.exists(DEVICE_ID_FILE))
        {
            File file = LittleFS.open(DEVICE_ID_FILE, "r");

            if (!file)
            {
                return false;
            }

            String storedId = file.readString();
            file.close();
            storedId.trim();

            if (storedId.length() == 36)
            {
                deviceId = storedId;
                return true;
            }
        }

        deviceId = generateUuid();

        File file = LittleFS.open(DEVICE_ID_FILE, "w");

        if (!file)
        {
            deviceId = "";
            return false;
        }

        size_t bytesWritten = file.print(deviceId);
        file.close();

        if (bytesWritten != 36)
        {
            deviceId = "";
            return false;
        }

        return true;
    }

    String getId()
    {
        return deviceId;
    }
}
