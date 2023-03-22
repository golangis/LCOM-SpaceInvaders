#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"

extern uint8_t data;
uint32_t cnt = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  //lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  cnt = 0;
  data = 0;
  message msg;
  int ipc_status = 0;
  int r = 0;
  uint8_t bit_no = KBC_HOOK_BIT;
  int irq_set = BIT(KBC_HOOK_BIT);
  uint8_t* scan = (uint8_t*) malloc(2);
  bool two_bytes = false;
  bool make;

  if(kbc_subscribe_int(&bit_no) != 0) return 1;

  while(data != KBD_ESC_KEY){
    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver_recieve failed with: %d", r);
      continue;
    }

    if(is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE:
          if((msg.m_notify.interrupts & irq_set)){
            kbc_ih();
            if(two_bytes){
              scan[1] = data;
              two_bytes = false;
              make = data & BIT(7);
              if(kbd_print_scancode(!make, 2, scan) != 0) return 1;
            }
            else{
              scan[0] = data;
              make = data & BIT(7);
              if (data == KBD_TWO_BYTE) two_bytes = true;
              else if(kbd_print_scancode(!make, 1, scan) != 0) return 1;
            }
          }
          break;
        default: break;  
      }
    }
  }
  free(scan);
  if(kbc_unsubscribe_int() != 0) return 1;
  if(kbd_print_no_sysinb(cnt) != 0) return 1;
  return 0;
}

int(kbd_test_poll)() {
  cnt = 0;
  data = 0;
  int make = 0;
  bool two_bytes = false;
  uint8_t* scan = (uint8_t*) malloc(2);
  uint8_t command = 0;
  
  if(kbd_read_cmd(&command) != 0) return 1;

  while(data != KBD_ESC_KEY){
    uint8_t status = 0;
    if(util_sys_inb(KBC_STAT_REG, &status)) return 1;

    if(status & BIT(0)){
      if(util_sys_inb(KBC_STAT_REG, &status) != 0) return 1;
      if(util_sys_inb(KBC_OUT_BUF, &data) != 0) return 1;
      if(((status & BIT(6)) != 0) || ((status & BIT(7)) != 0)) return 1;

      if(two_bytes){
        scan[1] = data;
        two_bytes = false;
        make = data & BIT(7);
        if(kbd_print_scancode(!make, 2, scan) != 0) return 1;
      }
      else{
        make = data & BIT(7);
        if(data == KBD_TWO_BYTE) two_bytes = true;
        scan[0] = data;
        if(kbd_print_scancode(!make, 1, scan) != 0) return 1;
      }
      cnt++;
    }
    tickdelay(micros_to_ticks(DELAY));
  }

  command = command & ~BIT(4);
  command = command | BIT(0);
  if(kbd_write_cmd(command) != 0) return 1;
  if(kbd_print_no_sysinb(cnt) != 0) return 1;

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
