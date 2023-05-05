#include "alien.h"

void initAliens(){
  Alien* first = (Alien*) malloc (sizeof(Alien) * 30);
  AlienGroup* group = (AlienGroup*) malloc (sizeof(AlienGroup));
  group->size = 30;
}
