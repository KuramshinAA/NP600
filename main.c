/**
  \file main.c
  \author KuramshinAA
  \brief  Main source file Nasos NP-600
*/

#include "inc.h"
#include "bsp.h"



int main(void)
{
	// Setup SysTick Timer for 1 msec interrupts
	if (SysTick_Config(72000))
	{
		// Capture error
		while (1);
	}

	perif_init();
    lcd_init();
    lcd_refresh();

    led_on(LED_POWER_MASK | LED_ERROR_MASK | LED_TEST_MASK);
    play_melody(MELODY_ELKA);
    _delay_ms(150);         // small delay
    led_off(LED_ERROR_MASK | LED_TEST_MASK);

    #if 0
    GPIO_InitTypeDef GPst;
    GPst.GPIO_Pin =  GPIO_Pin_4;
    GPst.GPIO_Mode = GPIO_Mode_Out_PP;
    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPst);


    while(1)
    {
    _delay_ms(1);
    GPIOB->ODR ^= GPIO_Pin_4;
    GPIOB->ODR ^= GPIO_Pin_11;
    }


    GPIO_InitTypeDef GPst;
    GPst.GPIO_Pin =  GPIO_Pin_8;
    GPst.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPst);

    set_counter(0x0100000A);

    while(1)
    {
    lcd_clear();
    lcd_put_hex_dword(get_counter(), FONT_DEFAULT);
    CRLF;

    lcd_refresh();
    _delay_ms(100);


    led_toggle(LED_POWER_MASK);
    }
    #endif

    #if 0
    lcd_putd(-1034.455123, 10, FONT_DEFAULT);
    lcd_refresh();
    _delay_ms(3000);
    #endif

    menu_init();
    menu_main();


    while(1);

}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
