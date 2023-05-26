#include <lcom/lcf.h>

#include "video.h"

#include "xpm/zero.xpm"
#include "xpm/um.xpm"
#include "xpm/dois.xpm"
#include "xpm/tres.xpm"
#include "xpm/quatro.xpm"
#include "xpm/cinco.xpm"
#include "xpm/seis.xpm"
#include "xpm/sete.xpm"
#include "xpm/oito.xpm"
#include "xpm/nove.xpm"

void* (video_init)(uint16_t mode) {
    vbe_mode_info_t info;
    if (vbe_get_mode_info(mode, &info) != 0) return NULL;

    struct minix_mem_range mr;
    int vram_base = info.PhysBasePtr;
    int vram_size = info.XResolution * info.YResolution * ((info.BitsPerPixel + 7)/8);
    int r;

    mr.mr_base = (phys_bytes) vram_base;	
    mr.mr_limit = mr.mr_base + vram_size;  

    if(OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED) panic("couldn't map video memory");

    h_res = info.XResolution;
    v_res = info.YResolution;
    bits_per_pixel = info.BitsPerPixel;
    bytes_per_pixel = (bits_per_pixel + 7)/8;

    RedMaskSize = info.RedMaskSize;
    GreenMaskSize = info.GreenMaskSize;
    BlueMaskSize = info.BlueMaskSize;

    RedFieldPosition = info.RedFieldPosition;
    GreenFieldPosition = info.GreenFieldPosition;
    BlueFieldPosition = info.BlueFieldPosition;

    video_buffer = (uint8_t*) malloc(h_res*v_res*bytes_per_pixel);

    reg86_t r_86;
    memset(&r_86, 0, sizeof(r_86));
    r_86.ax = 0x4F02;
    r_86.bx = (1<<14) | mode;
    r_86.intno = 0x10;
    if (sys_int86(&r_86) != OK) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }
    
    return 0;
}

void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x < 0 || x >= h_res || y < 0 || y >= v_res) return;
    uint8_t* pixel_mem = (uint8_t*)video_buffer + (x * bytes_per_pixel) + (y * h_res * bytes_per_pixel);

    for (uint8_t i = 0; i < bytes_per_pixel; i++) {
        *(pixel_mem + i) = (uint8_t) (color & 0xff);
        color >>= 8;
    }
}

void (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (uint16_t i = 0; i < len; i++) video_draw_pixel(x+i, y, color);
}

void (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (uint16_t i = 0; i < height; i++) video_draw_hline(x, y+i, width, color);
}

void (video_draw_xpm)(uint16_t x, uint16_t y, xpm_map_t xpm) {
    xpm_image_t img;
    uint8_t* map = xpm_load(xpm, XPM_8_8_8, &img);

    if (map == NULL) {
        printf("Error loading xpm\n");
        return;
    }

    for (uint16_t i = 0; i < img.width; i++) {
        for (uint16_t j = 0; j < img.height; j++) {
            uint32_t color = 0;

            for(int k = 0; k < 3; k++){
                color += ((uint32_t) map[j*img.width*3 + i*3 + k]) << (k*8);
            }

            video_draw_pixel(x + i, y + j, color);
        }
    }
}

void (video_draw_score)(uint16_t x, uint16_t y, int score){
    if(score < 10){
        loop_draw_score(x, y, score);
    }
    else if(score < 100){
        int second_half = score % 10;
        int first_half = score / 10;
        loop_draw_score(x, y, first_half);
        loop_draw_score(x + 17, y, second_half);    
    }
    else if(score < 1000){
        int third_half = score % 10;
        int second_half = (score / 10) % 10;
        int first_half = (score / 100) % 10;
        loop_draw_score(x, y, first_half);
        loop_draw_score(x + 17, y, second_half);
        loop_draw_score(x + 34, y, third_half);
    }
}

void (loop_draw_score)(uint16_t x, uint16_t y, int score) {
    switch(score){
        case 0:
            video_draw_xpm(x, y, zero_xpm);
            break;
        case 1:
            video_draw_xpm(x, y, um_xpm);
            break;
        case 2:
            video_draw_xpm(x, y, dois_xpm);
            break;
        case 3:
            video_draw_xpm(x, y, tres_xpm);
            break;
        case 4:
            video_draw_xpm(x, y, quatro_xpm);
            break;            
        case 5:
            video_draw_xpm(x, y, cinco_xpm);
            break;    
        case 6:
            video_draw_xpm(x, y, seis_xpm);
            break;
        case 7:
            video_draw_xpm(x, y, sete_xpm);
            break;        
        case 8:
            video_draw_xpm(x, y, oito_xpm);
            break;    
        case 9:
            video_draw_xpm(x, y, nove_xpm);
            break;
        default:
            video_draw_xpm(x, y, zero_xpm);
            break;    
    } 
}
