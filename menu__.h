

#ifndef  __MENU_H_
#define __MENU_H_

#define  MENU1_EDIT_VALS_CNT        8
#define  MENU2_EDIT_VALS_CNT        6

void show_error(uint8_t err);
int8_t menu_amplification();
uint8_t  menu_select_program(uint8_t sp);
int8_t  menu_2_pos(char *str1, char *str2);
int8_t  menu_edit_program(uint8_t prg_num);
void menu_scene_with_params();
void menu_scene_options();

#endif // __MENU_H_
