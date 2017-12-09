/**

*/


#include "bsp.h"
#include "inc.h"
#include "font.h"
#include "menu.h"
#include "counter.h"


uint8_t mmenu_pos = 0;

String mmenu_str[MAIN_MENU_ITEMS_CNT] =
{
  "Цикл. дозирование",
  "Настройки",
  "Дозирование",
  "Перекачивание"
};

menuListType mcycle_list;
menuListType msingle_list;
menuListType mpump_list;
menuComboType moptions_combo;


menuListType* allListMenu[MENU_LIST_CNT] =
{
    &mcycle_list,
    &msingle_list,
    &mpump_list
};

//================================================================================================//
void menu_init()
{
    mcycle_list.items_cnt = 3;
    mcycle_list.item[0].txt = "Объем,мл";
    mcycle_list.item[0].val = 10;
    mcycle_list.item[1].txt = "Пауза,с";
    mcycle_list.item[1].val = 5;
    mcycle_list.item[2].txt = "Кол-во циклов";
    mcycle_list.item[2].val = 3;

    msingle_list.items_cnt = 1;
    msingle_list.item[0].txt = "Объем,мл";
    msingle_list.item[0].val = 500;

    mpump_list.items_cnt = 2;
    mpump_list.item[0].txt = "Произв.,мл/мин";
    mpump_list.item[0].val = 11000;
    mpump_list.item[1].txt = "Время,с";
    mpump_list.item[1].val = 30;
    I2C_load_all_lists(allListMenu);

    moptions_combo.cnt = 4;
    moptions_combo.item[0].txt = "Диам.шланга";
    moptions_combo.item[0].cnt = K2_4_VALS_CNT;
    moptions_combo.item[0].selected = 2;
    moptions_combo.item[0].item[0].txt = "3 мм";
    moptions_combo.item[0].item[1].txt = "4 мм";
    moptions_combo.item[0].item[2].txt = "5 мм";
    moptions_combo.item[0].item[3].txt = "6 мм";
    moptions_combo.item[0].item[4].txt = "7 мм";
    moptions_combo.item[0].item[5].txt = "8 мм";
    moptions_combo.item[0].item[6].txt = "9 мм";
    moptions_combo.item[0].item[7].txt = "10 мм";
    moptions_combo.item[0].item[8].txt = "11 мм";
    moptions_combo.item[0].item[9].txt = "12 мм";
    moptions_combo.item[1].txt = "Толщ.стенки";
    moptions_combo.item[1].cnt = K3_VALS_CNT;
    moptions_combo.item[1].selected = 1;
    moptions_combo.item[1].item[0].txt = "1.5 мм";
    moptions_combo.item[1].item[1].txt = "2 мм";
    moptions_combo.item[1].item[2].txt = "3 мм";
    moptions_combo.item[1].item[3].txt = "4 мм";
    moptions_combo.item[1].item[4].txt = "5 мм";
    moptions_combo.item[2].txt = "Головка";
    moptions_combo.item[2].cnt = K1_VALS_CNT;
    moptions_combo.item[2].selected = 1;
    moptions_combo.item[2].item[0].txt = "ДГ80";
    moptions_combo.item[2].item[1].txt = "ДГ160";
    moptions_combo.item[3].txt = "Коэф.передачи";
    moptions_combo.item[3].cnt = I_VALS_CNT;
    moptions_combo.item[3].selected = 0;
    moptions_combo.item[3].item[0].txt = "10";
    moptions_combo.item[3].item[1].txt = "15";

    // load options from memory
    I2C_load_options(&moptions_combo);
    mainKoeffType*  mainKoeff = get_mainKoeff();
    mainKoeff->k0 = 100;
    calc_Rc(&moptions_combo);
}

