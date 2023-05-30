#include "get_voltage.h"
#include "adc.h"

#define ADC_REF     3.30f       /*Voltaje de referencia para conversion A/D del uC*/
#define MAX_VAL_ADC 4095.0f    /*resolucion: 12 bits*/

float getVoltage(uint8_t channel)
{
    uint16_t value = 0.0;

    if (0 == channel)
    {
        value = adc_readRegister(0x7600);
    }
    return ((float)value*ADC_REF)/MAX_VAL_ADC;
}