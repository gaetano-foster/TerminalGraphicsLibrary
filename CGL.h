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
		#define gotopos(X, Y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ X, Y });
		#define clrscr() system("cls")
		typedef COORD Coord;
		
		enum color {
			CGL_DARK_BLUE, CGL_GREEN, CGL_DARK_CYAN, 
			CGL_DARK_RED, CGL_DARK_MAGENTA, CGL_DARK_YELLOW, 
			CGL_LIGHT_GREY, CGL_GREY, CGL_BLUE, CGL_LIME, CGL_CYAN, 
			CGL_RED, CGL_MAGENTA, CGL_YELLOW, CGL_WHITE
		};

	#elif defined(unix) || defined(__unix__) || defined(__unix)	
		#define setcolor(color) printf("\x1B[%dm", color)
		#define gotopos(X, Y) printf("%c[%d;%df", 0X1B, Y, X)	
		#define clrscr() system("clear")
		
		typedef struct coord {
			int X, Y;
		} Coord;
		
		enum color {
			CGL_DARK_BLUE = 34, CGL_GREEN = 32, CGL_DARK_CYAN = 36, 
			CGL_DARK_RED = 31, CGL_DARK_MAGENTA = 35, CGL_DARK_YELLOW = 33, 
			CGL_LIGHT_GREY 37, CGL_GREY = 90, CGL_BLUE = 94, CGL_LIME = 92, CGL_CYAN = 96, 
			CGL_RED = 91, CGL_MAGENTA = 95, CGL_YELLOW = 93, CGL_WHITE = 97
		};
  
	#endif
	
	// macros & constants
	
	#define coord(X, Y) ((Coord) { X, Y })
	#define setchar(X, Y, character) gotopos(X, Y); putchar(character); gotopos(0, 0)
	#define drawtri(tri, fillCharacter, mode) drawtriangle(tri.points[0].X, tri.points[0].Y, tri.points[1].X, tri.points[1].Y, tri.points[2].X, tri.points[2].Y, fillCharacter, mode);
	
	// typedefs, structs, enums
	
	enum render_mode {
		CGL_WIREFRAME, CGL_FILL
	};
	
	typedef struct rect {
		float x, y;
		unsigned int w, h;
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
	void drawline(int X1, int Y1, int X2, int Y2, char fillCharacter, int color);
	void drawtriangle(int X1, int Y1, int X2, int Y2, int X3, int Y3, char fillCharacter, int mode, int color);
    void drawshape(Shape shape, char fillCharacter, int mode, int color);
    void newshape(Shape *shape, Coord *points, size_t numpts);
    void freeshape(Shape *shape);
	
	#ifdef __cplusplus
		}
	#endif
#endif