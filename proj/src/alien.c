#include "alien.h"

AlienGroup* (initAliens)(){
  Alien* first = (Alien*) malloc (sizeof(Alien) * 30);
  AlienGroup* group = (AlienGroup*) malloc (sizeof(AlienGroup));
  group->size = 30;
  group->first = first;

  return group;
}

void (moveAliens)(AlienGroup* group, enum direction dir, int speed) {
  switch (dir) {
    case right:
      for (size_t i = 0; i < group->size; i++) group->first[i].x += speed;
      break;
    case left:
      for (size_t i = 0; i < group->size; i++) group->first[i].x -= speed;
      break;
    case down:
      for (size_t i = 0; i < group->size; i++) group->first[i].y += speed;
      break;
    default: break;
  }
}

void (drawAliens)(AlienGroup* group) {
  for (size_t i = 0; i < group->size; i++) drawAlien(&(group->first[i]));
}

void (dieAlien)(AlienGroup* group, Alien* alien){
  Alien* a;
  for (size_t i = 0; i < group->size; i++) {
    if (group->first[i].id == alien->id) a = &(group->first[i]);
  }
  /*
  remove alien, shrink array and decrement size
  */
}

void (drawAlien)(Alien* alien) {
  video_draw_rectangle(alien->x, alien->y, 10, 10, 0xffffff);
}
