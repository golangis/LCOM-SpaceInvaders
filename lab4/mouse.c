#include "mouse.h"

int mouse_hook_id = 0;
uint8_t data = 0;

int (mouse_subscribe_int)(uint8_t* bit_no) {
    mouse_hook_id = *bit_no;
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

void (mouse_ih)() {
    uint8_t status = 0;
    while (1) {
        if (util_sys_inb(KBC_STAT_REG, &status) != 0) data = 0;
        if (status & KBC_OBF_FULL) {
            if (util_sys_inb(KBC_OUT_BUF, &data) != 0) data = 0;
            if (status & (KBC_PAR_ERR | KBC_TO_ERR)) data = 0;
            break;
        }
    }
}
