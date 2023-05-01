#ifndef __TIMER_H
#define __TIMER_H
  
#include <stdbool.h>
#include <stdint.h>
  
enum timer_init {
   INVAL_val,    
   LSB_only,     
   MSB_only,     
   MSB_after_LSB 
};
  
enum timer_status_field {
   tsf_all,     
   tsf_initial, 
   tsf_mode,    
   tsf_base     
};
    
union timer_status_field_val {
   uint8_t byte;            
   enum timer_init in_mode; 
   uint8_t count_mode;      
   bool bcd;                
};
  
int(timer_set_frequency)(uint8_t timer, uint32_t freq);
  
int(timer_subscribe_int)(uint8_t *bit_no);
  
int(timer_unsubscribe_int)();
  
void(timer_int_handler)();
  
int(timer_get_conf)(uint8_t timer, uint8_t *st);
  
int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);
  
int(timer_print_config)(uint8_t timer, enum timer_status_field field,
                         union timer_status_field_val val);
  
uint32_t(timer_print_elapsed_time)();
  
#endif /* __TIMER_H */