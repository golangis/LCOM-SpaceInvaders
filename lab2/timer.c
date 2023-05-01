#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t status;
  uint16_t division = 0;
  uint8_t LSB;
  uint8_t MSB;

  if(freq <= 20) return 1;
  switch(timer){
    case 0:
      if(timer_get_conf(0, &status) != 0) return 1;
      status = status & (BIT(0) | BIT(1) | BIT(2) | BIT(3));
      status = status | TIMER_LSB_MSB | TIMER_SEL0;
       
      division = TIMER_FREQ / freq;

      if(util_get_LSB(division, &LSB)!= 0) return 1;
      if(util_get_MSB(division, &MSB) != 0) return 1;

      if(sys_outb(TIMER_CTRL, status) != 0) return 1;
      if(sys_outb(TIMER_0, LSB) != 0) return 1;
      if(sys_outb(TIMER_0, MSB) != 0) return 1;
      return 0;
    case 1:
      if(timer_get_conf(1, &status) != 0) return 1;
      status = status & (BIT(0) | BIT(1) | BIT(2) | BIT(3));
      status = status | TIMER_LSB_MSB | TIMER_SEL1;
       
      division = TIMER_FREQ / freq;

      if(util_get_LSB(division, &LSB)!= 0) return 1;
      if(util_get_MSB(division, &MSB) != 0) return 1;

      if(sys_outb(TIMER_CTRL, status) != 0) return 1;
      if(sys_outb(TIMER_1, LSB) != 0) return 1;
      if(sys_outb(TIMER_1, MSB) != 0) return 1;
      return 0;
    case 2:
      if(timer_get_conf(2, &status) != 0) return 1;
      status = status & (BIT(0) | BIT(1) | BIT(2) | BIT(3));
      status = status | TIMER_LSB_MSB | TIMER_SEL2;
       
      division = TIMER_FREQ / freq;

      if(util_get_LSB(division, &LSB)!= 0) return 1;
      if(util_get_MSB(division, &MSB) != 0) return 1;

      if(sys_outb(TIMER_CTRL, status) != 0) return 1;
      if(sys_outb(TIMER_2, LSB) != 0) return 1;
      if(sys_outb(TIMER_2, MSB) != 0) return 1;
      return 0;      
  }
  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook);
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t RB = 0x00;
  switch(timer){
    case 0:
      RB = TIMER_RB_SEL(0) | TIMER_RB_COUNT_ | TIMER_RB_CMD;
      if(sys_outb(TIMER_CTRL, RB) != 0){ printf("sys outb error"); return 1; }
      if(util_sys_inb(TIMER_0, st) != 0){ printf("sys inb error "); return 1; }
      return 0;
    case 1:
      RB = TIMER_RB_SEL(1) | TIMER_RB_COUNT_ | TIMER_RB_CMD;
      if(sys_outb(TIMER_CTRL, RB) != 0) return 1;
      if(util_sys_inb(TIMER_1, st) != 0) return 1;
      return 0;
    case 2:
      RB = TIMER_RB_SEL(2) | TIMER_RB_COUNT_ | TIMER_RB_CMD;
      if(sys_outb(TIMER_CTRL, RB) != 0) return 1;
      if(util_sys_inb(TIMER_2, st) != 0) return 1;
      return 0;  
  }
  return 1;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  bool bcd = (st & BIT(0));

  uint8_t op_mode = (st) & (BIT(1) | BIT(2) | BIT(3));
  op_mode /= 2;
  if(op_mode == 6) op_mode = 2;
  if(op_mode == 7) op_mode = 3;

  uint8_t ini_mode = (st) & (BIT(4) | BIT(5));
  ini_mode /= 16;
  enum timer_init init_val;
  if(ini_mode == 1) init_val = LSB_only;
  if(ini_mode == 2) init_val = MSB_only;
  if(ini_mode == 3) ini_mode = MSB_after_LSB;
  else ini_mode = INVAL_val;

  if(field == tsf_all){
    val.bcd = bcd;
    val.in_mode = init_val;
    val.count_mode = op_mode;
    val.byte = st;
  }
  if(field == tsf_base) val.bcd = bcd;
  if(field == tsf_initial) val.in_mode = init_val;
  if(field == tsf_mode) val.count_mode = op_mode;

  if(timer_print_config(timer, field, val) != 0) return 1;
  return 0;
}
