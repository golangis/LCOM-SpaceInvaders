#ifndef UTILS_H
#define UTILS_H

#include <lcom/lcf.h>
#include <stdint.h>

int (ut_sys_inb)(int port, uint8_t* value);
uint8_t (bcd_to_bin)(uint8_t value);

#endif
