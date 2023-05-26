#include "mouse.h"

uint8_t counter_byte = 0;
uint8_t current_byte;


// Coordenadas Iniciais do Mouse
int x_mouse = 400;
int y_mouse = 300;

bool mouse_read = false;
struct packet mouse_packet;

int (mouse_interrupt_handler)() {
  if (readStatusByte() != 0) return 1; // DEU ERRO
  if (readPacket() != 0) return 1; // DEU ERRO
  if(update_mouse() != 0) return 1; // DEU ERRO
  printf("x_mouse: %d\n", x_mouse);
  printf("y_mouse: %d\n", y_mouse);
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

    mouse_read = false;

    if (counter_byte % 3 == 0){
      printf("Caralho Byte 1: 0x%x\n", data);
      // LER O BIT DE CONTROLO DO PACOTE
      mouse_packet.lb = data & MOUSE_LB;
      mouse_packet.rb = data & MOUSE_RB;
      mouse_packet.mb = data & MOUSE_MB;
      mouse_packet.delta_x = data & MOUSE_X_SIGN;
      mouse_packet.delta_y = data & MOUSE_Y_SIGN;
      mouse_packet.x_ov = data & MOUSE_X_OV;
      mouse_packet.y_ov = data & MOUSE_Y_OV;
    }
    else if (counter_byte % 3 == 1){
      if (mouse_packet.delta_x != 0){
        mouse_packet.delta_x = -((int16_t)data);
      }
      else{
        mouse_packet.delta_x = ((int16_t)data);
      }
    }
    else if (counter_byte % 3 == 2){
      if (mouse_packet.delta_y != 0){
        mouse_packet.delta_y = -((int16_t)data);
      }
      else{
        mouse_packet.delta_y = ((int16_t)data);
      }
      mouse_read = true;
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

int (update_mouse)(){
  if (mouse_read == true){
    // dar update às coordenadas do rato
    x_mouse += mouse_packet.delta_x;
    y_mouse += mouse_packet.delta_y;

    // verificar se o rato está dentro dos limites do ecrã
    if (x_mouse < 0)
      x_mouse = 0;
    else if (x_mouse > 800)
      x_mouse = 800;

    if (y_mouse < 0)
      y_mouse = 0;
    else if (y_mouse > 600)
      y_mouse = 600;

    return 0;
  }
  return 1;
}
