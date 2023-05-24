#ifndef VIDEO_H
#define VIDEO_H

#include <lcom/lcf.h>

unsigned h_res;
unsigned v_res;
unsigned bits_per_pixel;
unsigned bytes_per_pixel;

uint8_t RedMaskSize;
uint8_t GreenMaskSize;
uint8_t BlueMaskSize;

uint8_t RedFieldPosition;
uint8_t GreenFieldPosition;
uint8_t BlueFieldPosition;

char* video_mem;
uint8_t* video_buffer;

void* (video_init)(uint16_t mode);
void (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
void (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
void (video_draw_xpm)(uint16_t x, uint16_t y, xpm_map_t xpm);
void (video_draw_score)(uint16_t x, uint16_t y, int score);

#endif
