#ifndef DEAUTH_H
#define DEAUTH_H

#include <ESP8266WiFi.h>
#include "Utils.h"

class Deauth {
public:
    void performDeauth(const uint8_t *bssid, uint8_t channel);

private:
    unsigned long deauth_now = 0;
};

#endif // DEAUTH_H