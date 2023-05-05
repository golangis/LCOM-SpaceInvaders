#include "shield.h"

Shield* initShield(int x) {
  Shield* shield = (Shield*) malloc (sizeof(Shield));
  shield->x = x;
  shield->y = 450;
  shield->lives = 15;
  shield->thickness = 3;
  return shield;
}

void drawShield(Shield* shield) {
  if (shield->lives > 0) video_draw_rectangle(shield->x, 400, 100, (shield->thickness) * 10, 0xffffff);
}

void damage(Shield* shield) {
  shield->thickness--;
  shield->lives--;
}
