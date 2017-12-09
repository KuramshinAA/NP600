
#ifndef __LCD_UC1701_
#define __LCD_UC1701_


#include <stdint.h>
#include <stdio.h>
#include "stm32f10x_gpio.h"
#include "bsp.h"

#define DOUBLE_SUPPORT

#define _LCD_DISPLAY_ON          lcd_send_cmd(0xAF)
#define _LCD_DISPLAY_OFF         lcd_send_cmd(0xAE)
#define _LCD_REV_DISP_ON         lcd_send_cmd(0xA7)
#define _LCD_REV_DISP_NORM       lcd_send_cmd(0xA6)
#define _LCD_ALL_DISP_ON         lcd_send_cmd(0xA5)
#define _LCD_ALL_DIPS_NORM       lcd_send_cmd(0xA4)
#define _LCD_SET_ADC             lcd_send_cmd(0xA1)   //  Reverse disrect (SEG131-SEG0)
#define _LCD_CLEAR_ADC           lcd_send_cmd(0xA0)   //  Normal disrect (SEG0-SEG131)

// uncomment if double output number needed
//define DOUBLE_SUPPORT

// uncomment if big number needed
//define BIG_NUMBER_SUPPORT

#define LCD_PAGES_CNT           8
#define LCD_COLS_CNT            LCD_MAX_X

#define LCD_MAX_X               128
#define LCD_MAX_Y               64

#define CRLF                    lcd_crlf()


typedef enum
{
    COLOR_NONE = 0,
    COLOR_BLACK = 1,
    COLOR_WHITE = 2
}
lcd_Color;

typedef struct
{
    const uint8_t  *data;
    uint16_t width;
    uint16_t height;
    //uint8_t  dataSize;
}
tImage;

typedef struct
{
    long int code;
    const tImage *image;
}
tChar;

typedef struct
{
    int length;
    const tChar *chars;
}
tFont;

void lcd_perif_init();
void lcd_draw_bitmap_mono();
void lcd_draw_bitmap_mono_rle(int x, int y, const tImage *image);
const tChar *find_char_by_code(int code, const tFont *font);
void lcd_set_rle(bool st);
void lcd_set_inverted(bool st);
void lcd_set_XOR(bool st);
void lcd_set_auto_crlf(bool st);
void lcd_crlf();
void lcd_progress_bar_top(int vcur, int vmax);
void lcd_rect(int x0, int y0, int width, int height, int color);
void lcd_draw_window(int x, int y, int width, int height, int color);
void lcd_fill_rect(int x0, int y0, int width, int height, int color);
void lcd_line(int x0, int y0, int x1, int y1, int color);
void lcd_put_hex_dword(uint32_t val, uint8_t font_num);
void lcd_put_hex_word(uint16_t val, uint8_t font_num);
void lcd_put_hex_byte(uint8_t val, uint8_t font_num);
void lcd_put_time_min_sec(uint32_t tim, uint8_t font_num);
void lcd_put_time(uint32_t tim, uint8_t font_num);
void lcd_put_int(int16_t vl, uint8_t font_num);
void lcd_put_uint(uint16_t ui, uint8_t font_num);
void lcd_puts(String addr, uint8_t font_num);
void lcd_puts_sel(String addr, uint8_t font, uint8_t st_sel, uint8_t end_sel);
void lcd_puts_in_center(String str, uint8_t font, uint16_t y);
uint16_t lcd_get_string_width(String str, uint8_t font);
void lcd_putc(unsigned char code, uint8_t font_num);
void lcd_xy(int16_t x, int8_t y);
void lcd_refresh();
void lcd_put_pixel(int px, int py, int color);
void lcd_clear();
void lcd_sram_clear();
void lcd_set_page_addr(uint8_t addr);
void lcd_set_col_addr(uint8_t addr);
void lcd_init();
void lcd_send_data(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void lcd_select();
void lcd_unselect();
void lcd_reset();


void lcd_int16_to_str(int32_t ui, char* str, bool show_all_num);
//void lcd_puts_in_center_and_sel(String str, uint8_t font, uint16_t y,
//                                uint8_t st_sel, uint8_t end_sel);

uint16_t lcd_str_len(String str);
void lcd_str_add(char* str, String addstr);
void lcd_str_clear(char* str);

#ifdef DOUBLE_SUPPORT
void lcd_putd(double num, int ndigit, uint8_t font);
#endif




#endif /* __LCD_UC1701_ */
