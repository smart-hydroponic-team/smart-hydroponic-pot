#pragma once

#include <Arduino.h>

namespace AccessPoint {
    bool start();
    void stop();
    String getIpAddress();
}
