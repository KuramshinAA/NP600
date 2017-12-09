
/*******************************************************************************
* image
* filename: C:/lcd-image-converter-20131028/lcd-image-converter/pk_logo_1_1.xml
* name: logo1
*
* preset name: Monochrome
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: yes
* conversion type: Monochrome, Threshold Dither 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: yes
*******************************************************************************/

/*
 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     } tImage;
*/
#include <stdint.h>
#include <lcd.h>


// logo picture
static const uint8_t image_data_logo1[681] = {
    0xba, 0x00, 0xfc, 0x00, 0x60, 0x01, 0xc0, 0x30, 0x40, 0x04, 0x07, 0xe0, 0x3e, 0x81, 0xf4, 0x00, 0x0f, 0xf8, 0x06, 0x00, 0x7c, 0x1f, 0x3c, 0x00, 0xf0, 0xff, 0x83, 0xfe, 0x1f, 0xf8, 0x00, 0xf7, 0x80, 0xf0, 0x0f, 0xe3, 0xf9, 0xe3, 0x0f, 0x1f, 0x7c, 0x3d, 0xf1, 0xff, 0xc0, 0x0f, 0x3c, 0x0f, 0x81, 0xe0, 0x78, 0x1e, 0x38, 0xe3, 0xc3, 0xe3, 0xcf, 0x1e, 0x3e, 0x00, 0xf3, 0xc1, 0xf8, 0x1f, 0x07, 0xc0, 0xe7, 0xde, 0x7c, 0x1e, 0x3c, 0x02, 0xe1, 0xf3, 0xe0, 0x0f, 0x38, 0x3f, 0xc0, 0xf8, 0x3f, 0x0f, 0x7d, 0xc7, 0x81, 0xe3, 0xde, 0x02, 0x1e, 0xda, 0x00, 0xff, 0x83, 0x9e, 0x07, 0xe1, 0xf8, 0xff, 0xfc, 0x78, 0x1e, 0x3b, 0xc1, 0xe3, 0xe0, 0x0f, 0xf0, 0x79, 0xf0, 0x3e, 0x0f, 0x87, 0xef, 0xc7, 0x83, 0xe3, 0xde, 0x1e, 0x3c, 0x00, 0xfc, 0x0f, 0xff, 0x01, 0xe0, 0x78, 0x7c, 0xf8, 0x02, 0x3c, 0xd9, 0x3d, 0xf1, 0xef, 0x80, 0x0f, 0x00, 0xff, 0xf9, 0xfc, 0x7f, 0x03, 0x87, 0x03, 0xe7, 0x83, 0xcf, 0x9f, 0xf0, 0x00, 0xf0, 0x1e, 0x07, 0x9f, 0x83, 0xe0, 0x38, 0x30, 0x1f, 0xf8, 0x3c, 0x79, 0xfe, 0x00, 0x0f, 0x00, 0x60, 0x20, 0xc0, 0x30, 0x02, 0x01, 0xfb, 0x00, 0x7c, 0x03, 0xc6, 0x1e, 0x4d, 0x00, 0xf7, 0x0f, 0x08, 0x3f, 0x87, 0xf0, 0xfc, 0x07, 0xf0, 0xfc, 0x06, 0x00, 0xf7, 0xf1, 0xc3, 0xfc, 0x7f, 0x0f, 0xf8, 0x7f, 0x0f, 0xf8, 0x05, 0x00, 0xf6, 0x0f, 0x3e, 0x3c, 0x87, 0x90, 0xf7, 0xc7, 0x90, 0xf7, 0xc0, 0x05, 0x00, 0xf7, 0xf3, 0xe3, 0xc0, 0x78, 0x0f, 0x3c, 0x78, 0x0f, 0x3c, 0x05, 0x00, 0xf6, 0x0f, 0x7c, 0x3c, 0x07, 0x80, 0xf3, 0xc7, 0x80, 0xe3, 0x80, 0x05, 0x00, 0xf7, 0xff, 0x83, 0xf8, 0x7f, 0x0f, 0x38, 0x7f, 0x0f, 0x78, 0x05, 0x00, 0xf7, 0x0f, 0xf0, 0x3f, 0x87, 0xf0, 0xff, 0x87, 0xf0, 0xff, 0x06, 0x00, 0xf7, 0xf7, 0x83, 0xc0, 0x78, 0x0f, 0xf0, 0x78, 0x0e, 0x78, 0x05, 0x00, 0xf6, 0x0f, 0x7c, 0x3c, 0x07, 0x80, 0xfc, 0x07, 0x80, 0xf3, 0xc0, 0x05, 0x00, 0xf7, 0xf3, 0xe3, 0xfc, 0x7f, 0x8f, 0x00, 0x7f, 0x8f, 0x3e, 0x05, 0x00, 0xf6, 0x0f, 0x1c, 0x3f, 0xc7, 0xf8, 0xf0, 0x07, 0xf8, 0xf1, 0xe0, 0x05, 0x00, 0xf7, 0xf0, 0x83, 0xfc, 0x7f, 0x8f, 0x00, 0x7f, 0x8f, 0x18, 0x2f, 0x00, 0xff, 0x0f, 0x0d, 0x00, 0xfe, 0x01, 0x98, 0x03, 0x00, 0xfe, 0x3c, 0x40, 0x08, 0x00, 0xfe, 0x60, 0x40, 0x02, 0x00, 0xfe, 0x07, 0xd8, 0x08, 0x00, 0xfe, 0x06, 0x02, 0x03, 0x00, 0xff, 0xff, 0x08, 0x00, 0xfd, 0x60, 0xf0, 0x20, 0x02, 0x00, 0xfc, 0x07, 0xd8, 0x00, 0x20, 0x05, 0x00, 0xfd, 0x3f, 0x0e, 0x02, 0x03, 0x00, 0xfc, 0x1f, 0xe0, 0x07, 0xc0, 0x03, 0x00, 0xfb, 0x01, 0x07, 0xf0, 0xa0, 0x41, 0x02, 0x00, 0xfc, 0x01, 0xfe, 0x00, 0x78, 0x02, 0x00, 0x81, 0x3c, 0x80, 0x30, 0xfe, 0x38, 0x08, 0x30, 0x00, 0x03, 0xdf, 0xe0, 0x0c, 0x90, 0x03, 0x04, 0x38, 0x0b, 0x0f, 0xc3, 0x80, 0x03, 0x80, 0x00, 0xfd, 0xfe, 0x04, 0x07, 0x00, 0xe0, 0x01, 0xc0, 0xf0, 0xfc, 0x38, 0x00, 0x1c, 0x00, 0x0f, 0x84, 0xc0, 0x00, 0x60, 0x08, 0x00, 0x08, 0x0e, 0x04, 0xa6, 0xc0, 0x01, 0x60, 0x01, 0xf8, 0xe4, 0x77, 0xd0, 0x07, 0xc0, 0x20, 0x85, 0x40, 0x01, 0x04, 0x03, 0x8a, 0x00, 0x3f, 0x9f, 0x98, 0x1c, 0xe0, 0xf0, 0x00, 0x10, 0x76, 0x00, 0x04, 0x20, 0x79, 0xf8, 0x01, 0xf9, 0xfc, 0x00, 0x61, 0xe0, 0x00, 0x07, 0x0c, 0xc0, 0x00, 0x11, 0x04, 0x0c, 0x80, 0x18, 0x67, 0xe0, 0x06, 0x03, 0xc0, 0x00, 0x30, 0xb8, 0x00, 0xbf, 0xfc, 0x60, 0x6c, 0x00, 0x0c, 0xfe, 0x02, 0x60, 0x13, 0x80, 0x02, 0x11, 0x00, 0x62, 0x00, 0x32, 0x03, 0x40, 0x00, 0x87, 0xe0, 0xe4, 0x3e, 0x01, 0x87, 0x80, 0x03, 0x20, 0x06, 0xc0, 0x00, 0x34, 0x32, 0x00, 0x10, 0x04, 0x01, 0xc0, 0x0a, 0x0f, 0xe7, 0xec, 0x01, 0x88, 0x00, 0x3e, 0x11, 0xb0, 0x04, 0x60, 0x03, 0x00, 0xf5, 0xb0, 0x0f, 0x80, 0x00, 0x37, 0x00, 0x04, 0x0c, 0x01, 0x87, 0xf0, 0x03, 0x00, 0xfd, 0x0c, 0x00, 0x18, 0x02, 0x00, 0xfa, 0xf0, 0x00, 0xe0, 0x00, 0x07, 0xc0, 0x04, 0x00, 0xf9, 0xd0, 0x00, 0x61, 0x80, 0x78, 0x00, 0x1e, 0x02, 0x00, 0xff, 0x80, 0x04, 0x00, 0xf6, 0x03, 0x00, 0x01, 0xb0, 0x07, 0x80, 0x01, 0x80, 0x00, 0x08, 0x05, 0x00, 0xf6, 0x70, 0x00, 0x07, 0x80, 0xe0, 0x00, 0x10, 0x00, 0x01, 0xe0, 0x04, 0x00, 0xf9, 0x03, 0x80, 0x00, 0x3c, 0x0c, 0x00, 0x01, 0x02, 0x00, 0xff, 0x0f, 0x05, 0x00, 0xff, 0x18, 0x02, 0x00, 0xff, 0x80, 0x02, 0x00, 0xff, 0x10, 0x07, 0x00, 0xff, 0x01, 0x02, 0x00, 0xff, 0x10, 0x03, 0x00, 0xff, 0x84, 0x09, 0x00, 0xfe, 0x03, 0x80, 0x02, 0x00, 0xfe, 0x04, 0x80, 0x09, 0x00, 0xfe, 0x0c, 0x00
};
const tImage logo1 = { image_data_logo1, 116, 59};

