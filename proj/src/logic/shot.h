#ifndef SHOT_H
#define SHOT_H

#include "framework/video/video.h"

/**
 * @file shot.h
 * @brief Represents and manipulates the game's shots. 
 * 
 */

/**
 * @brief Represents possible shot sources (alien or player).
 * 
 */
enum shot_source {
    alien,
    player
};

/**
 * @brief Represents a Shot by its coordinates (area) and its source.
 * 
 */
typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    enum shot_source source;
} Shot;

/**
 * @brief Initializes a shot with given left uppermost coordinates and source.
 * @param x Left uppermost x coordinate.
 * @param y Left uppermost y coordinate.
 * @param source Shot source.
 * @return The generated and initialized shot.
 */
Shot (init_shot)(int x, int y, enum shot_source source);

/**
 * @brief Moves the given shot according to its source.
 * @param shot Pointer to the shot to be moved.
 */
void (move_shot)(Shot* shot);

/**
 * @brief Draws a given shot in the screen according to its position and source.
 * @param shot Pointer to the shot to be drawn.
 */
void (draw_shot)(Shot* shot);

#endif
