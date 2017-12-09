
/*******************************************************************************
* image
* filename: C:/Projects/Bioznaika/Briz/Source/ver11/images/stop_image.xml
* name: stop_image
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
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
     } tImage;
*/
#include <stdint.h>



static const uint8_t image_data_stop_image[35] = {
    0xf6, 0xf8, 0x1f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x80, 0x01, 0x02, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x02, 0x00, 0xf6, 0x80, 0x01, 0x80, 0x01, 0xc0, 0x03, 0xe0, 0x07, 0xf8, 0x1f
};
const tImage stop_image = { image_data_stop_image, 16, 16};

