
#include "bsp.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcd_UC1701.h"
#include "delay.h"
#include "font.h"


extern const tFont bnum_7x8;

__IO uint8_t 	LCDmem[LCD_COLS_CNT][LCD_PAGES_CNT];
__IO int16_t Xpos;
__IO int8_t Ypos;
__IO bool SelText;


bool  _crlf_allow_ = TRUE;
bool  _rle_image_ = TRUE;
bool  _inverted_ = FALSE;
bool  _XOR_mode_ = FALSE;


//================================================================================================//
//  Private functions
//================================================================================================//
inline void lcd_send_cmd(uint8_t cmd)
{
  GPIO_ResetBits(LCD_CD_PORT, LCD_CD_PIN);
  SPI_I2S_SendData(SPI2, cmd);
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
}

//================================================================================================//
inline void lcd_send_data(uint8_t data)
{
  GPIO_SetBits(LCD_CD_PORT, LCD_CD_PIN);
  SPI_I2S_SendData(SPI2, data);
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
}

//================================================================================================//
inline void lcd_select()
{
  GPIO_ResetBits(LCD_CS_PORT, LCD_CS_PIN);
}

//================================================================================================//
inline void lcd_unselect()
{
  GPIO_SetBits(LCD_CS_PORT, LCD_CS_PIN);
}

//================================================================================================//
//  Public functions
//================================================================================================//
void lcd_perif_init()
{
  GPIO_InitTypeDef GPst;

  // LCD pins config
	GPst.GPIO_Mode = GPIO_Mode_Out_PP;
	GPst.GPIO_Speed = GPIO_Speed_50MHz;

	GPst.GPIO_Pin = LCD_RST_PIN;
	GPIO_Init(LCD_RST_PORT, &GPst);
	GPIO_SetBits(LCD_RST_PORT, LCD_RST_PIN);

	GPst.GPIO_Pin = LCD_CS_PIN;
	GPIO_Init(LCD_CS_PORT, &GPst);
	GPIO_SetBits(LCD_CS_PORT, LCD_CS_PIN);

	GPst.GPIO_Pin = LCD_CD_PIN;
	GPIO_Init(LCD_CD_PORT, &GPst);
	GPIO_SetBits(LCD_CD_PORT, LCD_CD_PIN);

	// SPI2/LCD gpio config
	GPst.GPIO_Mode = GPIO_Mode_AF_PP;
	GPst.GPIO_Speed = GPIO_Speed_50MHz;

	GPst.GPIO_Pin = LCD_SCK_PIN;
	GPIO_Init(LCD_SCK_PORT, &GPst);
	GPst.GPIO_Pin = LCD_SDA_PIN;
	GPIO_Init(LCD_SDA_PORT, &GPst);

  // SPI2 INIT (LCD PORT)
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);

	SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;     // Tsck = 1us (period)
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);

  // Enable SPI interrupt
  //SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);

  // Enable SPI2
  SPI_Cmd(SPI2, ENABLE);

}

//================================================================================================//
void lcd_draw_bitmap_mono(int x, int y, const tImage *image)
{
  uint8_t value = 0;
  int x0, y0;
  int counter = 0;
  const uint8_t *pdata = (const uint8_t *) image->data;

  // rows
  for (y0 = 0; y0 < image->height; y0++)
  {
    // columns
    for (x0 = 0; x0 < image->width; x0++)
    {
      // load new data
      if (counter == 0)
      {
        value = *pdata++;
        counter = 8;//image->dataSize;
      }
      counter--;

      // set pixel - NORMAL MODE
      if (!_inverted_)
      {
          if ((value & 0x80) == 0)
          {
            lcd_put_pixel(x + x0, y + y0, COLOR_BLACK);
          }

          else
          {
            lcd_put_pixel(x + x0, y + y0, COLOR_NONE);
          }
      }

      // INVERTED MODE
      else
      {
        if ((value & 0x80) == 0)
        {
          lcd_put_pixel(x + x0, y + y0, 0);
        }

        else
        {
          lcd_put_pixel(x + x0, y + y0, 1);
        }
      }

      value = value << 1;
    }
  }
}

