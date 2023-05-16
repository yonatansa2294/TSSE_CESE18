/*-----------------------------------------------------------------------------------------------------
Pruebas:
1. Al inicializar la biblioteca, todos los leds quedan apagados
2. Con todos los leds apagados, enciendo el led 2 y verifico que el bit 1 = 1
3. Con el led 2 prendido, apago el led 2 y verifico que el bit 1 = 0
4. Con todos los leds apagados realizo la siguiente secuencia: enciendo el led 3 -> enciendo el led 5
   -> apago el led 3 -> apago el led 7. Deberian quedar el bit 4 = 1 y el resto en 0
5. Enciendo un led, consulto el estado y tiene que estar encendido
6. Apago un led, consulto el estado y tiene que estar apagado
7. Con todos los leds apagados, enciendo todos los leds y verifico que se encienden
8. Con todos los leds encendidos, apago todos los leds y verifico que se apagan
9. Revisar los valores limites de los argumentos
10. Revisar que sucede con los valores erroneos en los argumentos
-------------------------------------------------------------------------------------------------------*/
#include "unity.h"
#include "leds.h"
#include <stdint.h>

static uint16_t virtual_port;

/*Funcion que se ejecuta al inicio de cada test*/
void setUp(void)
{
    LedsInit(&virtual_port);
}

void tearDown(void) 
{
    
}

/*Prueba 1*/
void test_leds_start_off(void)
{
    uint16_t virtual_port = 0xFFFF; /*Pre requisito -> Leds: On*/
    LedsInit(&virtual_port);
    /*TEST_ASSERT_EQUAL_HEX16(expected,actual)*/
    TEST_ASSERT_EQUAL_HEX16(0x0000,virtual_port);
}

/*Prueba 2*/
void test_turn_on_single_led(void)
{
    LedsTurnOnSingle(2);    /*enciende el led 2*/
    TEST_ASSERT_EQUAL_HEX16(0x0002,virtual_port);
}

/*Prueba 3*/
void test_turn_on_and_turn_off_single_led(void)
{
    LedsTurnOnSingle(2);
    LedsTurnOffSingle(2);
    TEST_ASSERT_EQUAL_HEX16(0x0000,virtual_port);
}

/*Prueba 4*/
void test_turn_on_and_turn_off_multiples_leds(void)
{
    LedsTurnOnSingle(3);
    LedsTurnOnSingle(5);
    LedsTurnOffSingle(3);
    LedsTurnOffSingle(7);
    TEST_ASSERT_EQUAL_HEX16(0x0010,virtual_port);
} 

/*Prueba 5*/
void test_is_turned_on_led_from_on_to_off(void)
{
    LedsTurnOnSingle(4);
    TEST_ASSERT_BITS_HIGH(0x0008,LedsIsTurnedOn(4));
}

/*Prueba 6*/
void test_is_turned_off_led_no_status_(void)
{
    LedsTurnOffSingle(9);
    TEST_ASSERT_BITS_LOW(0x0200,LedsIsTurnedOff(9));
}

/*Prueba 7*/
void test_turn_on_all_leds(void)
{
    LedsTurnOnAll();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtual_port);
}

/*Prueba 8*/
void test_turn_off_all_leds(void)
{
    LedsTurnOnAll();
    LedsTurnOffAll();
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_port);
}