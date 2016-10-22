/* 
 * File:   LedBlinker.h
 * Author: drucik
 *
 * Created on 22 października 2016, 20:10
 */

#ifndef LEDBLINKER_H
#define LEDBLINKER_H

#include <SmingCore.h>

class LedBlinker {
public:
    LedBlinker(int reqPin);
    void on(bool reqOnOff);
    void blinker(bool reqOnOff);
    //LedBlinker(const LedBlinker& orig);
    virtual ~LedBlinker();
private :
    int ledPin = 2;
    Timer ledTimer;
    Timer ledBlinkTimer;
    const int ledInterval = 1000;
    const int ledBlinkInterval = 50;
    const int ledBlinkerCount = 5;
    bool ledState = true;
    bool ledBlinkerState = false;

    void ledBlink ();
    void ledBlinkReturn ();
};

#endif /* LEDBLINKER_H */