//================================================================================================//
void lcd_draw_bitmap_mono_rle(int x, int y, const tImage *image)
{
  uint8_t value = 0;
  int x0, y0;
  int counter = 0;
  int8_t sequence = 0;
  int8_t nonsequence = 0;
  const uint8_t *pdata = (const uint8_t *) image->data;

  // rows
  for (y0 = 0; y0 < image->height && (y0 + y) < 64; y0++)
  {
    // columns
    for (x0 = 0; x0 < image->width; x0++)
    {
      // load new data
      if (counter == 0)
      {
        if ((sequence == 0) && (nonsequence == 0))
        {
            sequence = *pdata++;
            if (sequence < 0)
            {
                nonsequence = -sequence;
                sequence = 0;
            }
        }

        if (sequence > 0)
        {
            value = *pdata;

            sequence--;

            if (sequence == 0)
                pdata++;
        }

        if (nonsequence > 0)
        {
            value = *pdata++;
            nonsequence--;
        }
        counter = 8;//image->dataSize;
      }
      counter--;

      // INVERTED MODE
      if (_inverted_)
      {
        if ((value & 0x80) == 0)
        {
            lcd_put_pixel(x + x0, y + y0, 0);
        }

        else
        {
            lcd_put_pixel(x + x0, y + y0, 1);
        }
      }

      // NORMAL MODE
      else
      {
        if ((value & 0x80) == 0)
        {
            lcd_put_pixel(x + x0, y + y0, 1);
        }

        else
        {
            lcd_put_pixel(x + x0, y + y0, 0);
        }
      }

      value = value << 1;
    }
  }
}

//================================================================================================//
const tChar *find_char_by_code(int code, const tFont *font)
{
  int count = font->length;
  int first = 0;
  int last = count - 1;
  int mid = 0;

  if (count > 0)
  {
    if ((code >= font->chars[0].code) && (font->chars[count - 1].code))
    {
      while (last >= first)
      {
        mid = first + ((last - first) / 2);

        if (font->chars[mid].code < code)
        {
          first = mid + 1;
        }

        else
        {
          if (font->chars[mid].code > code)
          {
            last = mid - 1;
          }

          else
          {
            break;
          }
        }
      }

      if (font->chars[mid].code == code)
      {
        return (&font->chars[mid]);
      }
    }
  }

  return (0);
}

//================================================================================================//
inline void lcd_set_rle(bool st)
{
  _rle_image_ = st;
}

//================================================================================================//
inline void lcd_set_inverted(bool st)
{
  _inverted_ = st;
}

//================================================================================================//
inline void lcd_set_XOR(bool st)
{
  _XOR_mode_ = st;
}

//================================================================================================//
inline void lcd_set_auto_crlf(bool st)
{
  _crlf_allow_ = st;
}

//================================================================================================//
void lcd_crlf()
{
	Xpos = 0;
	Ypos += 10;
	if (Ypos >= LCD_MAX_Y) Ypos = 0;
}

//================================================================================================//
void lcd_progress_bar_top(int vcur, int vmax)
{
  uint8_t wx;

  wx = (128 * vcur)/vmax;
  if (wx > 128) wx = 128;
  lcd_rect(0, 59, 128, 5, COLOR_BLACK);
  lcd_fill_rect(0, 59, wx, 5, COLOR_BLACK);

  lcd_put_pixel(0, 59, COLOR_NONE);
  lcd_put_pixel(127, 59, COLOR_NONE);
  lcd_put_pixel(0, 63, COLOR_NONE);
  lcd_put_pixel(127, 63, COLOR_NONE);
}

//================================================================================================//
void lcd_rect(int x0, int y0, int width, int height, int color)
{
  lcd_line(x0, y0, x0 + width - 1, y0, color);
  lcd_line(x0, y0, x0, y0 + height - 1, color);
  lcd_line(x0 + width - 1, y0, x0 + width - 1, y0 + height - 1, color);
  lcd_line(x0, y0 + height - 1, x0 + width - 1, y0 + height - 1, color);
}

//================================================================================================//
void lcd_draw_window(int x, int y, int width, int height, int color)
{
  if (color == COLOR_BLACK)
  {
    lcd_fill_rect(x+1, y+1, width, height, COLOR_BLACK);
  }

  else if (color == COLOR_NONE)
  {
    lcd_rect(x, y, width, height, COLOR_BLACK);
    lcd_line(x+1, y+height, x+width, y+height, COLOR_BLACK);
    lcd_line(x+width, y+1, x+width, y+height, COLOR_BLACK);
  }

  else if (color == COLOR_WHITE)
  {
    lcd_rect(x, y, width, height, COLOR_BLACK);
    lcd_fill_rect(x+1, y+1, width-2, height-2, COLOR_NONE);
    lcd_line(x+1, y+height, x+width, y+height, COLOR_BLACK);
    lcd_line(x+width, y+1, x+width, y+height, COLOR_BLACK);
  }
}

//================================================================================================//
void lcd_fill_rect(int x0, int y0, int width, int height, int color)
{
  for (int i = 0; i < height; i++)
  {
    lcd_line(x0, y0 + i, x0 + width - 1, y0 + i, color);
  }
}