//================================================================================================//
uint8_t menu_main()
{
  uint8_t mmenu_pos = 0;
  menu_draw_main(mmenu_pos);

  while(1)
  {
    uint8_t key = wait_key();

    // <--- RIGHT
    if (key == BUTTON_RIGHT)
    {
      if (++mmenu_pos >= MAIN_MENU_ITEMS_CNT) mmenu_pos = 0;
    }

    // LEFT --->
    else if (key == BUTTON_LEFT)
    {
      if (mmenu_pos > 0)
      {
        mmenu_pos--;
      }

      else
      {
        mmenu_pos = MAIN_MENU_ITEMS_CNT-1;
      }
    }

    // ENTER
    else if (key == BUTTON_OK)
    {
      uint8_t cur_p = ((mmenu_pos+2)%MAIN_MENU_ITEMS_CNT);

      if (cur_p == MAIN_MENU_OPTIONS)
      {
        menu_options();
      }

      else if (cur_p == MAIN_MENU_CONT_PUMP)
      {
        menu_pumping();
        wait_key_unpressed();
      }

      else if (cur_p == MAIN_MENU_SINGLE_PUMP)
      {
        menu_single_pumping();
      }

      else if (cur_p == MAIN_MENU_CYCLE_PUMP)
      {
        menu_cycle_pumping();
      }
    }

    // START
    else if (key == BUTTON_START)
    {
        play_melody(MELODY_CANCEL);
    }

    // STOP
    else if (key == BUTTON_STOP)
    {
        play_melody(MELODY_CANCEL);
    }

    // CANCEL
    else if (key == BUTTON_CANCEL)
    {
        play_melody(MELODY_CANCEL);
    }

    menu_draw_main(mmenu_pos);

    wait_key_unpressed();
  }
}

//================================================================================================//
void menu_draw_main(uint8_t ico_pos)
{
  lcd_clear();
  lcd_set_auto_crlf(FALSE);

  lcd_xy(-24, 3);
  lcd_putc(0x30 + ((ico_pos)%MAIN_MENU_ITEMS_CNT), FONT_ICONS_32xx32);

  lcd_xy(12, 3);
  lcd_putc(0x30 + ((ico_pos+1)%MAIN_MENU_ITEMS_CNT), FONT_ICONS_32xx32);

  lcd_xy(48, 12);
  lcd_putc(0x30 + ((ico_pos+2)%MAIN_MENU_ITEMS_CNT), FONT_ICONS_32xx32);

  lcd_xy(84, 3);
  lcd_putc(0x30 + ((ico_pos+3)%MAIN_MENU_ITEMS_CNT), FONT_ICONS_32xx32);

  lcd_xy(120, 3);
  lcd_putc(0x30 + ((ico_pos+4)%MAIN_MENU_ITEMS_CNT), FONT_ICONS_32xx32);

  lcd_xy(6,50);
  uint8_t cur_p = (ico_pos+2)%MAIN_MENU_ITEMS_CNT;

  lcd_puts_in_center(mmenu_str[cur_p], FONT_DEFAULT, 50);

  lcd_refresh();
  lcd_set_auto_crlf(TRUE);
}

//================================================================================================//
uint8_t menu_single_pumping()
{
  uint8_t ret = BUTTON_NONE;

  while(1)
  {
    ret = menu_list_menu(mmenu_str[MAIN_MENU_SINGLE_PUMP], &msingle_list);

    if (ret == BUTTON_CANCEL || ret == BUTTON_STOP) return 0;

    if (ret == BUTTON_START)
    {
      menu_single_pumping_start(msingle_list.item[0].val);
      // STOP
      wait_key_unpressed();
    }

    else if (ret == BUTTON_START)
    {
        play_melody(MELODY_CANCEL);
    }
  }

  return 0;
}