static const uint8_t image_data_logo2[607] = {
    0x0e, 0x00, 0xff, 0x01, 0x0f, 0x00, 0xff, 0xd4, 0x0e, 0x00, 0xfe, 0x01, 0xb0, 0x0e, 0x00, 0xfe, 0x6c, 0x40, 0x0e, 0x00, 0xfe, 0xfe, 0xf8, 0x0d, 0x00, 0xfd, 0x03, 0xff, 0xf0, 0x0d, 0x00, 0xfe, 0x07, 0x3f, 0x0e, 0x00, 0xfe, 0x8f, 0x70, 0x0d, 0x00, 0xfd, 0x03, 0xdf, 0xf0, 0x0d, 0x00, 0xfd, 0x07, 0xbf, 0x80, 0x0d, 0x00, 0xfe, 0x0f, 0x1f, 0x0d, 0x00, 0xfb, 0x04, 0x0c, 0x1c, 0x00, 0xc0, 0x0b, 0x00, 0xfb, 0x0c, 0x63, 0xd0, 0x07, 0xc0, 0x0b, 0x00, 0xfb, 0x19, 0xe6, 0xa2, 0x3f, 0x80, 0x0b, 0x00, 0xfc, 0x3b, 0xcf, 0xc1, 0xfe, 0x0c, 0x00, 0xfc, 0x31, 0x1e, 0x87, 0x3c, 0x0b, 0x00, 0xfb, 0x03, 0x80, 0x11, 0x0f, 0xe0, 0x0b, 0x00, 0xfb, 0x1f, 0x39, 0xf3, 0x0f, 0xc0, 0x0b, 0x00, 0xfc, 0x2c, 0xff, 0x3e, 0x07, 0x0c, 0x00, 0xfc, 0x03, 0x9e, 0x5e, 0x8e, 0x0c, 0x00, 0xfc, 0x04, 0x3c, 0x9f, 0x9e, 0x0d, 0x00, 0xfd, 0x78, 0x0e, 0x6c, 0x0e, 0x00, 0xf2, 0x0e, 0xf8, 0x7c, 0x00, 0x40, 0x03, 0x00, 0xc6, 0x00, 0x60, 0x7c, 0x07, 0xe0, 0x7c, 0x02, 0x00, 0x81, 0x0c, 0xf0, 0xff, 0x00, 0xc0, 0x1f, 0x0f, 0x9c, 0x00, 0xe1, 0xff, 0x0f, 0xf0, 0xff, 0x80, 0x01, 0x39, 0x19, 0xef, 0x03, 0xc0, 0xfe, 0x3f, 0x3c, 0x61, 0xcf, 0xbe, 0x1e, 0xf1, 0xff, 0x80, 0x0a, 0x7d, 0xbb, 0xde, 0x0f, 0x81, 0xe0, 0xf8, 0x38, 0xe7, 0x9e, 0x1e, 0x79, 0xe3, 0xc7, 0x80, 0x00, 0x77, 0x9f, 0xbc, 0x3f, 0x83, 0xe1, 0xf0, 0x73, 0xee, 0x38, 0x3c, 0x73, 0x87, 0x0f, 0x00, 0x08, 0x3e, 0x0f, 0x78, 0x77, 0x83, 0xf1, 0xf8, 0x7f, 0xfc, 0xf0, 0x78, 0xef, 0x0f, 0x1e, 0x00, 0x12, 0x68, 0x1f, 0xe1, 0xef, 0x83, 0xf0, 0xf8, 0xff, 0xf1, 0xe0, 0xf3, 0xfe, 0x1e, 0x78, 0x00, 0x30, 0xc0, 0x3f, 0x03, 0xff, 0x01, 0xc0, 0xf1, 0xf3, 0xe3, 0xc1, 0xc3, 0x9e, 0x3c, 0xf0, 0x01, 0xf3, 0xd0, 0x78, 0x0f, 0xff, 0x1f, 0x0f, 0xc1, 0xe3, 0x83, 0xc7, 0x87, 0xbc, 0x7f, 0xc0, 0x1f, 0xed, 0xe6, 0xe0, 0xf0, 0x1c, 0x1e, 0x7e, 0x1f, 0x03, 0x87, 0x07, 0xfe, 0x0e, 0x3c, 0xff, 0x00, 0x6f, 0x99, 0x11, 0xe0, 0x02, 0x18, 0xf3, 0x70, 0x30, 0x02, 0x00, 0x03, 0xf0, 0x1c, 0x31, 0xe0, 0x03, 0xb7, 0x92, 0x20, 0x0c, 0x00, 0xfc, 0x0f, 0xee, 0xa6, 0x80, 0x0c, 0x00, 0xfd, 0x3f, 0xbf, 0x4f, 0x0d, 0x00, 0xfd, 0xff, 0xfc, 0x8c, 0x0c, 0x00, 0xd0, 0x01, 0xff, 0xfb, 0x98, 0x00, 0x7c, 0x00, 0x7f, 0xe1, 0xff, 0x0f, 0xc0, 0x0f, 0xf8, 0x7f, 0x40, 0x03, 0xff, 0xe3, 0x30, 0x00, 0xf8, 0x70, 0x7f, 0xc3, 0xfe, 0x1f, 0xf8, 0x1f, 0xf0, 0xff, 0xe0, 0x01, 0xe3, 0x0e, 0x60, 0x01, 0xf1, 0xf0, 0xff, 0x87, 0xfc, 0x1f, 0xfc, 0x3f, 0xe1, 0xff, 0xe0, 0x02, 0x00, 0xe8, 0x08, 0xc0, 0x03, 0xe3, 0xe1, 0xf0, 0x0f, 0x80, 0x7e, 0xf8, 0x7c, 0x01, 0xe7, 0xe0, 0x00, 0x07, 0xb1, 0x80, 0x07, 0xcf, 0x83, 0xc0, 0x1f, 0x00, 0x03, 0xf8, 0xee, 0x03, 0xc7, 0xc0, 0x00, 0x3f, 0xe2, 0x00, 0x0f, 0xbf, 0x07, 0x80, 0x3c, 0x00, 0xf9, 0xe1, 0xe0, 0x0f, 0x8f, 0x02, 0x00, 0x95, 0xc9, 0xc4, 0x00, 0x1f, 0xfc, 0x0f, 0xf0, 0x7f, 0xc3, 0xe7, 0xc3, 0xfc, 0x1f, 0x3c, 0x00, 0x01, 0x87, 0xc8, 0x00, 0x3f, 0xf0, 0x3f, 0xf0, 0xff, 0x87, 0xcf, 0x07, 0xfc, 0x1e, 0xf8, 0x00, 0x02, 0x03, 0x90, 0x00, 0x7f, 0xe0, 0x3f, 0xc1, 0xff, 0x07, 0xfe, 0x0f, 0xf8, 0x7d, 0xe0, 0x00, 0x0c, 0x03, 0x60, 0x00, 0xfb, 0xe0, 0x7c, 0x03, 0xe0, 0x1f, 0xf8, 0x1f, 0x00, 0x7b, 0xe0, 0x00, 0x08, 0x05, 0x80, 0x01, 0xf3, 0xe0, 0xf0, 0x07, 0x80, 0x3f, 0x80, 0x3e, 0x01, 0xf3, 0xe0, 0x00, 0x18, 0x0b, 0x00, 0x03, 0xe7, 0xe1, 0xff, 0x0f, 0xf8, 0x7e, 0x00, 0x7f, 0xc1, 0xe3, 0xf0, 0x00, 0x1c, 0x16, 0x00, 0x07, 0xc7, 0xc3, 0xfe, 0x1f, 0xf0, 0x78, 0x00, 0xff, 0x02, 0xc7, 0xff, 0xc0, 0x02, 0x00, 0xf2, 0x28, 0x00, 0x0f, 0x8f, 0x07, 0xfc, 0x3f, 0xf1, 0xf8, 0x01, 0xff, 0x8f, 0x87, 0x80, 0x02, 0x00, 0xf3, 0x30, 0x00, 0x1f, 0x04, 0x0f, 0xf8, 0x7f, 0xc3, 0xe0, 0x03, 0xfe, 0x0f, 0x0e, 0x03, 0x00, 0xff, 0x40, 0x0e, 0x00, 0xfe, 0x01, 0x80, 0x0e, 0x00, 0xff, 0x02, 0x0f, 0x00, 0xff, 0x08, 0x0f, 0x00, 0xfe, 0x20, 0x00
};
const tImage logo2 = { image_data_logo2, 127, 57};

