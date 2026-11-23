## Local configuration

The project requires a local `secrets.ini` file containing credentials used by the ESP32 provisioning access point.

### Setup

1. Copy `secrets.example.ini` and rename the copy to `secrets.ini`.
2. Open `secrets.ini`.
3. Configure the following variables:

| Variable | Description |
|---|---|
| `AP_SSID` | Name of the Wi-Fi network broadcast by ESP32 during provisioning |
| `AP_PASSWORD` | Password required to connect to the provisioning network |