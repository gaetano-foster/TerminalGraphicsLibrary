#ifndef CGL_H
	#define CGL_H
	#ifdef __cplusplus
		extern "C" {
	#endif
	
	#include <stdio.h>
	#include <stdlib.h>
    #include <stddef.h>
	#include <stdint.h>
	
	#ifdef _WIN32
		#include <Windows.h>
		
		enum color 
        {
			CGL_WIN32, 
			CGL_DARK_BLUE, 
			CGL_GREEN, 
			CGL_DARK_CYAN, 
			CGL_DARK_RED, 
			CGL_DARK_MAGENTA, 
			CGL_DARK_YELLOW, 
			CGL_LIGHT_GREY, 
			CGL_GREY, 
			CGL_BLUE, 
			CGL_LIME, 
			CGL_CYAN, 
			CGL_RED, 
			CGL_MAGENTA, 
			CGL_YELLOW, 
			CGL_WHITE
		};

	#elif defined(unix) || defined(__unix__) || defined(__unix)
		
		enum color 
        {
			CGL_DARK_BLUE        = 34, 
			CGL_GREEN            = 32, 
			CGL_DARK_CYAN        = 36, 
			CGL_DARK_RED         = 31, 
			CGL_DARK_MAGENTA     = 35, 
			CGL_DARK_YELLOW      = 33, 
			CGL_LIGHT_GREY       = 37, 
			CGL_GREY             = 90, 
			CGL_BLUE             = 94, 
			CGL_LIME             = 92, 
			CGL_CYAN             = 96, 
			CGL_RED              = 91, 
			CGL_MAGENTA          = 95, 
			CGL_YELLOW           = 93, 
			CGL_WHITE            = 97
		};
  
	#endif

    #define SWAP(x, y) do { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); } while(0)
	
	/* To determine how CGL should render something. */
	enum render_mode 
    {
		CGL_WIREFRAME, 
		CGL_FILL
	};
	
	/* A point in space. */
	typedef struct 
    {
		int16_t x, y;
	} CGL_Coord;
	
	/* A rectangle. */
	typedef struct 
    {
		int16_t x, y;
		int16_t w, h;
	} CGL_Rect;
	
	/* A triangle. */
	typedef struct 
    {
		CGL_Coord points[3];
	} CGL_Triangle;
    
	/* A plolygon with an undefined amount of vertices. */
    typedef struct 
    {
        CGL_Coord *points, mid;
        size_t numpts;
    } CGL_Shape;
    
    /* A Circle */
    typedef struct
    {
        int x, y;
        int rad; // radius
    } CGL_Circle;
	
	/*  Function Definitions  */

	// handle.c
	void setcolor(uint8_t color);
	void gotopos(int16_t x, int16_t y); 
	void setchar(int16_t x, int16_t y, wchar_t character); 
	void lcd_hline(int16_t x1, int16_t x2, int16_t y, wchar_t character); // will only draw a horizontal line. It is faster
	void clrscr();
	
	// draw.c
	void drawrect(CGL_Rect rect, wchar_t fillchar, uint8_t mode);
	void drawline(int16_t x1, int16_t y1, int16_t x2, int16_t y2, wchar_t fillchar);
	void drawtriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, wchar_t fillchar, uint8_t mode);
    void drawcircle(int xc, int yc, int r, wchar_t fillchar, uint8_t mode);
    void drawshape(CGL_Shape shape, wchar_t fillchar, uint8_t mode);

	// shape.c
    void newshape(CGL_Shape *shape, CGL_Coord *points, size_t numpts);
    void freeshape(CGL_Shape *shape);
	
	#ifdef __cplusplus
		}
	#endif
#endif
