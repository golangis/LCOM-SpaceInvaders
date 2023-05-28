/**
 * @mainpage
 * This is our project for the Laboratório de Computadores course.\n\n
 * It is a recreation of the game Space Invaders.\n
 * A ship is controlled by the player, who tries to kill a group of aliens before they kill them.\n\n\n
 * The project was developed by Guilherme Ribeiro (up202108731@up.pt), Mariana Rocha (up202004656@up.pt) and Pedro Januário (up202108768@up.pt).
 */

#include <lcom/lcf.h>
#include <stdint.h>
extern int x_mouse_delta;


/**
 * @file main.c
 * @brief General functions that manage the app logic.
 * 
 * Loops that receive interrupt information, call the interrupt handlers and send commands and information to the functions delcared in spaceinvaders.h.
 */

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");
  if (lcf_start(argc, argv))
    return 1;
  lcf_cleanup();
  return 0;
}

#include "framework/keyboard/kbd.h"
#include "framework/rtc/rtc.h"
#include "framework/timer/timer.h"
#include "framework/mouse/mouse.h"
#include "framework/video/video.h"

#include "spaceinvaders.h"

// Game
extern Player* ship;
extern Shield* shield1;
extern Shield* shield2;
extern Shield* shield3;

// Timer
extern int timer_counter;

// Keyboard
extern int data;

void (highscores_loop)(bool* make, enum kbd_key* key, bool* two_bytes, uint8_t* scan, int ipc_timer, int ipc_keyboard, int ipc_mouse, message msg, enum state* state, Score* scores) {
    if (msg.m_notify.interrupts & ipc_timer) {
        timer_interrupt_handler();
        if (timer_counter % 2 == 0) draw_high_scores(scores);
        if (timer_counter >= 600) timer_counter = 0;
    }
    if (msg.m_notify.interrupts & ipc_keyboard) {
        kbc_ih();
        if (*two_bytes) {
            scan[1] = data;
            *two_bytes = false;
            *make = data & BIT(7);
            *key = kbd_get_key(!make, 2, scan);
            switch (*key) {
                case kbd_esc: *state = mainMenu; break;
                default: break;
            }
        } else {
            scan[0] = data;
            *make = data & BIT(7);
            if (data == KBD_TWO_BYTE) *two_bytes = true;
            else {
                *key = kbd_get_key(!make, 1, scan);
                switch (*key) {
                    case kbd_esc: *state = mainMenu; break;
                    default: break;
                }  
            }
        }
    }
    if (msg.m_notify.interrupts & ipc_mouse) {
        mouse_interrupt_handler();
    }
}

void (game_loop)(bool* make, enum kbd_key* key, bool* two_bytes, uint8_t* scan, bool* can_shoot, int ipc_timer, int ipc_keyboard, int ipc_mouse, message msg, enum state* state){
    int no_lives = 0;
    if (msg.m_notify.interrupts & ipc_timer) {
        timer_interrupt_handler();
        if (timer_counter % 2 == 0) {
            update(&no_lives);
            if(no_lives == 1) {
                Score* scores = load_scores();
                rtc_time time;
                while (get_time(&time));
                Score score = build_score(ship->score, &time);
                if (process_score(score, scores)) store_scores(scores);
                *state = gameOverMenu;
            }
            draw();
        }
        if (timer_counter % 90 == 0) *can_shoot = true;
        if (timer_counter >= 600) timer_counter = 0;
    }
    if (msg.m_notify.interrupts & ipc_keyboard) {
        kbc_ih();
        if (*two_bytes) {
            scan[1] = data;
            *two_bytes = false;
            *make = data & BIT(7);
            *key = kbd_get_key(!make, 2, scan);
            switch (*key) {
                case kbd_left: move_player(ship, left); *key = INVALID; break;
                case kbd_right: move_player(ship, right); *key = INVALID; break;
                case kbd_up: case kbd_space: 
                    if(*can_shoot){
                        fire(ship); 
                        *can_shoot = false;
                    } 
                    *key = INVALID; 
                    break;
                case kbd_esc: *state = mainMenu; break;
                default: break;
            }
        } else {
            scan[0] = data;
            *make = data & BIT(7);
            if (data == KBD_TWO_BYTE) *two_bytes = true;
            else {
                *key = kbd_get_key(!make, 1, scan);
                switch (*key) {
                    case kbd_left: move_player(ship, left); *key = INVALID; break;
                    case kbd_right: move_player(ship, right); *key = INVALID; break;
                    case kbd_up: case kbd_space: 
                        if(*can_shoot){
                            fire(ship); 
                            *can_shoot = false;
                        } 
                        *key = INVALID;
                        break;
                    case kbd_esc: *state = mainMenu; break;
                    default: break;
                }
            }
        }
    }
    if (msg.m_notify.interrupts & ipc_mouse) {
        if (x_mouse_delta < -100) move_player(ship, left);
        if (x_mouse_delta > 100) move_player(ship, right);
  
        if (left_click()){
            if(*can_shoot){
                fire(ship); 
                *can_shoot = false;
            } 
        }
        mouse_interrupt_handler();
    }
}

