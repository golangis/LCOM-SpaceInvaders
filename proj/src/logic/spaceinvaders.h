#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

/**
 * @file spaceinvaders.h
 * @brief Game logic functions. Stores the game elements and assures the interaction between them.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "framework/video/video.h"
#include "framework/mouse/mouse.h"
#include "framework/rtc/rtc.h"

#include "logic/alien.h"
#include "logic/player.h"
#include "logic/shield.h"
#include "logic/shot.h"

#include "logic/direction.h"

extern char* video_mem;
extern uint8_t* vg_buffer;
extern unsigned h_res;
extern unsigned v_res;
extern unsigned bytes_per_pixel;

Player* ship;
Shield* shield1;
Shield* shield2;
Shield* shield3;
AlienGroup* aliens;
Shot* shots;
int wave;

enum direction last_alien_mov;
unsigned int updates;

/**
 * @brief A struct to represent a score by its number of points and the date and time it was achieved.
 * 
 */
typedef struct {
  int points;
  char datetime[17];
} Score;

/**
 * @brief Initializes the game elements.
 * 
 */
void (init_game)();

/**
 * @brief Loads information from the file the top-10 highscores are stored in, parses them into Score struct instances and returns them in an array.
 * The file reading was adapted from https://www.geeksforgeeks.org/relational-database-from-csv-files-in-c/.
 * 
 * NOTE: The file path must be absolute.
 * @returns Dinamically alocated array of read scores.
 */
Score* (load_scores)();

/**
 * @brief Builds a Score struct instance according to a given points number and rtc_time struct instance.
 * @param points Number of the score's points.
 * @param time rtc_time struct instance representing the date and time the score was achieved.
 * @return Built score struct instance.
 */
Score (build_score)(int points, rtc_time* time);

/**
 * @brief Processes a score and determines if it is elegible to be amongst the top-10. If so, stores it in the scores array and returns true, returning false otherwise.
 * @param score The score to be processed.
 * @param array Current top-10 scores array.
 * @return Whether the given score is elegible to be amongst the top-10.
 */
bool (process_score)(Score score, Score* array);

/**
 * @brief Stores the given score array in the highscores file.
 * File writing adapted from https://www.programiz.com/c-programming/c-file-input-output.
 * NOTE: The file path must be absolute.
 * @param array Array of the scores to be stored.
 */
void (store_scores)(Score* array);

/**
 * @brief General game drawing function.
 * Calls the elements' respective drawing functions.
 */
void (draw)();

/**
 * @brief Updates the game's elements position (if appliable), checks colisions and updates the involved elements' lives/state.
 * @param no_lives Current number of the game's player lives.
 */
void (update)(int* no_lives);

/**
 * @brief Draws the main menu.
 * 
 */
void (draw_main_menu)();

/**
 * @brief Draws the highscore page, given a pre-generated top-10 score array.
 * @param scores Array with the top-10 scores to be drawn.
 */
void (draw_high_scores)(Score* scores);

/**
 * @brief Draws the game over menu.
 * 
 */
void (draw_game_over_menu)();

/**
 * @brief Regenerates all the aliens when a new game wave is started.
 * 
 */
void (reload_aliens)();

/**
 * @brief Possible app states, on which the artifacts to draw and the logic depends.
 * 
 */
enum state {
  game,
  mainMenu,
  highscores,
  quit,
  gameOverMenu
};

#endif
