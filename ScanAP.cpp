#include "ScanAP.h"

ScanAp::ScanAp() {
    clearArray();
}

void ScanAp::clearArray() {
    for (int i = 0; i < 16; i++) {
        Network network;
        networks[i] = network;
    }
}

void ScanAp::performScan() {
    int n = WiFi.scanNetworks();
    clearArray();
    if (n >= 0) {
        for (int i = 0; i < n && i < 16; ++i) {
            Network network;
            network.ssid = WiFi.SSID(i);
            for (int j = 0; j < 6; j++) {
                network.bssid[j] = WiFi.BSSID(i)[j];
            }
            network.ch = WiFi.channel(i);
            network.rssi = WiFi.RSSI(i);
            networks[i] = network;
        }
    }
}

ScanAp::Network ScanAp::getNetwork(int index) {
    if (index >= 0 && index < 16) {
        return networks[index];
    }
    Network emptyNetwork;
    return emptyNetwork;
}

int ScanAp::getNetworkCount() {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (networks[i].ssid != "") {
            count++;
        }
    }
    return count;
}