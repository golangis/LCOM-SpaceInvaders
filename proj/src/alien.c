#include "alien.h"

/*
reduzir tamanho aliens!
*/

Alien (initAlien)(int id, int x_min, int y_min) {
  Alien alien;
  alien.id = id;
  alien.x_min = x_min;
  alien.y_min = y_min;
  alien.x_max = x_min + 40;
  alien.y_max = y_min + 32;

  return alien;
}

AlienGroup* (initAliens)(){
  Alien* array = (Alien*) malloc (sizeof(Alien) * 30);
  AlienGroup* group = (AlienGroup*) malloc (sizeof(AlienGroup));
  group->size = 50;

  for (int i = 0; i < group->size; i++) {
    int x_min;
    switch (i % 10) {
      case 0: x_min = 155; break;
      case 1: x_min = 205; break;
      case 2: x_min = 255; break;
      case 3: x_min = 305; break;
      case 4: x_min = 355; break;
      case 5: x_min = 405; break;
      case 6: x_min = 455; break;
      case 7: x_min = 505; break;
      case 8: x_min = 555; break;
      case 9: x_min = 605; break;
    }
    int y_min = 40 * ((i / 10) + 1);
    array[i] = initAlien(i, x_min, y_min);
  }

  group->set = array;

  return group;
}

void (moveAliens)(AlienGroup* group, enum direction dir, int speed) {
  switch (dir) {
    case right:
      for (int i = 0; i < group->size; i++) {
        group->set[i].x_min += speed;
        group->set[i].x_max += speed;
      }
      break;
    case left:
      for (int i = 0; i < group->size; i++) {
        group->set[i].x_min -= speed;
        group->set[i].x_max -= speed;
      }
      break;
    case down:
      for (int i = 0; i < group->size; i++) {
        group->set[i].y_min += speed;
        group->set[i].y_max += speed;
      }
      break;
    default: break;
  }
}

void (drawAliens)(AlienGroup* group) {
  for (int i = 0; i < group->size; i++) drawAlien(&(group->set[i]));
}

void (dieAlien)(AlienGroup* group, Alien* alien){
  Alien* a;
  int i = 0;
  for (i = 0; i < group->size; i++) {
    if (group->set[i].id == alien->id) a = &(group->set[i]);
  }
  for (int x = i; x < group->size-1; x++) {
    group->set[x] = group->set[x+1];
  }
  free(a);
  group->size--;
}

void (drawAlien)(Alien* alien) {
  int id = alien->id;
  if (id >= 0 && id < 10) video_draw_xpm(alien->x_min, alien->y_min, alien1_xpm);
  else if (id >= 10 && id < 20) video_draw_xpm(alien->x_min, alien->y_min, alien2_xpm);
  else if (id >= 20 && id < 30) video_draw_xpm(alien->x_min, alien->y_min, alien3_xpm);
  else if (id >= 30 && id < 40) video_draw_xpm(alien->x_min, alien->y_min, alien4_xpm);
  else if (id >= 40 && id < 50) video_draw_xpm(alien->x_min, alien->y_min, alien5_xpm);
}
