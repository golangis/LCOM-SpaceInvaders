#include <lcom/lcf.h>

static char* video_mem;

static unsigned h_res;
static unsigned v_res;
static unsigned bits_per_pixel;
static unsigned bytes_per_pixel;

static char direct_or_indexed;

static uint8_t RedMaskSize;
static uint8_t GreenMaskSize;
static uint8_t BlueMaskSize;

static uint8_t RedFieldPosition;
static uint8_t GreenFieldPosition;
static uint8_t BlueFieldPosition;

static uint8_t* buffer;

void* (vg_init)(uint16_t mode) {
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

    if (mode == 0x105) direct_or_indexed = 'i';
    else direct_or_indexed = 'd';
    //direct_or_indexed = (mode == 0x105)? 'i' : 'd';

    RedMaskSize = info.RedMaskSize;
    GreenMaskSize = info.GreenMaskSize;
    BlueMaskSize = info.BlueMaskSize;

    RedFieldPosition = info.RedFieldPosition;
    GreenFieldPosition = info.GreenFieldPosition;
    BlueFieldPosition = info.BlueFieldPosition;

    buffer = (uint8_t*) malloc(h_res*v_res*bytes_per_pixel);

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

uint8_t (vg_get_red)(uint32_t color) {
    color <<= 8;
    return color >> 24;
}

uint8_t (vg_get_green)(uint32_t color) {
    color <<= 16;
    return color >> 24;
}

uint8_t (vg_get_blue)(uint32_t color) {
    color <<= 24;
    return color >> 24;
}

uint8_t (vg_get_alpha)(uint32_t color) {
    return color >> 24;
}

uint32_t (vg_build_color)(uint32_t color) {
    uint32_t red = (uint32_t) vg_get_red(color);
    uint32_t green = (uint32_t) vg_get_green(color);
    uint32_t blue = (uint32_t) vg_get_blue(color);

    uint32_t c = 0;
    
    uint8_t red_mask = 0;
    uint8_t green_mask = 0;
    uint8_t blue_mask = 0;

    for (int i = 0; i < RedMaskSize; i++) {
        red_mask |= BIT(i);
    }

    for (int i = 0; i < GreenMaskSize; i++) {
        green_mask |= BIT(i);
    }

    for (int i = 0; i < BlueMaskSize; i++) {
        blue_mask |= BIT(i);
    }

    red &= red_mask;
    green &= green_mask;
    blue &= blue_mask;

    red <<= RedFieldPosition;
    green <<= GreenFieldPosition;
    blue <<= BlueFieldPosition;

    c = (red | green | blue);

    return c;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    uint8_t* pixel_mem = (uint8_t*)buffer + (x * bytes_per_pixel) + (y * h_res * bytes_per_pixel);

    if (direct_or_indexed == 'i') {
        *pixel_mem = (uint8_t) color;
        return 0;
    }

    color = vg_build_color(color);
    
    for (uint8_t i = 0; i < bytes_per_pixel; i++) {
        *(pixel_mem + i) = (uint8_t) color;
        color >>= 8;
    }

    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (uint16_t i = 0; i < len; i++) {
        if (vg_draw_pixel(x+i, y, color) != 0) return 1;
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (uint16_t i = 0; i < height; i++) {
        if (vg_draw_hline(x, y+i, width, color) != 0) return 1;
    }
    memcpy(video_mem, buffer, h_res*v_res*bytes_per_pixel);
    sleep(2);
    return 0;
}

int (vg_draw_matrix)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    return 1;
}
