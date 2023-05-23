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
#include "framework/timer/timer.h"
#include "framework/video/video.h"

#include "spaceinvaders.h"

// Game
extern Player* ship;
extern Shield* shield1;
extern Shield* shield2;
extern Shield* shield3;

// Timer
extern unsigned int timer_counter;

// Keyboard
extern int data;

int (proj_main_loop)(int argc, char **argv) {
    int ipc_status;
    message msg;
    int r;

    int ipc_timer = BIT(TIMER_HOOK_BIT);  // check if 31
    int ipc_keyboard = BIT(KBC_HOOK_BIT);   // check if 1
    //int ipc_mouse = BIT(10);  // check if 10

    // timer
    timer_counter = 0;
    uint8_t timer_hook_bit = TIMER_HOOK_BIT;
    if (subscribe_timer_int(&timer_hook_bit) != 0) return 1;

    // keyboard
    data = 0;
    uint8_t kbc_hook_bit = KBC_HOOK_BIT;
    if (kbc_subscribe_int(&kbc_hook_bit) != 0) return 1;
    uint8_t* scan = (uint8_t*) malloc(2);
    bool two_bytes = false;
    bool make;
    enum kbd_key key = INVALID;

    // video
    video_init(0x115);

    init_game();

    while(key != kbd_esc) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);            
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & ipc_timer) {
                        timer_interrupt_handler();
                        if (timer_counter % 2 == 0) {
                            draw();
                            while (!update());
                        }
                        if (timer_counter == UINT_MAX) timer_counter = 0;
                    }
                    if (msg.m_notify.interrupts & ipc_keyboard) {
                        kbc_ih();
                        if (two_bytes) {
                            scan[1] = data;
                            two_bytes = false;
                            make = data & BIT(7);
                            key = kbd_get_key(!make, 2, scan);
                            switch (key) {
                                case kbd_left: movePlayer(ship, left); key = INVALID; break;
                                case kbd_right: movePlayer(ship, right); key = INVALID; break;
                                case kbd_up: case kbd_space: fire(ship); key = INVALID; break;
                                default: break;
                            }
                        } else {
                            scan[0] = data;
                            make = data & BIT(7);
                            if (data == KBD_TWO_BYTE) two_bytes = true;
                            else {
                                key = kbd_get_key(!make, 1, scan);
                                switch (key) {
                                    case kbd_left: movePlayer(ship, left); key = INVALID; break;
                                    case kbd_right: movePlayer(ship, right); key = INVALID; break;
                                    case kbd_up: case kbd_space: fire(ship); key = INVALID; break;
                                    default: break;
                                }
                            }
                        }
                    }
                    //if (msg.m_notify.interrupts & ipc_mouse) {}
                    break;
                default:
                    break;
            }
        }
    }

    free(scan);
    if (kbc_unsubscribe_int() != 0) return 1;
    if (unsubscribe_timer_int() != 0) return 1;
    vg_exit();
    return 0;
}
