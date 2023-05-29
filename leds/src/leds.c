#include "leds.h"

#define INDEX_OFFSET    1
#define FIRST_BIT       1
#define ALL_LEDS_OFF    0x0000
#define ALL_LEDS_ON     0xFFFF

static uint16_t * virtual_port;
static uint16_t port_state;

uint16_t IndexToMask(uint8_t led)
{
    return  (INDEX_OFFSET<<(led-FIRST_BIT));
}

static void UpdatePort()
{
    *virtual_port = port_state;
}

static bool GetState(uint8_t _led)
{
    bool _current_led_state = false;
    
    if((port_state & IndexToMask(_led)))
        _current_led_state = true;

    return _current_led_state; 
}

void LedsInit(uint16_t* address)
{
    virtual_port = address;
    LedsTurnOffAll();
}

void LedsTurnOnSingle(uint8_t led)
{
    port_state |= IndexToMask(led);
    UpdatePort();
}

void LedsTurnOffSingle(uint8_t led)
{
    port_state &= ~IndexToMask(led);
    UpdatePort();
}

bool LedsIsTurnedOn(uint8_t led)
{
    return GetState(led);
}

void LedsTurnOnAll()
{
    port_state = ALL_LEDS_ON;
    UpdatePort();
}

void LedsTurnOffAll()
{
    port_state = ALL_LEDS_OFF;
    UpdatePort();
}