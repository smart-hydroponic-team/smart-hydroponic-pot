## Local configuration

The project requires a local `secrets.ini` file containing credentials used by the Wi-Fi provisioning access point.

### Setup

1. Copy `secrets.example.ini` and rename the copy to `secrets.ini`.
2. Open `secrets.ini`.
3. Configure the following variables:

| Variable | Description |
|---|---|
| `AP_SSID` | Name of the Wi-Fi network broadcast by the device during provisioning |
| `AP_PASSWORD` | Password required to connect to the provisioning network. Must contain at least **8 characters** (WPA2 requirement). |

**Important:** The access point password must be at least 8 characters long. Shorter passwords will prevent the access point from starting.