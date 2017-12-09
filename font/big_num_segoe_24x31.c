
/*******************************************************************************
* font
* filename: E:/lcd-image-converter-20131028/lcd-image-converter/big_num_Segoe_24x31.xml
* name: bnum_24x31
* family: Segoe UI Black
* size: 44
* style: Black
* included characters: .0123456789C°º
* antialiasing: no
* type: proportional
* encoding: ANSI1251
* unicode bom: yes
*
* preset name: Монохромное
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: yes
* conversion type: Monochrome, Threshold Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     long int code;
     const tImage *image;
     } tChar;
 typedef struct {
     int length;
     const tChar *chars;
     } tFont;
*/

#include <stdint.h>
#include "lcd_UC1701.h"


static const uint8_t image_data_bnum_24x31_0x2e[17] = {
    0x21, 0xff, 0xf2, 0xe0, 0x7c, 0x03, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x1c, 0x03, 0xf0, 0x70
};
static const tImage bnum_24x31_0x2e = { image_data_bnum_24x31_0x2e, 12, 31};

static const uint8_t image_data_bnum_24x31_0x30[105] = {
    0xe0, 0xff, 0x80, 0xff, 0xfc, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xf0, 0x00, 0x07, 0xe0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x3c, 0x01, 0x80, 0x3c, 0x01, 0x00, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xe3, 0x3c, 0x01, 0x80, 0x3c, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xf0, 0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xff, 0x00, 0xff
};
static const tImage bnum_24x31_0x30 = { image_data_bnum_24x31_0x30, 24, 31};

static const uint8_t image_data_bnum_24x31_0x31[76] = {
    0xed, 0xff, 0xc0, 0xff, 0xe0, 0x1f, 0xf0, 0x03, 0xf8, 0x00, 0x70, 0x00, 0x0e, 0x00, 0x01, 0xc0, 0x00, 0x38, 0x00, 0x07, 0x02, 0x00, 0xcb, 0xe0, 0x40, 0x1c, 0x78, 0x03, 0xff, 0x00, 0x7f, 0xe0, 0x0f, 0xfc, 0x01, 0xff, 0x80, 0x3f, 0xf0, 0x07, 0xfe, 0x00, 0xff, 0xc0, 0x1f, 0xf8, 0x03, 0xff, 0x00, 0x7f, 0xe0, 0x0f, 0xfc, 0x01, 0xff, 0x80, 0x3f, 0xf0, 0x07, 0xfe, 0x00, 0xff, 0xc0, 0x1f, 0xf8, 0x03, 0xff, 0x00, 0x7f, 0xe0, 0x0f, 0xfc, 0x01, 0xff, 0x80, 0x38
};
static const tImage bnum_24x31_0x31 = { image_data_bnum_24x31_0x31, 19, 31};

static const uint8_t image_data_bnum_24x31_0x32[94] = {
    0xa3, 0xff, 0x00, 0xff, 0xf8, 0x00, 0x3f, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x03, 0xe1, 0xf0, 0x03, 0xe7, 0xf8, 0x03, 0xef, 0xf8, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf0, 0x03, 0xff, 0xe0, 0x07, 0xff, 0xc0, 0x07, 0xff, 0x80, 0x0f, 0xff, 0x00, 0x1f, 0xfe, 0x00, 0x3f, 0xf8, 0x00, 0x7f, 0xf0, 0x01, 0xff, 0xf0, 0x03, 0xff, 0xe0, 0x0f, 0xff, 0xc0, 0x1f, 0xff, 0xc0, 0x3f, 0xff, 0x80, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x03
};
static const tImage bnum_24x31_0x32 = { image_data_bnum_24x31_0x32, 24, 31};

static const uint8_t image_data_bnum_24x31_0x33[94] = {
    0xa3, 0xfc, 0x01, 0xff, 0xe0, 0x00, 0x7f, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xff, 0xe0, 0x07, 0xff, 0xf0, 0x07, 0xff, 0xf0, 0x07, 0xff, 0xf0, 0x07, 0xff, 0xc0, 0x0f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x3f, 0xf8, 0x00, 0xff, 0xf8, 0x00, 0x7f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xf8, 0x00, 0x07, 0xff, 0xe0, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf0, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xc0, 0x00, 0x7f, 0xf0, 0x01, 0xff
};
static const tImage bnum_24x31_0x33 = { image_data_bnum_24x31_0x33, 24, 31};

static const uint8_t image_data_bnum_24x31_0x34[87] = {
    0xda, 0xff, 0xf0, 0x07, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x01, 0xff, 0xfc, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xfe, 0x00, 0x1f, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0x07, 0xff, 0x00, 0x03, 0xff, 0x80, 0x01, 0xff, 0x81, 0x00, 0xff, 0x02, 0x80, 0xff, 0x7f, 0x02, 0xc0, 0xec, 0x3f, 0xc0, 0x60, 0x1f, 0xc0, 0x30, 0x0f, 0xc0, 0x38, 0x07, 0xe0, 0x3c, 0x03, 0xe0, 0x1e, 0x01, 0xe0, 0x1f, 0x00, 0xf0, 0x12, 0x00, 0xfd, 0x3f, 0xfe, 0x01, 0x02, 0xff, 0xff, 0x00, 0x02, 0xff, 0xf8, 0x80, 0x7f, 0xff, 0xc0, 0x3f, 0xff, 0xe0, 0x1e
};
static const tImage bnum_24x31_0x34 = { image_data_bnum_24x31_0x34, 25, 31};

