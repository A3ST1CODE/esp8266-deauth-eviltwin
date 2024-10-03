#include "Utils.h"

String Utils::bytesToStr(const uint8_t *b, uint32_t size)
{
    String str;
    const char ZERO = '0';
    const char DOUBLEPOINT = ':';
    for (uint32_t i = 0; i < size; i++)
    {
        if (b[i] < 0x10)
            str += ZERO;
        str += String(b[i], HEX);

        if (i < size - 1)
            str += DOUBLEPOINT;
    }
    return str;
}

String Utils::getTempHTML()
{
    return R"(
<html>
    <head>
        <meta name='viewport' content='initial-scale=1.0, width=device-width'>
        <title>Deauther</title>
        <style>
            body {
                background: #1a1a1a;
                color: #bfbfbf;
                font-family: sans-serif;
                margin: 0;
            }
            .content {max-width: 800px;margin: auto;}
            table {border-collapse: collapse; width: 100%;}
            th, td {
                padding: 10px 6px;
                text-align: left;
                border-style:solid;
                border-color: darkgray;
            }
            button {
                display: inline-block;
                height: 38px;
                padding: 0 20px;
                color:#fff;
                text-align: center;
                font-size: 11px;
                font-weight: 600;
                line-height: 38px;
                letter-spacing: .1rem;
                text-transform: uppercase;
                text-decoration: none;
                white-space: nowrap;
                background: #2f3136;
                border-radius: 4px;
                border: none;
                cursor: pointer;
                box-sizing: border-box;
            }
            button:hover {
                background: #42444a;
            }
            h1 {
                font-size: 1.7rem;
                margin-top: 1rem;
                background: #2f3136;
                color: #bfbfbb;
                padding: 0.2em 1em;
                border-radius: 3px;
                border-left: solid #0ba8cf 5px;
                font-weight: 100;
            }
        </style>
    </head>
    <body>
        <div class='content'>
        <p>
            <h1 style="border: solid #0ba8cf 3px; padding: 0.2em 0.2em; text-align: center; font-size: 2.5rem;">DEAUTHER</h1>
            <span>
                - This tool only purpose is to test the security of your own network.<br>
                - Use it only on your own network.<br>
                - Do not use it on networks you don't own.<br>
                - This tool is a modified version of the original Deauther project.<br>
                - Special Credits: spacehuhntech, M1z23R.
            </span>
        </p><br><hr><br>
        <h1>Actions</h1>
        <div>
            <form style='display:inline-block;' method='post' action='/?scan=scan'>
                <button style='display:inline-block;'>Scan</button>
            </form>
            <form style='display:inline-block; padding-left:8px;' method='post' action='/?deauth={deauth}'>
                <button style='display:inline-block;'{disabled}>{deauth_button}</button>
            </form>
            <form style='display:inline-block; padding-left:8px;' method='post' action='/?hotspot={hotspot}'>
                <button style='display:inline-block;'{disabled}>{hotspot_button}</button>
            </form>
        </div><br><hr><br>
        <h1>Targets</h1>
        <table>
            <tr><th>SSID</th><th>CH</th><th>RSSI</th><th>Select</th></tr>
)";
}

String Utils::getHeaderHTML(const String &title, const String &ssid, const String &subtitle)
{
    String CSS = "article { background: #f2f2f2; padding: 1.3em; }"
                 "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
                 "div { padding: 0.5em; }"
                 "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }"
                 "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #555555; }"
                 "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
                 "nav { background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
                 "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; } "
                 "textarea { width: 100%; }";
    return "<!DOCTYPE html><html>"
           "<head><title>" +
           ssid + " :: " + title + "</title>"
                                   "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
                                   "<style>" +
           CSS + "</style></head>"
                 "<body><nav><b>" +
           ssid + "</b> " + subtitle + "</nav><div><h1>" + title + "</h1></div><div>";
}

String Utils::getIndexHTML()
{
    return "<div>" + String(BODY) + "</ol></div><div><form action='/' >" +
           "<b>Password:</b> <center><input type=password name=password></input><input type=submit value=\"Sign in\"></form></center>";
}

String Utils::getPostedHTML()
{
    return String(POST_BODY) + "<script> setTimeout(function(){window.location.href = '/result';}, 15000); </script>";
}

String Utils::getFooterHTML()
{
    return "</div><div class=q><a>&#169; All rights reserved.</a></div>";
}