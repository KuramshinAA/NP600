#ifndef __COUNTER_H_
#define __COUNTER_H_

#include "memory.h"
#include "font.h"
#include "lcd_UC1701.h"
#include "delay.h"

#define K1_VALS_CNT         2
#define K2_4_VALS_CNT       10
#define K3_VALS_CNT         5
#define I_VALS_CNT          2

#define OPTO_SENS_TICK_BY_CYCLE     8

typedef struct
{
    uint8_t k0;     // (0-100%)
    //float   k1;
    //float   k2;
    //float   k3;
    //float   k4;
    //uint8_t  i;
    //float   Rc1;
    double   Rc;
}
mainKoeffType;

mainKoeffType*  get_mainKoeff();
void set_counter(uint32_t cnt_val);
uint32_t get_counter();
uint32_t get_V(uint32_t ticks);
void calc_Rc(menuComboType *moptions);
uint32_t calc_counter(uint32_t needVml);

#endif // __COUNTER_H_
