#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook_id = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq < 19) return 1;
  uint16_t div = TIMER_FREQ/freq;
  uint8_t divLSB = 0;
  uint8_t divMSB = 0;
  if (util_get_LSB(div, &divLSB) != 0) return 1;
  if (util_get_MSB(div, &divMSB) != 0) return 1;
  uint8_t status = 0;
  if (timer_get_conf(timer, &status) != 0) return 1;
  status &= 0xF;
  status |= TIMER_LSB_MSB;
  switch (timer) {
    case 0: status |= TIMER_SEL0; break;
    case 1: status |= TIMER_SEL1; break;
    case 2: status |= TIMER_SEL2; break;
    default: break;
  }
  if (sys_outb(TIMER_CTRL, status) != 0) return 1;
  switch (timer) {
    case 0:
      if (sys_outb(TIMER_0, divLSB) != 0) return 1;
      if (sys_outb(TIMER_0, divMSB) != 0) return 1;
      break;
    case 1:
      if (sys_outb(TIMER_1, divLSB) != 0) return 1;
      if (sys_outb(TIMER_1, divMSB) != 0) return 1;
      break;
    case 2:
      if (sys_outb(TIMER_2, divLSB) != 0) return 1;
      if (sys_outb(TIMER_2, divMSB) != 0) return 1;
      break;
    default: break;
  }
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  counter++;
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
