#include "player.h"

Player* (initPlayer)(){
  Player* ship = (Player*) malloc (sizeof(Player));

  ship->x_min = 400;
  ship->y_min = 480;
  ship->x_max = 440;
  ship->y_max = 520;
  ship->lives = 3;
  ship->score = 0;
  ship->shots_no = 0;

  return ship;
}

void (movePlayer)(Player* ship, enum direction dir) {
  ship->x_min += dir == left ? -5 : 5;
  ship->x_max += dir == left ? -5 : 5;
}

void (fire)(Player* ship) {
  Shot* array = (Shot*) malloc (sizeof(Shot) * (ship->shots_no + 1));
  for (size_t i = 0; i < ship->shots_no; i++) array[i] = ship->shots[i];
  Shot new_shot = initShot((ship->x_min + ship->x_max)/2, (ship->y_min - 1), player);
  ship->shots_no = ship->shots_no + 1;
  array[ship->shots_no - 1] = new_shot;
  ship->shots = array;
}

void (looseLife)(Player* ship) {
  ship->lives--;
}

void (deletePlayerShot)(Player* ship, unsigned int i) {
  Shot* array = (Shot*) malloc (sizeof(Shot) * (ship->shots_no - 1));
  for (size_t x = 0; x < i; x++) array[x] = ship->shots[x];
  for (size_t x = i + 1; x < ship->shots_no; x++) array[x-1] = ship->shots[x];
  ship->shots_no = ship->shots_no - 1;
  ship->shots = array;
}

void (drawPlayer)(Player* ship) {
  for (size_t i = 0; i < ship->shots_no; i++) drawShot(&(ship->shots[i]));
  video_draw_xpm(ship->x_min, ship->y_min, rocket_xpm);
}

void (incrementScore)(Player* ship, unsigned int n) {
  ship->score = ship->score + n;
}
