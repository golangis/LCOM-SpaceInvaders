#include "keyboard.h"

uint8_t data = 0;
int hook_id;

int (kbc_subscribe_int)(uint8_t* bit_no) {
    hook_id = *bit_no;
    return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (kbc_unsubscribe_int)() {
    return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)() {
    data = 0;
    while (1) {
        uint8_t status = 0;
        if (util_sys_inb(KBC_STATUS_PORT, &status) != 0) return;
        if (status & KBD_OUT_BUF_FULL) {
            if (!(status & (KBD_PAR_ERR | KBD_TIME_ERR))) {
                if (util_sys_inb(KBD_OUT_BUF, &data) != 0) data = 0;
                if (status & (KBD_PAR_ERR | KBD_TIME_ERR)) data = 0;
                break;
            }
        }
    }
}
