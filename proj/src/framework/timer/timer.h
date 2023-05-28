#ifndef TIMER_H
#define TIMER_H

/**
 * @file timer.h
 * @brief Functions to program the i8254 Timer.
 * 
 */

#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_counter;
int timer_shot;
int hook_id;

/**
 * @brief Subscribes and enables Timer 0 interrupts.
 * @param bit_no Variable to store the timer's hook id correspondent bit number.
 * @return int 0 upon success, non-zero otherwise
 */
int (subscribe_timer_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Timer 0 interrupts.
 * @return int 0 upon success, non-zero otherwise
 */
int (unsubscribe_timer_int)();

/**
 * @brief Timer interrupt handler. Increments the timer counter.
 */
void (timer_interrupt_handler)();

#endif
