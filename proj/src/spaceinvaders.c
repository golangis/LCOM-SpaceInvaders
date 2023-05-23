#include "spaceinvaders.h"

void (init_game)() {
  ship = initPlayer();
  shield1 = initShield(100);
  shield2 = initShield(350);
  shield3 = initShield(600);
  aliens = initAliens();
  shot_count = 0;
}

void (draw)() {
  memset(video_buffer, 0, h_res*v_res*bytes_per_pixel);

  drawShield(shield1);
  drawShield(shield2);
  drawShield(shield3);

  drawPlayer(ship);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (updateShots)() {
  for (size_t i = 0; i < ship->shots_no; i++) {
    moveShot(&(ship->shots[i]));
    if (ship->shots[i].y <= 0) deletePlayerShot(ship, i);
  }
  // update alien shots
}

void (check_collisions)() {
  /*for (size_t i = 0; i < shot_count; i++) {
    Shot shot = shots[i];
  }*/
}
