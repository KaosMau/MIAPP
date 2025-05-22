#include "DisplayManager.h"
#include <TimeLib.h>
#include <NTPClient.h>

extern NTPClient timeClient; // definido en main.ino

DisplayManager* DisplayManager::instance = nullptr;

DisplayManager::DisplayManager(const int segPins[7], const int digPins[8]) {
    memcpy(segmentPins, segPins, sizeof(segmentPins));
    memcpy(digitPins, digPins, sizeof(digitPins));
    memset(displayBuffer, 0, sizeof(displayBuffer));
    currentDigit = 0;
    instance = this;
}

void DisplayManager::begin() {
    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
        digitalWrite(segmentPins[i], LOW);
    }
    for (int i = 0; i < 8; i++) {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], HIGH);
    }
    startTimer();
}

void DisplayManager::startTimer() {
    timer = timerBegin(0, 80, true); // 1us per tick
    timerAttachInterrupt(timer, &DisplayManager::onTimerISR, true);
    timerAlarmWrite(timer, 1000, true); // 1ms
    timerAlarmEnable(timer);
}

void IRAM_ATTR DisplayManager::onTimerISR() {
    portENTER_CRITICAL_ISR(&instance->timerMux);

    for (int j = 0; j < 8; j++) digitalWrite(instance->digitPins[j], HIGH);
    instance->setSegments(instance->displayBuffer[instance->currentDigit]);
    digitalWrite(instance->digitPins[instance->currentDigit], LOW);

    instance->currentDigit = (instance->currentDigit + 1) % 8;

    portEXIT_CRITICAL_ISR(&instance->timerMux);
}

void DisplayManager::setSegments(uint8_t digit) {
    static const byte segmentCodes[14] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7D, 0x07, 0x7F, 0x6F,
        0x00, 0x39, 0x71 // space, C, F
    };
    byte code = (digit <= 12) ? segmentCodes[digit] : 0x00;
    for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], bitRead(code, i));
    }
}

uint8_t DisplayManager::charToSegment(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'C') return 11;
    if (c == 'F') return 12;
    return 10;
}

void DisplayManager::displayString(const String& str) {
    for (int i = 0; i < 8; i++) {
        char c = (i < str.length()) ? str.charAt(i) : ' ';
        displayBuffer[i] = charToSegment(c);
    }
}

void DisplayManager::displayTemperature() {
    displayString("33C  92F");
}

void DisplayManager::displayTime() {
    timeClient.update();
    String t = timeClient.getFormattedTime();
    String hora = t.substring(0, 2) + " " + t.substring(3, 5) + " " + t.substring(6, 8);
    displayString(hora);
}

void DisplayManager::displayDate() {
    timeClient.update();
    time_t raw = timeClient.getEpochTime();
    String d = String(day(raw));
    String m = String(month(raw));
    String y = String(year(raw) % 100);
    if (d.length() < 2) d = "0" + d;
    if (m.length() < 2) m = "0" + m;
    if (y.length() < 2) y = "0" + y;
    displayString(d + " " + m + " " + y);
}
