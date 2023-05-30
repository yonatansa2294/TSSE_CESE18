/*---------------------------------------------------------------------------------------------------------
Pruebas para medicion de valores RMS de voltaje y corriente de motor trifasico empleando filtros SAL y CAL:
1. Prueba de lectura de canal analogico del uC para un voltaje de 3v
2. Calcular el valor del filtro SAL para los voltajes rms de linea neutro
3. Calcular el valor del filtro SAL para las corriente rms
4. Calcular el valor del filtro CAL para los voltajes rms de linea neutro
5. Calcular el valor del filtro CAL para las corriente rms
6. Calculo del voltaje RMS de linea-neutro VBN
7. Calculo de la corriente RMS de la fase B
-------------------------------------------------------------------------------------------------------*/

#include "unity.h"
#include "capture_data.h"
#include "get_voltage.h"
#include "mock_adc.h"

#define VLL_RMS 480.0     /*Voltaje Linea-Linea*/
#define IL_RMS  10.0  
#define VLN_RMS 277.0910f /*Voltaje Linea-Neutro: VLL/sqrt(3)*/
#define GV      0.003608f /*Factor de reduccion del PT*/
#define GI      0.050f /*Factor de reduccion del CT*/

static const uint16_t van[4] = {2048, 293, 2047, 3802};  //muestras de señal voltaje rms de linea-neutro para la fase A
static const uint16_t vbn[4] = {3567, 2925, 528, 1170};  //muestras de señal voltaje rms de linea-neutro para la fase B
static const uint16_t vcn[4] = {528, 2925, 3567, 1170};  //muestras de señal voltaje rms de linea-neutro para la fase C

static const uint16_t ia[4] = {2486, 1288, 1609, 2807}; //muestras de señal corriente rms para la fase A
static const uint16_t ib[4] = {2486, 2807, 1609, 1288}; //muestras de señal corriente rms para la fase B
static const uint16_t ic[4] = {1170, 2048, 2925, 2048}; //muestras de señal corriente rms para la fase C

/*Funcion que se ejecuta al inicio de cada test*/
void setUp(void)
{
    
}

void tearDown(void) 
{
    
}

/*Prueba 1*/
void test_read_input_voltage_adc_channel(void)
{
    uint32_t adcDataRegisterAddress = 0x7600;   /*Ref: PIC32MK Microchip*/
    uint16_t expectedValue = 0x0E8B; /*3723*/
    uint8_t channel = 0;
    float expectedVoltage = 3.0;
    float tolerance = 0.1;


    adc_readRegister_ExpectAndReturn(adcDataRegisterAddress, expectedValue);

    float actualVoltage = getVoltage(channel);

    TEST_ASSERT_FLOAT_WITHIN(tolerance, expectedVoltage, actualVoltage);
}


/*Prueba 2*/
void test_compute_sal_filter_voltages(void)
{
    TEST_ASSERT_EQUAL_INT16(3508,ComputeSalFilter(&van));
    TEST_ASSERT_EQUAL_INT16(-4794,ComputeSalFilter(&vbn));
    TEST_ASSERT_EQUAL_INT16(1284,ComputeSalFilter(&vcn));
}

/*Prueba 3*/
void test_compute_sal_filter_currents(void)
{   
    TEST_ASSERT_EQUAL_INT16(642,ComputeSalFilter(&ia));
    TEST_ASSERT_EQUAL_INT16(-2396,ComputeSalFilter(&ib));
    TEST_ASSERT_EQUAL_INT16(1755,ComputeSalFilter(&ic));
}

/*Prueba 4*/
void test_compute_cal_filter_voltages(void)
{
    TEST_ASSERT_EQUAL_INT16(3510,ComputeCalFilter(&van));
    TEST_ASSERT_EQUAL_INT16(1284,ComputeCalFilter(&vbn));
    TEST_ASSERT_EQUAL_INT16(-4794,ComputeCalFilter(&vcn));
}

/*Prueba 5*/
void test_compute_cal_filter_currents(void)
{
    TEST_ASSERT_EQUAL_INT16(2396,ComputeCalFilter(&ia));
    TEST_ASSERT_EQUAL_INT16(-642,ComputeCalFilter(&ib));
    TEST_ASSERT_EQUAL_INT16(-1755,ComputeCalFilter(&ic));
}

/*Prueba 6*/
void test_compute_rms_voltage(void)
{
    int16_t salVbn = -4794;
    int16_t calVbn = 1284;
    TEST_ASSERT_FLOAT_WITHIN(0.1,VLN_RMS,ComputeRMSValue(salVbn, calVbn, GV));
}

/*Prueba 7*/
void test_compute_rms_current(void)
{
    int16_t salIb = -2396;
    int16_t calIb = -642;
    TEST_ASSERT_FLOAT_WITHIN(0.1,IL_RMS,ComputeRMSValue(salIb, calIb, GI));
}