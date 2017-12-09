#include <stdint.h>
#include "lcd_UC1701.h"
#include "font.h"

extern const tFont bnum_7x8;
extern const tFont icons_3232;

const tFont* font[3] =
{
  &bnum_7x8,
  &bnum_7x8,
  &icons_3232
};


inline const tFont* getFont(uint8_t fnum)
{
  return font[fnum];
}


