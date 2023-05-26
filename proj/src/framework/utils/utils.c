#include "utils.h"

int (ut_sys_inb)(int port, uint8_t* value) {
  uint32_t v32 = 0;
  if (sys_inb(port, &v32) != 0) return 1;
  *value = (uint8_t) (v32 & 0xff);
  return 0;
}

uint8_t (bcd_to_bin)(uint8_t value) {
  return ((value >> 4) * 10) + (value & 0xf);
}

/*
https://github.com/Fabio-A-Sa/Y2S2-LabComputadores/tree/main/Labs/lab6#bcd-vs-bin%C3%A1rio
*/
