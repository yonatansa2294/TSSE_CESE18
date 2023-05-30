#include "capture_data.h"
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#define V2N     1240.9 /*4095/ADC_REF(3.3v)*/
#define N2V     0.00080586/*1/V2N*/

static uint16_t samples[4];

static bool takeSamples(uint16_t* _samples)
{
    bool takeStatus = false;

    if(NULL != _samples)
    {
        samples[0] = *_samples;
        samples[1] = *(_samples+1);
        samples[2] = *(_samples+2);
        samples[3] = *(_samples+3);

        takeStatus = true;
    }

    return takeStatus;
}

int16_t ComputeSalFilter(uint16_t* ptrSamples)
{
    
    int16_t sal = 0;

    if(takeSamples(ptrSamples))
        sal = samples[3] + samples[2] - samples[1] - samples[0];    
    
    return sal;
}

int16_t ComputeCalFilter(uint16_t* ptrSamples)
{
    int16_t cal = 0;

     if(takeSamples(ptrSamples))
        cal = samples[3] - samples[2] - samples[1] + samples[0];    
    
    return cal;      
}

float ComputeRMSValue(int16_t sal, int16_t cal, float gain)
{
    float xRMS = 0.0;
    float salFactor = 0.0;
    float calFactor = 0.0;

    /*xRMS = |Cal + jSal|/(4*Gain)*/
    salFactor = (float)sal*N2V/(4*gain);
    calFactor = (float)cal*N2V/(4*gain);
    xRMS = sqrt(salFactor*salFactor+calFactor*calFactor);   
    
    return xRMS;
}