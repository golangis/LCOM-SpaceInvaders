#ifndef KBD_H
#define KBD_H

/**
 * @file kbd.h
 * @brief Constants for programming the KBC. Functions of the KBC framework.
 * 
 */

#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../utils/utils.h"

#define KBC_IRQ 1

#define KBC_STAT_REG 0x64
#define KBC_OUT_BUF 0x60
#define KBC_IN_BUF 0x60
#define KBC_CMD_REG 0x64
#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60

#define KBC_HOOK_BIT 1

#define KBD_TWO_BYTE 0xe0

#define DELAY 20000


#define KBD_ESC_KEY 129

#define SPACE_MAKE 57
#define SPACE_BREAK 185

#define LEFT_MAKE 75
#define LEFT_BREAK 203

#define UP_MAKE 72
#define UP_BREAK 200

#define DOWN_MAKE 80
#define DOWN_BREAK 208

#define RIGHT_MAKE 77
#define RIGHT_BREAK 205

/**
 * @brief Represents different keys that the information received from the keyboard can be mapped to.
 * 
 */
enum kbd_key {
  kbd_right,
  kbd_left,
  kbd_up,
  kbd_down,
  kbd_space,
  kbd_esc,
  INVALID
};

/**
 * @brief Subscribes and enables Keyboard interrupts.
 * @param bit_no Variable to store the keyboard's hook id correspondent bit number.
 * @return Return 0 upon success and non-zero otherwise.
 * 
 */
int (kbc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Keyboard interrupts.
 * @return Return 0 upon success and non-zero otherwise.
 * 
 */
int (kbc_unsubscribe_int)();

/**
 * @brief Handles Keyboard interrupts. Reads and stores the KBD data for later processing/interpretation.
 * 
 */
void (kbc_ih)();

/**
 * @brief Translates the KBD data into a key.
 * @param value KBD data.
 * @param make Whether the data is a makecode or a breakcode.
 * @return Returns the key correspondent to the KBD data.
 * 
 */
enum kbd_key kbd_get_key(bool make, uint8_t size, uint8_t bytes[]);

#endif
