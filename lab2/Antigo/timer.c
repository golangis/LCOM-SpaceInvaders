#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  uint8_t st = 0;
  uint32_t control_word = 0;
  uint16_t div = 0;
  uint8_t divLSB = 0;
  uint8_t divMSB = 0;

  if (freq < 19) return 1;
  switch (timer){
    case 0:
      if (timer_get_conf(0, &st) != 0) return 1;
      st &= (BIT(0) | BIT(1) | BIT(2) | BIT(3));
      control_word = TIMER_SEL0 | TIMER_LSB_MSB | st;
      div = TIMER_FREQ / freq;
      if (util_get_LSB(div, &divLSB) != 0) return 1;
      if (util_get_MSB(div, &divMSB) != 0) return 1;
      if(sys_outb(TIMER_CTRL, control_word) != 0) return 1;
      if(sys_outb(TIMER_0, divLSB) != 0) return 1;
      if(sys_outb(TIMER_0, divMSB) != 0) return 1;
    case 1:
      if (timer_get_conf(1, &st) != 0) return 1;
      st &= (BIT(0) | BIT(1) | BIT(2) | BIT(3));
      control_word = TIMER_SEL1 | TIMER_LSB_MSB | st;
      div = TIMER_FREQ / freq;
      divLSB = 0;
      divMSB = 0;
      if (util_get_LSB(div, &divLSB) != 0) return 1;
      if (util_get_MSB(div, &divMSB) != 0) return 1;
      if(sys_outb(TIMER_CTRL, control_word) != 0) return 1;
      if(sys_outb(TIMER_1, divLSB) != 0) return 1;
      if(sys_outb(TIMER_1, divMSB) != 0) return 1;
    case 2:
      if (timer_get_conf(2, &st) != 0) return 1;
      st &= (BIT(0) | BIT(1) | BIT(2) | BIT(3));
      control_word = TIMER_SEL2 | TIMER_LSB_MSB | st;
      div = TIMER_FREQ / freq;
      divLSB = 0;
      divMSB = 0;
      if (util_get_LSB(div, &divLSB) != 0) return 1;
      if (util_get_MSB(div, &divMSB) != 0) return 1;
      if(sys_outb(TIMER_CTRL, control_word) != 0) return 1;
      if(sys_outb(TIMER_2, divLSB) != 0) return 1;
      if(sys_outb(TIMER_2, divMSB) != 0) return 1;  
    default:
      return 1;  
  }
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook);
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook) != 0) return 1;
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t RB;
  switch(timer){
    case 0:
      RB = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(0);
      if(sys_outb(TIMER_CTRL, RB) != 0) return 1;
      if(util_sys_inb(TIMER_0, st) != 0) return 1;
      return 0;
    case 1:
      RB = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(1);
      if(sys_outb(TIMER_CTRL, RB) != 0) return 1;
      if(util_sys_inb(TIMER_1, st) != 0) return 1;
      return 0;
    case 2:
      RB = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(2);
      if(sys_outb(TIMER_CTRL, RB) != 0) return 1;
      if(util_sys_inb(TIMER_2, st) != 0) return 1;
      return 0; 
    default:
      return 1;    
  }
  return 1;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  bool bcd = (st % 2);

  uint8_t operating_mode = st;
  uint8_t mask = BIT(3) | BIT(2) | BIT(1);
  operating_mode &= mask;
  operating_mode >>= 1;
  
  if (operating_mode == 7) operating_mode = 3;
  else if (operating_mode == 6) operating_mode = 2;

  uint8_t initialization = st;
  mask = BIT(4) | BIT(5);
  initialization &= mask;
  initialization >>= 4;

  enum timer_init initialization_mode;

  if (initialization == 1) initialization_mode = LSB_only;
  else if (initialization == 2) initialization_mode = MSB_only;
  else if (initialization == 3) initialization_mode = MSB_after_LSB;
  else initialization_mode = INVAL_val;

  if (field == tsf_all){
    val.bcd = bcd;
    val.count_mode = operating_mode;
    val.in_mode = initialization_mode;
    val.byte = st;
  }
  else if (field == tsf_initial) val.in_mode = initialization_mode;
  else if (field == tsf_mode) val.count_mode = operating_mode;
  else if (field == tsf_base) val.bcd = bcd;

  return timer_print_config(timer, field, val);
}
