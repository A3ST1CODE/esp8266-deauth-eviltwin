# ESP8266 Web Server with Deauthentication and Evil Twin Attack

This project implements a web server on an ESP8266 microcontroller that allows for deauthentication attacks and Evil Twin attacks. The web server provides a user-friendly interface to control these functionalities directly from your browser.

## Features

- **Web Server**: Serves a web interface to control the ESP8266 functionalities.
- **Deauthentication Attack**: Disconnects clients from a WiFi network by sending deauth packets.
- **Evil Twin Attack**: Creates a fake access point to capture credentials or mislead users.
- **WiFi Network Scanning**: Scans and lists available WiFi networks in the vicinity.
- **Password Validation**: Validates the entered password and provides feedback.

## Components

1. **WebServ**  
   Handles the web server setup and client requests.

2. **ScanAp**  
   Scans for available WiFi networks and stores the results.

3. **Utils**  
   Provides utility functions for HTML generation and byte-string conversion.

4. **EvilTwin**  
   Manages the creation and stopping of the Evil Twin access point.

5. **Deauth**  
   Performs deauthentication attacks on specified WiFi networks.

## File Structure

- `WebServ.h` / `WebServ.cpp`: Web server implementation.
- `ScanAp.h` / `ScanAp.cpp`: WiFi network scanning implementation.
- `Utils.h` / `Utils.cpp`: Utility functions for handling HTML and data conversions.
- `EvilTwin.h` / `EvilTwin.cpp`: Evil Twin attack implementation.
- `Deauth.h` / `Deauth.cpp`: Deauthentication attack implementation.
- `esp8266-deauth-eviltwin.ino`: Main Arduino sketch.

## Setup

### Hardware Requirements:
- ESP8266 microcontroller (e.g., NodeMCU or Wemos D1 Mini)
- USB cable for programming

### Software Requirements:
- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP8266 board package installed in Arduino IDE

### Library Dependencies:
- `ESP8266WiFi`
- `DNSServer`
- `ESP8266WebServer`

### Instructions for Deauther Installation

1. Go into the `esp8266-deauth-eviltwin` folder and open `esp8266-deauth-eviltwin.ino` with Arduino IDE.
2. In Arduino IDE, go to **File > Preferences** and add this URL to the **Additional Boards Manager URLs**:  
   `https://raw.githubusercontent.com/SpacehuhnTech/arduino/main/package_spacehuhn_index.json`.
3. Now go to **Tools > Board > Boards Manager**, search for "Deauther," and install **Deauther ESP8266 Boards**.
4. Select your board at **Tools > Board** and ensure it is set to **Deauther ESP8266 Boards** (not ESP8266 Modules).
5. Plug in your Deauther and select its COM port at **Tools > Port**.
6. Optional: To reset or override previous settings, select **Tools > Erase Flash > All Flash Contents**.
7. Press **Upload** to upload the sketch to the board.
   
## Installation
1. ```bash
   git clone https://github.com/A3ST1CODE/esp8266-deauth-eviltwin.git
2. Open the `esp8266-deauth-eviltwin.ino` file in Arduino IDE.
3. Select the correct ESP8266 board and port in the Arduino IDE settings.
4. Upload the sketch to the ESP8266.

## Usage

1. Connect to the ESP8266's access point (SSID: **Deauther**, Password: **deauther**).
2. Open a web browser and navigate to `http://192.168.4.1`.
3. Use the web interface to:
   - Scan for WiFi networks.
   - Start/Stop Deauthentication attacks.
   - Start/Stop the Evil Twin attack.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Disclaimer

This project is intended for **educational purposes only**. You are responsible for using it responsibly and ethically. Do not use it to harm others or violate any laws. The authors are not responsible for any misuse of this project.

## Acknowledgements

- ESP8266 Community
- Arduino

## Special Credits

Special thanks to [SpacehuhnTech](https://github.com/spacehuhntech) and [M1z23R](https://github.com/M1z23R) for their contributions and inspiration.

---

For any issues or contributions, please open an issue or submit a pull request on the GitHub repository.

Happy hacking!
