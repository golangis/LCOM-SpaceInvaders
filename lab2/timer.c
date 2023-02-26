#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer == 0) {
    uint8_t st = 0;
    if (timer_get_conf(timer, &st) != 0) return 1;
    st &= 0x0F;
    uint32_t control = (TIMER_SEL0 | TIMER_LSB_MSB | st);
    uint16_t div = TIMER_FREQ/freq;
    uint8_t divLSB = 0;
    uint8_t divMSB = 0;
    if (util_get_LSB(div, &divLSB) != 0) return 1;
    if (util_get_MSB(div, &divMSB) != 0) return 1;
    if (sys_outb(TIMER_CTRL, control) != 0) return 1;
    if (sys_outb(TIMER_0, divLSB) != 0) return 1;
    if (sys_outb(TIMER_0, divMSB) != 0) return 1;
  } else if (timer == 1) {
    uint8_t st = 0;
    if (timer_get_conf(timer, &st) != 0) return 1;
    st &= 0x0F;
    uint32_t control = (TIMER_SEL1 | TIMER_LSB_MSB | st);
    uint16_t div = TIMER_FREQ/freq;
    uint8_t divLSB = 0;
    uint8_t divMSB = 0;
    if (util_get_LSB(div, &divLSB) != 0) return 1;
    if (util_get_MSB(div, &divMSB) != 0) return 1;
    if (sys_outb(TIMER_CTRL, control) != 0) return 1;
    if (sys_outb(TIMER_1, divLSB) != 0) return 1;
    if (sys_outb(TIMER_1, divMSB) != 0) return 1;
  } else if (timer == 2) {
    uint8_t st = 0;
    if (timer_get_conf(timer, &st) != 0) return 1;
    st &= 0x0F;
    uint32_t control = (TIMER_SEL2 | TIMER_LSB_MSB | st);
    uint16_t div = TIMER_FREQ/freq;
    uint8_t divLSB = 0;
    uint8_t divMSB = 0;
    if (util_get_LSB(div, &divLSB) != 0) return 1;
    if (util_get_MSB(div, &divMSB) != 0) return 1;
    if (sys_outb(TIMER_CTRL, control) != 0) return 1;
    if (sys_outb(TIMER_2, divLSB) != 0) return 1;
    if (sys_outb(TIMER_2, divMSB) != 0) return 1;
  } else return 1;
  return 0;
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
  if (timer == 0) {
    uint32_t rb = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(0);
    if (sys_outb(TIMER_CTRL, rb) != 0) return 1;
    if (util_sys_inb(TIMER_0, st) != 0) return 1;
  } else if (timer == 1) {
    uint32_t rb = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(1);
    if (sys_outb(TIMER_CTRL, rb) != 0) return 1;
    if (util_sys_inb(TIMER_1, st) != 0) return 1;
  } else if (timer == 2) {
    uint32_t rb = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(2);
    if (sys_outb(TIMER_CTRL, rb) != 0) return 1;
    if (util_sys_inb(TIMER_2, st) != 0) return 1;
  } else return 1;
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  union timer_status_field_val val;
  
  bool bcd = (st % 2);
  
  uint8_t programmed_mode = st;
  uint8_t mask = BIT(3) | BIT(2) | BIT(1);
  programmed_mode &= mask;
  programmed_mode >>= 1;
  if (programmed_mode == 6) programmed_mode = 2;
  else if (programmed_mode == 7) programmed_mode = 3;
  
  uint8_t access = st;
  mask = BIT(5) | BIT(4);
  access &= mask;
  access >>= 4;
  enum timer_init access_mode;
  if (access == 1) access_mode = LSB_only;
  else if (access == 2) access_mode = MSB_only;
  else if (access == 3) access_mode = MSB_after_LSB;
  else access_mode = INVAL_val;

  if (field == tsf_all) {
    val.bcd = bcd;
    val.count_mode = programmed_mode;
    val.in_mode = access_mode;
    val.byte = st;
  } else if (field == tsf_initial) val.in_mode = access_mode;
  else if (field == tsf_mode) val.count_mode = programmed_mode;
  else if (field == tsf_base) val.bcd = bcd;

  return timer_print_config(timer, field, val);
}
