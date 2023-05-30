#ifndef CAPTURE_DATA_H
#define CAPTURE_DATA_H

#include <stdint.h>

int16_t ComputeSalFilter(uint16_t* ptrSamples);
int16_t ComputeCalFilter(uint16_t* ptrSamples);
float ComputeRMSValue(int16_t sal, int16_t cal, float gain);

#endif