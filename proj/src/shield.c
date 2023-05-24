#include "shield.h"

Shield* (initShield)(int x_min, int id) {
  Shield* shield = (Shield*) malloc (sizeof(Shield));
  
  shield->x_min = x_min;
  shield->x_max = x_min + 100;
  shield->y_min = 400;
  shield->y_max = 432;
  shield->lives = 3;
  shield->id = id;

  return shield;
}

void (drawShield)(Shield* shield) {
  switch (shield->lives) {
    case 1: video_draw_xpm(shield->x_min, shield->y_min, shield1_xpm); break;
    case 2: video_draw_xpm(shield->x_min, shield->y_min, shield2_xpm); break;
    case 3: video_draw_xpm(shield->x_min, shield->y_min, shield3_xpm); break;
    default: break;
  }
}

void (damage)(Shield* shield, enum shot_source src) {
  shield->lives--;
  switch (shield->lives) {
    case 2: shield->x_min += 7; shield->x_max -= 7; shield->y_min += 5; shield->y_max -= 5; break;
    case 1: shield->x_min += 7; shield->x_max -= 7; shield->y_min += 6; shield->y_max -= 6; break;
    default: break;
  }
}

/*
3 vidas: 100x32
2 vidas: 86x22
1 vida : 71x10
*/
