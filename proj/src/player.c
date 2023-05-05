#include "player.h"

Player* initPlayer(){
  Player* player = (Player*) malloc (sizeof(Player));

  player->x = 400;
  player->y = 480;
  player->lives = 3;
  player->score = 0;

  return player;
}
