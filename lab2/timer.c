#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
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
