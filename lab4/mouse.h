#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>

#include "i8042.h"

int (mouse_subscribe_int)(uint8_t* bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (mouse_reset_state)();

#endif
