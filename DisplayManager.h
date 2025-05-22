#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Arduino.h>

class DisplayManager {
public:
    DisplayManager(const int segmentPins[7], const int digitPins[8]);
    void begin();
    void updateDisplay();
    void displayString(const String& str);
    void displayTemperature();
    void displayTime();
    void displayDate();

private:
    int segmentPins[7];
    int digitPins[8];
    uint8_t displayBuffer[8];
    volatile int currentDigit;

    hw_timer_t* timer = nullptr;
    portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

    static DisplayManager* instance;
    static void IRAM_ATTR onTimerISR();

    void setSegments(uint8_t digit);
    uint8_t charToSegment(char c);
    void startTimer();
};

#endif
