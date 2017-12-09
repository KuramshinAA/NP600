

#include "delay.h"
#include "STM32f10x.h"

__IO uint32_t TimingDelay;
__IO uint32_t msec_cnt;

//**************************************************************************//
/*void init_delay_us_timer()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   				// подать тактирование на TIM2
	TIM9->PSC     = (72000000/1000000)-1;   		// настроить делитель для формирования миллисекунд
	TIM9->CR1     = TIM_CR1_OPM;          				// режим одного импульса
	TIM9->SR &= ~TIM_SR_UIF;	      					// сбросить флаг
}*/

//**************************************************************************//
/*
void _delay_us(uint16_t value)
{
  TIM9->ARR = value;                  		// загрузить значение задержки
  TIM9->CNT = 0;
  TIM9->CR1 |= TIM_CR1_CEN;	      			// запустить таймер
  while((TIM9->SR & TIM_SR_UIF)==0); 		// дождаться конца задержки
  TIM9->SR &= ~TIM_SR_UIF;	      			// сбросить флаг
}
*/
//**************************************************************************//
void _delay_ms(uint32_t nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

//**************************************************************************//
void SysTick_Handler(void)
{
	// delay_ms counter
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
	msec_cnt++;
}

//**************************************************************************//
