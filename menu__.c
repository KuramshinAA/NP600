
#include "bsp.h"

extern const tFont font;
extern const tFont bnum_9x13;
extern const tFont bnum_7x8;

extern __IO bool ref_screen;
extern uint8_t tim_ms_presc_refscr;




//extern __IO uint16_t dest_temp;
//extern __IO uint16_t gotoTTime;

//extern __IO PID_type T_PID;

extern __IO bool test_mode;



//====================================================================================================
//
//====================================================================================================
int8_t menu_amplification()
{
    uint8_t prev_but = BUTTON_NONE;

    while(1)
    {
        lcd_clear();

        // current temp
        lcd_xy(0, 0);
        lcd_putc('\x1b', &bnum_7x8);
        //lcd_put_temp_val(Tcell_v, &bnum_7x8);

        // heater state
        //lcd_xy(60, 0);
        //lcd_puts("\x15", &bnum_7x8);
        //lcd_put_int(get_heater_pwm(), &bnum_7x8);

        // total time
        lcd_xy(60, 0);
        lcd_puts("\x14 ", &bnum_7x8);
        //lcd_put_time(Amplif.totalTime, &bnum_7x8);


        // Temp graph
        uint8_t lx = 8;
        uint8_t ly = 45;
        uint8_t h;
        uint8_t shft = 0;


#if 0
        // draw temp columns
        for (uint8_t t=0; t<4; t++)
        {
            if ((t+shft) > tempProg[Amplif.cur_prg].stages_cnt-1) break;

            // Current temp
            if ((t+shft) == Amplif.cur_stage)
            {
                h = 20 - (tempProg[Amplif.cur_prg].stage[t+shft].T/10 - 40)*(45-25)/(99-40);
                lcd_fill_rect(lx, 12 + h, 51, 45-h, COLOR_BLACK);

                lcd_set_inverted(TRUE);

                // heating
                if (Amplif.State == Amp_Heating || Amplif.State == Amp_Heating_2step)
                {
                    // dest temp value
                    lcd_xy(lx+10, 40);
                    lcd_puts("\x1e ", &bnum_7x8);
                    lcd_put_int(tempProg[Amplif.cur_prg].stage[t+shft].T/10, &bnum_7x8);
                    lcd_putc('\xb0', &bnum_7x8);
                    lcd_putc('C', &bnum_7x8);
                }

                // cooling
                else if (Amplif.State == Amp_Cooling)
                {
                    // dest temp value
                    lcd_xy(lx+10, 40);
                    lcd_puts("\x1f ", &bnum_7x8);
                    lcd_put_int(tempProg[Amplif.cur_prg].stage[t+shft].T/10, &bnum_7x8);
                    lcd_putc('\xb0', &bnum_7x8);
                    lcd_putc('C', &bnum_7x8);
                }

                // Hold T
                else if (Amplif.State == Amp_HoldTHi)
                {
                    // High temp value
                    lcd_xy(lx+11, 35);
                    lcd_puts("= ", &bnum_7x8);
                    lcd_put_int(tempProg[Amplif.cur_prg].stage[t+shft].T/10, &bnum_7x8);
                    lcd_putc('\xb0', &bnum_7x8);
                    lcd_putc('C', &bnum_7x8);

                    // High temp Hold Time
                    // calc center
                    uint8_t w=6;
                    if (Amplif.TempHoldTime >= 100) w = 6*3;
                    else if (Amplif.TempHoldTime >= 10) w = 6*2;
                    lcd_xy(lx+20-w/2, 46);
                    lcd_puts("\x1c ", &bnum_7x8);
                    lcd_put_int(Amplif.TempHoldTime, &bnum_7x8);
                    //lcd_puts("сек", &bnum_7x8);
                }

                // repetitions
                if (tempProg[Amplif.cur_prg].stage[Amplif.cur_stage].rep_cnt > 0 && tempProg[Amplif.cur_prg].stage[Amplif.cur_stage].gotoPos != 0)
                {
                    if (h < 9)
                    {
                        lcd_set_inverted(TRUE);
                        lcd_xy(lx+15, 22);
                        lcd_puts("\x1d ", &bnum_7x8);
                        lcd_put_int(tempProg[Amplif.cur_prg].stage[Amplif.cur_stage].rep_cnt, &bnum_7x8);
                    }

                    else
                    {
                        lcd_set_inverted(FALSE);
                        lcd_xy(lx+15, 3+h);
                        lcd_puts("\x1d ", &bnum_7x8);
                        lcd_put_int(tempProg[Amplif.cur_prg].stage[Amplif.cur_stage].rep_cnt, &bnum_7x8);
                    }
                }

                lcd_set_inverted(FALSE);

                // arrow left
                if (shft > 0)
                {
                    lcd_xy(2, 38);
                    lcd_putc('\x07', &bnum_7x8);
                }

                // arrow right
                if (3+shft < tempProg[Amplif.cur_prg].stages_cnt-1)
                {
                    lcd_xy(122, 38);
                    lcd_putc('\x08', &bnum_7x8);
                }

                lx += 50;
            }

            // not current temp
            else
            {
                lcd_xy(lx+3, 45);
                lcd_set_inverted(FALSE);
                lcd_put_int(tempProg[Amplif.cur_prg].stage[t+shft].T/10, &bnum_7x8);
                lcd_putc('\xb0', &bnum_7x8);

                h = 20 - (tempProg[Amplif.cur_prg].stage[t+shft].T/10 - 40)*(45-25)/(99-40);
                lcd_rect(lx, 12 + h, 21, 45-h, COLOR_BLACK);
                lx += 20;
            }
        }

        // progress bar
        lcd_progress_bar_top(Amplif.cur_iter, Amplif.total_iter);

        //lcd_xy(0, 63-8);
        //lcd_put_int(Amplif.total_iter, &bnum_7x8);

        // ready
        if (Amplif.readyFlag)
        {
            lcd_draw_panel(23, 18, 80, 35, COLOR_WHITE);
            lcd_xy(42, 30);
            lcd_puts("Готово!", &bnum_7x8);
        }
#endif // 0

        lcd_refresh();

        _delay_ms(15);



    }

    wait_key_unpressed();
}

//====================================================================================================
//
//====================================================================================================
void show_error(uint8_t err)
{
    lcd_draw_panel(20, 13, 85, 40, COLOR_WHITE);
    lcd_xy(36, 20);
    lcd_puts("ОШИБКА!:", &bnum_7x8);
    lcd_xy(55, 35);
//    lcd_put_hex_byte(Amplif.error, &bnum_7x8);
    lcd_refresh();
    while(1);
}

