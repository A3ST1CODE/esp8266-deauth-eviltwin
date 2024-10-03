#ifndef SCANAP_H
#define SCANAP_H

#include <ESP8266WiFi.h>

class ScanAp {
public:
    struct Network {
        String ssid;
        uint8_t ch;
        uint8_t bssid[6];
        int rssi;
    };

    ScanAp();
    void performScan();
    Network getNetwork(int index);
    int getNetworkCount();

private:
    Network networks[16];
    void clearArray();
};

#endif // SCANAP_H