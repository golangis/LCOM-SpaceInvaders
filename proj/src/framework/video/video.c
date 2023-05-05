#include <lcom/lcf.h>

#include "video.h"

void* (video_init)(uint16_t mode) {
    vbe_mode_info_t info;
    if (vbe_get_mode_info(mode, &info) != 0) return NULL;

    struct minix_mem_range mr;
    unsigned int vram_base = info.PhysBasePtr;
    unsigned int vram_size = info.XResolution * info.YResolution * ((info.BitsPerPixel + 7)/8);
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

int (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    uint8_t* pixel_mem = (uint8_t*)video_buffer + (x * bytes_per_pixel) + (y * h_res * bytes_per_pixel);

    for (uint8_t i = 0; i < bytes_per_pixel; i++) {
        *(pixel_mem + i) = (uint8_t) (color & 0xff);
        color >>= 8;
    }

    return 0;
}

int (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (uint16_t i = 0; i < len; i++) {
        if (video_draw_pixel(x+i, y, color) != 0) return 1;
    }
    return 0;
}

int (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (uint16_t i = 0; i < height; i++) {
        if (video_draw_hline(x, y+i, width, color) != 0) return 1;
    }
    //memcpy(video_mem, buffer, h_res*v_res*bytes_per_pixel);
    //sleep(2);
    return 0;
}

int (video_draw_xpm)(uint16_t x, uint16_t y, xpm_map_t xpm) {
    xpm_image_t img;
    uint8_t* map = xpm_load(xpm, XPM_INDEXED, &img);

    for (uint8_t i = 0; i < img.width; i++) {
        for (uint8_t j = 0; j < img.height; j++) {
            video_draw_pixel(x + i, y + j, *(map + ((i + (j * img.width)) * bytes_per_pixel)));
        }
    }

    //memcpy(video_mem, buffer, h_res*v_res*bytes_per_pixel);
    //sleep(3);
    return 0;
}