#ifndef ALIEN_H
#define ALIEN_H

/**
 * @file alien.h
 * @brief Represent and manipulate the game's aliens.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "logic/direction.h"

#include "framework/video/video.h"

#include "logic/shot.h"

/**
 * @brief Represents a Space Invaders alien.
 * 
 */
typedef struct {
    int id;
    int x_min;
    int y_min;
    int x_max;
    int y_max;
    Shot* shots;
    int shots_no;
    bool alive;
} Alien;

/**
 * @brief Represents a group of Space Invaders aliens.
 * 
 */
typedef struct {
    Alien* set;
    int size;
    int alive_no;
} AlienGroup;

/**
 * @brief Initializes a group of aliens.
 * @return The initialized group of aliens.
 */
AlienGroup* (init_aliens)();

/**
 * @brief Initializes an alien with a given id and leftmost upper position.
 * @param id The alien's id.
 * @param x_min The alien's minimum x coordinate.
 * @param y_min The alien's minimum y coordinate.
 * @return The initialized alien.
 */
Alien (init_alien)(int id, int x_min, int y_min);

/**
 * @brief Moves a group of aliens in a given direction.
 * @param group The group of aliens to move.
 * @param dir The direction to move the aliens.
 */
void (move_aliens)(AlienGroup* group, enum direction dir);

/**
 * @brief Kills an alien with a given id from a group.
 * @param group The group of aliens.
 * @param i The id of the alien to kill.
 */
void (die_alien)(AlienGroup* group, int i);

/**
 * @brief Makes an alien shoot.
 * @param a The alien that will fire.
 */
void (shoot_alien)(Alien* a);

/**
 * @brief Makes a random alien within a group shoot.
 * @param group The group of aliens.
 */
void (shoot_aliens)(AlienGroup* group);

/**
 * @brief Deletes an alien's shot.
 * @param alien The alien that fired the shot.
 * @param i The index of the shot to delete within the alien's shots.
 */
void (delete_alien_shot)(Alien* alien, int i);

/**
 * @brief Returns whether an alien can move in a given direction.
 * @param alien The alien to check.
 * @param dir The direction to check.
 * @return Whether the alien can move in the given direction.
 */
bool (can_alien_move)(Alien* alien, enum direction dir);

/**
 * @brief Returns whether a group of aliens can move in a given direction.
 * @param group The group of aliens to check.
 * @param dir The direction to check.
 * @return Whether the group of aliens can move in the given direction.
 */
bool (can_alien_group_move)(AlienGroup* group, enum direction dir);

/**
 * @brief Returns whether a given alien was hit by a given shot.
 * @param alien The alien to check.
 * @param shot The shot to check.
 * @return Whether the alien was hit by the shot.
 */
bool (was_i_hit_alien)(Alien* alien, Shot* shot);

/**
 * @brief Checks if a given shot hit any alien within a group and returns the index of the hit alien.
 * @param group The group of aliens to check.
 * @param shot The shot to check.
 * @return The index of the hit alien or -1 if no alive alien was hit.
 */
int (hit_index)(AlienGroup* group, Shot* shot);

/**
 * @brief Draws a group of aliens.
 * @param group The group of aliens to draw. 
 */
void (draw_aliens)(AlienGroup* group);

/**
 * @brief Draws an alien.
 * @param alien The alien to draw.
 */
void (draw_alien)(Alien* alien);

#endif
