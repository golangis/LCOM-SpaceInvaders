#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  uint16_t mask = BIT(15) | BIT(14) | BIT(13) | BIT(12) | BIT(11) | BIT(10) | BIT(9) | BIT(8);
  val &= mask;
  val >>= 8;
  *lsb = (uint8_t)val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  val >>= 8;
  *msb = (uint8_t)val;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t v32 = 0;
  if (sys_inb(port, &v32) != 0) return 1;
  *value = (uint8_t)v32;
  return 0;
}
