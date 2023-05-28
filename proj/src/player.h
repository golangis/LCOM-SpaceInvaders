#ifndef PLAYER_H
#define PLAYER_H

/**
 * @file player.h
 * @brief Represents and manipulates the game's player (space ship).
 * Note: The terms "Ship" and "Player" are used interchangeably.
 */

#include "direction.h"
#include "shot.h"

#include "framework/video/video.h"

/**
 * @brief Represents a player (space ship) by its coordinates, lives, score and fired shots that are still active (inside the screen borders or that did not kill any alien or damaged any shield.)
 * 
 */
typedef struct {
    int x_min;
    int y_min;
    int x_max;
    int y_max;
    int lives;
    int score;
    Shot* shots;
    int shots_no;
} Player;

/**
 * @brief Initializes a Player (space ship).
 * @return A pointer to the initialized Player.
 */
Player* (init_player)();

/**
 * @brief Moves a given player in the desired direction if possible.
 * @param ship Pointer to the player to be moved.
 * @param dir Direction to move the ship to.
 */
void (move_player)(Player* ship, enum direction dir);

/**
 * @brief Returns whether the given player can be moved in the given direction.
 * @param ship Pointer to the player to be checked.
 * @param dir Direction to be checked.
 * @return Whether the given player can be moved to the given direction.
 */
bool (can_player_move)(Player* ship, enum direction dir);

/**
 * @brief Creates a shot fired from the given player, according to its coordinates.
 * @param ship Pointer to the ship that will fire.
 */
void (fire)(Player* ship);

/**
 * @brief Decrements the given player's lives by a unit.
 * @param ship Pointer to the ship that will loose a life.
 */
void (loose_life)(Player* ship);

/**
 * @brief Deletes a given player's shot with a given index within the active player's shots array.
 * @param ship Pointer to the ship whose shot will be deleted.
 * @param i Index, within the ship's active shots array, of the shot to be deleted.
 */
void (delete_player_shot)(Player* ship, int i);

/**
 * @brief Draws a player by its coordinates and corresponding XPM image.
 * @param ship Pointer to the ship to be drawn.
 */
void (draw_player)(Player* ship);

/**
 * @brief Increments the given player's score according to the id of the alien they killed, since the number of points earned depends on the alien's vertical position (reflected in its id).
 * @param ship Pointer to the ship whose score will be incremented.
 * @param id Id of the alien the player killed.
 */
void (increment_score)(Player* ship, int id);

/**
 * @brief Draws the given player's score in the screen.
 * @param ship Pointer to the player whose score will be drawn. 
 */
void (draw_score)(Player* ship);

/**
 * @brief Auxiliary function to draw the score.
 * @param x Upper leftmost x coordinate.
 * @param y Upper leftmost y coordinate.
 * @param score The value of the score to draw.
 * 
 */
void (draw_score_aux)(uint16_t x, uint16_t y, int score);

/**
 * @brief Draws the provided algarism's XPM image.
 * @param x Upper leftmost x coordinate.
 * @param y Upper leftmost y coordinate.
 * @param score Algarism to draw.
 */
void (loop_draw_score_aux)(uint16_t x, uint16_t y, int score);

/**
 * @brief Draws hearts representing the given (player's) lives.
 * @param lives The number of the lives which representation is to be drawn.
 * 
 */
void (draw_lives)(int lives);

#endif
