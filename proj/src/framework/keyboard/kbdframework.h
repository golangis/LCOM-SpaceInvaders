#ifndef KBDFRAMEWORK_H
#define KBDFRAMEWORK_H

#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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

typedef enum kbd_key {
  kbd_right,
  kbd_left,
  kbd_up,
  kbd_down,
  kbd_space,
  kbd_esc,
  INVALID
} kbd_key;

int (util_get_LSB)(uint16_t val, uint8_t *lsb);
int (util_get_MSB)(uint16_t val, uint8_t *msb);
int (util_sys_inb)(int port, uint8_t *value);
int (kbc_subscribe_int)(uint8_t *bit_no);
int (kbc_unsubscribe_int)();
void (kbc_ih)();
void kbd_print_code(bool make, uint8_t size, uint8_t bytes[]);

#endif
