#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook_id = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  return 1;
}

int (timer_unsubscribe_int)() {
  return 1;
}

void (timer_int_handler)() {
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t rb = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if (sys_outb(TIMER_CTRL, rb) != 0) return 1;
  switch (timer) {
    case 0: if (util_sys_inb(TIMER_0, st) != 0) return 1; break;
    case 1: if (util_sys_inb(TIMER_1, st) != 0) return 1; break;
    case 2: if (util_sys_inb(TIMER_2, st) != 0) return 1; break;
    default: break;
  }
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  enum timer_init in_mode;
  switch ((st & (BIT(5) | BIT(4))) >> 4) {
    case 1: in_mode = LSB_only; break;
    case 2: in_mode = MSB_only; break;
    case 3: in_mode = MSB_after_LSB; break;
    default: in_mode = INVAL_val; break;
  }
  uint8_t count_mode = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
  if (count_mode == 6) count_mode = 2;
  else if (count_mode == 7) count_mode = 3;
  bool bcd = st & BIT(0);

  union timer_status_field_val val;
  if (field == tsf_all) {
    val.byte = st;
    val.in_mode = in_mode;
    val.count_mode = count_mode;
    val.bcd = bcd;
  } else if (field == tsf_initial) val.in_mode = in_mode;
  else if (field == tsf_mode) val.count_mode = count_mode;
  else if (field == tsf_base) val.bcd = bcd;
  else return 1;
  return timer_print_config(timer, field, val);
}
