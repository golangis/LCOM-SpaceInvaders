#include "utils.h"

int (ut_sys_inb)(int port, uint8_t* value) {
  uint32_t v32 = 0;
  if (sys_inb(port, &v32) != 0) return 1;
  *value = (uint8_t) (v32 & 0xff);
  return 0;
}
