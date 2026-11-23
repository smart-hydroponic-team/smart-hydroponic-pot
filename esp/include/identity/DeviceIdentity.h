#pragma once

#include <Arduino.h>

namespace DeviceIdentity
{
    bool begin();
    String getId();
}
