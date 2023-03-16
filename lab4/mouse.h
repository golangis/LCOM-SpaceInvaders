#include <lcom/lcf.h>

#include "i8042.h"

int (mouse_subscribe_int)(uint8_t* bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();
