#include <lcom/lcf.h>
#include "kbdframework.h"
#include <stdbool.h>
#include <stdint.h>

int hook = 0;
uint8_t data = 0;

int (util_get_LSB)(uint16_t val, uint8_t *lsb) {
  uint16_t mask = BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) | BIT (6) | BIT(7);
  *lsb = val & mask;
  return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb) {
  uint16_t mask = BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) | BIT (6) | BIT(7);
  val >>= 8;
  *msb = val & mask;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t value1 = 0;
  if(sys_inb(port, &value1) != 0) return 1;
  *value = (uint8_t)value1;
  return 0;
}

int (kbc_subscribe_int)(uint8_t *bit_no) {
  hook = *bit_no;
  return sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook);
}

int (kbc_unsubscribe_int)(){
    return sys_irqrmpolicy(&hook);
}

void (kbc_ih)(){
    uint8_t status = 0;
    while(true){
        if(util_sys_inb(KBC_STAT_REG, &status) != 0) data = 0; 
        if((status & BIT(0)) != 0){
            if((status & BIT(7)) != 0 || (status & BIT(6)) != 0) data = 0;
            if(util_sys_inb(KBC_OUT_BUF, &data) != 0) data = 0;
            break;
        }
    }
}

void translate(uint8_t value, bool make){
  char string[100];
  switch(value){
    case SPACE_MAKE :
      sprintf(string, "SPACE BAR PRESSED"); 
      break;
    case SPACE_BREAK:
      sprintf(string, "SPACE BAR RELEASED"); 
      break;
    case RIGHT_MAKE:
      sprintf(string, "RIGHT KEY PRESSED"); 
      break;
    case RIGHT_BREAK:
      sprintf(string, "RIGHT KEY RELEASED");  
      break;
    case LEFT_MAKE:
      sprintf(string, "LEFT KEY PRESSED"); 
      break;
    case LEFT_BREAK:
      sprintf(string, "LEFT KEY RELEASED"); 
      break;
    case UP_MAKE:
      sprintf(string, "UP KEY PRESSED"); 
      break;
    case UP_BREAK:
      sprintf(string, "UP KEY RELEASED"); 
      break;   
    case DOWN_MAKE:
      sprintf(string, "DOWN KEY PRESSED"); 
      break;
    case DOWN_BREAK:
      sprintf(string, "DOWN KEY RELEASED"); 
      break;
    case KBD_ESC_KEY:
      sprintf(string, "QUIT");
      break;
    default:
      if(make) sprintf(string, "MAKECODE: %d", value);
      else sprintf(string, "BREAKCODE: %d", value);
      break;
  }
  printf("%s \n", string);
}

void kbd_print_code(bool make, uint8_t size, uint8_t bytes[]){
  if(size == 1) translate(bytes[0], make);  
  else if (size == 2) translate(bytes[1], make);
}

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/g3/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/g3/proj/src/output.txt");
  if (lcf_start(argc, argv))
    return 1;
  lcf_cleanup();
  return 0;
}

int kbd_scan() {
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
              kbd_print_code(!make, 2, scan);
            }
            else{
              scan[0] = data;
              make = data & BIT(7);
              if (data == KBD_TWO_BYTE) two_bytes = true;
              else kbd_print_code(!make, 1, scan);
            }
          }
          break;
        default: break;  
      }
    }
  }
  free(scan);
  if(kbc_unsubscribe_int() != 0) return 1;
  return 0;
}

int (proj_main_loop)(){
  if(kbd_scan() != 0) return 1;
  return 0;
}
