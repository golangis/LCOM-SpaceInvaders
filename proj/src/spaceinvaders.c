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

void (update)() {
  for (size_t i = 0; i < ship->shots_no; i++) {
    moveShot(&(ship->shots[i]));
    if (ship->shots[i].y == 0) {
      deletePlayerShot(ship, i);
      return;
    }
    else if (ship->shots[i].y == shield1->y_max && ship->shots[i].x >= shield1->x_min && ship->shots[i].x <= shield1->x_max) {
      printf("shield1\n");
      deletePlayerShot(ship, i);
      damage(shield1);
      //return false;
    } else if (ship->shots[i].y == shield2->y_max && ship->shots[i].x >= shield2->x_min && ship->shots[i].x <= shield2->x_max) {
      printf("shield2\n");
      deletePlayerShot(ship, i);
      damage(shield2);
      //return false;
    } else if (ship->shots[i].y == shield3->y_max && ship->shots[i].x >= shield3->x_min && ship->shots[i].x <= shield3->x_max) {
      printf("shield3\n");
      deletePlayerShot(ship, i);
      damage(shield3);
      //return false;
    }
  }
  // update alien shots
  //return true;
}
