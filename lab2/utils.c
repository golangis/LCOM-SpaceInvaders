#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  val &= 0x00FF;
  *lsb = (uint8_t) val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  val >>= 8;
  *msb = (uint8_t) val;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t v32 = 0;
  if (sys_inb(port, &v32) != 0) return 1;
  *value = (uint8_t) v32;
  return 0;
}