static const uint8_t image_data_logo3[496] = {
    0xfd, 0x00, 0x08, 0x40, 0x0e, 0x00, 0xff, 0xfb, 0x0e, 0x00, 0xfe, 0x07, 0xcc, 0x0d, 0x00, 0xfd, 0x01, 0xc4, 0xb8, 0x0d, 0x00, 0xfd, 0x07, 0xe1, 0xd8, 0x0d, 0x00, 0xfd, 0x1d, 0xe7, 0x20, 0x0d, 0x00, 0xc5, 0x31, 0xdf, 0x83, 0xf0, 0x01, 0x80, 0x07, 0x00, 0xc3, 0x00, 0x10, 0x0f, 0x80, 0xfc, 0x07, 0xf0, 0x72, 0xc3, 0x87, 0xfc, 0x03, 0x00, 0x3e, 0x0f, 0x9e, 0x00, 0x78, 0x7f, 0xc1, 0xff, 0x0f, 0xfc, 0xf1, 0x87, 0x0f, 0x7c, 0x0f, 0x00, 0xfe, 0x3f, 0x9c, 0x10, 0xf3, 0xf7, 0xc3, 0xdf, 0x1f, 0xfc, 0x04, 0x00, 0x1e, 0x78, 0x1f, 0x03, 0xc0, 0xf0, 0x3c, 0x71, 0xc7, 0x02, 0x87, 0xef, 0x9e, 0x3c, 0x7c, 0x1c, 0xf0, 0x3c, 0xf0, 0x7e, 0x07, 0xc1, 0xf0, 0x39, 0xf7, 0x8f, 0x0f, 0x8f, 0x38, 0x02, 0x78, 0xf3, 0x1f, 0xf0, 0x79, 0xc1, 0xee, 0x07, 0xe1, 0xf8, 0x77, 0xef, 0x3c, 0x0f, 0x1c, 0x03, 0xf0, 0xe7, 0x1e, 0x70, 0xff, 0x83, 0x9e, 0x07, 0xe1, 0xf8, 0xff, 0xfc, 0x78, 0x1e, 0x3f, 0xc1, 0xe1, 0xe0, 0x38, 0xc1, 0xfe, 0x0f, 0x7e, 0x07, 0xc1, 0xf0, 0xff, 0x02, 0xf0, 0xf1, 0x3c, 0x7b, 0xc3, 0xc7, 0x80, 0x73, 0x83, 0xf0, 0x3f, 0xfc, 0x07, 0x81, 0xe1, 0xf3, 0xe1, 0x02, 0xf0, 0xd4, 0xe7, 0xc7, 0xbe, 0x03, 0xc0, 0x07, 0x80, 0x7f, 0xfc, 0xfe, 0x3f, 0x81, 0xc3, 0xc1, 0xf7, 0xe1, 0xe7, 0xcf, 0xf8, 0x0c, 0x80, 0x0f, 0x01, 0xe0, 0x79, 0xf8, 0x3e, 0x03, 0x83, 0x01, 0xff, 0x03, 0xc7, 0x9f, 0xe0, 0x08, 0xe0, 0x1e, 0x00, 0xc0, 0x61, 0x80, 0x60, 0x02, 0x02, 0x00, 0xf9, 0xf8, 0x07, 0x8c, 0x3c, 0x00, 0x3f, 0x80, 0x0e, 0x00, 0xff, 0xfe, 0x0e, 0x00, 0xfe, 0x01, 0x9c, 0x0e, 0x00, 0xfe, 0x07, 0x3c, 0x0e, 0x00, 0xfe, 0x0e, 0x38, 0x0e, 0x00, 0xfe, 0x0e, 0x10, 0x04, 0x00, 0xf7, 0x3c, 0x20, 0xfe, 0x1f, 0xc3, 0xf0, 0x1f, 0xc3, 0xe8, 0x02, 0x00, 0xff, 0xc0, 0x03, 0x00, 0xf3, 0x20, 0x78, 0xe1, 0xfc, 0x3f, 0x87, 0xfc, 0x3f, 0xc7, 0xfc, 0x00, 0x03, 0x80, 0x03, 0x00, 0xf3, 0x80, 0xf3, 0xe3, 0xc8, 0x79, 0x0f, 0x7c, 0x78, 0x0f, 0x7c, 0x00, 0x01, 0xe0, 0x02, 0x00, 0xc4, 0x1b, 0x01, 0xe7, 0x87, 0x80, 0xf0, 0x1e, 0x78, 0xf0, 0x1e, 0x78, 0x00, 0x03, 0xc0, 0x00, 0x73, 0x9c, 0x03, 0xdf, 0x0f, 0x01, 0xe0, 0x3c, 0xf1, 0xe0, 0x3c, 0xe0, 0x00, 0x04, 0x00, 0x01, 0xf7, 0xb8, 0x07, 0xfc, 0x1f, 0xc3, 0xf8, 0x79, 0xc3, 0xf8, 0x73, 0xc0, 0x00, 0x04, 0x60, 0x03, 0x65, 0xc8, 0x0f, 0xf0, 0x3f, 0x87, 0xf0, 0xf7, 0x87, 0xf0, 0xff, 0x00, 0x01, 0x02, 0xc0, 0xec, 0x00, 0xe3, 0xe0, 0x1e, 0xf0, 0x79, 0x0f, 0x01, 0xfe, 0x0f, 0x01, 0xef, 0x00, 0x03, 0x40, 0x08, 0x21, 0xc7, 0xc0, 0x3d, 0x02, 0xf0, 0xea, 0x1e, 0x03, 0xf0, 0x1e, 0x03, 0xdf, 0x00, 0x01, 0x87, 0xff, 0x8f, 0x18, 0x80, 0x79, 0xf1, 0xfc, 0x3f, 0x87, 0x80, 0x3f, 0xc7, 0x1f, 0x02, 0x00, 0xf2, 0x02, 0x9f, 0xbc, 0x07, 0x00, 0xf1, 0xc3, 0xfc, 0x7f, 0x8f, 0x00, 0x7f, 0x8f, 0x1e, 0x02, 0x00, 0xec, 0xe3, 0x3d, 0xff, 0xc4, 0x01, 0xe1, 0x07, 0xf8, 0xff, 0x1e, 0x00, 0xff, 0x1e, 0x30, 0x00, 0x01, 0x60, 0x18, 0x3d, 0xe0, 0x0c, 0x00, 0xfc, 0xc2, 0x3e, 0x19, 0xe0, 0x0c, 0x00, 0xfc, 0x06, 0xec, 0x01, 0xc0, 0x0c, 0x00, 0xfc, 0x0f, 0x80, 0x01, 0xc0, 0x0c, 0x00, 0xfd, 0x0f, 0x00, 0x33, 0x0f, 0x00, 0xff, 0x7e, 0x0f, 0x00, 0xff, 0x78, 0x0f, 0x00, 0xff, 0x40, 0x0b, 0x00
};
const tImage logo3 = { image_data_logo3, 127, 43};


