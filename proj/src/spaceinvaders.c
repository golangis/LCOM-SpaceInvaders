#include "spaceinvaders.h"

void (init_game)() {
  ship = initPlayer();
  shield1 = initShield(100);
  shield2 = initShield(350);
  shield3 = initShield(600);
  aliens = initAliens();
}

void (draw)() {
  memset(video_mem, 0, h_res*v_res*bytes_per_pixel);

  drawShield(shield1);
  drawShield(shield2);
  drawShield(shield3);

  drawPlayer(ship);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}