void (main_menu_loop)(bool* make, enum kbd_key* key, bool* two_bytes, uint8_t* scan, int ipc_timer, int ipc_keyboard, int ipc_mouse, message msg, enum state* state) {
    extern int x_mouse;
    extern int y_mouse;

    bool is_on_play_button = x_mouse <= 150 + 175 && x_mouse >= 150 && y_mouse <= 400 + 70 && y_mouse >= 400;
    bool is_on_rank_button = x_mouse <= 475 + 175 && x_mouse >= 475 && y_mouse <= 400 + 70 && y_mouse >= 400;

    if (msg.m_notify.interrupts & ipc_timer) {
        timer_interrupt_handler();
        if (timer_counter % 2 == 0) draw_main_menu();
        if (timer_counter >= 600) timer_counter = 0;
    }
    if (msg.m_notify.interrupts & ipc_keyboard) {
        kbc_ih();
        if (*two_bytes) {
            scan[1] = data;
            *two_bytes = false;
            *make = data & BIT(7);
            *key = kbd_get_key(!make, 2, scan);
            switch (*key) {
                case kbd_space: *state = game; init_game(); break;
                case kbd_esc: *state = quit; break;
                default: break;
            }
        } else {
            scan[0] = data;
            *make = data & BIT(7);
            if (data == KBD_TWO_BYTE) *two_bytes = true;
            else {
                *key = kbd_get_key(!make, 1, scan);
                switch (*key) {
                    case kbd_space: *state = game; init_game(); break;
                    case kbd_esc: *state = quit; break;
                    default: break;
                }  
            }
        }
    }
    if (msg.m_notify.interrupts & ipc_mouse) {
        if (is_on_play_button && left_click()) {
            *state = game;
            init_game();
        }
        if (is_on_rank_button && left_click()) *state = highscores;
        mouse_interrupt_handler();
    }
}

void (game_over_menu_loop)(bool* make, enum kbd_key* key, bool* two_bytes, uint8_t* scan, int ipc_timer, int ipc_keyboard, int ipc_mouse, message msg, enum state* state){
    extern int x_mouse;
    extern int y_mouse;
    bool is_on_replay_button = x_mouse <= 312 + 175 && x_mouse >= 312 && y_mouse <= 420 + 70 && y_mouse >= 420;

    if (msg.m_notify.interrupts & ipc_timer) {
        timer_interrupt_handler();
        if (timer_counter % 2 == 0) draw_game_over_menu();
        if (timer_counter >= 600) timer_counter = 0;
    }
    if (msg.m_notify.interrupts & ipc_keyboard) {
        kbc_ih();
        if (*two_bytes) {
            scan[1] = data;
            *two_bytes = false;
            *make = data & BIT(7);
            *key = kbd_get_key(!make, 2, scan);
            switch (*key) {
                case kbd_space: *state = game; init_game(); break;
                case kbd_esc: *state = quit; break;
                default: break;
            }
        } else {
            scan[0] = data;
            *make = data & BIT(7);
            if (data == KBD_TWO_BYTE) *two_bytes = true;
            else {
                *key = kbd_get_key(!make, 1, scan);
                switch (*key) {
                    case kbd_space: *state = game; init_game(); break;
                    case kbd_esc: *state = quit; break;
                    default: break;
                }  
            }
        }
    }
    if (msg.m_notify.interrupts & ipc_mouse) {
        if (is_on_replay_button && left_click()) {
            extern struct packet mouse_packet;
            *state = game;
            mouse_packet.lb = false;
            init_game();
        }
        mouse_interrupt_handler();
    }
}

int (proj_main_loop)(int argc, char **argv) {
    int ipc_status;
    message msg;
    int r;

    int ipc_timer = BIT(TIMER_HOOK_BIT);  // check if 31
    int ipc_keyboard = BIT(KBC_HOOK_BIT);   // check if 1
    int ipc_mouse = BIT(MOUSE_HOOK_BIT);  // check if 10

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
    bool can_shoot = false;
    enum kbd_key key = INVALID;

    // mouse
    uint8_t mouse_hook_bit = MOUSE_HOOK_BIT;
    if (subscribe_mouse_int(&mouse_hook_bit) != 0) return 1;

    // video
    video_init(0x115);

    enum state state = mainMenu;
    wave = 1;

    state = mainMenu;

    Score* hs = load_scores();

    while (state != quit) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);            
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    switch (state) {
                        case mainMenu:
                            main_menu_loop(&make, &key, &two_bytes, scan, ipc_timer, ipc_keyboard, ipc_mouse, msg, &state);
                            break;
                        case game:    
                            game_loop(&make, &key, &two_bytes, scan, &can_shoot, ipc_timer, ipc_keyboard, ipc_mouse, msg, &state);
                            break;
                        case highscores:
                            highscores_loop(&make, &key, &two_bytes, scan, ipc_timer, ipc_keyboard, ipc_mouse, msg, &state, hs);
                            break;
                        case quit:
                            break;
                        case gameOverMenu:
                            game_over_menu_loop(&make, &key, &two_bytes, scan, ipc_timer, ipc_keyboard, ipc_mouse, msg, &state);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    free(scan);
    if (unsubscribe_timer_int() != 0) return 1;
    if (kbc_unsubscribe_int() != 0) return 1;
    if (unsubscribe_mouse_int() != 0) return 1;
    vg_exit();

    return 0;
}
