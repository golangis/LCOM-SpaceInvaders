#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

int(kbc_subscribe_int)(uint8_t* bit_no);
int(kbc_unsubscribe_int)();
void (kbc_ih)();
int(kbd_read_cmd)(uint8_t* byte);
int(kbd_write_cmd)(uint8_t command);

#endif
