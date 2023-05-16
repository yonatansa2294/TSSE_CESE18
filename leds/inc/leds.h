#ifndef LEDS_H
#define  LEDS_H

#include <stdint.h>

void LedsInit(uint16_t* address);
void LedsTurnOnSingle(uint8_t led);
void LedsTurnOffSingle(uint8_t led);
uint16_t LedsIsTurnedOn(uint8_t led);
uint16_t LedsIsTurnedOff(uint8_t led);
void LedsTurnOnAll();
void LedsTurnOffAll();

#endif