// question icon
//
static const uint8_t image_data_a1[26] = {
    0x03, 0x00, 0xeb, 0x38, 0x03, 0xf0, 0x7f, 0x80, 0xfc, 0x03, 0xc0, 0x3c, 0x07, 0x80, 0xf8, 0x0e, 0x00, 0x80, 0x00, 0x01, 0xc0, 0x1c, 0x01, 0xc0, 0x06, 0x00
};
const tImage a1 = { image_data_a1, 12, 20};

static const uint8_t image_data_a2[28] = {
    0xe7, 0x00, 0x01, 0x00, 0x3c, 0x03, 0xf0, 0x3f, 0xc0, 0x7c, 0x03, 0xe0, 0x3e, 0x07, 0xe1, 0xfc, 0x1f, 0x81, 0xe0, 0x00, 0x07, 0x00, 0x78, 0x07, 0x80, 0x38, 0x05, 0x00
};
const tImage a2 = { image_data_a2, 12, 20};

static const uint8_t image_data_a3[31] = {
    0xe2, 0x00, 0x02, 0x00, 0x78, 0x07, 0xe0, 0x7f, 0x83, 0xfc, 0x0f, 0xc0, 0x7e, 0x07, 0xe0, 0xfc, 0x3f, 0xc7, 0xf8, 0x7f, 0x07, 0x80, 0x00, 0x04, 0x00, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0x00
};
const tImage a3 = { image_data_a3, 12, 20};

