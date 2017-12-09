#ifndef __MENU_H_
#define __MENU_H_

/// Main menu definitions
#define MAIN_MENU_ITEMS_CNT     4
#define MAIN_MENU_CYCLE_PUMP    0
#define MAIN_MENU_OPTIONS       1
#define MAIN_MENU_SINGLE_PUMP   2
#define MAIN_MENU_CONT_PUMP     3

/// Cycle pumping menu
#define MENU_CPUMP_ITEMS_CNT     3

#include "bsp.h"

typedef struct
{
  String   txt;
  int32_t val;
}
menuListItemType;

typedef struct
{
  menuListItemType item[4];
  uint8_t items_cnt;
}
menuListType;

#define MENU_LIST_CNT       3

#define MENU_COMBO_ITEMS_MAX  10
#define MENU_COMBO_SUBITEMS_MAX  15

typedef struct
{
  String txt;
}
menuComboSubItemType;

typedef struct
{
  menuComboSubItemType item[MENU_COMBO_SUBITEMS_MAX];
  uint8_t selected;
  String txt;
  uint8_t cnt;
}
menuComboItemType;

typedef struct
{
  menuComboItemType item[MENU_COMBO_ITEMS_MAX];
  uint8_t cnt;
}
menuComboType;

void menu_init();
uint8_t menu_main();
void menu_draw_main(uint8_t ico_pos);


uint8_t menu_options();

uint8_t menu_pumping();
void menu_pumping_start(uint32_t ptime);

uint8_t menu_single_pumping();
void menu_single_pumping_start(uint32_t needV);

uint8_t menu_cycle_pumping();
void menu_cpumping_start(uint32_t needV, uint32_t ptime, uint8_t ccnt);

uint8_t menu_list_menu(String header, menuListType *mlist);
uint8_t menu_draw_list(String header, menuListType *mlist, uint8_t act_i);

uint8_t menu_combo_menu(String header, menuComboType *mcombo);
uint8_t menu_subcombo_menu(String header, menuComboItemType *mscombo);
uint8_t menu_draw_combo(String header, menuComboType *mcombo, uint8_t act_i, uint8_t shft);
uint8_t menu_draw_sub_combo(String header, menuComboItemType *mscombo, uint8_t act_i, uint8_t shft);

void menu_draw_header(String hstr);
int32_t menu_enter_int(String txt, int32_t intval);

#endif // __MENU_H_