//================================================================================================//
void lcd_line(int x0, int y0, int x1, int y1, int color)
{
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;

	if (dy < 0) { dy = -dy; stepy = -1; } else { stepy = 1; }
	if (dx < 0) { dx = -dx; stepx = -1; } else { stepx = 1; }
	dy <<= 1; // dy is now 2*dy
	dx <<= 1; // dx is now 2*dx

	lcd_put_pixel(x0, y0, color);

	if (dx > dy)
	{
		int fraction = dy - (dx >> 1); // same as 2*dy - dx

		while (x0 != x1)
		{
      if (fraction >= 0)
      {
        y0 += stepy;
        fraction -= dx; // same as fraction -= 2*dx
      }

      x0 += stepx;
      fraction += dy; // same as fraction -= 2*dy

      lcd_put_pixel(x0, y0, color);
		}
	}

	else
	{
		int fraction = dx - (dy >> 1);

		while (y0 != y1)
		{
			if (fraction >= 0)
			{
				x0 += stepx;
				fraction -= dy;
			}

			y0 += stepy;
			fraction += dx;

			lcd_put_pixel(x0, y0, color);
		}
	}
}

//================================================================================================//
void lcd_put_hex_word(uint16_t val, uint8_t font)
{
	uint8_t f;

	f = (val & 0xF000)>>12;
	if (f < 10) { lcd_putc(f + 0x30, font); } else { lcd_putc(f + 0x37, font); }
	f = (val & 0x0F00)>>8;
	if (f < 10) { lcd_putc(f + 0x30, font); } else { lcd_putc(f + 0x37, font); }
	f = (val & 0x00F0)>>4;
	if (f < 10) { lcd_putc(f + 0x30, font); } else { lcd_putc(f + 0x37, font); }
	f = (val & 0x000F);
	if (f < 10) { lcd_putc(f + 0x30, font); } else { lcd_putc(f + 0x37, font); }
}

//================================================================================================//
void lcd_put_hex_dword(uint32_t val, uint8_t font)
{
	uint16_t w;
	w = val>>16;
	lcd_put_hex_word(w, font);
	w = (uint16_t)val;
	lcd_put_hex_word(w, font);
}

//================================================================================================//
void lcd_put_hex_byte(uint8_t val, uint8_t font)
{
	uint8_t f;

	f = (val & 0xF0)>>4;
	if (f < 10) { lcd_putc(f + 0x30, font); } else { lcd_putc(f + 0x37, font); }
	f = (val & 0x0F);
	if (f < 10) { lcd_putc(f + 0x30, font); } else { lcd_putc(f + 0x37, font); }
}

//================================================================================================//
void lcd_put_time_min_sec(uint32_t tim, uint8_t font)
{
  // secs
  uint8_t sec = tim % 60;
  tim /= 60;
  uint8_t min = tim % 60;
  //tim /= 60;
  //uint8_t hour = tim;

  //if (hour < 10) lcd_putc('0', font);
  //lcd_put_uint(hour, font);
  //lcd_putc(':', font);
  if (min < 10) lcd_putc('0', font);
  lcd_put_uint(min, font);
  lcd_putc(':', font);
  if (sec < 10) lcd_putc('0', font);
  lcd_put_uint(sec, font);
}

//================================================================================================//
void lcd_put_time(uint32_t tim, uint8_t font)
{
  // secs
  uint8_t sec = tim % 60;
  tim /= 60;
  uint8_t min = tim % 60;
  tim /= 60;
  uint8_t hour = tim;

  if (hour < 10) { lcd_putc('0', font); }
  lcd_put_uint(hour, font);

  lcd_putc(':', font);

  if (min < 10) { lcd_putc('0', font); }
  lcd_put_uint(min, font);

  lcd_putc(':', font);

  if (sec < 10) { lcd_putc('0', font); }
  lcd_put_uint(sec, font);
}

//================================================================================================//
void lcd_put_int(int16_t vl, uint8_t font)
{
  if (vl < 0)
  {
    vl *= -1;
    lcd_putc('-', font);
  }

  lcd_put_uint(vl, font);
}

//================================================================================================//
void lcd_put_uint(uint16_t ui, uint8_t font)
{
	uint8_t i = 0, z = 0;

	i = ui / 10000;
	if (i != 0)
  {
		lcd_putc(0x30 + i, font);
		z = 1;
	}

	ui %= 10000;
	i = ui / 1000;

	if (i != 0 || z != 0)
	{
		lcd_putc(0x30 + i, font);
		z = 1;
	}

	ui %= 1000;
	i = ui / 100;

	if (i != 0 || z != 0)
  {
		lcd_putc(0x30 + i, font);
		z = 1;
	}

	ui %= 100;
	i = ui / 10;

	if(i != 0 || z != 0)
  {
    lcd_putc(0x30 + i, font);
  }

	ui %= 10;
	lcd_putc(0x30 + ui, font);
}

