# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/framework/keyboard
.PATH: ${.CURDIR}/framework/mouse
.PATH: ${.CURDIR}/framework/rtc
.PATH: ${.CURDIR}/framework/timer
.PATH: ${.CURDIR}/framework/utils
.PATH: ${.CURDIR}/framework/video

# source code files to be compiled
SRCS = kbd.c rtc.c timer.c utils.c video.c alien.c main.c player.c shield.c shot.c spaceinvaders.c mouse.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>