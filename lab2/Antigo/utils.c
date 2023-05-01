#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  uint16_t mask = 0xff;
  *lsb = val & mask;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  uint16_t mask = 0xff;
  *msb = val & mask;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t value1;
  if(sys_inb(port, &value1) == 0){
    *value = (uint8_t)value1;
    return 0;
  }
  return 1;
}
