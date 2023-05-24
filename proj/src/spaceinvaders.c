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

  drawAliens(aliens);

  drawPlayer(ship);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}

void (update)() {
  for (int i = 0; i < ship->shots_no; i++) {
    moveShot(&(ship->shots[i]));
    if ((ship->shots[i].y) <= 0) {
      deletePlayerShot(ship, i);
      return;
    } else if (shield1->lives > 0 && ship->shots[i].y <= shield1->y_max && ship->shots[i].x >= shield1->x_min && ship->shots[i].x <= shield1->x_max) {
      deletePlayerShot(ship, i);
      damage(shield1, player);
      return;
    } else if (shield2->lives > 0 && ship->shots[i].y <= shield2->y_max && ship->shots[i].x >= shield2->x_min && ship->shots[i].x <= shield2->x_max) {
      deletePlayerShot(ship, i);
      damage(shield2, player);
      return;
    } else if (shield3->lives > 0 && ship->shots[i].y <= shield3->y_max && ship->shots[i].x >= shield3->x_min && ship->shots[i].x <= shield3->x_max) {
      deletePlayerShot(ship, i);
      damage(shield3, player);
      return;
    }
  }
  // update alien shots
}
