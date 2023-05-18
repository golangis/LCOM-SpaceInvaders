#include "player.h"

Player* (initPlayer)(){
  Player* ship = (Player*) malloc (sizeof(Player));

  ship->x = 400;
  ship->y = 480;
  ship->lives = 3;
  ship->score = 0;

  return ship;
}

void (movePlayer)(Player* ship, enum direction dir) {
  ship->x += dir == left ? -1 : 1;
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
  vg_draw_rectangle(ship->x, ship->y, 20, 20, 0xfffffff);
}

void (incrementScore)(Player* ship, unsigned int n) {
  ship->score += n;
}
