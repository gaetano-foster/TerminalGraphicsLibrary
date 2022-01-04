#ifndef CGL_H
	#define CGL_H
	#ifdef __cplusplus
		extern "C" {
	#endif
	
	#include <stdio.h>
	#include <stdlib.h>
    #include <stddef.h>
	
	// os testing
	#ifdef _WIN32
		#include <Windows.h>
		#define setcolor(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		#define gotopos(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ x, y });
		#define clrscr() system("cls")
		
		enum color {
			CGL_WIN32, CGL_DARK_BLUE, CGL_GREEN, CGL_DARK_CyAN, 
			CGL_DARK_RED, CGL_DARK_MAGENTA, CGL_DARK_YELLOW, 
			CGL_LIGHT_GREY, CGL_GREY, CGL_BLUE, CGL_LIME, CGL_CyAN, 
			CGL_RED, CGL_MAGENTA, CGL_YELLOW, CGL_WHITE
		};h

	#elif defined(unix) || defined(__unix__) || defined(__unix)	
		#define setcolor(color) printf("\x1B[%dm", color)
		#define gotopos(x, y) printf("%c[%d;%df", 0x1B, y, x)	
		#define clrscr() system("clear")
		
		enum color {
			CGL_DARK_BLUE = 34, CGL_GREEN = 32, CGL_DARK_CyAN = 36, 
			CGL_DARK_RED = 31, CGL_DARK_MAGENTA = 35, CGL_DARK_YELLOW = 33, 
			CGL_LIGHT_GREY = 37, CGL_GREY = 90, CGL_BLUE = 94, CGL_LIME = 92, CGL_CyAN = 96, 
			CGL_RED = 91, CGL_MAGENTA = 95, CGL_YELLOW = 93, CGL_WHITE = 97
		};
  
	#endif
	
	// macros & constants
	
	#define coord(x, y) ((Coord) { x, y })
	#define setchar(x, y, character) gotopos(x, y); putchar(character); gotopos(0, 0)
	#define drawtri(tri, fillCharacter, mode, color) drawtriangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, fillCharacter, mode, color)
	
	// typedefs, structs, enums
	
	enum render_mode {
		CGL_WIREFRAME, CGL_FILL
	};
	
	typedef struct coord {
		int x, y;
	} Coord;
	
	typedef struct rect {
		int x, y;
		int w, h;
	} Rect;
	
	typedef struct tri {
		Coord points[3];
	} Tri;
    
    typedef struct shape {
        Coord *points, mid;
        size_t numpts;
    } Shape;
	
	// functions
	
	void drawrect(Rect rect, char fillCharacter, int mode, int color);
	void drawline(int x1, int y1, int x2, int y2, char fillCharacter, int color);
	void drawtriangle(int x1, int y1, int x2, int y2, int x3, int y3, char fillCharacter, int mode, int color);
    void drawshape(Shape shape, char fillCharacter, int mode, int color);
    void newshape(Shape *shape, Coord *points, size_t numpts);
    void freeshape(Shape *shape);
	
	#ifdef __cplusplus
		}
	#endif
#endif
