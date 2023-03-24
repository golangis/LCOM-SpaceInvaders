#ifndef I8042_H
#define I8042_H

#define KBC_IRQ 1

#define KBC_STATUS_PORT 0x64
#define KBC_CMD_BUF 0x64
#define KBD_OUT_BUF 0x60
#define KBD_IN_BUF 0x60

#define KBD_PAR_ERR BIT(7)
#define KBD_TIME_ERR BIT(6)
#define KBD_IN_BUF_FULL BIT(1)
#define KBD_OUT_BUF_FULL BIT(0)

#define KBC_ESC_BREAK 0x81
#define KBC_DOUBLE_BYTE 0xe0

#define DELAY_US 20000

#endif
