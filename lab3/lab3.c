#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("PT-PT");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern uint8_t data;
int counter = 0;

int(kbd_test_scan)() {
  int r;
  int ipc_status = 0;
  message msg;
  uint8_t bit_no = 12;
  int irq_set = BIT(12);

  if (kbc_subscribe_int(&bit_no) != 0) return 1;

  bool two_byte = false;
  uint8_t scan[2];

  while (data != KBC_ESC_BREAK) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            if (two_byte) {
              two_byte = false;
              scan[1] = data;
              if (kbd_print_scancode(!(data & BIT(7)), 2, scan) != 0) return 1;
            } else {
              scan[0] = data;
              if (data == KBC_DOUBLE_BYTE) two_byte = true;
              else if (kbd_print_scancode(!(data & BIT(7)), 1, scan) != 0) return 1;
            }
          }
          break;
        default: break;
      }
    }
  }
  if (kbc_unsubscribe_int() != 0) return 1;
  return kbd_print_no_sysinb(counter);
}

int(kbd_test_poll)() {
  return 1;
}

int(kbd_test_timed_scan)(uint8_t idle) {
  return 1;
}
