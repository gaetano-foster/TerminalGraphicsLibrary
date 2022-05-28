#ifndef __TGL_H__
#define __TGL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "TGL_types.h"

#define SWAP(x, y)       \
	do                   \
	{                    \
		(x) = (x) ^ (y); \
		(y) = (x) ^ (y); \
		(x) = (x) ^ (y); \
	} while (0)
#define VEC2_GENERIC(type) \
	struct {               \
		type x, y;         \
	}

typedef struct _color {
	FG_COLOR fg;
	BG_COLOR bg;
	enum {
		FALSE,
		TRUE
	} bold;
} TGL_Color;

typedef struct _pixel {
	char sym;
	TGL_Color col;
} TGL_Pixel;

typedef struct _renderer
{
	char sym;
	TGL_Color col;
	enum {
		WIREFRAME,
		FILL
	} mode;
	TGL_Pixel *back, *front;  /* front and back buffers */
	int SCR_W, SCR_H, SCR_SZ; /* Screen width, screen height, screen size */
} TGL_Renderer;

typedef VEC2_GENERIC(i32) TGL_Vec2i;
typedef VEC2_GENERIC(float) TGL_Vec2f;

typedef struct _rect
{
	i32 x, y;
	i32 w, h;
} TGL_Rect;

typedef struct _tri
{
	TGL_Vec2i points[3];
} TGL_Tri;

typedef struct _cir
{
	i32 x, y;
	i32 rad;
} TGL_Circle;

void TGL_clrscr(TGL_Renderer *renderer);
void TGL_RendererMakeNew(TGL_Renderer *renderer);
void TGL_RendererDestroy(TGL_Renderer *renderer);
void TGL_RendererPresent(TGL_Renderer *renderer);
void TGL_SetRenderPixel(TGL_Renderer *renderer, char sym, FG_COLOR fg, BG_COLOR bg);
void TGL_RenderDrawPoint(TGL_Renderer *renderer, i32 x, i32 y);
void TGL_RenderDrawLine(TGL_Renderer *renderer, i32 x1, i32 y1, i32 x2, i32 y2);
void TGL_RenderDrawRect(TGL_Renderer *renderer, TGL_Rect rect);
void TGL_RenderDrawTri(TGL_Renderer *renderer, TGL_Tri tri);
void TGL_RenderDrawCircle(TGL_Renderer *renderer, TGL_Circle cir);

#ifdef __cplusplus
}
#endif
#endif // __TGL_H__