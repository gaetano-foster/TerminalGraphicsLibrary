#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "TGL.h"

void __gxy(i32 x, i32 y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void __swp(TGL_Pixel **buf1, TGL_Pixel **buf2) {
	TGL_Pixel *temp = *buf1;
	*buf1 = *buf2;
	*buf2 = temp;
}

void TGL_RendererMakeNew(TGL_Renderer *renderer) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    renderer->mode = FILL;
    renderer->sym = '#';
    renderer->col = (TGL_Color) { 0, 0, FALSE };
    renderer->SCR_W = w.ws_col;
    renderer->SCR_H = w.ws_row;
    renderer->SCR_SZ = w.ws_col * w.ws_row;
    renderer->back = calloc(renderer->SCR_SZ, sizeof(TGL_Pixel));
    renderer->front = calloc(renderer->SCR_SZ, sizeof(TGL_Pixel));
}

void TGL_RendererDestroy(TGL_Renderer *renderer) {
    free(renderer->back);
    free(renderer->front);
}

void TGL_RendererPresent(TGL_Renderer *renderer) {
    for (int y = 0; y < renderer->SCR_H; y++) {
        for (int x = 0; x < renderer->SCR_W; x++) {
            __gxy(x, y);
            printf("\e[0;%dm", renderer->front[y*renderer->SCR_W+x].col.bg);
            printf("\e[%d;%dm", renderer->front[y*renderer->SCR_W+x].col.bold, renderer->front[y*renderer->SCR_W+x].col.fg);
            putchar(renderer->front[y*renderer->SCR_W+x].sym);
            printf("\e[0;m");
        }
    }
    __swp(&(renderer->back), &(renderer->front));
}

void TGL_SetRenderPixel(TGL_Renderer *renderer, char sym, FG_COLOR fg, BG_COLOR bg) {
    renderer->sym = sym;
    renderer->col.fg = fg;
    renderer->col.bg = bg;
}

void TGL_clrscr(TGL_Renderer *renderer) {
    for (int i = 0; i < renderer->SCR_SZ; i++)
		renderer->back[i] = (TGL_Pixel) { 0, renderer->col };
}