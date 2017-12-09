
#include "inc.h"
#include "bsp.h"
#include "menu.h"



//**************************************************************************//
// PERIFERALS INIT
void perif_init()
{
	/* Enable POWER Clock */
	RCC->APB1ENR |= (RCC_APB1Periph_PWR | RCC_APB1Periph_I2C1);

	/* Enable the Clocks */
	RCC->APB2ENR |= (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2ENR_AFIOEN);

	// SET ONLY SWD
	AFIO->MAPR &= (~((uint32_t)7<<24));
	AFIO->MAPR |= ((uint32_t)2<<24);

	GPIO_InitTypeDef GPst;
	NVIC_InitTypeDef NVIC_InitStructure;

	// BUTTONS GPIO config
	keys_init();

	// LEDS gpio config
	GPst.GPIO_Mode = GPIO_Mode_Out_PP;
	GPst.GPIO_Speed = GPIO_Speed_50MHz;

	GPst.GPIO_Pin = LED1_PIN;
	GPIO_Init(LED1_PORT, &GPst);
	GPIO_ResetBits(LED1_PORT, LED1_PIN);

	GPst.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_PORT, &GPst);
	GPIO_ResetBits(LED2_PORT, LED2_PIN);

	GPst.GPIO_Pin = LED3_PIN;
	GPIO_Init(LED3_PORT, &GPst);
	GPIO_ResetBits(LED3_PORT, LED3_PIN);

    // Configure EXTI Line8 (PA8) to generate an interrupt on fallining edge
    // before zero-cross point
    /*
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line8;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    */

    // LCD
    lcd_perif_init();

    // TIMERS INIT
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    // =============== TIMER 1 ====================
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_TIxExternalClockConfig(TIM1, TIM_TIxExternalCLK1Source_TI1,
                             TIM_ICPolarity_Falling, 0x0F);
    //TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
    TIM_SetCounter(TIM1, 0);

    //TIM_SetAutoreload(TIM1, 0x0010);

    //enable tim1 irq
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM1, ENABLE);

    GPst.GPIO_Pin =  GPIO_Pin_8;
    GPst.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPst);

#if 0
    // =============== TIMER 2 ====================
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  //enable tim2 irq
	/*NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);*/

	//TIM_SelectInputTrigger(TIM2, TIM_TS_ITR1);
	//TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_External1);
    TIM_ITRxExternalClockConfig(TIM2, TIM_TS_ITR1);

    TIM_SetCounter(TIM2, 0x0000);

    // TIM2 enable counter
    TIM_Cmd(TIM2, ENABLE);
#endif

    // =============== TIMER 3 ====================
    // Buzzer timer sound generator
    // используется для формирования ШИМ на выходах TIM3_CH1
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    // ~4000 Hz
    TIM_TimeBaseStructure.TIM_Period = 3600-1;////900-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 10;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // PWM1 Mode configuration: Channel1
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    //TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    //TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel2
    //TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    //TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    //TIM_ARRPreloadConfig(TIM3, ENABLE);

    // REMAP GPIOB Configuration: TIM3 channel1
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
    GPst.GPIO_Pin =  SPEAKER_PIN;
    GPst.GPIO_Mode = GPIO_Mode_AF_PP;
    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPEAKER_PORT, &GPst);

    // TIM3 enable counter
    TIM_Cmd(TIM3, DISABLE);

    //TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);       // Update as trigger output for ADC

    //enable tim3 irq
    //NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_Init(&NVIC_InitStructure);
    //TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

#if 1
    // =============== TIMER 4 ====================
    // используется как общий таймер для запуска измерений АЦП и т.д.
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = 100-1;           // 10ms period (for 72MHz)
    //TIM_TimeBaseStructure.TIM_Period = 200-1;           // 20ms period (for 72MHz)
    //TIM_TimeBaseStructure.TIM_Period = 500-1;
    TIM_TimeBaseStructure.TIM_Prescaler = 7200;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    //enable tim4 irq
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    // TIM4 enable counter
    TIM_Cmd(TIM4, ENABLE);