//================================================================================================//
#define MSPSBOX_TOP    13
void menu_single_pumping_start(uint32_t needV)
{
  char str[40];
  uint16_t tm = 10;
  uint8_t  tm_del = 0;

  lcd_draw_window(7, 6, LCD_MAX_X-14, 47, COLOR_WHITE);
  lcd_puts_in_center("Дозируем...", FONT_DEFAULT, MSPSBOX_TOP);
  lcd_puts_in_center("Объем,мл:", FONT_DEFAULT, MSPSBOX_TOP + 12);

  play_melody(MELODY_GAMMA);

  uint32_t Vc = calc_counter(needV);
  uint32_t sVc = Vc;
  set_counter(Vc);

  do
  {
    lcd_fill_rect(30, MSPSBOX_TOP + 23, 127-60, 10, COLOR_NONE);

    // calc actual V
    Vc = get_counter();
    uint32_t V = get_V(sVc - Vc);

    lcd_int16_to_str(V, str, FALSE);
    lcd_puts_in_center(str, FONT_DEFAULT, MSPSBOX_TOP + 24);

    #if 1
    lcd_xy(50, MSPSBOX_TOP + 36);
    lcd_put_hex_dword(Vc, FONT_DEFAULT);
    #endif

    lcd_refresh();

    /*for (uint8_t d=0; d<40; d++)
    {
      _delay_ms(25);

      if (get_key() == BUTTON_STOP)
      {
        return;
      }
    }

    tm--;*/

    if (get_key() == BUTTON_STOP)
    {
        play_melody(MELODY_CANCEL);
        return;
    }
  }
  while(Vc != 0);

  play_melody(MELODY_ELKA);
}

//================================================================================================//
uint8_t menu_options()
{
  uint8_t ret = BUTTON_NONE;

  while(1)
  {
    ret = menu_combo_menu(mmenu_str[MAIN_MENU_OPTIONS], &moptions_combo);

    calc_Rc(&moptions_combo);

    if (ret == BUTTON_CANCEL || ret == BUTTON_STOP)
    {
        return 0;
    }

    // START
    else if (ret == BUTTON_START)
    {
        play_melody(MELODY_CANCEL);
    }
  }

  return 0;
}

//================================================================================================//
uint8_t menu_cycle_pumping()
{
  uint8_t ret = BUTTON_NONE;

  while(1)
  {
    ret = menu_list_menu(mmenu_str[MAIN_MENU_CYCLE_PUMP], &mcycle_list);
    if (ret == BUTTON_CANCEL || ret == BUTTON_STOP) return 0;

    if (ret == BUTTON_START)
    {
      // START
      menu_cpumping_start(mcycle_list.item[0].val, mcycle_list.item[1].val,
                          mcycle_list.item[2].val);
      // STOP
      wait_key_unpressed();
    }

    else
    {
        play_melody(MELODY_CANCEL);
    }
  }

  return 0;
}

//================================================================================================//
uint8_t menu_pumping()
{
  uint8_t ret = BUTTON_NONE;

  while(1)
  {
    ret = menu_list_menu(mmenu_str[MAIN_MENU_CONT_PUMP], &mpump_list);

    if (ret == BUTTON_CANCEL || ret == BUTTON_STOP) return 0;

    if (ret == BUTTON_START)
    {
        // START
        menu_pumping_start(mpump_list.item[1].val);
        // STOP
        wait_key_unpressed();
    }

    else
    {
        play_melody(MELODY_CANCEL);
    }
  }

  return 0;
}

//================================================================================================//
#define MPSBOX_TOP    13
void menu_pumping_start(uint32_t ptime)
{
  char str[10];
  uint16_t tm = 10;
  uint8_t  tm_del = 0;

  lcd_draw_window(7, 6, LCD_MAX_X-14, 47, COLOR_WHITE);
  lcd_puts_in_center("Перекачиваем...", FONT_DEFAULT, MPSBOX_TOP);
  lcd_puts_in_center("Время,с:", FONT_DEFAULT, MPSBOX_TOP + 12);

  play_melody(MELODY_GAMMA);

  while(ptime != 0)
  {
    lcd_fill_rect(30, MPSBOX_TOP + 23, 127-60, 10, COLOR_NONE);

    lcd_int16_to_str(ptime, str, FALSE);
    lcd_puts_in_center(str, FONT_DEFAULT, MPSBOX_TOP + 24);

    lcd_refresh();

    for (uint8_t d=0; d<40; d++)
    {
      _delay_ms(25);

      if (get_key() == BUTTON_STOP)
      {
        play_melody(MELODY_CANCEL);
        return;
      }
    }

    ptime--;
  }

  play_melody(MELODY_ELKA);
}

