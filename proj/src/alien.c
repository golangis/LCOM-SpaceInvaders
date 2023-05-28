#include "alien.h"

Alien (init_alien)(int id, int x_min, int y_min) {
  Alien alien;
  alien.id = id;
  alien.x_min = x_min;
  alien.y_min = y_min;
  alien.x_max = x_min + 40;
  alien.y_max = y_min + 32;
  alien.shots_no = 0;
  alien.alive = true;

  return alien;
}

AlienGroup* (init_aliens)(){
  Alien* array = (Alien*) malloc (sizeof(Alien) * 50);
  AlienGroup* group = (AlienGroup*) malloc (sizeof(AlienGroup));
  group->size = 50;
  group->alive_no = 50;

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
    int y_min = (40 * ((i / 10) + 1)) + 14;
    array[i] = init_alien(i, x_min, y_min);
  }

  group->set = array;

  return group;
}

void (move_aliens)(AlienGroup* group, enum direction dir) {
  switch (dir) {
    case right:
      for (int i = 0; i < group->size; i++) {
        group->set[i].x_min += 5;
        group->set[i].x_max += 5;
      }
      break;
    case left:
      for (int i = 0; i < group->size; i++) {
        group->set[i].x_min -= 5;
        group->set[i].x_max -= 5;
      }
      break;
    case down:
      for (int i = 0; i < group->size; i++) {
        group->set[i].y_min += 5;
        group->set[i].y_max += 5;
      }
      break;
    default: break;
  }
}

void (die_alien)(AlienGroup* group, int i) {
  group->set[i].alive = false;
  group->alive_no--;
}

void (shoot_alien)(Alien* a) {
  Shot* array = (Shot*) malloc (sizeof(Shot) * (a->shots_no + 1));
  for (int i = 0; i < a->shots_no; i++) array[i] = a->shots[i];
  Shot new_shot = init_shot(a->x_min + 10, a->y_max + 20, alien);
  a->shots_no++;
  array[a->shots_no - 1] = new_shot;
  free(a->shots);
  a->shots = array;
}

void (delete_alien_shot)(Alien* alien, int i) {
  Shot* s = &(alien->shots[i]);
  for (int x = i; x < alien->shots_no - 1; x++) alien->shots[x] = alien->shots[x + 1];
  free(s);
  alien->shots_no--;
}

void (shoot_aliens)(AlienGroup* group) {
  int index = rand() % group->size;
  while (!(group->set[index].alive)) index = rand() % group->size;
  Alien* a = &(group->set[index]);
  shoot_alien(a);
}

bool (can_alien_move)(Alien* alien, enum direction dir) {
  switch (dir) {
    case down: return true;
    case left: if (alien->x_min <= 1) return false;
    case right: if (alien->x_max >= 798) return false;
    default: break;
  }
  return true;
}

bool (can_alien_group_move)(AlienGroup* group, enum direction dir) {
  for (int i = 0; i < group->size; i++) if (group->set[i].alive && !can_alien_move(&(group->set[i]), dir)) return false;
  return true;
}

bool (was_i_hit_alien)(Alien* alien, Shot* shot) {
  return shot->x_min <= alien->x_max && shot->x_max >= alien->x_min && shot->y_min <= alien->y_max - 40;
}

int (hit_index)(AlienGroup* group, Shot* shot) {
  for (int i = 0; i < group->size; i++) if (was_i_hit_alien(&(group->set[i]), shot) && group->set[i].alive) return i;
  return -1;
}

void (draw_alien)(Alien* alien) {
  switch (alien->id / 10) {
    case 0: video_draw_xpm(alien->x_min, alien->y_min, "alien1"); break;
    case 1: video_draw_xpm(alien->x_min, alien->y_min, "alien2"); break;
    case 2: video_draw_xpm(alien->x_min, alien->y_min, "alien3"); break;
    case 3: video_draw_xpm(alien->x_min, alien->y_min, "alien4"); break;
    case 4: video_draw_xpm(alien->x_min, alien->y_min, "alien5"); break;
    default: break;
  }
  for (int i = 0; i < alien->shots_no; i++) draw_shot(&(alien->shots[i]));
}

void (draw_aliens)(AlienGroup* group) {
  for (int i = 0; i < group->size; i++) {
    if (group->set[i].alive) draw_alien(&(group->set[i]));
  }
}