//====================================================================================================
//
//====================================================================================================
uint8_t  menu_select_program(uint8_t sp)
{
    #define SQW_WIDTH   28
    #define SQW_HEIGHT  24


    uint8_t pcur = sp;

    while(1)
    {
        lcd_clear();
        lcd_xy(7, 0);
        lcd_set_inverted(FALSE);
        lcd_puts("Выбор программы:", &bnum_7x8);

        //lcd_xy(0, 0);
        //lcd_put_temp_val(Tcell_v, &bnum_7x8);

        uint8_t k = 0;
        for (uint8_t y=0; y<2; y++)
        {
            for (uint8_t x=0; x<4; x++)
            {
                k++;

                if (pcur == k-1)
                {
                    lcd_draw_panel(3+x*(SQW_WIDTH+3), 10 + y*(SQW_HEIGHT+3), SQW_WIDTH, SQW_HEIGHT, COLOR_BLACK);
                    lcd_set_inverted(TRUE);
                    lcd_xy(14+x*(SQW_WIDTH+3), 16 + y*(SQW_HEIGHT+3));
                    lcd_put_int(k, &bnum_9x13);
                }
                else
                {
                    lcd_draw_panel(3+x*(SQW_WIDTH+3), 10 + y*(SQW_HEIGHT+3), SQW_WIDTH, SQW_HEIGHT, COLOR_NONE);
                    lcd_set_inverted(FALSE);
                    lcd_xy(12+x*(SQW_WIDTH+3), 14 + y*(SQW_HEIGHT+3));
                    lcd_put_int(k, &bnum_9x13);
                }
            }
        }

        lcd_refresh();

        uint8_t but = wait_key();

        if (but == BUTTON_LEFT)
        {
            if (pcur > 0)
                pcur--;
            else
                pcur = 7;
        }

        else if (but == BUTTON_RIGHT)
        {
            if (pcur < 7)
                pcur++;
            else
                pcur = 0;
        }

        else if (but == BUTTON_OK)
        {
            break;
        }

        else if (but == BUTTON_CANCEL)
        {
            //break;
        }

        wait_key_unpressed();

    }

    wait_key_unpressed();

    return pcur;
}

//====================================================================================================
//
//====================================================================================================
int8_t  menu_2_pos(char *str1, char *str2)
{
    #define SQW2_WIDTH      98
    #define SQW2_HEIGHT     20

    uint8_t acur = 0;

    while(1)
    {
        lcd_draw_panel(8, 2, 110, 52, COLOR_WHITE);
        for (uint8_t y = 0; y < 2; y++)
        {
            if (acur == y)
            {
                lcd_draw_panel(14, 5 + y*(SQW2_HEIGHT+5), SQW2_WIDTH, SQW2_HEIGHT, COLOR_BLACK);
                lcd_set_inverted(TRUE);
                lcd_xy(23, 13 + y*(SQW2_HEIGHT+5));
            }
            else
            {
                lcd_draw_panel(14, 5 + y*(SQW2_HEIGHT+5), SQW2_WIDTH, SQW2_HEIGHT, COLOR_NONE);
                lcd_set_inverted(FALSE);
                lcd_xy(21, 11 + y*(SQW2_HEIGHT+5));
            }

            if (y == 0)
            {
                lcd_puts(str1, &bnum_7x8);
            }
            else if (y == 1)
            {
                lcd_puts(str2, &bnum_7x8);
            }
        }

        lcd_refresh();

        uint8_t but = wait_key();

        if (but == BUTTON_LEFT)
        {
            if (acur > 0) acur--;
        }

        else if (but == BUTTON_RIGHT)
        {
            if (acur < 1) acur++;
        }

        else if (but == BUTTON_OK)
        {
            wait_key_unpressed();
            return acur;
        }

        else if (but == BUTTON_CANCEL)
        {
            break;
        }
    }

    wait_key_unpressed();

    return -1;
}


