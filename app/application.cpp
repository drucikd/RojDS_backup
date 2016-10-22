#include <user_config.h>
#include <SmingCore.h>

class LedBlinker
{
/*
 * State NORMAL / BLINKER
 * NORMAL blink 50ms+1 time /1s
 * BLINKER blink 50ms+5 time /1s
 * State ON/OFF
 */
public :
	LedBlinker(int reqPin) : ledPin(reqPin) {
		pinMode(ledPin, OUTPUT);
                digitalWrite(ledPin, ledState);
                ledTimer.initializeMs(ledInterval, TimerDelegate(&LedBlinker::ledBlink, this));
                ledBlinkTimer.initializeMs(ledBlinkInterval, TimerDelegate(&LedBlinker::ledBlinkReturn, this));
                ledTimer.start();
	};
        
        void on(bool reqOnOff) { ledState = reqOnOff; }
        void blinker(bool reqOnOff)
        {
            ledBlinkerState = reqOnOff;
            
            ledTimer.stop();
            if (reqOnOff) {
                ledTimer.setIntervalMs(ledInterval/ledBlinkerCount);
                //getIntervalMs(ledInterval/ledBlinkerCount, 
                //        TimerDelegate(&LedBlinker::ledBlink, this));
            } else {
                ledTimer.setIntervalMs(ledInterval);
                //        TimerDelegate(&LedBlinker::ledBlink, this));
            }
            ledTimer.start();
        }

private :
	int ledPin = 2;
	Timer ledTimer;
        Timer ledBlinkTimer;
	const int ledInterval = 1000;
        const int ledBlinkInterval = 50;
        const int ledBlinkerCount = 5;
	bool ledState = true;
	bool ledBlinkerState = false;
        
        void ledBlink () { digitalWrite(ledPin, !ledState); ledBlinkTimer.startOnce();}
	void ledBlinkReturn () { digitalWrite(ledPin, ledState);}
};

#define LEDPIN_1  2 // GPIO2 - blue led onboard

LedBlinker Led1 = LedBlinker(LEDPIN_1);

Timer procTimerState;
Timer procTimerBlink;
bool state = true;
bool blink = true;

void stateChance()
{
    Led1.on(state);
    state = !state;
}

void blinkChance()
{
    Led1.blinker(blink);
    blink = !blink;
}

void init()
{
	procTimerBlink.initializeMs(10000, blinkChance).start();
	procTimerState.initializeMs(18800, stateChance).start();
}