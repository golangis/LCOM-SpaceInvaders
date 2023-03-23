#ifndef I8042_H
#define I8042_H

#define KBC_IRQ 1
#define MOUSE_IRQ 12
#define KBC_OUT_BUF 0x60
#define KBC_IN_BUF 0x60
#define KBC_STAT_REG 0x64
#define KBC_CMD_REG 0x64

#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)

#define KBC_AUX BIT(5)
#define KBC_IBF_FULL BIT(1)
#define KBC_OBF_FULL BIT(0)

#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60

#define KBD_ESC_BREAK 0x81
#define KBD_TWO_BYTE 0xe0

#define MOUSE_ACK 0xfa
#define MOUSE_NACK 0xfe
#define MOUSE_ERROR 0xfc

#define KBC_WRITE_MOUSE_BYTE 0xd4
#define MOUSE_DIS_REPORT 0xf5
#define MOUSE_RESET 0xff

#define KBC_HOOK_BIT 1
#define MOUSE_HOOK_BIT 29

#define DELAY_US 20000

#endif