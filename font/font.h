#ifndef __FONT_H_
#define __FONT_H_

#include "lcd_UC1701.h"

typedef enum
{
  default_font = 0,
  main_font
}
fontType;


const tFont* getFont(uint8_t fnum);

#define FONT_DEFAULT          0
#define FONT_BNUM_7x8         1
#define FONT_ICONS_32xx32     2

#endif // __FONT_H_
