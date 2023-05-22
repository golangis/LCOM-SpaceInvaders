#include "player.h"

Player* (initPlayer)(){
  Player* ship = (Player*) malloc (sizeof(Player));

  ship->x_min = 400;
  ship->y_min = 480;
  ship->x_max = 440;
  ship->y_max = 520;
  ship->lives = 3;
  ship->score = 0;

  return ship;
}

void (movePlayer)(Player* ship, enum direction dir) {
  ship->x_min += dir == left ? -5 : 5;
  ship->x_max += dir == left ? -5 : 5;
}

void (fire)(Player* ship) {
  /*
  create shot
  */
}

void (looseLife)(Player* ship) {
  ship->lives--;
}

void (drawPlayer)(Player* ship) {
  video_draw_xpm(ship->x_min, ship->y_min, rocket_xpm);
}

void (incrementScore)(Player* ship, unsigned int n) {
  ship->score += n;
}
