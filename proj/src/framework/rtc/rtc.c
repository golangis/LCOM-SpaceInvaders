#include "rtc.h"

int (rtc_write_control)(uint8_t addr) {
  return sys_outb(RTC_ADDR_REG, addr);
}

int (rtc_read)(uint8_t* data) {
  return ut_sys_inb(RTC_DATA_REG, data);
}

int (get_time)(rtc_time* time) {
  uint8_t regb = 0;
  if (rtc_write_control(RTC_REGISTER_B) != 0) return 1;
  if (rtc_read(&regb) != 0) return 1;

  uint8_t status = RTC_UIP;
  
  while (status & RTC_UIP) {
    if (rtc_write_control(RTC_REGISTER_A) != 0) return 1;
    if (rtc_read(&status) != 0) return 1;
  }

  uint8_t year = 0;
  uint8_t month = 0;
  uint8_t day = 0;
  uint8_t hour = 0;
  uint8_t minute = 0;

  if (rtc_write_control(RTC_YEAR_ADDR) != 0) return 1;
  if (rtc_read(&year) != 0) return 1;

  if (rtc_write_control(RTC_MONTH_ADDR) != 0) return 1;
  if (rtc_read(&month) != 0) return 1;

  if (rtc_write_control(RTC_DAY_ADDR) != 0) return 1;
  if (rtc_read(&day) != 0) return 1;

  if (rtc_write_control(RTC_HOURS_ADDR) != 0) return 1;
  if (rtc_read(&hour) != 0) return 1;

  if (rtc_write_control(RTC_MINUTES_ADDR) != 0) return 1;
  if (rtc_read(&minute) != 0) return 1;

  if (!(regb & RTC_DM)) {
    year = bcd_to_bin(year);
    month = bcd_to_bin(month);
    day = bcd_to_bin(day);
    hour = bcd_to_bin(hour);
    minute = bcd_to_bin(minute);
  }

  time->year = year;
  time->month = month;
  time->day = day;
  time->hour = hour;
  time->minute = minute;

  return 0;
}