#endif

    // I2C Init
    I2C_InitTypeDef I2C_InitStruct;
    I2C_DeInit(I2C1);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    //GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPst.GPIO_Mode = GPIO_Mode_AF_OD;

    GPst.GPIO_Pin =  I2C_SDA_PIN;
    GPIO_Init(I2C_SDA_PORT, &GPst);
    GPst.GPIO_Pin =  I2C_SCL_PIN;
    GPIO_Init(I2C_SCL_PORT, &GPst);

    I2C_InitStruct.I2C_ClockSpeed = 100000;                // initialize the I2C_ClockSpeed member
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;                // Initialize the I2C_Mode member
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;        // Initialize the I2C_DutyCycle member
    I2C_InitStruct.I2C_OwnAddress1 = 0xA0;                 // Initialize the I2C_OwnAddress1 member
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;               // Initialize the I2C_Ack member
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;     // Initialize the I2C_AcknowledgedAddress member
    I2C_Init(I2C1, &I2C_InitStruct);

    I2C_Cmd(I2C1, ENABLE);

    // USART INIT (RS485)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPst.GPIO_Mode = GPIO_Mode_AF_PP;
    GPst.GPIO_Pin =  RS485_TX_PIN;
    GPIO_Init(RS485_TX_PORT, &GPst);

    GPst.GPIO_Speed = GPIO_Speed_50MHz;
    GPst.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPst.GPIO_Pin =  RS485_RX_PIN;
    GPIO_Init(RS485_RX_PORT, &GPst);

    USART_InitTypeDef  USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No ;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStruct);

    USART_Cmd(USART1, ENABLE);
}


//**************************************************************************//
void led_on(uint8_t led_mask)
{
  if ((led_mask & LED_POWER_MASK) != 0)
  {
    LED1_PORT->BSRR = LED1_PIN;
  }

  if ((led_mask & LED_ERROR_MASK) != 0)
  {
    LED2_PORT->BSRR = LED2_PIN;
  }

  if ((led_mask & LED_TEST_MASK) != 0)
  {
    LED3_PORT->BSRR = LED3_PIN;
  }
}

//**************************************************************************//
void led_off(uint8_t led_mask)
{
  if ((led_mask & LED_POWER_MASK) != 0)
  {
    LED1_PORT->BRR = LED1_PIN;
  }

  if ((led_mask & LED_ERROR_MASK) != 0)
  {
    LED2_PORT->BRR = LED2_PIN;
  }

  if ((led_mask & LED_TEST_MASK) != 0)
  {
    LED3_PORT->BRR = LED3_PIN;
  }
}

//**************************************************************************//
void led_toggle(uint8_t led_mask)
{
  if ((led_mask & LED_POWER_MASK) != 0)
  {
    LED1_PORT->ODR ^= LED1_PIN;
  }

  else if ((led_mask & LED_ERROR_MASK) != 0)
  {
    LED2_PORT->ODR ^= LED2_PIN;
  }

  else if ((led_mask & LED_TEST_MASK) != 0)
  {
    LED3_PORT->ODR ^= LED3_PIN;
  }
}

//**************************************************************************//
void speaker(bool state)
{
    if (state == TRUE)
    {
        TIM3->CNT = 0;
        TIM_Cmd(TIM3, ENABLE);
    }

    else
    {
        TIM_Cmd(TIM3, DISABLE);
    }
}

//**************************************************************************//
//  Beeper functions
//**************************************************************************//
uint8_t tim_ms_presc_note = 0;
uint8_t tim_ms_presc_note_top;
uint8_t player_cnt = 0;
uint8_t player_notes = 0;
const uint8_t *player_mel;

