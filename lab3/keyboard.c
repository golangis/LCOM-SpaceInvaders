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

}
