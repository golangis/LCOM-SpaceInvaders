#ifndef RTC_H
#define RTC_H

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

typedef struct {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
} rtc_time;

int (rtc_write_control)(uint8_t addr);
int (rtc_write_data)(uint8_t data);
int (rtc_read)(uint8_t* data);
int (get_time)(rtc_time* time);

#endif
