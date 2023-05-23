#include "shot.h"

Shot (initShot)(int x, int y, enum shot_source source) {
  Shot shot;
  shot.x = x;
  shot.y = y;
  shot.source = source;

  return shot;
}

void (moveShot)(Shot* shot) {
  switch (shot->source) {
    case alien:
      shot->y += 2;
      break;
    case player:
      shot->y -= 2;
      break;
  }
}

void (drawShot)(Shot* shot) {
  video_draw_rectangle(shot->x, shot->y, 2, 20, 0xffffff);
}
