#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <WiFi.h>
#include <M5Core2.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>


class WIFI_NETWORK{
    private:
        const char* ssid = "";// Wi-FiのSSID
        const char* password = "";// Wi-Fiのパスワード

        const char* host = "script.google.com";
        const int httpsPort = 443;
        String url = "";
        String hostName;
        String dnsIP;
        String macAddress;

        WiFiClientSecure client;
        // HTTP通信開始
        HTTPClient http;

    public:
        void connectWifi();
        
        void printLocalTime(tm timeinfo);
        void printLocalDay(tm timeinfo);
        
        tm getLocalTimeInfo();
        bool nextSecondTime(tm *time);
        String getHostName();
        String getDNSAddress();
        String httpPOSTRequest(String values_to_post);
        String httpGETRequest(String values_to_post);
};

#endif //TIME_EVENT_H