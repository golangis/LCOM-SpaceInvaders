#include <lcom/lcf.h>

#include "utils.h"

#ifdef LAB3
extern int cnt;
#endif

int (util_sys_inb)(uint8_t port, uint8_t* value) {
    #ifdef LAB3
    cnt++;
    #endif
    uint32_t v32 = 0;
    if (sys_inb(port, &v32) != 0) return 1;
    *value = (uint8_t)v32;
    return 0;
}
