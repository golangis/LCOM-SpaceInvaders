#ifndef MOUSE_H
#define MOUSE_H

#include <lcom/lcf.h>  
#include "../utils/utils.h"
#include "i8042.h"


int (mouse_interrupt_handler)();
int (readStatusByte)();
int (readPacket)();
int (subscribe_mouse_int)(uint8_t *bit_no);
int (unsubscribe_mouse_int)();
int (update_mouse)();

#endif
