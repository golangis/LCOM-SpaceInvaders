#include <lcom/lcf.h>

#include <stdint.h>

int (util_sys_inb)(int port, uint8_t* value) {
    uint32_t v32 = 0;
    if (sys_inb(port, &v32) != 0) return 1;
    *value = v32 & 0xFF;
    return 0;
}
