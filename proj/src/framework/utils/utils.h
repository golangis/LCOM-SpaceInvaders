#ifndef UTILS_H
#define UTILS_H

#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @file utils.h
 * @brief Set of auxiliary functions to be used in the framework.
 * 
 */

/**
 * @brief Gets a 16-bit value's least significant byte.
 * @param val Value to get the LSB from.
 * @param lsb Variable to store the LSB.
 * @return int 0 upon success, non-zero otherwise
 */
int (util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Gets a 16-bit value's most significant byte.
 * @param val Value to get the MSB from.
 * @param msb Variable to store the MSB.
 * @return int 0 upon success, non-zero otherwise
 */
int (util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 * @brief Reads a byte from a given port.
 * @param port Port to read from.
 * @param value Variable to store the byte read from the port.
 */
int (ut_sys_inb)(int port, uint8_t* value);

/**
 * @brief Converts a given value in BCD to binary. Got the function body from https://github.com/Fabio-A-Sa/Y2S2-LabComputadores/tree/main/Labs/lab6#bcd-vs-bin%C3%A1rio.
 * @param value Value to convert.
 * @return uint8_t Converted value in binary.
 */
uint8_t (bcd_to_bin)(uint8_t value);

#endif
