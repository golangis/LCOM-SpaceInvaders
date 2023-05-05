#include "draw.h"

void draw() {
  drawShield(shield1);
  drawShield(shield2);
  drawShield(shield3);

  memcpy(video_mem, video_buffer, h_res*v_res*bytes_per_pixel);
}