//================================================================================================//
#define MPCBOX_TOP    13
void menu_cpumping_start(uint32_t needV, uint32_t ptime, uint8_t ccnt)
{
    char str[30];
    char temp_str[10];
    uint16_t tm = 10;
    uint8_t  tm_del = 0;

    uint32_t V;
    uint32_t T;
    uint8_t C = ccnt;

    play_melody(MELODY_GAMMA);

    while(C != 0)
    {
        uint32_t Vc = calc_counter(needV);
        uint32_t sVc = Vc;
        set_counter(Vc);

        do
        {
            lcd_draw_window(7, 6, LCD_MAX_X-14, 47, COLOR_WHITE);
            lcd_puts_in_center("Дозируем...", FONT_DEFAULT, MPCBOX_TOP);

            lcd_str_clear(str);
            lcd_str_add(str, "Объем,мл: ");

            // calc actual V
            Vc = get_counter();
            uint32_t V = get_V(sVc - Vc);

            lcd_int16_to_str(V, temp_str, FALSE);
            lcd_str_add(str, temp_str);
            lcd_puts_in_center(str, FONT_DEFAULT, MPCBOX_TOP + 12);

            lcd_str_clear(str);
            lcd_str_add(str, "Циклы: ");
            lcd_int16_to_str(C, temp_str, FALSE);
            lcd_str_add(str, temp_str);
            lcd_puts_in_center(str, FONT_DEFAULT, MPCBOX_TOP + 24);

            lcd_refresh();

            if (get_key() == BUTTON_STOP)
            {
                play_melody(MELODY_CANCEL);
                return;
            }
        }
        while(Vc != 0);

        T = ptime;
        do
        {
            lcd_draw_window(7, 6, LCD_MAX_X-14, 47, COLOR_WHITE);
            lcd_puts_in_center("Дозируем...", FONT_DEFAULT, MPCBOX_TOP);

            lcd_str_clear(str);
            lcd_str_add(str, "Пауза,с: ");
            lcd_int16_to_str(T, temp_str, FALSE);
            lcd_str_add(str, temp_str);
            lcd_puts_in_center(str, FONT_DEFAULT, MPCBOX_TOP + 12);

            lcd_str_clear(str);
            lcd_str_add(str, "Циклы: ");
            lcd_int16_to_str(C, temp_str, FALSE);
            lcd_str_add(str, temp_str);
            lcd_puts_in_center(str, FONT_DEFAULT, MPCBOX_TOP + 24);

            lcd_refresh();

            for (uint8_t d=0; d<40; d++)
            {
                _delay_ms(25);

                if (get_key() == BUTTON_STOP)
                {
                    play_melody(MELODY_CANCEL);
                    return;
                }
            }

            T--;
        }
        while(T != 0);

        C--;
    }

    play_melody(MELODY_ELKA);
}

