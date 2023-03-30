#include <lcom/lcf.h>

void* (vg_init)(uint16_t mode) {
    vbe_mode_info_t info;
    if (vbe_get_mode_info(mode, &info) != 0) return NULL;

    reg86_t r;
    memset(&r, 0, sizeof(r));
    r.ax = 0x4F02;
    r.bx = (1<<14) | mode;
    r.intno = 0x10;
    if (sys_int86(&r) != OK) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }

    return NULL;
}
