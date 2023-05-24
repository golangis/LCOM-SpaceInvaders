#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_counter;
int hook_id;

int (subscribe_timer_int)(uint8_t *bit_no);
int (unsubscribe_timer_int)();
void (timer_interrupt_handler)();

#endif