static const uint8_t image_data_a4[28] = {
    0x03, 0x00, 0xf1, 0xfc, 0x0f, 0xf0, 0xff, 0x8f, 0xfc, 0x07, 0xc0, 0x7c, 0x07, 0x80, 0xf8, 0x1f, 0x01, 0xc0, 0x02, 0x00, 0xfb, 0x40, 0x1c, 0x01, 0xe0, 0x1c, 0x05, 0x00
};
const tImage a4 = { image_data_a4, 12, 20};

static const uint8_t image_data_a5[30] = {
    0xee, 0x7e, 0x07, 0xf8, 0x7f, 0xe7, 0xfe, 0x07, 0xf0, 0x3f, 0x03, 0xf0, 0x3e, 0x07, 0xc0, 0xfc, 0x0f, 0x80, 0xe0, 0x03, 0x00, 0xfa, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0x70, 0x03, 0x00
};
const tImage a5 = { image_data_a5, 12, 20};

static const uint8_t image_data_a6[25] = {
    0xf1, 0x00, 0x03, 0xfc, 0x3f, 0xc3, 0xfe, 0x01, 0xe0, 0x1e, 0x01, 0xc0, 0x7c, 0x07, 0x80, 0x20, 0x02, 0x00, 0xfc, 0x78, 0x07, 0x80, 0x38, 0x09, 0x00
};
const tImage a6 = { image_data_a6, 12, 20};

