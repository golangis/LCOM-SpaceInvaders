#include "shield.h"

Shield* (initShield)(int x_min) {
  Shield* shield = (Shield*) malloc (sizeof(Shield));
  
  shield->x_min = x_min;
  shield->x_max = x_min + 100;
  shield->y_min = 400;
  shield->y_max = 430;
  shield->lives = 15;
  shield->thickness = 3;

  return shield;
}

void (drawShield)(Shield* shield) {
  if (shield->lives > 0) video_draw_rectangle(shield->x_min, 400, 100, (shield->thickness) * 10, 0xffffff);
}

void (damage)(Shield* shield) {
  shield->thickness--;
  shield->lives--;
}
