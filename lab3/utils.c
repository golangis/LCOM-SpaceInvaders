#include <lcom/lcf.h>

#include "utils.h"

#ifdef LAB3
extern int cnt;
#endif

int (util_sys_inb)(int port, uint8_t* value) {
    #ifdef LAB3
    cnt++;
    #endif
    uint32_t v32 = 0;
    if (sys_inb(port, &v32) != 0) return 1;
    *value = v32 & 0xFF;
    return 0;
}