//================================================================================================//
void lcd_int16_to_str(int32_t ui, char* str, bool show_all_num)
{
	uint8_t i = 0, z = 0;
	uint8_t cp = 0;

	if (show_all_num)
  {
    z = 1;
  }

  if (ui < 0)
  {
    ui *= -1;
    str[cp++] = '-';
  }

	i = ui / 10000;
	if (i != 0 || z != 0)
  {
		str[cp++] = 0x30 + i;
		z = 1;
	}

	ui %= 10000;
	i = ui / 1000;

	if (i != 0 || z != 0)
	{
		str[cp++] = 0x30 + i;
		z = 1;
	}

	ui %= 1000;
	i = ui / 100;

	if (i != 0 || z != 0)
  {
		str[cp++] = 0x30 + i;
		z = 1;
	}

	ui %= 100;
	i = ui / 10;

	if(i != 0 || z != 0)
  {
    str[cp++] = 0x30 + i;
  }

	ui %= 10;
	str[cp++] = 0x30 + ui;
  str[cp++] = 0;
}

//================================================================================================//
uint16_t lcd_str_len(String str)
{
  uint16_t i = 0;
  while(str[i] != 0)
  {
    i++;
    if (i == 0) return 0;
  }
  return i;
}

//================================================================================================//
inline void lcd_str_clear(char* str)
{
  *str = 0;
}

//================================================================================================//
void lcd_str_add(char* str, String addstr)
{
  uint16_t l1 = 0, l2 = 0;

  l1 = lcd_str_len(str);
  l2 = lcd_str_len(addstr);

  for (uint16_t i = 0; i < l2; i++)
  {
    str[l1 + i] = addstr[i];
  }

  str[l1 + l2] = 0;
}


//================================================================================================//
uint16_t lcd_get_string_width(String str, uint8_t fnum)
{
	uint8_t i = 0;
	uint16_t width = 0;
	char c = 0;

	const tFont *font = getFont(fnum);

	do
	{
		c = str[i++];
		if (!c) break;

		const tChar *ch = find_char_by_code(c, font);
		width += ch->image->width;
	}
  while(c);

  return width;
}

#if 0
//================================================================================================//
void lcd_puts_in_center_and_sel(String str, uint8_t font, uint16_t y,
                                uint8_t st_sel, uint8_t end_sel)
{
  uint16_t x = (LCD_MAX_X / 2) - (lcd_get_string_width(str, font) / 2);

  lcd_xy(x, y);
  lcd_puts_sel(str, font, st_sel, end_sel);
}
#endif

//================================================================================================//
void lcd_puts_in_center(String str, uint8_t font, uint16_t y)
{
  uint16_t x = (LCD_MAX_X / 2) - (lcd_get_string_width(str, font) / 2);

  lcd_xy(x, y);
  lcd_puts(str, font);
}

//================================================================================================//
#if 0
void lcd_puts_sel(String addr, uint8_t font, uint8_t st_sel, uint8_t end_sel)
{
  char c;
	uint8_t i = 0;

	while (1)
	{
		c = addr[i];
		if (c == 0) break;
		if (i >= st_sel && i <= end_sel)
    {
      lcd_set_inverted(TRUE);
    }

    else
    {
      lcd_set_inverted(FALSE);
    }

		lcd_putc(c, font);
		i++;
	}

}
#endif // 0

//================================================================================================//
void lcd_puts(String addr, uint8_t font)
{
	char c;
	uint8_t i = 0;

	while (1)
	{
		c = addr[i];
		if (c == 0) break;
		lcd_putc(c, font);
		i++;
	}
}


//================================================================================================//
void lcd_putc(unsigned char code, uint8_t font_num)
{
	if (code == 0) return;

	if (code == '\n')
    {
		Xpos = 0;
		Ypos += 10; //ch->image->height;
		return;
	}

	const tFont *font = getFont(font_num);

	const tChar *ch = find_char_by_code(code, font);

	if (ch != 0)
  {
    // если нужен перевод строки
    if ((Xpos + ch->image->width) >= LCD_MAX_X  && _crlf_allow_)
    {
      Xpos = 0;
      Ypos += ch->image->height;
      if (Ypos >= LCD_MAX_Y) Ypos=0;
    }

    if (_rle_image_)
    {
      lcd_draw_bitmap_mono_rle(Xpos, Ypos, ch->image);
    }

    else
    {
      lcd_draw_bitmap_mono(Xpos, Ypos, ch->image);
    }

    Xpos += ch->image->width;
  }
}

