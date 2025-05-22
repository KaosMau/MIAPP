#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "DisplayManager.h"
#include "FirebaseManager.h"

// Pines del display
const int segPins[7] = {16, 15, 26, 27, 14, 4, 25};
const int digPins[8] = {5, 17, 18, 12, 19, 21, 22, 23};

// WiFi y Firebase
#define WIFI_SSID "INFINITUM8BAF"
#define WIFI_PASSWORD "7anDvTdyzZ"
#define FIREBASE_HOST "pia1-4739e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyD6MWwFlkKigBkog4xJzryUWpqPlO_dc4g"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -21600);
DisplayManager display(segPins, digPins);
FirebaseManager firebase(FIREBASE_HOST, FIREBASE_AUTH);

String currentMode = "manual";
unsigned long lastUpdate = 0;
unsigned long lastAutoChange = 0;
enum AutoDisplayState { SHOW_TEMP, SHOW_TIME, SHOW_DATE };
AutoDisplayState autoState = SHOW_TEMP;

void setup() {
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }
    Serial.println("WiFi conectado!");

    firebase.begin();
    timeClient.begin();
    timeClient.update();
    display.begin();
}

void loop() {
    if (millis() - lastUpdate >= 2000) {
        currentMode = firebase.getModo();

        static String lastMode = "";
        if (lastMode != currentMode) {
            autoState = SHOW_TEMP;
            lastAutoChange = millis();
            lastMode = currentMode;
        }

        if (currentMode == "manual") {
            String numero = firebase.getNumero();
            while (numero.length() < 8) numero = "0" + numero;
            display.displayString(numero);
        } else {
            if (millis() - lastAutoChange >= 3000) {
                autoState = static_cast<AutoDisplayState>((autoState + 1) % 3);
                lastAutoChange = millis();
            }

            switch (autoState) {
                case SHOW_TEMP:
                    display.displayTemperature();
                    break;
                case SHOW_TIME:
                    display.displayTime();
                    break;
                case SHOW_DATE:
                    display.displayDate();
                    break;
            }
        }

        lastUpdate = millis();
    }
}
