/**
  ******************************************************************************
  * @file    stm32_it.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_it.h"
#include "bsp.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}


/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}*/

/*******************************************************************************
* Function Name  : EVAL_COM1_IRQHandler
* Description    : This function handles EVAL_COM1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EVAL_COM1_IRQHandler(void)
{
  //if (USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET)
  //{
    /* Send the received data to the PC Host*/
    //USART_To_USB_Send_Data();
  //}

  /* If overrun condition occurs, clear the ORE flag and recover communication */
  //if (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_ORE) != RESET)
  //{
    //(void)USART_ReceiveData(EVAL_COM1);
  //}
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
void USBWakeUp_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}*/

/******************************************************************************/
/*                 STM32 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32xxx.s).                                            */
/******************************************************************************/


/******************************************************************************/
//  TIMER2 IRQ
/******************************************************************************/
void TIM2_IRQHandler(void)
{
  TIM2->SR &= (~(TIM_SR_UIF));        // clear update flag

}




/******************************************************************************/
/******************************************************************************/
void TIM3_IRQHandler(void)
{
	TIM3->SR &= (~(TIM_SR_UIF));        // clear update flag

	//led_toggle(LED_RED);

	//ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	//led_toggle();

	//optic_led(led_brightness);

    // Enable the TIM2 Counter
    //TIM2->CR1 |= TIM_CR1_CEN;
}


/******************************************************************************/
/******************************************************************************/
void ADC1_2_IRQHandler(void)
{

}

//*******************************************************************************
//	SPI2 handler
//
//*******************************************************************************
void SPI2_IRQHandler(void)
{
	//extern volatile uint8_t		was_SPI_data;
	//extern volatile uint16_t	SPI_data;
	//extern volatile uint16_t	SPI_data_bad;

	//SPI2->SR &= (~(SPI_SR_RXNE));

	//TIM4->CR1 &= (~(TIM_CR1_CEN));          // остановим таймер тайм-аута

	//SPI_data = SPI2->DR;                    // считать байт из буфера

    //was_SPI_data = TRUE;                    // установить флажок, запомнить байт, обработчик в main
}

//*******************************************************************************
//	External 9:5 lines int.
//*******************************************************************************
//uint8_t pv_cnt = 0;
//uint8_t pv_ccr = 1;
//uint8_t triac_on_T = 2;
//uint8_t triac_on_W = 1;
//uint8_t triac_on_p = 0;

void EXTI9_5_IRQHandler(void)
{
/*
    static bool ftrig = FALSE;

    // test ZC_OUT
	if (EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
	    EXTI->PR = EXTI_Line8;
		//EXTI_ClearITPendingBit(EXTI_Line8);

		// FALLING
		if ((GPIOA->IDR & GPIO_Pin_8) == 0)
        {
            if (!ftrig)
            {
                // period
                if (++triac_pwr_cnt >= TRIAC_PWR_CNT_MAX)
                {
                    triac_pwr_cnt = 0;
                }

                // get current pulse state
                if (pwr_mtrx_5_perc[triac_pwr_val][triac_pwr_cnt])
                {
                    TRIAC_ON_PORT->BSRR |= TRIAC_ON_PIN;      // ZC_OUT = 1: TRIAC_ON
                }
                else
                {
                    TRIAC_ON_PORT->BRR |= TRIAC_ON_PIN;      // ZC_OUT = 0: TRIAC_OFF
                }

                ftrig = TRUE;
                //led_toggle(LED_BLUE);
            }
        }

        // RISING
        else
        {
            ftrig = FALSE;
        }
	}*/
}



/*******************************************************************************
* Function Name  : PPP_IRQHandler
* Description    : This function handles PPP interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*void PPP_IRQHandler(void)
{
}*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

