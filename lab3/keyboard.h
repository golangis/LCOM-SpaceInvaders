#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

#include "i8042.h"

int (kbc_subscribe_int)(uint8_t* bit_no);
int (kbc_unsubscribe_int)();
void (kbc_ih)();

#endif
