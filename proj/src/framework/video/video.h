#ifndef VIDEO_H
#define VIDEO_H

/**
 * @file video.h
 * @brief Functions for programming the video card. Also contains variables to store the xpm images and maps drawn in the app.
 * 
 */

#include <lcom/lcf.h>

#include <string.h>

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

#include "xpm/algarisms.xpm"
#include "xpm/aliens.xpm"
#include "xpm/heart.xpm"
#include "xpm/logo.xpm"
#include "xpm/mouse.xpm"
#include "xpm/play-button.xpm"
#include "xpm/rocket.xpm"
#include "xpm/score.xpm"
#include "xpm/shield.xpm"
#include "xpm/shot.xpm"
#include "xpm/GameOver.xpm"

xpm_image_t zero_img;
xpm_image_t one_img;
xpm_image_t two_img;
xpm_image_t three_img;
xpm_image_t four_img;
xpm_image_t five_img;
xpm_image_t six_img;
xpm_image_t seven_img;
xpm_image_t eight_img;
xpm_image_t nine_img;
xpm_image_t alien1_img;
xpm_image_t alien2_img;
xpm_image_t alien3_img;
xpm_image_t alien4_img;
xpm_image_t alien5_img;
xpm_image_t heart_img;
xpm_image_t heart_bad_img;
xpm_image_t logo_img;
xpm_image_t mouse_img;
xpm_image_t play_button_img;
xpm_image_t rocket_img;
xpm_image_t score_img;
xpm_image_t shield3_img;
xpm_image_t shield2_img;
xpm_image_t shield1_img;
xpm_image_t ship_shot_img;
xpm_image_t alien_shot_img;
xpm_image_t gameOver_img;

uint8_t* zero_map;
uint8_t* one_map;
uint8_t* two_map;
uint8_t* three_map;
uint8_t* four_map;
uint8_t* five_map;
uint8_t* six_map;
uint8_t* seven_map;
uint8_t* eight_map;
uint8_t* nine_map;
uint8_t* alien1_map;
uint8_t* alien2_map;
uint8_t* alien3_map;
uint8_t* alien4_map;
uint8_t* alien5_map;
uint8_t* heart_map;
uint8_t* heart_bad_map;
uint8_t* logo_map;
uint8_t* mouse_map;
uint8_t* play_button_map;
uint8_t* rocket_map;
uint8_t* score_map;
uint8_t* shield3_map;
uint8_t* shield2_map;
uint8_t* shield1_map;
uint8_t* ship_shot_map;
uint8_t* alien_shot_map;
uint8_t* gameOver_map;

/**
 * @brief Initializes the video card in the given mode and maps the VRAM.
 * @param mode Mode to initialize the video card in.
 */
void* (video_init)(uint16_t mode);

/**
 * @brief Sets the pixel at the given coordinates to the given color.
 * @param x X coordinate of the pixel.
 * @param y Y coordinate of the pixel.
 * @param color Color to set the pixel to.
 */
void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Loads the XPM images used in the app.
 * 
 */
void (video_load_xpms)();

/**
 * @brief Draws a XPM image with the leftmost upper pixel at the given coordinates.
 * @param x X coordinate of the leftmost upper pixel.
 * @param y Y coordinate of the leftmost upper pixel.
 * @param xpm Name of the XPM image to draw.
 */
void (video_draw_xpm)(uint16_t x, uint16_t y, char xpm[]);

#endif
