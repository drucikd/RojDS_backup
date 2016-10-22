/* 
 * File:   LedBlinker.cpp
 * Author: drucik
 * 
 * Created on 22 października 2016, 20:10
 */

/*
 * State NORMAL / BLINKER
 * NORMAL blink 50ms+1 time /1s
 * BLINKER blink 50ms+5 time /1s
 * State ON/OFF
 */

#include <LedBlinker.h>

LedBlinker::LedBlinker(int reqPin) : ledPin(reqPin) {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);
    ledTimer.initializeMs(ledInterval, TimerDelegate(&LedBlinker::ledBlink, this));
    ledBlinkTimer.initializeMs(ledBlinkInterval, TimerDelegate(&LedBlinker::ledBlinkReturn, this));
    ledTimer.start();
}

void LedBlinker::on(bool reqOnOff) {
    ledState = reqOnOff;
}

void LedBlinker::blinker(bool reqOnOff) {
    ledBlinkerState = reqOnOff;
    
    ledTimer.stop();
    if (reqOnOff) { ledTimer.setIntervalMs(ledInterval / ledBlinkerCount); }
    else { ledTimer.setIntervalMs(ledInterval); }
    ledTimer.start();
}
//LedBlinker::LedBlinker(const LedBlinker& orig) {
//}

LedBlinker::~LedBlinker() {
}

void LedBlinker::ledBlink () { 
    digitalWrite(ledPin, !ledState); 
    ledBlinkTimer.startOnce();
}

void LedBlinker::ledBlinkReturn () { 
    digitalWrite(ledPin, ledState);
}