const tImage *imgQuestion[6] = {&a1,&a2,&a3,&a4,&a5,&a6};

// points images
//

static const uint8_t image_data_p1[11] = {
    0x09, 0x00, 0xfa, 0x0e, 0x00, 0xf0, 0x0f, 0x00, 0x60, 0x0f, 0x00
};
const tImage p1 = { image_data_p1, 12, 20};

static const uint8_t image_data_b2[10] = {
    0x0b, 0x00, 0xfb, 0x78, 0x07, 0x80, 0x78, 0x07, 0x0e, 0x00
};
const tImage p2 = { image_data_b2, 12, 20};

static const uint8_t image_data_p3[10] = {
    0x0b, 0x00, 0xfb, 0xe0, 0x1e, 0x01, 0xe0, 0x0c, 0x0e, 0x00
};
const tImage p3 = { image_data_p3, 12, 20};

const tImage *imgPoint[3] = {&p1,&p2,&p3};


// passcode image
//
static const uint8_t image_data_passcode[189] = {
    0xbd, 0xff, 0x80, 0x18, 0x00, 0x70, 0x0e, 0x00, 0x38, 0x0f, 0xe0, 0x7f, 0xc0, 0x7f, 0x80, 0x7f, 0xf0, 0x1c, 0x01, 0xf8, 0x3f, 0x00, 0x7c, 0x1f, 0xfc, 0x3f, 0xf8, 0x3f, 0xc0, 0x3f, 0xfc, 0x0f, 0x01, 0xfe, 0x3f, 0xc0, 0xfe, 0x1f, 0xff, 0x1f, 0xfe, 0x1f, 0xe0, 0x1f, 0x3e, 0x0f, 0xc1, 0xf8, 0x3f, 0x00, 0xff, 0x1f, 0x0f, 0x8f, 0x9f, 0x8f, 0x00, 0xff, 0x9f, 0x0f, 0xf0, 0xf8, 0x1f, 0x00, 0xfc, 0x1f, 0x03, 0xe7, 0x02, 0xc7, 0xf4, 0x80, 0x7f, 0xcf, 0x87, 0xf8, 0x7f, 0x8f, 0xf0, 0xfc, 0x0f, 0x81, 0xf3, 0x02, 0xe3, 0xf4, 0xfc, 0x3f, 0xef, 0x87, 0xbe, 0x1f, 0xe3, 0xfc, 0x7c, 0x07, 0xc0, 0xf9, 0x02, 0xf1, 0xf4, 0xfe, 0x01, 0xff, 0x87, 0xcf, 0x83, 0xf8, 0x7f, 0x3e, 0x03, 0xe0, 0x7c, 0x02, 0xf8, 0xb7, 0xff, 0x00, 0xff, 0x83, 0xff, 0xc0, 0x7c, 0x0f, 0x9f, 0x01, 0xf0, 0x3e, 0x7c, 0xf8, 0x78, 0x00, 0x7e, 0x03, 0xff, 0xf0, 0x7e, 0x0f, 0xcf, 0xfc, 0x7c, 0x3e, 0x3f, 0xf8, 0x3e, 0x00, 0x3e, 0x01, 0xff, 0xfd, 0xfe, 0x3f, 0xc3, 0xff, 0x3f, 0xfe, 0x1f, 0xf8, 0x1f, 0xf1, 0xff, 0x01, 0xf0, 0x3e, 0xfc, 0x1f, 0x80, 0xff, 0x8f, 0xfe, 0x0f, 0xf0, 0x0f, 0xf8, 0xff, 0x80, 0x30, 0x0c, 0x78, 0x0f, 0x00, 0x1f, 0xc1, 0xfc, 0x07, 0xc0, 0x07, 0xfc, 0x78
};
const tImage passcode = { image_data_passcode, 113, 13};


