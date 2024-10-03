#ifndef WEBSERV_H
#define WEBSERV_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "ScanAp.h"
#include "Utils.h"
#include "Deauth.h"
#include "EvilTwin.h"

class WebServ
{
public:
    WebServ();
    void setupServer();
    void handleClient();
    void handleIndex();
    void handleResult();
    bool isDeauthingActive() const;
    Deauth &getDeauth();
    ScanAp::Network getSelectedNetwork() const;
    ScanAp &getScanAp();

private:
    DNSServer dnsServer;
    ESP8266WebServer webServer;
    ScanAp scanAp;
    ScanAp::Network selectedNetwork;
    Deauth deauth;
    EvilTwin evilTwin;
    bool hotspot_active;
    bool deauthing_active;
    String _correct;
    String _tryPassword;

    String header(String t);
    String index();
    String posted();
    String footer();
    String _tempHTML;
};

#endif // WEBSERV_H