#ifndef EVILTWIN_H
#define EVILTWIN_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include "Utils.h"

class EvilTwin {
public:
    void startEvilTwin(const String &ssid);
    void stopEvilTwin();

private:
    DNSServer dnsServer;
};

#endif // EVILTWIN_H