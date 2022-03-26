#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "TGL.h"

void tgl_gotoxy(int32_t x, int32_t y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void tgl_swap(Pixel **buf1, Pixel **buf2) {
	Pixel *temp = *buf1;
	*buf1 = *buf2;
	*buf2 = temp;
}

void renderer_makenew(Renderer *renderer) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    renderer->mode = FILL;
    renderer->sym = '#';
    renderer->col = (Color) { 0, 0, FALSE };
    renderer->SCR_W = w.ws_col;
    renderer->SCR_H = w.ws_row;
    renderer->SCR_SZ = w.ws_col * w.ws_row;
    renderer->back = calloc(renderer->SCR_SZ, sizeof(Pixel));
    renderer->front = calloc(renderer->SCR_SZ, sizeof(Pixel));
}

void renderer_destroy(Renderer *renderer) {
    free(renderer->back);
    free(renderer->front);
}

void renderer_present(Renderer *renderer) {
    for (int y = 0; y < renderer->SCR_H; y++) {
        for (int x = 0; x < renderer->SCR_W; x++) {
            tgl_gotoxy(x, y);
            printf("\e[0;%dm", renderer->front[y*renderer->SCR_W+x].col.bg);
            printf("\e[%d;%dm", renderer->front[y*renderer->SCR_W+x].col.bold, renderer->front[y*renderer->SCR_W+x].col.fg);
            putchar(renderer->front[y*renderer->SCR_W+x].sym);
            printf("\e[0;m");
        }
    }
    tgl_swap(&(renderer->back), &(renderer->front));
}

void renderer_setpixel(Renderer *renderer, char sym, FG_COLOR fg, BG_COLOR bg) {
    renderer->sym = sym;
    renderer->col.fg = fg;
    renderer->col.bg = bg;
}

void clrscr(Renderer *renderer) {
    for (int i = 0; i < renderer->SCR_SZ; i++)
		renderer->back[i] = (Pixel) { 0, renderer->col };
}