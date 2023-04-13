#include <lcom/lcf.h>

void* (vg_init)(uint16_t mode) {
    vbe_mode_info_t info;
    if (vbe_get_mode_info(mode, &info) != 0) return NULL;

    reg86_t r_86;
    memset(&r_86, 0, sizeof(r_86));
    r_86.ax = 0x4F02;
    r_86.bx = (1<<14) | mode;
    r_86.intno = 0x10;
    if (sys_int86(&r_86) != OK) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }

    void *video_mem;

    struct minix_mem_range mr;
    unsigned int vram_base = info.PhysBasePtr;
    unsigned int vram_size = info.XResolution * info.YResolution * ((info.BitsPerPixel + 7)/8);
    int r;

    mr.mr_base = (phys_bytes) vram_base;	
    mr.mr_limit = mr.mr_base + vram_size;  

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

    //memset(video_mem, 0xff, vram_size);

    return video_mem;
}
