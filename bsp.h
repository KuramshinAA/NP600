
#ifndef __BSP_H
#define __BSP_H

#ifdef __cplusplus
 extern "C" {
#endif


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum
{
  FALSE = 0,
  TRUE  = !FALSE
}
bool;

typedef const char* String;


#define BUTTON_LEFT_PIN         GPIO_Pin_14
#define BUTTON_LEFT_PORT        GPIOC
#define BUTTON_RIGHT_PIN        GPIO_Pin_15
#define BUTTON_RIGHT_PORT       GPIOC
#define BUTTON_UP_PIN           GPIO_Pin_13
#define BUTTON_UP_PORT          GPIOC
#define BUTTON_DOWN_PIN         GPIO_Pin_0
#define BUTTON_DOWN_PORT        GPIOA
#define BUTTON_OK_PIN           GPIO_Pin_2
#define BUTTON_OK_PORT          GPIOA
#define BUTTON_CANCEL_PIN       GPIO_Pin_1
#define BUTTON_CANCEL_PORT      GPIOA
#define BUTTON_START_PIN        GPIO_Pin_3
#define BUTTON_START_PORT       GPIOA
#define BUTTON_STOP_PIN         GPIO_Pin_4
#define BUTTON_STOP_PORT        GPIOA


#define LED1_PORT           GPIOB
#define LED1_PIN            GPIO_Pin_2
#define LED2_PORT           GPIOB
#define LED2_PIN            GPIO_Pin_11
#define LED3_PORT           GPIOB
#define LED3_PIN            GPIO_Pin_10


#define LED_POWER_MASK           1
#define LED_ERROR_MASK           2
#define LED_TEST_MASK            4

#define SPEAKER_PORT    GPIOB
#define SPEAKER_PIN     GPIO_Pin_4


#define LCD_RST_PIN     GPIO_Pin_15
#define LCD_RST_PORT    GPIOA
#define LCD_CS_PIN      GPIO_Pin_12
#define LCD_CS_PORT     GPIOB
#define LCD_SCK_PIN     GPIO_Pin_13
#define LCD_SCK_PORT    GPIOB
#define LCD_CD_PIN      GPIO_Pin_14
#define LCD_CD_PORT     GPIOB
#define LCD_SDA_PIN     GPIO_Pin_15
#define LCD_SDA_PORT    GPIOB

#define I2C_SDA_PORT    GPIOB
#define I2C_SDA_PIN     GPIO_Pin_7
#define I2C_SCL_PORT    GPIOB
#define I2C_SCL_PIN     GPIO_Pin_6

#define RS485_TX_PORT   GPIOA
#define RS485_TX_PIN    GPIO_Pin_9
#define RS485_RX_PORT   GPIOA
#define RS485_RX_PIN    GPIO_Pin_10

// MUSIC
typedef enum
{
    P = 0,
    C_1, Cd_1, D_1, Dd_1, E_1, F_1, Fd_1, G_1, Gd_1, A_1, Bb_1, B_1,
    C_2, Cd_2, D_2, Dd_2, E_2, F_2, Fd_2, G_2, Gd_2, A_2, Bb_2, B_2,
    C_3, Cd_3, D_3, Dd_3, E_3, F_3, Fd_3, G_3, Gd_3, A_3, Bb_3, B_3,
    C_4, Cd_4, D_4, Dd_4, E_4, F_4, Fd_4, G_4, Gd_4, A_4, Bb_4, B_4,
    C_5, Cd_5, D_5, Dd_5, E_5, F_5, Fd_5, G_5, Gd_5, A_5, Bb_5, B_5
}
notesFreqType;


/*typedef struct
{
    notesFreqType  note;
    uint8_t duration;
}
oneNoteType;*/

#define NFREQ(a) (((7200000.0)/a)/2.0)

#define MELODY_GAMMA    0
#define MELODY_ELKA     1
#define MELODY_BEEP     2
#define MELODY_CANCEL   3



void perif_init();
void led_on(uint8_t led_mask);
void led_off(uint8_t led_mask);
void led_toggle(uint8_t led_mask);
void speaker(bool state);

void play_melody_by_hndl(const uint8_t* mel);
void play_melody(uint8_t melody_num);
void TIM4_IRQHandler(void);

#ifdef __cplusplus
}
#endif


#endif /* __BSP_H */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