static const uint8_t image_data_bnum_24x31_0x35[94] = {
    0xa3, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0f, 0xf0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xe0, 0x1f, 0xff, 0xe0, 0x00, 0x7f, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x0f, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xef, 0xe0, 0x03, 0xff, 0xf0, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf0, 0x03, 0xff, 0xe0, 0x03, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xc0, 0x00, 0x3f, 0xc0, 0x00, 0x7f, 0xf0, 0x03, 0xff
};
static const tImage bnum_24x31_0x35 = { image_data_bnum_24x31_0x35, 24, 31};

static const uint8_t image_data_bnum_24x31_0x36[95] = {
    0xcc, 0xff, 0xf0, 0x07, 0xff, 0x80, 0x03, 0xfe, 0x00, 0x03, 0xfc, 0x00, 0x03, 0xf8, 0x00, 0x03, 0xf0, 0x00, 0x03, 0xf0, 0x00, 0x03, 0xe0, 0x03, 0xff, 0xe0, 0x0f, 0xff, 0xc0, 0x1f, 0xff, 0xc0, 0x1f, 0xff, 0xc0, 0x38, 0x1f, 0x80, 0x20, 0x07, 0x80, 0x00, 0x03, 0x80, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x02, 0x00, 0xd9, 0x80, 0x1c, 0x00, 0x80, 0x3e, 0x00, 0x80, 0x3e, 0x00, 0x80, 0x3e, 0x00, 0xc0, 0x3e, 0x00, 0xc0, 0x1c, 0x00, 0xc0, 0x00, 0x01, 0xe0, 0x00, 0x01, 0xe0, 0x00, 0x03, 0xf0, 0x00, 0x07, 0xf8, 0x00, 0x0f, 0xfe, 0x00, 0x1f, 0xff, 0x80, 0xff
};
static const tImage bnum_24x31_0x36 = { image_data_bnum_24x31_0x36, 24, 31};

static const uint8_t image_data_bnum_24x31_0x37[100] = {
    0xff, 0x80, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xb5, 0x80, 0x00, 0x01, 0xff, 0xfe, 0x01, 0xff, 0xfc, 0x03, 0xff, 0xf8, 0x03, 0xff, 0xf8, 0x07, 0xff, 0xf0, 0x07, 0xff, 0xf0, 0x0f, 0xff, 0xe0, 0x0f, 0xff, 0xe0, 0x1f, 0xff, 0xc0, 0x1f, 0xff, 0xc0, 0x1f, 0xff, 0x80, 0x3f, 0xff, 0x80, 0x3f, 0xff, 0x00, 0x7f, 0xff, 0x00, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0xff, 0xfc, 0x00, 0xff, 0xfc, 0x00, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff
};
static const tImage bnum_24x31_0x37 = { image_data_bnum_24x31_0x37, 24, 31};

static const uint8_t image_data_bnum_24x31_0x38[98] = {
    0xc2, 0xff, 0x00, 0xff, 0xf8, 0x00, 0x1f, 0xf0, 0x00, 0x0f, 0xe0, 0x00, 0x07, 0xc0, 0x00, 0x03, 0x80, 0x00, 0x01, 0x80, 0x3c, 0x01, 0x80, 0x7e, 0x01, 0x80, 0x7e, 0x01, 0x80, 0x7e, 0x01, 0x80, 0x7e, 0x01, 0xc0, 0x3c, 0x03, 0xc0, 0x00, 0x07, 0xe0, 0x00, 0x0f, 0xf0, 0x00, 0x1f, 0xf0, 0x00, 0x1f, 0xe0, 0x00, 0x07, 0xc0, 0x00, 0x03, 0x80, 0x3c, 0x01, 0x00, 0x7e, 0x01, 0x00, 0xff, 0x02, 0x00, 0xff, 0xff, 0x02, 0x00, 0xff, 0xff, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xec, 0x3c, 0x00, 0x80, 0x00, 0x01, 0x80, 0x00, 0x01, 0xc0, 0x00, 0x03, 0xe0, 0x00, 0x07, 0xf8, 0x00, 0x1f, 0xff, 0x00, 0xff
};
static const tImage bnum_24x31_0x38 = { image_data_bnum_24x31_0x38, 24, 31};

