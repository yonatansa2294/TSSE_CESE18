#include "inc/leds.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




static uint16_t virtual_port;





void setUp(void)

{

    LedsInit(&virtual_port);

}



void tearDown(void)

{



}





void test_leds_start_off(void)

{

    uint16_t virtual_port = 0xFFFF;

    LedsInit(&virtual_port);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((virtual_port)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_on_single_led(void)

{

    LedsTurnOnSingle(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0002)), (UNITY_INT)(UNITY_INT16)((virtual_port)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_on_and_turn_off_single_led(void)

{

    LedsTurnOnSingle(2);

    LedsTurnOffSingle(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((virtual_port)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_on_and_turn_off_multiples_leds(void)

{

    LedsTurnOnSingle(3);

    LedsTurnOnSingle(5);

    LedsTurnOffSingle(3);

    LedsTurnOffSingle(7);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0010)), (UNITY_INT)(UNITY_INT16)((virtual_port)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_HEX16);

}





void test_is_turned_on_led_from_on_to_off(void)

{

    LedsTurnOnSingle(4);

    UnityAssertBits((UNITY_INT)((0x0008)), (UNITY_INT)((UNITY_UINT)(-1)), (UNITY_INT)((LedsIsTurnedOn(4))), (

   ((void *)0)

   ), (UNITY_UINT)(70));

}





void test_is_turned_off_led_no_status_(void)

{

    LedsTurnOffSingle(9);

    UnityAssertBits((UNITY_INT)((0x0200)), (UNITY_INT)((UNITY_UINT)(0)), (UNITY_INT)((LedsIsTurnedOff(9))), (

   ((void *)0)

   ), (UNITY_UINT)(77));

}





void test_turn_on_all_leds(void)

{

    LedsTurnOnAll();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((virtual_port)), (

   ((void *)0)

   ), (UNITY_UINT)(84), UNITY_DISPLAY_STYLE_HEX16);

}





void test_turn_off_all_leds(void)

{

    LedsTurnOnAll();

    LedsTurnOffAll();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((virtual_port)), (

   ((void *)0)

   ), (UNITY_UINT)(92), UNITY_DISPLAY_STYLE_HEX16);

}
