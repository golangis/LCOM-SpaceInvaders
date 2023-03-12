#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

int (kbc_subscribe_int)(uint8_t* bit_no);

int (kbc_unsubscribe_int)();

void (kbc_ih)();

bool (is_kbc_input_ready)();

bool (is_kbc_out_ready)();

int (kbc_read_cmd_byte)(uint8_t* byte);

int (kbc_write_cmd_byte)(uint8_t cmd);

#endif
