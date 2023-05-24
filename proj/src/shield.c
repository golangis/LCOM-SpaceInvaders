#include "shield.h"

Shield* (initShield)(int x_min) {
  Shield* shield = (Shield*) malloc (sizeof(Shield));
  
  shield->x_min = x_min;
  shield->x_max = x_min + 100;
  shield->y_min = 400;
  shield->y_max = 430;
  shield->lives = 3;

  return shield;
}

void (drawShield)(Shield* shield) {
  if (shield->lives > 0) video_draw_rectangle(shield->x_min, shield->y_min, shield->x_max - shield->x_min, shield->y_max - shield->y_min, 0xffffff);
}

void (damage)(Shield* shield, enum shot_source src) {
  shield->lives--;
  switch (src) {
    case alien: shield->y_min += 10; break;
    case player: shield->y_max -= 10; break;
  }
}
