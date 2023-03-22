// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "mouse.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern int mouse_hook_id;
extern uint8_t data;

int (mouse_test_packet)(uint32_t cnt) {
  if (mouse_enable_data_reporting() != 0) return 1;
  uint8_t bitno = MOUSE_HOOK_BIT;
  if (mouse_subscribe_int(&bitno) != 0) return 1;

  int ipc_status = 0;
  int r = 0;
  message msg;
  int irq_set = BIT(MOUSE_HOOK_BIT);
  struct packet pp;

  int index = 0;
  uint8_t bytes[3];
  bool msb_y_delta, msb_x_delta;

  while (cnt > 0) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("drive_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            data = 0;
            mouse_ih();
            bytes[index] = data;
            if (index == 0) {
              bool y_ov = data & BIT(7);
              bool x_ov = data & BIT(6);
              msb_y_delta = data & BIT(5);
              msb_x_delta = data & BIT(4);
              bool mb = data & BIT(2);
              bool rb = data & BIT(1);
              bool lb = data & BIT(0);
              pp.y_ov = y_ov;
              pp.x_ov = x_ov;
              pp.mb = mb;
              pp.rb = rb;
              pp.lb = lb;
            } else if (index == 1) {
              if (msb_x_delta) pp.delta_x = data | 0xFF00;
              else pp.delta_x = data;
            } else if (index == 2) {
              if (msb_y_delta) pp.delta_y = data | 0xFF00;
              else pp.delta_y = data;
              for (int i = 0; i < 3; i++) pp.bytes[i] = bytes[i];
              mouse_print_packet(&pp);
              cnt--;
            }
            index++;
            index %= 3;
          }
          break;
        default: break;
      }
    }
  }
  if (mouse_unsubscribe_int() != 0) return 1;
  return mouse_reset_state();
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
