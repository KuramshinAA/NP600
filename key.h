#ifndef _KEY_H_
#define _KEY_H_

#define BUTTON_NONE		  0
#define BUTTON_LEFT     1
#define BUTTON_RIGHT    2
#define BUTTON_UP       4
#define BUTTON_DOWN     8
#define BUTTON_OK       16
#define BUTTON_CANCEL   32
#define BUTTON_START    64
#define BUTTON_STOP     128

void keys_init();
uint8_t get_key();
uint8_t wait_key();
void wait_key_unpressed();

#endif /* _KEY_H_ */