//================================================================================================//
uint8_t menu_list_menu(String header, menuListType *mlist)
{
  uint8_t mpos = 0;

  menu_draw_list(header, mlist, mpos);
  wait_key_unpressed();

  while(1)
  {
    uint8_t key = wait_key();

    // DOWN
    if (key == BUTTON_DOWN)
    {
      if (++mpos >= MENU_CPUMP_ITEMS_CNT) mpos = 0;
    }

    // UP
    else if (key == BUTTON_UP)
    {
      if (mpos > 0)
      {
        mpos--;
      }

      else
      {
        mpos = MENU_CPUMP_ITEMS_CNT-1;
      }
    }

    // OK
    else if (key == BUTTON_OK)
    {
      mlist->item[mpos].val = menu_enter_int(mlist->item[mpos].txt, mlist->item[mpos].val);
      I2C_save_all_lists(allListMenu);
    }

    // CANCEL
    else if (key == BUTTON_CANCEL)
    {
      break;
    }

    // START
    else if (key == BUTTON_START)
    {
      return BUTTON_START;
    }

    // STOP
    else if (key == BUTTON_STOP)
    {
      return BUTTON_STOP;
    }

    menu_draw_list(header, mlist, mpos);

    wait_key_unpressed();
  }

  wait_key_unpressed();
  return BUTTON_CANCEL;
}

//================================================================================================//
uint8_t menu_draw_list(String header, menuListType *mlist, uint8_t act_i)
{
  lcd_clear();
  menu_draw_header(header);

  for (uint8_t i=0; i<mlist->items_cnt; i++)
  {
    // selected item
    if (act_i == i)
    {
      lcd_set_inverted(TRUE);
      lcd_fill_rect(0, 16 + i*12, LCD_MAX_X-1, 12, COLOR_BLACK);
    }

    else
    {
      lcd_set_inverted(FALSE);
    }

    lcd_xy(1, 18 + i*12);
    lcd_puts(mlist->item[i].txt, FONT_DEFAULT);

    char str_bf[10];
    lcd_int16_to_str(mlist->item[i].val, str_bf, FALSE);
    uint8_t lw = lcd_get_string_width(str_bf, FONT_DEFAULT);

    lcd_xy(LCD_MAX_X - lw - 1, 18 + i*12);
    lcd_puts(str_bf, FONT_DEFAULT);
  }

  lcd_set_inverted(FALSE);
  lcd_refresh();
}

//================================================================================================//
uint8_t menu_combo_menu(String header, menuComboType *mcombo)
{
  uint8_t mpos = 0;
  uint8_t shft = 0;

  menu_draw_combo(header, mcombo, mpos, shft);
  wait_key_unpressed();

  while(1)
  {
    uint8_t key = wait_key();

    // DOWN
    if (key == BUTTON_DOWN)
    {
      if (++mpos >= mcombo->cnt)
      {
        mpos = 0;
      }
    }

    // UP
    else if (key == BUTTON_UP)
    {
      if (mpos > 0)
      {
        mpos--;
      }

      else
      {
        mpos = mcombo->cnt-1;
      }
    }

    // OK
    else if (key == BUTTON_OK)
    {
      menu_subcombo_menu(mcombo->item[mpos+shft].txt, &mcombo->item[mpos+shft]);
      I2C_save_options(&moptions_combo);
    }

    // CANCEL
    else if (key == BUTTON_CANCEL)
    {
      break;
    }

    // START
    else if (key == BUTTON_START)
    {
      return BUTTON_START;
    }

    // STOP
    else if (key == BUTTON_STOP)
    {
      return BUTTON_STOP;
    }

    menu_draw_combo(header, mcombo, mpos, shft);

    wait_key_unpressed();
  }

  wait_key_unpressed();
  return BUTTON_CANCEL;
}

//================================================================================================//
uint8_t menu_draw_combo(String header, menuComboType *mcombo, uint8_t sel_line, uint8_t shft)
{
  lcd_clear();
  menu_draw_header(header);

  for (uint8_t i=0; i<4; i++)
  {
    if (i+shft >= mcombo->cnt)
    {
      break;
    }

    // selected item
    if (sel_line == i+shft)
    {
      lcd_set_inverted(TRUE);
      lcd_fill_rect(0, 16 + i*12, LCD_MAX_X-1, 12, COLOR_BLACK);
    }

    else
    {
      lcd_set_inverted(FALSE);
    }

    lcd_xy(1, 18 + i*12);
    lcd_puts(mcombo->item[i+shft].txt, FONT_DEFAULT);

    String sel_i = mcombo->item[i+shft].item[mcombo->item[i+shft].selected].txt;
    uint8_t lw = lcd_get_string_width(sel_i, FONT_DEFAULT);

    lcd_xy(LCD_MAX_X - lw - 1, 18 + i*12);
    lcd_puts(sel_i, FONT_DEFAULT);
  }

  lcd_set_inverted(FALSE);
  lcd_refresh();
}