//================================================================================================//
void lcd_xy(int16_t x, int8_t y)
{
	Xpos = x;
	Ypos = y;
}

//================================================================================================//
void lcd_refresh()
{
  lcd_select();

  for (uint8_t p = 0; p < LCD_PAGES_CNT; p++)
  {
    lcd_set_page_addr(p);
    lcd_set_col_addr(0);

    for (int16_t c = LCD_COLS_CNT-1; c>=0; c--)
    {
      lcd_send_data(LCDmem[c][p]);
    }
  }

  lcd_unselect();
}

//================================================================================================//
void lcd_put_pixel(int px, int py, int color)
{
	uint8_t page = py / 8;
  uint8_t  bt = py % 8;

  if (px >= 0 && px < LCD_MAX_X && py >= 0 && py <= LCD_MAX_Y)
  {
    // XOR MODE
    if (_XOR_mode_)
    {
      if (color != 0)
      {
        LCDmem[px][page] = LCDmem[px][page] ^ (1<<bt);
      }

      else
      {
        LCDmem[px][page] = LCDmem[px][page] ^ (0<<bt);
      }
    }

    // NORMAL MODE
    else
    {
      if (color != 0)
      {
        LCDmem[px][page] |= (1<<bt);
      }

      else
      {
        LCDmem[px][page] &= (~(1<<bt));
      }
    }
  }
}

//================================================================================================//
void lcd_clear()
{
	for(uint8_t p = 0; p < LCD_PAGES_CNT; p++)
  {
		for(uint16_t c = 0; c < LCD_COLS_CNT; c++)
    {
      LCDmem[c][p] = 0;
    }
  }

	Xpos = 0;
	Ypos = 0;
}

//================================================================================================//
void lcd_sram_clear()
{
  for (int p = 0; p < LCD_PAGES_CNT; p++)
  {
    lcd_set_page_addr(p);
    lcd_set_col_addr(0);

    for (int c = 0; c < LCD_COLS_CNT; c++)
    {
      lcd_send_data(0x00);
    }
  }
}

//================================================================================================//
// Set page address 0~15
void lcd_set_page_addr(uint8_t addr)
{
  addr = 0xb0|addr;
  lcd_send_cmd(addr);
}

//================================================================================================//
void lcd_set_col_addr(uint8_t addr)
{
  lcd_send_cmd((0x10|(addr>>4)));
	lcd_send_cmd((0x0f&addr));
}

//================================================================================================//
void lcd_init()
{
  lcd_reset();
  lcd_select();

  lcd_send_cmd(0xA0);
  lcd_send_cmd(0xC0);     // clear SHL: SHL 0,COM0-COM63
  lcd_send_cmd(0xA2);     //  bias 0   1/9 bais

  // Power_Control
  lcd_send_cmd(0x28|0x07);  // 0x07: 4 (internal converter ON) + 2 (internal regulor ON) + 1 (internal follower ON)

  /*  Regulor resistor select
  1+Rb/Ra  Vo=(1+Rb/Ra)Vev    Vev=(1-(63-a)/162)Vref   2.1v
  0  3.0       4  5.0(default)
  1  3.5       5  5.5
  2  4         6  6
  3  4.5       7  6.4*/
  lcd_send_cmd(0x20|0x06);

  // Set_Contrast_Control_Register
  // a(0-63) 32default   Vev=(1-(63-a)/162)Vref   2.1v
  lcd_send_cmd(0x81);
  lcd_send_cmd(19);       // contrast level

  //Specify DDRAM line for COM0 0~63
  // Initial_Dispay_Line: 0
  lcd_send_cmd(0x40 | 0);

  lcd_sram_clear();
  _LCD_DISPLAY_ON;      //  Display on

  lcd_unselect();
}

//================================================================================================//
void lcd_reset()
{
  GPIO_ResetBits(LCD_RST_PORT, LCD_RST_PIN);
  _delay_ms(5);
  GPIO_SetBits(LCD_RST_PORT, LCD_RST_PIN);
  _delay_ms(10);
}

//================================================================================================//

//================================================================================================//
#ifdef DOUBLE_SUPPORT
void lcd_putd(double num, int ndigit, uint8_t font)
{
    char buf[ndigit+4];
    gcvt(num, ndigit, buf);
    lcd_puts(buf, font);
}
#endif // DOUBLE_SUPPORT

