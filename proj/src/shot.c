#include "shot.h"

Shot (init_shot)(int x_min, int y_min, enum shot_source source) {
  Shot shot;
  /*
  width = 20px
  height = 40px;
  */
  shot.x_min = x_min;
  shot.x_max = x_min + 20;
  shot.y_min = y_min;
  shot.y_max = y_min + 40;
  shot.source = source;

  return shot;
}

void (move_shot)(Shot* shot) {
  switch (shot->source) {
    case alien:
      shot->y_min += 5;
      shot->y_max += 5;
      break;
    case player:
      shot->y_min -= 10;
      shot->y_max -= 10;
      break;
    default: break;
  }
}

void (draw_shot)(Shot* shot) {
  switch (shot->source) {
    case alien: video_draw_xpm(shot->x_min, shot->y_max, "alien_shot"); break;
    case player: video_draw_xpm(shot->x_min, shot->y_max, "ship_shot"); break;
    default: break;
  }
}
