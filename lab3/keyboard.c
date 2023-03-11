#include <lcom/lcf.h>

#include "keyboard.h"
#include "i8042.h"

int hook_id = 0;
uint8_t data = 0;

int (kbc_subscribe_int)(uint8_t* bit_no) {
    hook_id = *bit_no;
    return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (kbc_unsubscribe_int)() {
    return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)() {
    uint8_t status = 0;
    while (1) {
        if (util_sys_inb(KBC_STAT_REG, &status) != 0) data = 0;
        if (status & BIT(0)) {
            if (util_sys_inb(KBC_OUT_BUF, &data) != 0) data = 0;
            if (status & BIT(7) || status & BIT(6)) data = 0;
            break;
        }
    }
}
