#include "player.h"

Player* (initPlayer)(){
  Player* ship = (Player*) malloc (sizeof(Player));
  /*
  width = 40px;
  height = 40px;
  */
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
  if (canPlayerMove(ship, dir)) {
    ship->x_min += dir == left ? -10 : 10;
    ship->x_max += dir == left ? -10 : 10;
  }
}

bool (canPlayerMove)(Player* ship, enum direction dir) {
  switch (dir) {
    case left: if (ship->x_min <= 1) return false; break;
    case right: if (ship->x_max >= 798) return false; break;
    default: break;
  }
  return true;
}

void (fire)(Player* ship) {
  Shot* array = (Shot*) malloc (sizeof(Shot) * (ship->shots_no + 1));
  for (int i = 0; i < ship->shots_no; i++) array[i] = ship->shots[i];
  Shot new_shot = initShot(ship->x_min + 10, (ship->y_min - 60), player);
  ship->shots_no = ship->shots_no + 1;
  array[ship->shots_no - 1] = new_shot;
  ship->shots = array;
}

void (looseLife)(Player* ship) {
  ship->lives--;
}

void (deletePlayerShot)(Player* ship, int i) {
  for (int x = i; x < ship->shots_no - 1; x++) ship->shots[x] = ship->shots[x + 1];
  ship->shots_no--;
}

void (drawPlayer)(Player* ship) {
  for (int i = 0; i < ship->shots_no; i++) drawShot(&(ship->shots[i]));
  video_draw_xpm(ship->x_min, ship->y_min, rocket_xpm);
}

void (incrementScore)(Player* ship, int n) {
  ship->score = ship->score + n;
}

void (drawScore)(Player* ship){
  int score = ship->score;
  video_draw_xpm(10, 570, score_xpm);
  video_draw_score(112, 570, score);
}
