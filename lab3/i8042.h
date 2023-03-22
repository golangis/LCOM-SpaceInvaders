#ifndef I8042_H
#define I8042_H

#define KBC_IRQ 1

#define KBC_STAT_REG 0x64
#define KBC_OUT_BUF 0x60
#define KBC_IN_BUF 0x60
#define KBC_CMD_REG 0x64
#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60

#define KBC_HOOK_BIT 1

#define KBD_ESC_KEY 0x81

#define KBD_TWO_BYTE 0xe0

#define DELAY 20000

#endif
