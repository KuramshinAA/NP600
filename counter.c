#include "STM32f10x.h"
#include "bsp.h"
#include "counter.h"
#include "font.h"
#include "lcd_UC1701.h"

static __IO uint16_t TIM1_HiB = 0;
mainKoeffType mainKoeff;


static double K1def[K1_VALS_CNT] =
{
    80.0, 160.0
};

static double K2def[K2_4_VALS_CNT] =
{
    3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0
};

static double K3def[K3_VALS_CNT] =
{
    3.0, 4.0, 6.0, 8.0, 10.0
};

static double K4def[K2_4_VALS_CNT] =
{
    0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99
};

static double Idef[I_VALS_CNT] =
{
    10.0, 15.0
};

//**************************************************************************//
void calc_Rc(menuComboType *moptions)
{
    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double k4 = 0;
    double I_ = 0;

    // диам. шланга
    uint8_t i = moptions->item[0].selected;
    if (i < K2_4_VALS_CNT)
    {
        k2 = K2def[i];
        k4 = K4def[i];
    }

    // толщ. стенки
    i = moptions->item[1].selected;
    if (i < K3_VALS_CNT)
    {
        k3 = K3def[i];
    }

    // головка
    i = moptions->item[2].selected;
    if (i < K1_VALS_CNT)
    {
        k1 = K1def[i];
    }

    // коэфф.передачи
    i = moptions->item[3].selected;
    if (i < I_VALS_CNT)
    {
        I_ = Idef[i];
    }

    double Rc1 = 0.002467 * (((double)mainKoeff.k0)/100.0) * k4 * k2 * k2 * (k1 - k2 - k3);
    mainKoeff.Rc = Rc1 / I_;

    #if 0
    lcd_clear();
    lcd_putd(mainKoeff.Rc, 8, FONT_DEFAULT);
    lcd_refresh();
    _delay_ms(4000);
    #endif

}

//**************************************************************************//
uint32_t calc_counter(uint32_t needVml)
{
    double ticks = ((double)needVml * (double)OPTO_SENS_TICK_BY_CYCLE) / mainKoeff.Rc;
    #if 0
    lcd_clear();
    lcd_putd(ticks, 8, FONT_DEFAULT);
    lcd_refresh();
    _delay_ms(4000);
    #endif
    return ticks;
}

//**************************************************************************//
mainKoeffType*  get_mainKoeff()
{
    return &mainKoeff;
};


//**************************************************************************//
void set_counter(uint32_t cnt_val)
{
  TIM1_HiB = cnt_val>>16;
  TIM1->CNT = cnt_val & 0x0000FFFF;
  TIM1->CR1 |= TIM_CR1_CEN;
  led_on(LED_TEST_MASK);
}

//**************************************************************************//
uint32_t get_counter()
{
  uint32_t v = ((uint32_t)TIM1_HiB<<16) | (TIM1->CNT);
  return v;
}

//**************************************************************************//
uint32_t get_V(uint32_t ticks)
{
  uint32_t v = ((double)ticks * mainKoeff.Rc) / (double)OPTO_SENS_TICK_BY_CYCLE;
  return v;
}

//*******************************************************************************
//	TIM1 UPDATE handler
//*******************************************************************************
void TIM1_UP_IRQHandler(void)
{
  TIM1->SR &= (~(TIM_SR_UIF));        // clear update flag
  if (TIM1_HiB == 0)
  {
    // disable counter
     TIM1->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
     TIM1->CNT = 0;
     led_off(LED_TEST_MASK);
  }
  else
  {
    --TIM1_HiB;
  }
}
