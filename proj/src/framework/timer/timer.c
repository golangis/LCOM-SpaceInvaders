#include "timer.h"

int (subscribe_timer_int)(uint8_t* bit_no) {
  hook_id = *bit_no;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (subscribe_timer_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  timer_counter++;
}
