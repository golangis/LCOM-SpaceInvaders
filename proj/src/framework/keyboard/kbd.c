#include <lcom/lcf.h>
#include "kbd.h"
#include <stdbool.h>
#include <stdint.h>

int hook = 0;
uint8_t data = 0;

int (kbc_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook);
}

int (kbc_unsubscribe_int)(){
  return sys_irqrmpolicy(&hook);
}

void (kbc_ih)(){
  uint8_t status = 0;
  while(true){
    if(ut_sys_inb(KBC_STAT_REG, &status) != 0) data = 0; 
    if((status & BIT(0)) != 0){
      if((status & BIT(7)) != 0 || (status & BIT(6)) != 0) data = 0;
      if(ut_sys_inb(KBC_OUT_BUF, &data) != 0) data = 0;
      break;
    }
  }
}

enum kbd_key translate(uint8_t value, bool make){
  enum kbd_key print = INVALID;
  switch(value){
    case SPACE_BREAK:
      print = kbd_space; 
      break;
    case RIGHT_BREAK:
      print = kbd_right;  
      break;
    case LEFT_BREAK:
      print = kbd_left; 
      break;
    case UP_BREAK:
      print = kbd_up; 
      break;
    case DOWN_BREAK:
      print = kbd_down; 
      break;
    case KBD_ESC_KEY:
      print = kbd_esc;
      break;
    default:
      break;
  }
  return print;
}

enum kbd_key kbd_get_key(bool make, uint8_t size, uint8_t bytes[]){
  if (size == 1) return translate(bytes[0], make);  
  else if (size == 2) return translate(bytes[1], make);
  else return INVALID;
}
