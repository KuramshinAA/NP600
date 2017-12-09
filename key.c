#include "bsp.h"
#include "stm32f10x_gpio.h"
#include "delay.h"
#include "key.h"


//******************************************************************************************************
//******************************************************************************************************
void keys_init()
{
	// GPIO INIT

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = BUTTON_LEFT_PIN;
	GPIO_Init(BUTTON_LEFT_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = BUTTON_RIGHT_PIN;
	GPIO_Init(BUTTON_RIGHT_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = BUTTON_UP_PIN;
	GPIO_Init(BUTTON_UP_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = BUTTON_DOWN_PIN;
	GPIO_Init(BUTTON_DOWN_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = BUTTON_OK_PIN;
	GPIO_Init(BUTTON_OK_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = BUTTON_CANCEL_PIN;
	GPIO_Init(BUTTON_CANCEL_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = BUTTON_START_PIN;
	GPIO_Init(BUTTON_START_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = BUTTON_STOP_PIN;
	GPIO_Init(BUTTON_STOP_PORT, &GPIO_InitStruct);
}

//******************************************************************************************************
//******************************************************************************************************
uint8_t get_key()
{
    uint8_t  keys_ = BUTTON_NONE;

    if ((BUTTON_LEFT_PORT->IDR & BUTTON_LEFT_PIN) == 0)
    {
        keys_ |= BUTTON_LEFT;
    }

    if ((BUTTON_RIGHT_PORT->IDR & BUTTON_RIGHT_PIN) == 0)
    {
        keys_ |= BUTTON_RIGHT;
    }

    if ((BUTTON_UP_PORT->IDR & BUTTON_UP_PIN) == 0)
    {
        keys_ |= BUTTON_UP;
    }

    if ((BUTTON_DOWN_PORT->IDR & BUTTON_DOWN_PIN) == 0)
    {
        keys_ |= BUTTON_DOWN;
    }

    if ((BUTTON_OK_PORT->IDR & BUTTON_OK_PIN) == 0)
    {
        keys_ |= BUTTON_OK;
    }

    if ((BUTTON_CANCEL_PORT->IDR & BUTTON_CANCEL_PIN) == 0)
    {
        keys_ |= BUTTON_CANCEL;
    }

    if ((BUTTON_START_PORT->IDR & BUTTON_START_PIN) == 0)
    {
        keys_ |= BUTTON_START;
    }

    if ((BUTTON_STOP_PORT->IDR & BUTTON_STOP_PIN) == 0)
    {
        keys_ |= BUTTON_STOP;
    }

    return keys_;
}

//******************************************************************************************************
//******************************************************************************************************
uint8_t wait_key()
{
	uint8_t k = BUTTON_NONE;

	do
	{
		k = get_key();
		if (k != BUTTON_NONE)
    {
        break;
    }
	}
	while(1);

	_delay_ms(50);

	return k;
}

//******************************************************************************************************
//******************************************************************************************************
void wait_key_unpressed()
{
	do
	{
		_delay_ms(50);
		if (get_key() == BUTTON_NONE)
    {
      break;
    }
	}
	while(1);
}

//******************************************************************************************************
//******************************************************************************************************
