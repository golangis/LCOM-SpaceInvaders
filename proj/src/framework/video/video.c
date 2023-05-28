#include <lcom/lcf.h>

#include "video.h"

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

    video_load_xpms();
    
    return 0;
}

void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x < 0 || x >= h_res || y < 0 || y >= v_res || color == 0) return;
    uint8_t* pixel_mem = (uint8_t*)video_buffer + (x * bytes_per_pixel) + (y * h_res * bytes_per_pixel);

    for (uint8_t i = 0; i < bytes_per_pixel; i++) {
        *(pixel_mem + i) = (uint8_t) (color & 0xff);
        color >>= 8;
    }
}

void (video_load_xpms)() {
    h_map = xpm_load(h_xpm, XPM_8_8_8, &h_img);
    slash_map = xpm_load(slash_xpm, XPM_8_8_8, &slash_img);
    zero_map = xpm_load(zero_xpm, XPM_8_8_8, &zero_img);
    one_map = xpm_load(one_xpm, XPM_8_8_8, &one_img);
    two_map = xpm_load(two_xpm, XPM_8_8_8, &two_img);
    three_map = xpm_load(three_xpm, XPM_8_8_8, &three_img);
    four_map = xpm_load(four_xpm, XPM_8_8_8, &four_img);
    five_map = xpm_load(five_xpm, XPM_8_8_8, &five_img);
    six_map = xpm_load(six_xpm, XPM_8_8_8, &six_img);
    seven_map = xpm_load(seven_xpm, XPM_8_8_8, &seven_img);
    eight_map = xpm_load(eight_xpm, XPM_8_8_8, &eight_img);
    nine_map = xpm_load(nine_xpm, XPM_8_8_8, &nine_img);
    alien1_map = xpm_load(alien1_xpm, XPM_8_8_8, &alien1_img);
    alien2_map = xpm_load(alien2_xpm, XPM_8_8_8, &alien2_img);
    alien3_map = xpm_load(alien3_xpm, XPM_8_8_8, &alien3_img);
    alien4_map = xpm_load(alien4_xpm, XPM_8_8_8, &alien4_img);
    alien5_map = xpm_load(alien5_xpm, XPM_8_8_8, &alien5_img);
    heart_map = xpm_load(heart_xpm, XPM_8_8_8, &heart_img);
    heart_bad_map = xpm_load(heart_bad_xpm, XPM_8_8_8, &heart_bad_img);
    logo_map = xpm_load(logo_xpm, XPM_8_8_8, &logo_img);
    mouse_map = xpm_load(mouse_xpm, XPM_8_8_8, &mouse_img);
    play_button_map = xpm_load(play_button_xpm, XPM_8_8_8, &play_button_img);
    rocket_map = xpm_load(rocket_xpm, XPM_8_8_8, &rocket_img);
    score_map = xpm_load(score_xpm, XPM_8_8_8, &score_img);
    shield3_map = xpm_load(shield3_xpm, XPM_8_8_8, &shield3_img);
    shield2_map = xpm_load(shield2_xpm, XPM_8_8_8, &shield2_img);
    shield1_map = xpm_load(shield1_xpm, XPM_8_8_8, &shield1_img);
    ship_shot_map = xpm_load(ship_shot_xpm, XPM_8_8_8, &ship_shot_img);
    alien_shot_map = xpm_load(alien_shot_xpm, XPM_8_8_8, &alien_shot_img);
    gameOver_map = xpm_load(gameOver_xpm, XPM_8_8_8, &gameOver_img);
}

void (video_draw_xpm)(uint16_t x, uint16_t y, char xpm[]) {
    uint8_t* map;
    xpm_image_t img;

    if (strcmp(xpm, "h") == 0) {
        map = h_map;
        img = h_img;
    } else if (strcmp(xpm, "slash") == 0) {
        map = slash_map;
        img = slash_img;
    } else if (strcmp(xpm, "zero") == 0) {
        map = zero_map;
        img = zero_img;
    } else if (strcmp(xpm, "one") == 0) {
        map = one_map;
        img = one_img;
    } else if (strcmp(xpm, "two") == 0) {
        map = two_map;
        img = two_img;
    } else if (strcmp(xpm, "three") == 0) {
        map = three_map;
        img = three_img;
    } else if (strcmp(xpm, "four") == 0) {
        map = four_map;
        img = four_img;
    } else if (strcmp(xpm, "five") == 0) {
        map = five_map;
        img = five_img;
    } else if (strcmp(xpm, "six") == 0) {
        map = six_map;
        img = six_img;
    } else if (strcmp(xpm, "seven") == 0) {
        map = seven_map;
        img = seven_img;
    } else if (strcmp(xpm, "eight") == 0) {
        map = eight_map;
        img = eight_img;
    } else if (strcmp(xpm, "nine") == 0) {
        map = nine_map;
        img = nine_img;
    } else if (strcmp(xpm, "alien1") == 0) {
        map = alien1_map;
        img = alien1_img;
    } else if (strcmp(xpm, "alien2") == 0) {
        map = alien2_map;
        img = alien2_img;
    } else if (strcmp(xpm, "alien3") == 0) {
        map = alien3_map;
        img = alien3_img;
    } else if (strcmp(xpm, "alien4") == 0) {
        map = alien4_map;
        img = alien4_img;
    } else if (strcmp(xpm, "alien5") == 0) {
        map = alien5_map;
        img = alien5_img;
    } else if (strcmp(xpm, "heart") == 0) {
        map = heart_map;
        img = heart_img;
    } else if (strcmp(xpm, "heart_bad") == 0) {
        map = heart_bad_map;
        img = heart_bad_img;
    } else if (strcmp(xpm, "logo") == 0) {
        map = logo_map;
        img = logo_img;
    } else if (strcmp(xpm, "mouse") == 0) {
        map = mouse_map;
        img = mouse_img;
    } else if (strcmp(xpm, "play_button") == 0) {
        map = play_button_map;
        img = play_button_img;
    } else if (strcmp(xpm, "rocket") == 0) {
        map = rocket_map;
        img = rocket_img;
    } else if (strcmp(xpm, "score") == 0) {
        map = score_map;
        img = score_img;
    } else if (strcmp(xpm, "shield3") == 0) {
        map = shield3_map;
        img = shield3_img;
    } else if (strcmp(xpm, "shield2") == 0) {
        map = shield2_map;
        img = shield2_img;
    } else if (strcmp(xpm, "shield1") == 0) {
        map = shield1_map;
        img = shield1_img;
    } else if (strcmp(xpm, "ship_shot") == 0) {
        map = ship_shot_map;
        img = ship_shot_img;
    } else if (strcmp(xpm, "alien_shot") == 0) {
        map = alien_shot_map;
        img = alien_shot_img;
    } else if (strcmp(xpm, "gameOver") == 0) {
        map = gameOver_map;
        img = gameOver_img;
    }    
    else return;

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
