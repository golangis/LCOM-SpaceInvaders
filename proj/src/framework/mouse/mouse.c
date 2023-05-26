#include "mouse.h"

uint8_t counter_byte = 0;
uint8_t current_byte;
struct packet pp;


int (mouse_interrupt_handler)() {
  if (readStatusByte() != 0) return 1; // DEU ERRO
  if (readPacket() != 0) return 1; // DEU ERRO

  return 0;
}

int (readStatusByte)() {
    uint8_t status = 0;
    ut_sys_inb(STATUS_REGISTER, &status);

    if ((status & BIT(5)) == 0) { // NÃO É RATO, É TECLADO
        printf("Não é rato.\n");
        return 1;
    }
    if ((status & BIT(6)) != 0) { // TIMEOUT
        printf("Erro de Timeout.\n");
        return 1;
    } 
    if ((status & BIT(7)) != 0) { // ERRO DE PARIDADE
        printf("Erro de paridade.\n");
        return 1;
    }
    if ((status & BIT(0)) == 0) { // BUFFER DE SAÍDA VAZIO
        printf("Buffer de saída vazio.\n");
        return 1;
    }

   return 0; // NÃO DEU ERRO 
  }

int (readPacket)() {
    uint8_t data;

    if (ut_sys_inb(OUTPUT_BUFFER, &data) != 0) {
        printf("Erro a ler o packet.\n");
        return 1;
    }

    if (counter_byte % 3 == 0){
      // LER O BIT DE CONTROLO DO PACOTE
      pp.lb = data & MOUSE_LB;
      pp.rb = data & MOUSE_RB;
      pp.mb = data & MOUSE_MB;
      pp.delta_x = data & MOUSE_X_SIGN;
      pp.delta_y = data & MOUSE_Y_SIGN;
      pp.x_ov = data & MOUSE_X_OV;
      pp.y_ov = data & MOUSE_Y_OV;
    }
    else if (counter_byte % 3 == 1){
      if (pp.delta_x != 0){
        pp.delta_x = -((int16_t)data);
      }
      else{
        pp.delta_x = ((int16_t)data);
      }
    }
    else if (counter_byte % 3 == 2){
      if (pp.delta_y != 0){
        pp.delta_y = -((int16_t)data);
      }
      else{
        pp.delta_y = ((int16_t)data);
      }
    }
    counter_byte++;
    return 0;
}

int hook_id_mouse;

int (subscribe_mouse_int)(uint8_t* bit_no) {
  hook_id_mouse = *bit_no;
  return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse);
}

int (unsubscribe_mouse_int)() {
  return sys_irqrmpolicy(&hook_id_mouse);
}
