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

static uint16_t GetState(uint8_t _led)
{
    uint16_t _port_state;
    _port_state = port_state & IndexToMask(_led);

}

void LedsInit(uint16_t* address)
{
    virtual_port = address;
    port_state = ALL_LEDS_OFF;
    UpdatePort();
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

uint16_t LedsIsTurnedOn(uint8_t led)
{
    return GetState(led);
}

uint16_t LedsIsTurnedOff(uint8_t led)
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