//================================================================================================//
uint8_t menu_subcombo_menu(String header, menuComboItemType *mscombo)
{
  uint8_t mpos = 0;
  uint8_t shft = 0;

  menu_draw_sub_combo(header, mscombo, mpos, shft);
  wait_key_unpressed();

  while(1)
  {
    uint8_t key = wait_key();

    // DOWN
    if (key == BUTTON_DOWN)
    {
      if ((mpos+shft+1) >= mscombo->cnt)
      {
        mpos = 0;
        shft = 0;
      }

      else
      {
        if (mpos < 3)
        {
          mpos++;
        }
        else
        {
          shft++;
        }
      }
    }

    // UP
    else if (key == BUTTON_UP)
    {
      if (mpos > 0)
      {
        mpos--;
      }

      else
      {
        if (shft > 0)
        {
          shft--;
        }
        else
        {
          if (mscombo->cnt > 4)
          {
            mpos = 3;
            shft = mscombo->cnt - 4;
          }
          else
          {
            mpos = mscombo->cnt-1;
          }
        }
      }
    }

    // OK
    else if (key == BUTTON_OK)
    {
      mscombo->selected = mpos + shft;
      wait_key_unpressed();
      return BUTTON_OK;
    }

    // CANCEL
    else if (key == BUTTON_CANCEL)
    {
      break;
    }

    menu_draw_sub_combo(header, mscombo, mpos, shft);

    wait_key_unpressed();
  }

  wait_key_unpressed();
  return BUTTON_CANCEL;
}

//================================================================================================//
uint8_t menu_draw_sub_combo(String header, menuComboItemType *mscombo, uint8_t sel_line, uint8_t shft)
{
  lcd_clear();
  menu_draw_header(header);

  for (uint8_t i=0; i<4; i++)
  {
    if (i+shft >= mscombo->cnt)
    {
      break;
    }

    // selected item
    if (sel_line == i)
    {
      lcd_set_inverted(TRUE);
      lcd_fill_rect(0, 16 + i*12, LCD_MAX_X-1, 12, COLOR_BLACK);
    }

    else
    {
      lcd_set_inverted(FALSE);
    }

    lcd_xy(1, 18 + i*12);
    lcd_puts(mscombo->item[i+shft].txt, FONT_DEFAULT);

    // if selected
    if (mscombo->selected == i+shft)
    {
      lcd_xy(118, 18 + i*12);
      lcd_putc('V', FONT_DEFAULT);
    }
  }

  lcd_set_inverted(FALSE);
  lcd_refresh();
}

