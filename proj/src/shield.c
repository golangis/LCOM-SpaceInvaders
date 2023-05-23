#include "shield.h"

Shield* (initShield)(int x_min) {
  Shield* shield = (Shield*) malloc (sizeof(Shield));
  
  shield->x_min = x_min;
  shield->x_max = x_min + 100;
  shield->y_min = 400;
  shield->y_max = 430;
  shield->lives = 3;
  shield->thickness = 15;

  return shield;
}

void (drawShield)(Shield* shield) {
  if (shield->lives > 0) video_draw_rectangle(shield->x_min, 400, 100, (shield->thickness) * 2, 0xffffff);
}

void (damage)(Shield* shield) {
  shield->thickness -= 5;
  shield->lives--;
}