//====================================================================================================
//
//====================================================================================================
int8_t  menu_edit_program(uint8_t prg_num)
{
/*
    tempProg_type tempSeq;
    tempSeq.stages_cnt = 1;
    tempSeq.cur_stage = 1;
    tempSeq.stage[0].T = 960;
    tempSeq.stage[0].time = 60*4;
    tempSeq.stage[0].rep = 0;
    tempSeq.stage[0].rep_cnt = tempSeq.stage[0].rep;
    tempSeq.stage[0].gotoPos = 0;
    tempSeq.stage[1].T = 760;
    tempSeq.stage[1].time = 60;
    tempSeq.stage[1].rep = 0;
    tempSeq.stage[1].rep_cnt = tempSeq.stage[1].rep;
    tempSeq.stage[1].gotoPos = 0;

    for (uint8_t i=2; i<TEMPS_IN_SEQ; i++)
    {
        tempSeq.stage[i].T = 600;
        tempSeq.stage[i].time = 20;
        tempSeq.stage[i].rep = 0;
        tempSeq.stage[i].rep_cnt = tempSeq.stage[i].rep;
        tempSeq.stage[i].gotoPos = 0;
    }*/



    uint8_t cur_pos = 0;
    uint8_t shft_pos = 0;
    uint8_t blink_cnt = 0;
    bool m_lp = TRUE;
#if 0
    while(m_lp)
    {
        while(1)
        {
            // цикл просмотра программы/редактирования стадии

            lcd_clear();

            uint8_t mn_cnt = 3;
            if (mn_cnt > tempSeq->stages_cnt) mn_cnt = tempSeq->stages_cnt;

            // draw stages
            for (uint8_t i=0; i<mn_cnt; i++)
            {
                lcd_set_inverted(FALSE);
                lcd_xy(3, 4+i*16);
                lcd_put_int(i+1+shft_pos, &bnum_7x8);

                if (i+shft_pos == cur_pos)// && blink_cnt == 1)
                {
                    //lcd_fill_rect(9+1, 1+i*16, 115, 14, COLOR_BLACK);
                    lcd_draw_panel(9+1, 1+i*16, 115, 14, COLOR_BLACK);
                    lcd_set_inverted(TRUE);
                    lcd_xy(15, 5+i*16);
                }
                else
                {
                    //lcd_rect(9+1, 1+i*16, 115, 14, COLOR_BLACK);
                    lcd_draw_panel(9+1, 1+i*16, 115, 14, COLOR_NONE);
                    lcd_set_inverted(FALSE);
                    lcd_xy(14, 4+i*16);
                }

                lcd_put_int(tempSeq->stage[i+shft_pos].T/10, &bnum_7x8);
                lcd_putc('\xb0', &bnum_7x8);
                lcd_putc('C', &bnum_7x8);
                lcd_puts("  ", &bnum_7x8);
                lcd_put_time_min_sec(tempSeq->stage[i+shft_pos].time, &bnum_7x8);
                lcd_puts("  ", &bnum_7x8);

                if (tempSeq->stage[i+shft_pos].rep > 0 && tempSeq->stage[i+shft_pos].gotoPos > 0)
                {
                    // repetitions
                    lcd_putc('\x1d', &bnum_7x8);
                    lcd_put_int(tempSeq->stage[i+shft_pos].rep, &bnum_7x8);
                    lcd_puts("  ", &bnum_7x8);

                    // goto
                    lcd_putc('\x10', &bnum_7x8);
                    lcd_put_int(tempSeq->stage[i+shft_pos].gotoPos, &bnum_7x8);
                    lcd_puts(" ", &bnum_7x8);
                }
            }

            if (cur_pos == tempSeq->stages_cnt)
            {
                lcd_set_inverted(TRUE);
                //lcd_fill_rect(17, 49, 57, 14, COLOR_BLACK);
                lcd_draw_panel(17, 49, 57, 14, COLOR_BLACK);
                lcd_xy(21, 53);
                lcd_puts("+СТАДИЯ", &bnum_7x8);
            }
            else
            {
                lcd_set_inverted(FALSE);
                //lcd_rect(17, 49, 57, 14, COLOR_BLACK);
                lcd_draw_panel(17, 49, 57, 14, COLOR_NONE);
                lcd_xy(20, 52);
                lcd_puts("+СТАДИЯ", &bnum_7x8);
            }

            if (cur_pos == tempSeq->stages_cnt+1)
            {
                lcd_set_inverted(TRUE);
                //lcd_fill_rect(79, 49, 46, 14, COLOR_BLACK);
                lcd_draw_panel(79, 49, 46, 14, COLOR_BLACK);
                lcd_xy(83, 53);
                lcd_puts("ВЫХОД", &bnum_7x8);
            }
            else
            {
                lcd_set_inverted(FALSE);
                //lcd_rect(79, 49, 46, 14, COLOR_BLACK);
                lcd_draw_panel(79, 49, 46, 14, COLOR_NONE);
                lcd_xy(82, 52);
                lcd_puts("ВЫХОД", &bnum_7x8);
            }



            lcd_set_inverted(FALSE);

            // UP ARROW
            if (shft_pos > 0)
            {
                lcd_xy(0, 52);
                lcd_putc('\x1e', &bnum_7x8);
            }

            // DOWN ARROW
            if (tempSeq->stages_cnt - 1 > shft_pos + 2)
            {
                lcd_xy(7, 52);
                lcd_putc('\x1f', &bnum_7x8);

            }

            lcd_refresh();

            uint8_t but = wait_key();

            // menu down
            if (but == BUTTON_RIGHT)
            {
                if (cur_pos < tempSeq->stages_cnt + 1)
                {
                    cur_pos++;
                    if (cur_pos > 2 && cur_pos < tempSeq->stages_cnt)
                    {
                        if (cur_pos - shft_pos > 2)
                        {
                            shft_pos = cur_pos - 2;
                        }
                    }
                }
            }

            // menu up
            else if (but == BUTTON_LEFT)
            {
                if (cur_pos > 0)
                {
                    cur_pos--;

                    if (cur_pos < shft_pos)
                    {
                       shft_pos = cur_pos;

                    }
                }
            }

            // delete temp
            else if (but == BUTTON_CANCEL)
            {
                if (cur_pos < tempSeq->stages_cnt)
                {
                    if (cur_pos > 0)
                    {
                        // delete last
                        if (cur_pos == tempSeq->stages_cnt-1)
                        {
                            tempSeq->stages_cnt--;
                        }

                        // NOT last
                        else
                        {
                            // copy and shift
                            for (uint8_t cp = cur_pos; cp < tempSeq->stages_cnt-1; cp++)
                            {
                                tempSeq->stage[cp].T = tempSeq->stage[cp+1].T;
                                tempSeq->stage[cp].time = tempSeq->stage[cp+1].time;
                                tempSeq->stage[cp].rep = tempSeq->stage[cp+1].rep;
                                tempSeq->stage[cp].gotoPos = tempSeq->stage[cp+1].gotoPos;
                            }
                            tempSeq->stages_cnt--;
                        }

                        shft_pos = 0;
                        cur_pos = 0;
                    }
                }
            }

            // select
            else if (but == BUTTON_OK)
            {
                // edit selected stage
                if (cur_pos < tempSeq->stages_cnt)
                {
                    //t_lp = TRUE;
                    break;

                }

                // add mew temp stage
                if (cur_pos == tempSeq->stages_cnt)
                {
                    if (tempSeq->stages_cnt < TEMPS_IN_SEQ)
                    {
                        tempSeq->stages_cnt++;

                        if (cur_pos > 2 && cur_pos < tempSeq->stages_cnt)
                        {
                            shft_pos = cur_pos - 2;
                        }
                    }
                }

                // exit
                if (cur_pos == tempSeq->stages_cnt+1)
                {
                    m_lp = FALSE;
                    break;
                }
            }

            wait_key_unpressed();
        }

        wait_key_unpressed();

        if (!m_lp) break;

        // цикл редактирования выбранной стадии
        uint8_t st_cur = 0;
        uint8_t st_y = cur_pos - shft_pos;
        uint16_t  st_temp = tempSeq->stage[cur_pos].T;
        uint8_t  st_time_m = tempSeq->stage[cur_pos].time/60;
        uint8_t  st_time_s = tempSeq->stage[cur_pos].time%60;
        uint8_t   st_rep = tempSeq->stage[cur_pos].rep;
        uint8_t   st_goto = tempSeq->stage[cur_pos].gotoPos;

        while(1)
        {
            //clear
            lcd_fill_rect(9+1, 1+st_y*16, 115, 14, COLOR_NONE);
            lcd_rect(9+1, 1+st_y*16, 115, 14, COLOR_BLACK);

            lcd_set_inverted(FALSE);

            // draw temp 10
            if (st_cur == 0)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(14, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_xy(14, 4 + st_y*16);
            lcd_put_int(st_temp/100, &bnum_7x8);

            // draw temp 1
            if (st_cur == 1)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(20, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int((st_temp/10)%10, &bnum_7x8);


            lcd_set_inverted(FALSE);
            lcd_putc('\xb0', &bnum_7x8);
            lcd_putc('C', &bnum_7x8);
            lcd_puts("  ", &bnum_7x8);


            // draw time min 10
            if (st_cur == 2)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(43, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_time_m/10, &bnum_7x8);

            // draw time min 1
            if (st_cur == 3)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(49, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_time_m%10, &bnum_7x8);

            lcd_set_inverted(FALSE);
            lcd_puts(":", &bnum_7x8);

            // draw time sec 10
            if (st_cur == 4)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(58, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_time_s/10, &bnum_7x8);

            // draw time sec 1
            if (st_cur == 5)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(64, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_time_s%10, &bnum_7x8);

            lcd_set_inverted(FALSE);
            lcd_puts("  ", &bnum_7x8);

            // repetitions
            lcd_putc('\x1d', &bnum_7x8);

            // draw rep 10
            if (st_cur == 6)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(84, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_rep/10, &bnum_7x8);

            // draw rep 1
            if (st_cur == 7)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(90, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_rep%10, &bnum_7x8);


            lcd_set_inverted(FALSE);
            lcd_puts("  ", &bnum_7x8);

            // goto
            lcd_putc('\x10', &bnum_7x8);

            // draw goto pos
            if (st_cur == 8)
            {
                lcd_set_inverted(TRUE);
                lcd_fill_rect(110, 1+st_y*16, 6, 14, COLOR_BLACK);
            }
            else
            {
                lcd_set_inverted(FALSE);
            }

            lcd_put_int(st_goto, &bnum_7x8);

            lcd_set_inverted(FALSE);
            lcd_puts(" ", &bnum_7x8);

            lcd_refresh();

            uint8_t but = wait_key();

            // MOVE LEFT
            if (but == BUTTON_LEFT)
            {
                if (st_cur > 0)
                {
                    st_cur--;
                }

                // exit
                else
                {
                    break;
                }
            }

            // MOVE RIGHT
            else if (but == BUTTON_RIGHT)
            {
                if (st_cur < 8)
                {
                    st_cur++;
                }

                // exit
                else
                {
                    break;
                }
            }

            // INC
            else if (but == BUTTON_OK)
            {
                // INC TEMP 10
                if (st_cur == 0)
                {
                    uint8_t a = st_temp / 100;
                    uint8_t b = (st_temp / 10)%10;

                    if (a < 9)
                        a++;
                    else
                        a = 0;

                    st_temp = a*100 + b*10;
                }

                // INC TEMP 1
                else if (st_cur == 1)
                {
                    uint8_t a = st_temp / 100;
                    uint8_t b = (st_temp / 10)%10;

                    if (b < 9)
                        b++;
                    else
                        b = 0;

                    st_temp = a*100 + b*10;
                }

                // INC TIME MINUTES 10
                else if (st_cur == 2)
                {
                    uint8_t a = st_time_m / 10;
                    uint8_t b = st_time_m % 10;

                    if (a < 5)
                        a++;
                    else
                        a = 0;

                    st_time_m = a*10 + b;
                }

                // INC TIME MINUTES 1
                else if (st_cur == 3)
                {
                    uint8_t a = st_time_m / 10;
                    uint8_t b = st_time_m % 10;

                    if (b < 9)
                        b++;
                    else
                        b = 0;

                    st_time_m = a*10 + b;
                }

                // INC TIME SECONDS 10
                else if (st_cur == 4)
                {
                    uint8_t a = st_time_s / 10;
                    uint8_t b = st_time_s % 10;

                    if (a < 5)
                        a++;
                    else
                        a = 0;

                    st_time_s = a*10 + b;
                }

                // INC TIME SECONDS 1
                else if (st_cur == 5)
                {
                    uint8_t a = st_time_s / 10;
                    uint8_t b = st_time_s % 10;

                    if (b < 9)
                        b++;
                    else
                        b = 0;

                    st_time_s = a*10 + b;
                }

                // INC REP 10
                else if (st_cur == 6)
                {
                    uint8_t a = st_rep / 10;
                    uint8_t b = st_rep % 10;

                    if (a < 9)
                        a++;
                    else
                        a = 0;

                    st_rep = a*10 + b;
                }

                // INC REP 1
                else if (st_cur == 7)
                {
                    uint8_t a = st_rep / 10;
                    uint8_t b = st_rep % 10;

                    if (b < 9)
                        b++;
                    else
                        b = 0;

                    st_rep = a*10 + b;
                }

                // INC GOTO POS
                else if (st_cur == 8)
                {
                    if (st_goto < 9)
                        st_goto++;
                    else
                        st_goto = 0;
                }
            }

            // DEC
            else if (but == BUTTON_CANCEL)
            {
                // DEC TEMP 10
                if (st_cur == 0)
                {
                    uint8_t a = st_temp / 100;
                    uint8_t b = (st_temp / 10)%10;

                    if (a > 0)
                        a--;
                    else
                        a = 9;

                    st_temp = a*100 + b*10;
                }

                // DEC TEMP 1
                else if (st_cur == 1)
                {
                    uint8_t a = st_temp / 100;
                    uint8_t b = (st_temp / 10)%10;

                    if (b > 0)
                        b--;
                    else
                        b = 9;

                    st_temp = a*100 + b*10;
                }

                // DEC TIME MINUTES 10
                else if (st_cur == 2)
                {
                    uint8_t a = st_time_m / 10;
                    uint8_t b = st_time_m % 10;

                    if (a > 0)
                        a--;
                    else
                        a = 5;

                    st_time_m = a*10 + b;
                }

                // DEC TIME MINUTES 1
                else if (st_cur == 3)
                {
                    uint8_t a = st_time_m / 10;
                    uint8_t b = st_time_m % 10;

                    if (b > 0)
                        b--;
                    else
                        b = 9;

                    st_time_m = a*10 + b;
                }

                // DEC TIME SECONDS 10
                else if (st_cur == 4)
                {
                    uint8_t a = st_time_s / 10;
                    uint8_t b = st_time_s % 10;

                    if (a > 0)
                        a--;
                    else
                        a = 5;

                    st_time_s = a*10 + b;
                }

                // DEC TIME SECONDS 1
                else if (st_cur == 5)
                {
                    uint8_t a = st_time_s / 10;
                    uint8_t b = st_time_s % 10;

                    if (b > 0)
                        b--;
                    else
                        b = 9;

                    st_time_s = a*10 + b;
                }

                // DEC REP 10
                else if (st_cur == 6)
                {
                    uint8_t a = st_rep / 10;
                    uint8_t b = st_rep % 10;

                    if (a > 0)
                        a--;
                    else
                        a = 9;

                    st_rep = a*10 + b;
                }

                // DEC REP 1
                else if (st_cur == 7)
                {
                    uint8_t a = st_rep / 10;
                    uint8_t b = st_rep % 10;

                    if (b > 0)
                        b--;
                    else
                        b = 9;

                    st_rep = a*10 + b;
                }

                // DEC GOTO POS
                else if (st_cur == 8)
                {
                    if (st_goto > 0)
                        st_goto--;
                    else
                        st_goto = 9;
                }

            }

            wait_key_unpressed();

        }

        // test edited values
        if (st_temp > MAX_HIGH_TEMP)
        {
            st_temp = MAX_HIGH_TEMP;
        }

        if (st_temp < MIN_LOW_TEMP)
        {
            st_temp = MIN_LOW_TEMP;
        }

        if (st_goto >= cur_pos+1)
        {
            st_goto = 0;
        }

        // save edited values
        tempSeq->stage[cur_pos].T = st_temp;
        tempSeq->stage[cur_pos].time = st_time_m*60 + st_time_s;
        tempSeq->stage[cur_pos].rep = st_rep;
        tempSeq->stage[cur_pos].gotoPos = st_goto;

        if (tempSeq->stage[cur_pos].time < 1)
        {
            tempSeq->stage[cur_pos].time = 10;
        }


        wait_key_unpressed();
    }
#endif
    return 0;
}


//====================================================================================================
//   Reset temperature sequence
//====================================================================================================
void set_default_profiles()
{
    for (int i = 0; i < MAX_PROFILES; i++)
    {
        tempSequence.tProf[i].Thigh = 400;
        tempSequence.tProf[i].Tlow = 400;
        tempSequence.tProf[i].timeTH = 30;
        tempSequence.tProf[i].timeTL = 30;
        tempSequence.tProf[i].times = 1;
    }
    tempSequence.profiles_cnt = 1;
    I2C_save_TempProfiles();
}

//====================================================================================================
//  Common Menus variables
//====================================================================================================
uint8_t cur_profile = 0;
bool edit_mode = TRUE;
uint8_t edit_val = 0;
bool edit_blink = FALSE;
bool long_press = FALSE;
uint8_t but = BUTTON_NONE;
uint8_t lng_cnt = 0;
uint8_t lng_coeff = 1;
//extern __IO uint16_t  dest_temp;
//extern __IO bool amplif_on;

//====================================================================================================
// Menu scene 1
//
//====================================================================================================
void menu_scene_with_params()
{
    if (ref_screen)
    {
        ref_screen = FALSE;

        lcd_clear();

        // edit mode
        if (edit_mode)
        {
            // current temp
            lcd_xy(0, 0);
            lcd_putc('\x1b', &bnum_7x8);
            lcd_put_temp_val(Tcell_v, &bnum_7x8);
            //lcd_put_temp_val(Tval[1], &bnum_7x8);
            //lcd_put_int(Temp[0], &bnum_7x8);

            // Real temp of block
            //lcd_xy(60, 0);
            //lcd_putc('\x18', &bnum_7x8);
            //lcd_put_temp_val(Tval[0], &bnum_7x8);

            // profiles indicator
            lcd_xy(0, 15);
            lcd_puts("\x1a ", &bnum_7x8);
            if (edit_blink && edit_val == 0)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_put_int(cur_profile + 1, &bnum_7x8);
            lcd_set_inverted(FALSE);

            lcd_putc('/', &bnum_7x8);
            if (edit_blink && edit_val == 1)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_put_int(tempSequence.profiles_cnt, &bnum_7x8);
            lcd_set_inverted(FALSE);

            // High temp value
            lcd_xy(0, 30);
            lcd_puts("\x1e ", &bnum_7x8);
            if (edit_blink && edit_val == 2)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_put_int(tempSequence.tProf[cur_profile].Thigh/10, &bnum_7x8);
            lcd_set_inverted(FALSE);

            lcd_putc('\xb0', &bnum_7x8);
            lcd_putc('C', &bnum_7x8);
            lcd_xy(0, 40);

            lcd_puts("\x1c ", &bnum_7x8);
            if (edit_blink && edit_val == 3)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_put_int(tempSequence.tProf[cur_profile].timeTH, &bnum_7x8);
            lcd_set_inverted(FALSE);
            lcd_puts("сек", &bnum_7x8);

            // Low temp value
            lcd_xy(60, 30);
            lcd_puts("\x1f ", &bnum_7x8);
            if (edit_blink && edit_val == 4)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_put_int(tempSequence.tProf[cur_profile].Tlow/10, &bnum_7x8);
            lcd_set_inverted(FALSE);

            lcd_putc('\xb0', &bnum_7x8);
            lcd_putc('C', &bnum_7x8);
            lcd_xy(60, 40);

            lcd_puts("\x1c ", &bnum_7x8);
            if (edit_blink && edit_val == 5)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);

            lcd_put_int(tempSequence.tProf[cur_profile].timeTL, &bnum_7x8);
            lcd_set_inverted(FALSE);
            lcd_puts("сек", &bnum_7x8);

            // repetitions
            lcd_xy(0, 50);
            lcd_puts("\x1d ", &bnum_7x8);
            if (edit_blink && edit_val == 6)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_put_int(tempSequence.tProf[cur_profile].times, &bnum_7x8);
            lcd_set_inverted(FALSE);

            // total time
            lcd_xy(40, 50);
            lcd_puts("\x14 ", &bnum_7x8);
            lcd_put_time(Amplif.totalTime, &bnum_7x8);

            // exit icon
            lcd_xy(118, 53);
            if (edit_blink && edit_val == 7)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_putc('\x19', &bnum_7x8);
            lcd_set_inverted(FALSE);
        }

        // monitor mode
        else
        {
            lcd_set_inverted(FALSE);
            // current temp
            lcd_xy(0, 0);
            lcd_putc('\x1b', &bnum_7x8);
            lcd_put_temp_val(Tcell_v, &bnum_7x8);
            //lcd_put_temp_val(Tval[1], &bnum_7x8);

            // Real temp of block
            //lcd_xy(60, 0);
            //lcd_putc('\x18', &bnum_7x8);
            //lcd_put_temp_val(Tval[0], &bnum_7x8);

            // profiles indicator
            lcd_xy(0, 15);
            lcd_puts("\x1a ", &bnum_7x8);
            lcd_put_int(tempSequence.curProfile + 1, &bnum_7x8);

            lcd_putc('/', &bnum_7x8);
            lcd_put_int(tempSequence.profiles_cnt, &bnum_7x8);

            // heater state
            lcd_xy(35, 15);
            lcd_puts("\x15", &bnum_7x8);
            //lcd_put_int(get_heater(), &bnum_7x8);
            lcd_put_int(get_heater_pwm(), &bnum_7x8);

            // время выхода на целевую темп.
            if (Amplif.State == Amp_Heating || Amplif.State == Amp_Heating_2step || Amplif.State == Amp_Cooling)
            {
                // time to go to cur temp
                lcd_xy(70, 15);
                lcd_puts("\x1c ", &bnum_7x8);
                //lcd_put_int(Amplif.gotoTempTime, &bnum_7x8);
                //lcd_puts("сек", &bnum_7x8);
                lcd_put_time(Amplif.gotoTempTime, &bnum_7x8);
            }

            //
            if (Amplif.State == Amp_Heating || Amplif.State == Amp_Heating_2step)// || Amplif.State == Amp_HoldTHi)
            {
                // High temp value
                lcd_xy(0, 30);
                lcd_puts("\x1e ", &bnum_7x8);
                lcd_put_int(tempSequence.tProf[tempSequence.curProfile].Thigh/10, &bnum_7x8);
                lcd_putc('\xb0', &bnum_7x8);
                lcd_putc('C', &bnum_7x8);
            }

            if (Amplif.State == Amp_HoldTHi)
            {
                // High temp value
                lcd_xy(0, 30);
                lcd_puts("= ", &bnum_7x8);
                lcd_put_int(tempSequence.tProf[tempSequence.curProfile].Thigh/10, &bnum_7x8);
                lcd_putc('\xb0', &bnum_7x8);
                lcd_putc('C', &bnum_7x8);

                // High temp Hold Time
                lcd_xy(0, 40);
                lcd_puts("\x1c ", &bnum_7x8);
                lcd_put_int(Amplif.TempHoldTime, &bnum_7x8);
                lcd_puts("сек", &bnum_7x8);
            }

            if (Amplif.State == Amp_Cooling)// || Amplif.State == Amp_HoldTLow)
            {
                // Low temp value
                lcd_xy(60, 30);
                lcd_puts("\x1f ", &bnum_7x8);
                lcd_put_int(tempSequence.tProf[tempSequence.curProfile].Tlow/10, &bnum_7x8);
                lcd_putc('\xb0', &bnum_7x8);
                lcd_putc('C', &bnum_7x8);
            }

            if (Amplif.State == Amp_HoldTLow)
            {
                // Low temp value
                lcd_xy(60, 30);
                lcd_puts("= ", &bnum_7x8);
                lcd_put_int(tempSequence.tProf[tempSequence.curProfile].Tlow/10, &bnum_7x8);
                lcd_putc('\xb0', &bnum_7x8);
                lcd_putc('C', &bnum_7x8);

                // time
                lcd_xy(60, 40);
                lcd_puts("\x1c ", &bnum_7x8);
                lcd_put_int(Amplif.TempHoldTime, &bnum_7x8);
                lcd_puts("сек", &bnum_7x8);
            }

            // repetitions
            lcd_xy(0, 50);
            lcd_puts("\x1d ", &bnum_7x8);
            lcd_put_int(tempSequence.tProf[tempSequence.curProfile].times - Amplif.Repeat, &bnum_7x8);
            lcd_puts("/", &bnum_7x8);
            lcd_put_int(tempSequence.tProf[tempSequence.curProfile].times, &bnum_7x8);

            // total time
            lcd_xy(40, 50);
            lcd_puts("\x14 ", &bnum_7x8);
            lcd_put_time(Amplif.totalTime, &bnum_7x8);
            //lcd_put_int(T_PID.pid_, &bnum_7x8);

            // progress bar
            //lcd_progress_bar_top(Amplif.cur_cycle, Amplif.total_cycles);

            // for test, print Bk_H1
            //lcd_xy(95, 30);
            //lcd_putc('\x12', &bnum_7x8);
            //lcd_xy(104, 30);
            //lcd_put_int(Amplif.AmpK.Bk, &bnum_7x8);

        }

        lcd_refresh();

        // if blink enabled
        if (edit_mode)
        {
            if (edit_blink)
                edit_blink = FALSE;
            else
                edit_blink = TRUE;
        }
    }

    // if button longer was not released
    if (long_press)
    {

    }

    // no one button early was pressed
    else
    {
        if (Amplif.error == ERROR_NONE)
        {
            // read buttons state
            but = get_key();
            if (but != BUTTON_NONE)
            {
                one_beep();
                if (edit_mode)
                {
                    edit_blink = TRUE;
                    ref_screen = TRUE;
                    tim_ms_presc_refscr = 0;
                }
            }
        }
        else
        {
            but = BUTTON_NONE;
        }
    }

    // MOVE LEFT + INC BUT
    if (but == BUTTON_1 + BUTTON_4)
    {
        test_mode = TRUE;
        beep(2, 25);
    }

    // MOVE LEFT
    else if (but == BUTTON_LEFT)
    {
        if (edit_mode)
        {
            if (edit_val > 0)
                edit_val--;
            else
                edit_val = MENU1_EDIT_VALS_CNT-1;
        }
    }

    // MOVE RIGHT
    else if (but == BUTTON_RIGHT)
    {
        if (edit_mode)
        {
            if (edit_val < MENU1_EDIT_VALS_CNT-1)
                edit_val++;
            else
                edit_val = 0;
        }
    }

    // DEC VAL
    else if (but == BUTTON_CANCEL)
    {
        if (edit_mode)
        {
            // current profile
            if (edit_val == 0)
            {
                if (cur_profile > 0)
                {
                    cur_profile--;
                }
            }

            // profiles count
            else if (edit_val == 1)
            {
                if (tempSequence.profiles_cnt > 1)
                {
                    tempSequence.profiles_cnt--;
                }
            }

            // High temp
            else if (edit_val == 2)
            {
                if (tempSequence.tProf[cur_profile].Thigh > MIN_HIGH_TEMP)
                {
                    tempSequence.tProf[cur_profile].Thigh -= lng_coeff*10;
                }
            }

            // High temp time
            else if (edit_val == 3)
            {
                if (tempSequence.tProf[cur_profile].timeTH > MIN_T_HOLD_TIME)
                {
                    tempSequence.tProf[cur_profile].timeTH -= lng_coeff;
                }
            }

            // Low temp
            else if (edit_val == 4)
            {
                if (tempSequence.tProf[cur_profile].Tlow > MIN_LOW_TEMP)
                {
                    tempSequence.tProf[cur_profile].Tlow -= lng_coeff*10;
                }
            }

            // Low temp time
            else if (edit_val == 5)
            {
                if (tempSequence.tProf[cur_profile].timeTL > MIN_T_HOLD_TIME)
                {
                    tempSequence.tProf[cur_profile].timeTL -= lng_coeff;
                }
            }

            // Repetitions
            else if (edit_val == 6)
            {
                if (tempSequence.tProf[cur_profile].times > 1)
                {
                    tempSequence.tProf[cur_profile].times--;
                }
            }

            // exit
            else if (edit_val == 7)
            {
                long_press = FALSE;
                edit_mode = FALSE;
                edit_blink = FALSE;
                I2C_save_TempProfiles();

                Amplif_Init(0);
                Amplif_heating_prepare();
                Amplif_Start();
            }
        }

        // edit выключен
        else
        {
            Amplif_Stop();
            beep(1, 40);
            led_off(LED_RED);
            led_off(LED_BLUE);

            edit_mode = TRUE;
            edit_blink = TRUE;
            cur_profile = 0;
            edit_val = 0;
            long_press = FALSE;
            lng_cnt = 0;
            lng_coeff = 1;
            wait_key_unpressed();
        }
    }

    // INC VAL
    else if (but == BUTTON_OK)
    {
        if (edit_mode)
        {
            // current profile
            if (edit_val == 0)
            {
                if (cur_profile < tempSequence.profiles_cnt - 1)
                {
                    cur_profile++;
                }
            }

            // profiles count
            else if (edit_val == 1)
            {
                if (tempSequence.profiles_cnt < MAX_PROFILES)
                {
                    tempSequence.profiles_cnt++;
                }
            }

            // High temp
            else if (edit_val == 2)
            {
                if (tempSequence.tProf[cur_profile].Thigh < MAX_HIGH_TEMP)
                {
                    tempSequence.tProf[cur_profile].Thigh += lng_coeff*10;
                }
            }

            // High temp time
            else if (edit_val == 3)
            {
                if (tempSequence.tProf[cur_profile].timeTH < MAX_T_HOLD_TIME)
                {
                    tempSequence.tProf[cur_profile].timeTH += lng_coeff;
                }
            }

            // Low temp
            else if (edit_val == 4)
            {
                if (tempSequence.tProf[cur_profile].Tlow < MAX_LOW_TEMP)
                {
                    tempSequence.tProf[cur_profile].Tlow += lng_coeff*10;
                }
            }

            // Low temp time
            else if (edit_val == 5)
            {
                if (tempSequence.tProf[cur_profile].timeTL < MAX_T_HOLD_TIME)
                {
                    tempSequence.tProf[cur_profile].timeTL += lng_coeff;
                }
            }

            // Repetitions
            else if (edit_val == 6)
            {
                if (tempSequence.tProf[cur_profile].times < MAX_REPETITIONS)
                {
                    tempSequence.tProf[cur_profile].times++;
                }
            }

            // exit
            else if (edit_val == 7)
            {
                long_press = FALSE;
                edit_mode = FALSE;
                edit_blink = FALSE;
                I2C_save_TempProfiles();

                Amplif_Init(0);
                Amplif_heating_prepare();
                Amplif_Start();
            }
        }

        // выключен edit
        else
        {
            Amplif_Stop();
            beep(1, 40);
            led_off(LED_RED);
            led_off(LED_BLUE);

            edit_mode = TRUE;
            edit_blink = TRUE;
            cur_profile = 0;
            edit_val = 0;
            long_press = FALSE;
            lng_cnt = 0;
            lng_coeff = 1;
            wait_key_unpressed();
        }
    }

    // short button press
    if (!long_press)
    {
        if (but != BUTTON_NONE)
        {
            uint8_t lng_press = 0;
            do
            {
                _delay_ms(50);
                if (get_key() == BUTTON_NONE)
                    break;
                if (edit_mode) lng_press++;
                if (lng_press > 15) break;
            } while(1);

            // long press
            if (lng_press > 15)
            {
                long_press = TRUE;
            }
        }
    }

    // long button press
    else
    {
        _delay_ms(50);
        if (get_key() == BUTTON_NONE)
        {
            long_press = FALSE;
            lng_cnt = 0;
            lng_coeff = 1;
        }

        if (lng_cnt < 30)
        {
            if (++lng_cnt >= 30)
            {
                lng_coeff = 10;
            }
        }

        tim_ms_presc_refscr = 0;
        edit_blink = FALSE;
        ref_screen = TRUE;
    }

    // IF amplification is ready
    if (Amplif.readyFlag)
    {
        Amplif.readyFlag = FALSE;
        edit_mode = TRUE;
        beep(3, 30);
        led_off(LED_RED);
        led_off(LED_BLUE);
    }

    // SHOW ERRORS
    if (Amplif.error != ERROR_NONE)
    {
        Amplif.State = Amp_Off;
        set_triac_pwr(0);
        lcd_xy(0, 50);
        lcd_set_inverted(TRUE);
        lcd_puts("ERROR:  ", &bnum_7x8);
        lcd_put_hex_byte(Amplif.error, &bnum_7x8);
        lcd_puts("  ", &bnum_7x8);
        lcd_set_inverted(FALSE);
        lcd_refresh();

    }
}



//====================================================================================================
// Menu scene 2
//
//====================================================================================================
void menu_scene_options()
{
    //test_mode = TRUE;

    if (ref_screen)
    {
        ref_screen = FALSE;

        lcd_clear();

        // current temp
        lcd_xy(0, 0);
        lcd_putc('\x18', &bnum_7x8);
        lcd_put_temp_val(Tval[0], &bnum_7x8);
        lcd_xy(60, 0);
        lcd_putc('\x1b', &bnum_7x8);
        lcd_put_temp_val(Tval[1], &bnum_7x8);

        // heater indicator
        lcd_xy(0, 15);
        lcd_puts("\x15 ", &bnum_7x8);
        if (edit_blink && edit_val == 0)
            lcd_set_inverted(TRUE);
        else
            lcd_set_inverted(FALSE);
        //lcd_put_int(get_triac_pwr(), &bnum_7x8);
        lcd_put_int(get_heater_pwm(), &bnum_7x8);
        lcd_set_inverted(FALSE);
        lcd_puts("%", &bnum_7x8);

        // vents indicators
        lcd_xy(0, 26);
        lcd_puts("\x17 ", &bnum_7x8);
        if (edit_blink && edit_val == 1)
            lcd_set_inverted(TRUE);
        else
            lcd_set_inverted(FALSE);
        lcd_put_int(get_fan_speed(FAN1_INDEX), &bnum_7x8);
        lcd_set_inverted(FALSE);
        lcd_putc('%', &bnum_7x8);

        lcd_xy(60, 26);
        lcd_puts("\x16 ", &bnum_7x8);
        if (edit_blink && edit_val == 2)
            lcd_set_inverted(TRUE);
        else
            lcd_set_inverted(FALSE);
        lcd_put_int(get_fan_speed(FAN2_INDEX), &bnum_7x8);
        lcd_set_inverted(FALSE);
        lcd_putc('%', &bnum_7x8);


        /*
        lcd_xy(0, 40);
        if (edit_blink && edit_val == 3)
            lcd_set_inverted(TRUE);
        else
            lcd_set_inverted(FALSE);
        lcd_put_temp_val(dest_temp, &bnum_7x8);
        lcd_set_inverted(FALSE);
        */
        /*
        lcd_xy(60, 40);
        if (edit_blink && edit_val == 4)
            lcd_set_inverted(TRUE);
        else
            lcd_set_inverted(FALSE);
        lcd_put_int(amplif_on, &bnum_7x8);
        lcd_set_inverted(FALSE);
        */

        // exit icon
        if (edit_mode)
        {
            lcd_xy(118, 53);
            if (edit_blink && edit_val == 5)
                lcd_set_inverted(TRUE);
            else
                lcd_set_inverted(FALSE);
            lcd_putc('\x19', &bnum_7x8);
            lcd_set_inverted(FALSE);
        }

        lcd_refresh();

        // if blink enabled
        if (edit_mode)
        {
            if (edit_blink)
                edit_blink = FALSE;
            else
                edit_blink = TRUE;
        }
    }

    // if button longer was not released
    if (long_press)
    {

    }

    // no one button early was pressed
    else
    {
        // read buttons state
        but = get_key();
        if (but != BUTTON_NONE)
        {
            one_beep();
            if (edit_mode)
            {
                edit_blink = TRUE;
                ref_screen = TRUE;
                tim_ms_presc_refscr = 0;
            }
        }
    }

    // MOVE LEFT
    if (but == BUTTON_LEFT)
    {
        if (edit_mode)
        {
            if (edit_val > 0)
                edit_val--;
            else
                edit_val = MENU2_EDIT_VALS_CNT-1;
        }
    }

    // MOVE RIGHT
    else if (but == BUTTON_RIGHT)
    {
        if (edit_mode)
        {
            if (edit_val < MENU2_EDIT_VALS_CNT-1)
                edit_val++;
            else
                edit_val = 0;
        }
    }

    // DEC VAL
    else if (but == BUTTON_CANCEL)
    {
        if (edit_mode)
        {
            // heater power
            if (edit_val == 0)
            {
                //uint8_t tp = get_triac_pwr();
                uint8_t tp = get_heater_pwm();
                if (tp > 0)
                {
                    tp--;
                    //set_triac_pwr(tp);
                    set_heater_pwm(tp);
                }
            }

            // vent 1 speed
            else if (edit_val == 1)
            {
                uint8_t sp = get_fan_speed(FAN1_INDEX);
                /*if (sp >= 5)
                {
                    sp -= 5;
                    set_fan_speed(FAN1_INDEX, sp);
                }*/
                if (sp)
                    set_fan(FAN1_INDEX, FALSE);
                else
                    set_fan(FAN1_INDEX, TRUE);

            }

            // vent 2 speed
            else if (edit_val == 2)
            {
                uint8_t sp = get_fan_speed(FAN2_INDEX);
                /*
                if (sp >= 5)
                {
                    sp -= 5;
                    set_fan_speed(FAN2_INDEX, sp);
                }*/
                if (sp)
                    set_fan(FAN2_INDEX, FALSE);
                else
                    set_fan(FAN2_INDEX, TRUE);
            }

            // destination temp
            else if (edit_val == 3)
            {/*
                if (dest_temp > MIN_TEMP)
                {
                    dest_temp -= 10;
                }*/
            }

            // amplif on/off
            else if (edit_val == 4)
            {
                //amplif_on = !amplif_on;
            }

            // exit
            else if (edit_val == 5)
            {
                long_press = FALSE;
                edit_mode = FALSE;
                edit_blink = FALSE;
            }
        }

        // edit выключен
        else
        {
            edit_mode = TRUE;
            edit_blink = TRUE;
            cur_profile = 0;
            edit_val = 0;
            long_press = FALSE;
            lng_cnt = 0;
            lng_coeff = 1;
            wait_key_unpressed();
        }
    }

    // INC VAL
    else if (but == BUTTON_OK)
    {
        if (edit_mode)
        {
            // heater power
            if (edit_val == 0)
            {
                //uint8_t tp = get_triac_pwr();
                uint8_t tp = get_heater_pwm();
                if (tp < 100)
                {
                    tp++;
                    //set_triac_pwr(tp);
                    set_heater_pwm(tp);
                }
            }

            // vent 1 speed
            else if (edit_val == 1)
            {
                uint8_t sp = get_fan_speed(FAN1_INDEX);
                /*if (sp <= 95)
                {
                    sp += 5;
                    set_fan_speed(FAN1_INDEX, sp);
                }*/
                if (sp)
                    set_fan(FAN1_INDEX, FALSE);
                else
                    set_fan(FAN1_INDEX, TRUE);
            }

            // vent 2 speed
            else if (edit_val == 2)
            {
                uint8_t sp = get_fan_speed(FAN2_INDEX);
                /*if (sp <= 95)
                {
                    sp += 5;
                    set_fan_speed(FAN2_INDEX, sp);
                }*/
                if (sp)
                    set_fan(FAN2_INDEX, FALSE);
                else
                    set_fan(FAN2_INDEX, TRUE);
            }

            // destination temp
            else if (edit_val == 3)
            {/*
                if (dest_temp < MAX_TEMP)
                {
                    dest_temp += 10;
                }*/
            }

            // amplif on/off
            else if (edit_val == 4)
            {
                //amplif_on = !amplif_on;
            }

            // exit
            else if (edit_val == 5)
            {
                long_press = FALSE;
                edit_mode = FALSE;
                edit_blink = FALSE;
            }
        }

        // выключен edit
        else
        {
            edit_mode = TRUE;
            edit_blink = TRUE;
            cur_profile = 0;
            edit_val = 0;
            long_press = FALSE;
            lng_cnt = 0;
            lng_coeff = 1;
            wait_key_unpressed();
        }
    }


    // short button press
    if (!long_press)
    {
        if (but != BUTTON_NONE)
        {
            uint8_t lng_press = 0;
            do
            {
                _delay_ms(50);
                if (get_key() == BUTTON_NONE)
                    break;
                if (edit_mode) lng_press++;
                if (lng_press > 15) break;
            } while(1);

            // long press disabled
            if (lng_press > 15)
            {
                long_press = TRUE;
            }
        }
    }

    // long button press
    else
    {
        _delay_ms(50);
        if (get_key() == BUTTON_NONE)
        {
            long_press = FALSE;
            lng_cnt = 0;
            lng_coeff = 1;
        }

        if (lng_cnt < 30)
        {
            if (++lng_cnt >= 30)
            {
                lng_coeff = 10;
            }
        }

        tim_ms_presc_refscr = 0;
        edit_blink = FALSE;
        ref_screen = TRUE;
    }
}