// skeleton
static const uint8_t image_skeleton[111] = {
    0xcb, 0x00, 0xfe, 0x00, 0x03, 0xff, 0x80, 0x07, 0xff, 0xc0, 0x0f, 0xff, 0xe0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0x1f, 0xff, 0xf0, 0x1e, 0x38, 0xf0, 0x1e, 0x38, 0xe0, 0x0e, 0x38, 0xe0, 0x0f, 0x7d, 0xc0, 0x07, 0xff, 0xc0, 0x07, 0xef, 0xc0, 0x07, 0xef, 0x80, 0x00, 0xfe, 0x00, 0x01, 0xff, 0x00, 0x01, 0xc6, 0x02, 0x00, 0xff, 0xfe, 0x02, 0x00, 0xf2, 0x7c, 0x00, 0x70, 0x38, 0x0e, 0x78, 0x00, 0x3e, 0x7c, 0x00, 0x7e, 0xff, 0x81, 0xff, 0x02, 0xef, 0xfd, 0xcf, 0x01, 0xff, 0x02, 0x00, 0xf3, 0x7c, 0x00, 0x01, 0xff, 0x00, 0x03, 0xef, 0x80, 0x0f, 0x83, 0xe0, 0x7f, 0x01, 0x02, 0xfe, 0xf5, 0x00, 0xff, 0xfc, 0x00, 0x7f, 0xfc, 0x00, 0x7c, 0x1c, 0x00, 0x38
};
const tImage imgSkeleton = {image_skeleton, 24, 35};