//**************************************************************************//
const uint16_t note_freq[12*5] =
{
    // pause
    0,

    // 1 octave
    NFREQ(261.63), NFREQ(277.18), NFREQ(293.66), NFREQ(311.13), NFREQ(329.63), NFREQ(349.23),
    NFREQ(369.99), NFREQ(392), NFREQ(415.3), NFREQ(440), NFREQ(466.16), NFREQ(493.88),

    // 2 octave
    NFREQ(523.26), NFREQ(554.26), NFREQ(587.32), NFREQ(622.26), NFREQ(659.26), NFREQ(698.46),
    NFREQ(739.98), NFREQ(784), NFREQ(830.6), NFREQ(880), NFREQ(932.32), NFREQ(987.76),

    // 3 octave
    NFREQ(1046.52), NFREQ(1108.72), NFREQ(1174.64), NFREQ(1244.52), NFREQ(1318.52), NFREQ(1396.92),
    NFREQ(1479.96), NFREQ(1568.00), NFREQ(1661.2), NFREQ(1760), NFREQ(1864.64), NFREQ(1975.52),

    // 4 octave
    NFREQ(2093), NFREQ(2217.4), NFREQ(2349.2), NFREQ(2489), NFREQ(2637), NFREQ(2793.8),
    NFREQ(2960), NFREQ(3136), NFREQ(3332.4), NFREQ(3440), NFREQ(3729.2), NFREQ(3951),

    // 5 octave
    NFREQ(4186)
};

//**************************************************************************//
#define MELODY_ARR_SIZE(a)  (a*2+1)
#define MELODY_GAMMA_NCNT    8
const uint8_t melody_gamma[MELODY_ARR_SIZE(MELODY_GAMMA_NCNT)] =
{
    MELODY_GAMMA_NCNT,
    C_1, 4,
    D_1, 4,
    E_1, 4,
    F_1, 4,
    G_1, 4,
    A_1, 4,
    B_1, 4,
    C_2, 4
};

//**************************************************************************//
#define MELODY_ELKA_NCNT    10
const uint8_t melody_elka[MELODY_ARR_SIZE(MELODY_ELKA_NCNT)] =
{
    MELODY_ELKA_NCNT,
    D_2, 20,
    B_2, 20,
    P, 4,
    B_2, 20,
    A_2, 20,
    B_2, 20,
    G_2, 20,
    D_2, 20,
    P, 4,
    D_2, 20
};

//**************************************************************************//
#define MELODY_BEEP_NCNT    1
const uint8_t melody_beep[MELODY_ARR_SIZE(MELODY_BEEP_NCNT)] =
{
    MELODY_BEEP_NCNT,
    C_5, 15
};

//**************************************************************************//
#define MELODY_CANCEL_NCNT    2
const uint8_t melody_cancel[MELODY_ARR_SIZE(MELODY_CANCEL_NCNT)] =
{
    MELODY_CANCEL_NCNT,
    E_1, 35,
    C_1, 35
};

//**************************************************************************//
const uint8_t* melodies[4] =
{
    melody_gamma,
    melody_elka,
    melody_beep,
    melody_cancel
};

//**************************************************************************//
void TIM4_IRQHandler(void)
{
  TIM4->SR &= (~(TIM_SR_UIF));        // clear update flag

  if (tim_ms_presc_note > 0)
  {
    if (++tim_ms_presc_note >= tim_ms_presc_note_top)
    {
      if (++player_cnt < player_notes)
      {
        // play next note
        tim_ms_presc_note = 1;                      // start counter
        tim_ms_presc_note_top = player_mel[player_cnt*2+2];             // duration
        TIM3->ARR = note_freq[player_mel[player_cnt*2+1]];                   // note
      }

      else
      {
        tim_ms_presc_note = 0;
        speaker(FALSE);
      }
    }
  }
}

//**************************************************************************//
void play_melody_by_hndl(const uint8_t* mel)
{
    player_mel = mel;
    player_cnt = 0;                             // from firt note
    player_notes = player_mel[0];                      // notes count
    tim_ms_presc_note = 1;                      // start counter
    tim_ms_presc_note_top = player_mel[2];             // duration
    uint8_t n = player_mel[1];
    TIM3->ARR = note_freq[n];              // first note
    speaker(TRUE);
}

//**************************************************************************//
void play_melody(uint8_t melody_num)
{
    //play_melody_by_hndl(melodies[melody_num]);
}


