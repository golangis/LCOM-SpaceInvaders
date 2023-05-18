#include "spaceinvaders.h"

void (init_game)() {
  ship = initPlayer();
  shield1 = initShield(100);
  shield2 = initShield(350);
  shield3 = initShield(600);
  aliens = initAliens();
}

void (draw)() {
  printf("Drew\n");
  drawShield(shield1);
  drawShield(shield2);
  drawShield(shield3);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}
