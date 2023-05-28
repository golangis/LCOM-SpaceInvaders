#ifndef RTC_H
#define RTC_H

/**
 * @file rtc.h
 * @brief Constants for programming the RTC. Functions of the RTC framework.
 * 
 */

#include <lcom/lcf.h>
#include "../utils/utils.h"

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define RTC_MINUTES_ADDR 2
#define RTC_HOURS_ADDR 4
#define RTC_DAY_ADDR 7
#define RTC_MONTH_ADDR 8
#define RTC_YEAR_ADDR 9

#define RTC_REGISTER_A 10
#define RTC_REGISTER_B 11

#define RTC_DM BIT(2)
#define RTC_UIP BIT(7)

/**
 * @brief Represents a time by its day, month, year, hour and minute.
 * 
 */
typedef struct {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
} rtc_time;

/**
 * @brief Writes a given address to be read from the RTC to the RTC's address register.
 * @param addr Address to be read later from the RTC.
 * @return int 0 upon success, non-zero otherwise
 */
int (rtc_write_control)(uint8_t addr);

/**
 * @brief Reads a byte from the RTC's data register.
 * @param data Variable to store the byte read from the RTC.
 * @return int 0 upon success, non-zero otherwise
 */
int (rtc_read)(uint8_t* data);

/**
 * @brief Gets the current time from the RTC and stores into a given rtc_time struct instance.
 * @param time Variable to store the read current time.
 * @return int 0 upon success, non-zero otherwise
 */
int (get_time)(rtc_time* time);

#endif
