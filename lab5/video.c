// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

static unsigned h_res;
static unsigned v_res;
static unsigned bits_per_pixel;
static unsigned bytes_per_pixel;

static bool dir_ind;

static uint8_t RedMaskSize;
static uint8_t GreenMaskSize;
static uint8_t BlueMaskSize;

static uint8_t RedFieldPosition;
static uint8_t GreenFieldPosition;
static uint8_t BlueFieldPosition;

static uint8_t* buffer;


void* (vg_init)(uint16_t mode){
  vbe_mode_info_t info;
  if(vbe_get_mode_info(mode, &info) != 0) return NULL;
  static void *video_mem;         

  struct minix_mem_range mr;
  unsigned int vram_base = info.PhysBasePtr;  
  unsigned int vram_size = info.XResolution * info.YResolution * ((info.BitsPerPixel + 7)/8);  
  int r;				    

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED) panic("couldn't map video memory");

  h_res = info.XResolution;
  v_res = info.YResolution;
  bits_per_pixel = info.BitsPerPixel;
  bytes_per_pixel = (info.BitsPerPixel + 7) / 8;

  if(mode == 0x105) dir_ind = false;
  else dir_ind = true;

  RedMaskSize = info.RedMaskSize;
  BlueMaskSize = info.BlueMaskSize;
  GreenMaskSize = info.BlueMaskSize;

  RedFieldPosition = info.RedFieldPosition;
  GreenFieldPosition = info.GreenFieldPosition;
  BlueFieldPosition = info.BlueFieldPosition;

  buffer = (uint8_t*)malloc(vram_size);

  reg86_t r_86;
  memset(&r_86, 0, sizeof(r_86));
  r_86.ax = 0x4F02;
  r_86.bx = (1<<14) | mode;
  r_86.intno = 0x10;

  if( sys_int86(&r_86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return NULL;
  }

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(uint16_t i = 0; i < height; i++){
    if(vg_draw_hline(x, y + i, width, color) != 0) return 1;
  }
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t width, uint32_t color){
  for(uint16_t i = 0; i < width; i++){
    if(vg_draw_pixel(x+i, y, color) != 0) return 1;
  }
}