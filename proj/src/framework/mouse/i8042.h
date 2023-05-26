#ifndef I8042_H
#define I8042_H

#define MOUSE_IRQ 12
#define INPUT_BUFFER 0x64
#define OUTPUT_BUFFER 0x60
#define STATUS_REGISTER 0x64
#define ACK 0xFA
#define NACK 0xFE

#define MOUSE_HOOK_BIT 10

#define MOUSE_LB BIT(0)
#define MOUSE_RB BIT(1)
#define MOUSE_MB BIT(2)
#define MOUSE_X_SIGN BIT(4)
#define MOUSE_Y_SIGN BIT(5)
#define MOUSE_X_OV BIT(6)
#define MOUSE_Y_OV BIT(7)

#endif

