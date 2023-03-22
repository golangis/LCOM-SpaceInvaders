#include <lcom/lcf.h>

#include <stdint.h>

#include "keyboard.h"
#include "i8042.h"

int hook = 0;
uint8_t data = 0;

int (kbc_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook);
}

int(kbc_unsubscribe_int)(){
    return sys_irqrmpolicy(&hook);
}

void (kbc_ih)(){
    uint8_t status = 0;
    while(true){
        if(util_sys_inb(KBC_STAT_REG, &status) != 0) data = 0; 
        if((status & BIT(0)) != 0){
            if((status & BIT(7)) != 0 || (status & BIT(6)) != 0) data = 0;
            if(util_sys_inb(KBC_OUT_BUF, &data) != 0) data = 0;
            break;
        }
    }
}

int(kbd_read_cmd)(uint8_t* byte){
    uint8_t status = 0;
    int i = 0;

    if(sys_outb(KBC_CMD_REG, KBC_READ_CMD) != 0) return 1;
    while(i < 10){; 
        if(util_sys_inb(KBC_STAT_REG, &status) != 0) return 1;

        if((status & BIT(0)) != 0){
            if((status & BIT(7)) != 0 || (status & BIT(6)) != 0) return 1;
            if(util_sys_inb(KBC_OUT_BUF, byte) != 0) return 1;
            return 0;
        }
        tickdelay(micros_to_ticks(DELAY));
        i++;
    }
    return 1;
}

int(kbd_write_cmd)(uint8_t command){
    uint8_t status = 0;
    int i = 0;

    while(i < 10){
        if(util_sys_inb(KBC_STAT_REG, &status) != 0) return 1;
        if((status & BIT(1)) == 0){
            if(sys_outb(KBC_CMD_REG, KBC_WRITE_CMD) != 0) return 1;
            if(sys_outb(KBC_IN_BUF, command) != 0) return 1;
            return 0;
        }
        tickdelay(micros_to_ticks(DELAY));
        i++;
    }
    return 1;
}
