#include "spaceinvaders.h"

typedef struct Shot {
    int x;
    int y;
};

void move(Shot* shot, direction direction);
void draw(Shot* shot);