static const uint8_t image_data_bnum_24x31_0x39[102] = {
    0xe3, 0xff, 0x00, 0xff, 0xf8, 0x00, 0x3f, 0xf0, 0x00, 0x1f, 0xe0, 0x00, 0x07, 0xc0, 0x00, 0x07, 0x80, 0x00, 0x03, 0x80, 0x00, 0x01, 0x00, 0x3c, 0x01, 0x00, 0x7e, 0x01, 0x00, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xff, 0x7e, 0x02, 0x00, 0xfd, 0x3c, 0x00, 0x80, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xff, 0xc0, 0x02, 0x00, 0xff, 0xe0, 0x02, 0x00, 0xd9, 0xf0, 0x02, 0x00, 0xfc, 0x0e, 0x01, 0xff, 0xfe, 0x01, 0xff, 0xfc, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xe0, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xc0, 0x00, 0x3f, 0xc0, 0x00, 0xff, 0xf0, 0x03, 0xff
};
static const tImage bnum_24x31_0x39 = { image_data_bnum_24x31_0x39, 24, 31};

static const uint8_t image_data_bnum_24x31_0x43[112] = {
    0xf2, 0xff, 0xf0, 0x01, 0xff, 0xe0, 0x00, 0x1f, 0xe0, 0x00, 0x07, 0xf0, 0x00, 0x01, 0xf8, 0x02, 0x00, 0xff, 0x7c, 0x02, 0x00, 0xff, 0x1e, 0x02, 0x00, 0xff, 0x07, 0x02, 0x00, 0xe7, 0x01, 0xc0, 0x01, 0xfe, 0x60, 0x01, 0xff, 0xf8, 0x00, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0x00, 0x1f, 0xff, 0xc0, 0x0f, 0xff, 0xf0, 0x03, 0xff, 0xfc, 0x00, 0x02, 0xff, 0xe9, 0x00, 0x3f, 0xff, 0xc0, 0x0f, 0xff, 0xf0, 0x03, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0x80, 0x0f, 0xff, 0xe0, 0x01, 0xff, 0xf8, 0x00, 0x1f, 0xe7, 0x02, 0x00, 0xfe, 0x01, 0xc0, 0x02, 0x00, 0xff, 0x78, 0x02, 0x00, 0xff, 0x1f, 0x02, 0x00, 0xfb, 0x07, 0xe0, 0x00, 0x01, 0xfc, 0x02, 0x00, 0xf9, 0x7f, 0xc0, 0x00, 0x1f, 0xfe, 0x00, 0x3c
};
static const tImage bnum_24x31_0x43 = { image_data_bnum_24x31_0x43, 26, 31};

static const uint8_t image_data_bnum_24x31_0xb0[29] = {
    0xf9, 0xf8, 0x3f, 0xe0, 0x1f, 0x80, 0x1f, 0x00, 0x02, 0x3c, 0xfc, 0x38, 0x78, 0x70, 0xf0, 0x02, 0xe1, 0xf9, 0xe0, 0x07, 0xc0, 0x0f, 0xc0, 0x3f, 0xc1, 0x24, 0xff, 0x01, 0x80
};
static const tImage bnum_24x31_0xb0 = { image_data_bnum_24x31_0xb0, 15, 31};

static const uint8_t image_data_bnum_24x31_0x3f[43] = {
    0xf6, 0xfc, 0x07, 0xf8, 0x00, 0x7c, 0x00, 0x0e, 0x00, 0x01, 0x80, 0x02, 0x00, 0xf3, 0x78, 0x00, 0x1f, 0x00, 0x07, 0xc0, 0x01, 0xf0, 0x00, 0x7c, 0x00, 0x1e, 0x02, 0x02, 0x00, 0xf7, 0x80, 0x00, 0x70, 0x00, 0x3e, 0x00, 0x1f, 0xe0, 0x1f, 0x21, 0xff, 0x01, 0xfc
};
static const tImage bnum_24x31_0x3f = { image_data_bnum_24x31_0x3f, 18, 31};


static const tChar bnum_24x31_array[] = {

  // character: '.'
  {0x2e, &bnum_24x31_0x2e},

  // character: '0'
  {0x30, &bnum_24x31_0x30},

  // character: '1'
  {0x31, &bnum_24x31_0x31},

  // character: '2'
  {0x32, &bnum_24x31_0x32},

  // character: '3'
  {0x33, &bnum_24x31_0x33},

  // character: '4'
  {0x34, &bnum_24x31_0x34},

  // character: '5'
  {0x35, &bnum_24x31_0x35},

  // character: '6'
  {0x36, &bnum_24x31_0x36},

  // character: '7'
  {0x37, &bnum_24x31_0x37},

  // character: '8'
  {0x38, &bnum_24x31_0x38},

  // character: '9'
  {0x39, &bnum_24x31_0x39},

  // character: 'C'
  {0x43, &bnum_24x31_0x43},

  // character: '°'
  {0xb0, &bnum_24x31_0xb0},

  // character: 'º'
  {0x3f, &bnum_24x31_0x3f}

};


const tFont bnum_24x31 = { 14, bnum_24x31_array };

