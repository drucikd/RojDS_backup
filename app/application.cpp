#include <user_config.h>
#include <SmingCore.h>
#include <LedBlinker.h>

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