#include <lcom/lcf.h>

#include "i8042.h"

extern int counter;

int (util_sys_inb)(int port, uint8_t* value) {
    #ifdef LAB3
    counter++;
    #endif
    uint32_t v32 = 0;
    if (sys_inb(port, &v32) != 0) return 1;
    *value = (uint8_t) v32;
    return 0;
}
