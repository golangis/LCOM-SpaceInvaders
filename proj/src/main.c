#include <lcom/lcf.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/g3/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/g3/proj/src/output.txt");
  if (lcf_start(argc, argv))
    return 1;
  lcf_cleanup();
  return 0;
}

#include "framework/keyboard/kbdframework.h"
#include "framework/video/video.h"

#include "draw.h"

#include "alien.h"
#include "player.h"
#include "shield.h"
#include "shot.h"
#include "spaceinvaders.h"

//Player* player;
Shield* shield1;
Shield* shield2;
Shield* shield3;

void (init_game)() {
    //player = (Player*) malloc(sizeof(Player));
    shield1 = initShield(100);
    shield2 = initShield(350);
    shield3 = initShield(600);
}

extern int data;

int (proj_main_loop)(int argc, char **argv) {
    int ipc_status;
    message msg;
    int r;

    int ipc_timer = BIT(31);  // check if 31
    int ipc_keyboard = BIT(KBC_HOOK_BIT);   // check if 1
    int ipc_mouse = BIT(10);  // check if 10

    // timer

    // keyboard
    data = 0;
    uint8_t kbc_hook_bit = 1;
    if (kbc_subscribe_int(&kbc_hook_bit) != 0) return 1;
    uint8_t* scan = (uint8_t*) malloc(2);
    bool two_bytes = false;
    bool make;

    // video
    video_init(0x115);

    init_game();

    while(data != KBD_ESC_KEY) {
        draw();
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & ipc_timer) {
                    } else if (msg.m_notify.interrupts & ipc_keyboard) {
                        kbc_ih();
                        if(two_bytes){
                            scan[1] = data;
                            two_bytes = false;
                            make = data & BIT(7);
                            //kbd_print_code(!make, 2, scan);
                        } else {
                            scan[0] = data;
                            make = data & BIT(7);
                            if (data == KBD_TWO_BYTE) two_bytes = true;
                            //else kbd_print_code(!make, 1, scan);
                        }
                    } else if (msg.m_notify.interrupts & ipc_mouse) {}
                    break;
                default:
                    break;
            }
        }
    }

    free(scan);
    if (kbc_unsubscribe_int() != 0) return 1;
    vg_exit();
    return 0;
}
