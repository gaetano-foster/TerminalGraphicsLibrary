#ifndef CGL_H
#define CGL_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdint.h>

#define SWAP(x, y) 				do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)
#define VEC2_GENERIC(type)		struct { type x, y; }

typedef enum {
	FG_BLACK = 30,
	FG_RED,
	FG_GREEN,
	FG_YELLOW,
	FG_BLUE,
	FG_MAGENTA,
	FG_CYAN,
	FG_WHITE,
	FG_HBLACK = 90,
	FG_HRED,
	FG_HGREEN,
	FG_HYELLOW,
	FG_HBLUE,
	FG_HMAGENTA,
	FG_HCYAN,
	FG_HWHITE
} FG_COLOR;

typedef enum {
	BG_BLACK = 40,
	BG_RED,
	BG_GREEN,
	BG_YELLOW,
	BG_BLUE,
	BG_MAGENTA,
	BG_CYAN,
	BG_WHITE,
	BG_HBLACK = 100,
	BG_HRED,
	BG_HGREEN,
	BG_HYELLOW,
	BG_HBLUE,
	BG_HMAGENTA,
	BG_HCYAN,
	BG_HWHITE
} BG_COLOR;

typedef struct _color {
	FG_COLOR fg;
	BG_COLOR bg;
	enum { FALSE, TRUE } bold;
} Color;

typedef struct _pixel {
	char sym;
	Color col;
} Pixel;

typedef struct _renderer {
	char sym;
	Color col;
	enum { WIREFRAME, FILL } mode;
	Pixel *back, *front; /* front and back buffers */
	int SCR_W, SCR_H, SCR_SZ; /* Screen width, screen height, screen size */
} Renderer;
	
typedef VEC2_GENERIC(int32_t) Vec2i;
typedef VEC2_GENERIC(float) Vec2f;

typedef struct _rect {
	int32_t x, y;
	int32_t w, h;
} Rectangle;

typedef struct _tri {
	Vec2i points[3];
} Triangle;

typedef struct _cir {
    int32_t x, y;
    int32_t rad;
} Circle;

void clrscr(Renderer *renderer);
void renderer_makenew(Renderer *renderer);
void renderer_destroy(Renderer *renderer);
void renderer_present(Renderer *renderer);
void renderer_setpixel(Renderer *renderer, char sym, FG_COLOR fg, BG_COLOR bg);

void draw_point(Renderer *renderer, int32_t x, int32_t y);
void draw_line(Renderer *renderer, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void draw_rect(Renderer *renderer, Rectangle rect);
void draw_triangle(Renderer *renderer, Triangle tri);
void draw_circle(Renderer *renderer, Circle cir);


#ifdef __cplusplus
}
#endif
#endif