#define MEBOX_X   27
#define MEBOX_Y   30
#define MEBOX_W   13
#define MEBOX_H   13
#define MEBOX_S   15
//================================================================================================//
int32_t menu_enter_int(String txt, int32_t intval)
{
  uint8_t num[5];
  uint8_t npos = 0;
  int32_t sval = intval;

  num[4] = intval / 10000;
  intval = intval % 10000;
  num[3] = intval / 1000;
  intval = intval % 1000;
  num[2] = intval / 100;
  intval = intval % 100;
  num[1] = intval / 10;
  num[0] = intval % 10;

  lcd_draw_window(15, 9, LCD_MAX_X-30, 41, COLOR_WHITE);
  lcd_puts_in_center(txt, FONT_DEFAULT, 16);

  lcd_fill_rect(MEBOX_X-2, MEBOX_Y-2, 15*5 + 2, 17, COLOR_NONE);

  for (uint8_t i = 0; i < 5; i++)
  {
    lcd_rect(MEBOX_X + i*MEBOX_S, MEBOX_Y, MEBOX_W, MEBOX_H, COLOR_BLACK);
    lcd_xy(MEBOX_X + 4 + i*MEBOX_S, MEBOX_Y + 3);
    lcd_putc(0x30 + num[4-i], FONT_DEFAULT);
  }

  lcd_rect(MEBOX_X + (4-npos)*MEBOX_S - 1, MEBOX_Y - 1, MEBOX_W + 2, MEBOX_H + 2, COLOR_BLACK);
  lcd_rect(MEBOX_X + (4-npos)*MEBOX_S - 2, MEBOX_Y - 2, MEBOX_W + 4, MEBOX_H + 4, COLOR_BLACK);

  lcd_refresh();

  wait_key_unpressed();

  while(1)
  {
    uint8_t key = wait_key();

    // <-- LEFT
    if (key == BUTTON_LEFT)
    {
      if (npos < 4) npos++;
    }

    // --> RIGHT
    else if (key == BUTTON_RIGHT)
    {
      if (npos > 0)
      {
        npos--;
      }
    }

    // UP
    else if (key == BUTTON_UP)
    {
      if (num[npos] == 9)
      {
        num[npos] = 0;
      }

      else
      {
        num[npos]++;
      }
    }

    // DOWN
    else if (key == BUTTON_DOWN)
    {
      if (num[npos] == 0)
      {
        num[npos] = 9;
      }

      else
      {
        num[npos]--;
      }
    }

    // OK
    else if (key == BUTTON_OK)
    {
      sval = num[4] * 10000;
      sval += num[3] * 1000;
      sval += num[2] * 100;
      sval += num[1] * 10;
      sval += num[0];
      break;
    }

    // CANCEL
    else if (key == BUTTON_CANCEL)
    {
      break;
    }

    lcd_fill_rect(MEBOX_X-2, MEBOX_Y-2, 15*5 + 2, 17, COLOR_NONE);

    for (uint8_t i = 0; i < 5; i++)
    {
      lcd_rect(MEBOX_X + i*MEBOX_S, MEBOX_Y, MEBOX_W, MEBOX_H, COLOR_BLACK);
      lcd_xy(MEBOX_X + 4 + i*MEBOX_S, MEBOX_Y + 3);
      lcd_putc(0x30 + num[4-i], FONT_DEFAULT);
    }

    lcd_rect(MEBOX_X + (4-npos)*MEBOX_S - 1, MEBOX_Y - 1, MEBOX_W + 2, MEBOX_H + 2, COLOR_BLACK);
    lcd_rect(MEBOX_X + (4-npos)*MEBOX_S - 2, MEBOX_Y - 2, MEBOX_W + 4, MEBOX_H + 4, COLOR_BLACK);

    lcd_refresh();

    wait_key_unpressed();
  }

  wait_key_unpressed();
  return sval;
}

//================================================================================================//
void menu_draw_header(String hstr)
{
  lcd_line(0, 0, 0, 11, COLOR_BLACK);
  lcd_line(1, 0, 1, 11, COLOR_BLACK);
  lcd_line(LCD_MAX_X-1, 0, LCD_MAX_X-1, 11, COLOR_BLACK);
  lcd_line(LCD_MAX_X-2, 0, LCD_MAX_X-2, 11, COLOR_BLACK);

  lcd_line(2, 12, LCD_MAX_X-3, 12, COLOR_BLACK);
  lcd_line(2, 13, LCD_MAX_X-3, 13, COLOR_BLACK);

  lcd_put_pixel(2, 11, COLOR_BLACK);
  lcd_put_pixel(1, 12, COLOR_BLACK);
  lcd_put_pixel(LCD_MAX_X-3, 11, COLOR_BLACK);
  lcd_put_pixel(LCD_MAX_X-2, 12, COLOR_BLACK);

  lcd_puts_in_center(hstr, FONT_DEFAULT, 2);
}