// INVALID PASSCODE
static const uint8_t image_data_imgInvalid[334] = {
    0xf2, 0x03, 0x84, 0x0e, 0x00, 0x40, 0x60, 0x1c, 0x0e, 0x1f, 0x80, 0x00, 0x38, 0x60, 0xe7, 0x02, 0x06, 0xf8, 0x01, 0xc0, 0xe1, 0xff, 0x00, 0x03, 0x87, 0x0e, 0x03, 0xf0, 0xb9, 0x1c, 0x0e, 0x1e, 0xf0, 0x00, 0x38, 0x78, 0xe7, 0x8e, 0x0f, 0x81, 0xc0, 0xe1, 0xc7, 0x80, 0x03, 0x87, 0xee, 0x39, 0xe1, 0xf8, 0x1c, 0x0e, 0x1c, 0x38, 0x00, 0x38, 0xff, 0xe3, 0xdc, 0x39, 0xc1, 0xc0, 0xe1, 0xc7, 0x80, 0x03, 0x8e, 0xfe, 0x1f, 0x83, 0x9e, 0x1c, 0x0e, 0x1c, 0x70, 0x00, 0x38, 0xe3, 0xe1, 0xf8, 0x7f, 0xe1, 0xc0, 0xe1, 0xcf, 0x00, 0x03, 0x8e, 0x1e, 0x0f, 0x07, 0xff, 0x1f, 0xce, 0x1f, 0xe0, 0x00, 0x38, 0xe0, 0x60, 0x02, 0xf0, 0xf2, 0x71, 0xfc, 0xe1, 0xf8, 0x00, 0x03, 0x8e, 0x02, 0x06, 0x02, 0x06, 0x1f, 0xce, 0x1e, 0x36, 0x00, 0xfd, 0xfc, 0x03, 0x00, 0x02, 0x30, 0xf8, 0x0c, 0x0f, 0xc0, 0xfc, 0x07, 0xef, 0xe0, 0x30, 0x02, 0x0f, 0xed, 0x03, 0xc3, 0xff, 0x0f, 0xf8, 0x7e, 0xef, 0x07, 0x81, 0xe1, 0xe0, 0xfc, 0x78, 0xf0, 0xf7, 0x87, 0x0e, 0x70, 0x7c, 0x02, 0x3c, 0xff, 0x1f, 0x02, 0x07, 0xd1, 0x8e, 0x3c, 0x70, 0xe7, 0x0f, 0xc3, 0xf3, 0xf1, 0xc0, 0xf0, 0x78, 0xe1, 0xc7, 0x0e, 0xe1, 0xce, 0x1f, 0x9f, 0xbc, 0x0f, 0x07, 0x8e, 0x3c, 0x7e, 0xfe, 0x1c, 0xf0, 0x7c, 0x7f, 0xc0, 0xf0, 0x78, 0xe3, 0x87, 0xef, 0x83, 0xff, 0x03, 0xc3, 0xfc, 0x0f, 0x07, 0x0e, 0x78, 0x70, 0xe0, 0x3f, 0x02, 0xf8, 0xe4, 0xf9, 0xfc, 0x78, 0xf0, 0xff, 0x07, 0x8e, 0x07, 0x83, 0x9f, 0x1f, 0x0f, 0xc3, 0xfe, 0x0f, 0xc0, 0x7f, 0xe0, 0x10, 0x31, 0xc1, 0xc0, 0x3c, 0x1f, 0x80, 0xf0, 0x07, 0xf0, 0x74, 0x00, 0xf8, 0x87, 0xff, 0xef, 0x80, 0x21, 0xe3, 0xf9, 0x80, 0x02, 0x00, 0xf8, 0x08, 0x7f, 0xfe, 0xe0, 0xc2, 0x1f, 0xbf, 0xb8, 0x02, 0x00, 0xf7, 0x01, 0xc0, 0xc1, 0x8c, 0x0e, 0x71, 0x98, 0x67, 0x0c, 0x02, 0x00, 0xf8, 0x3e, 0x0c, 0x18, 0xf0, 0xef, 0x1b, 0x86, 0x7c, 0x02, 0x00, 0xf7, 0x03, 0x60, 0xc1, 0x8e, 0x1f, 0xf1, 0xf0, 0x61, 0xe0, 0x02, 0x00, 0xf8, 0x77, 0x0c, 0x18, 0xc1, 0xbb, 0x9e, 0x06, 0x0e, 0x02, 0x00, 0xf7, 0x07, 0xf8, 0xc1, 0x8f, 0xb9, 0x99, 0x80, 0x63, 0xc0, 0x02, 0x00, 0xf6, 0xe1, 0x8c, 0x18, 0xfb, 0x11, 0x98, 0x06, 0x30, 0xc0, 0x00
};
const tImage imgInvalid = { image_data_imgInvalid, 84, 46};

