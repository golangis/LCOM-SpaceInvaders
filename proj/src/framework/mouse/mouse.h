#ifndef MOUSE_H
#define MOUSE_H

/**
 * @file mouse.h
 * @brief Framework for the Mouse.
 * 
 */

#include <lcom/lcf.h>  
#include "../utils/utils.h"
#include "i8042.h"

/**
 * @brief Subscribes and enables Mouse interrupts.
 * @param bit_no Variable to store the mouse's hook id correspondent bit number.
 * @return int 0 upon success, non-zero otherwise
 */
int (subscribe_mouse_int)(uint8_t *bit_no);

/**
 * @brief Mouse interrupt handler. Gets the mouse packet and updates the user interface mouse struct.
 * @return int 0 upon success, non-zero otherwise
 */
int (mouse_interrupt_handler)();

/**
 * @brief Unsubscribes Mouse interrupts.
 * @return int 0 upon success, non-zero otherwise
 */
int (unsubscribe_mouse_int)();

/**
 * @brief Reads the mouse status byte.
 * @return int 0 upon success, non-zero otherwise
 */
int (readStatusByte)();

/**
 * @brief Reads and parses the packet from the mouse output buffer.
 * @return int 0 upon success, non-zero otherwise
 */
int (readPacket)();

/**
 * @brief Updates the user interface mouse.
 * @return int 0 upon success, non-zero otherwise
 */
int (update_mouse)();

#endif
