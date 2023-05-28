#ifndef SHIELD_H
#define SHIELD_H

#include "framework/video/video.h"

#include "shot.h"

/**
 * @file shield.h
 * 
 * @brief Represents and manipulates the game's shields. 
 */

/**
 * @brief Represents a game's shield by its position (area/hitbox), lives and id.
 * The thickness of the shield in the screen is determined by its lives.
 */
typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int lives;
    int id;
} Shield;

/**
 * @brief Initializes a Shield with a given left uppermost x coordinate and id.
 * @param x_min Left uppermost x coordinate.
 * @param id Shield's id.
 * @return Pointer to the initialized shield.
 */
Shield* (init_shield)(int x_min, int id);

/**
 * @brief Draws a given shield according to its position and lives.
 * @param shield Pointer to the shield to be drawn.
 */
void (draw_shield)(Shield* shield);

/**
 * @brief Causes damage to a given shield (decrements its lives) and alters its coordinates to match the new thickness and mantain its center's position.
 * @param shield Pointer to the shield to be damaged.
 */
void (damage)(Shield* shield);

#endif
