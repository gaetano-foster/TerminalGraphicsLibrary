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
			DARK_BLUE, GREEN, DARK_CYAN, 
			DARK_RED, DARK_MAGENTA, DARK_YELLOW, 
			LIGHT_GREY, GREY, BLUE, LIME, CYAN, 
			RED, MAGENTA, YELLOW, WHITE
		};

	#elif defined(unix) || defined(__unix__) || defined(__unix)	
		#define setcolor(color) printf(color)
		#define gotopos(X, Y) printf("%c[%d;%df", 0X1B, Y, X)	
		#define clrscr() system("clear")
		
		typedef struct coord {
			int X, Y;
		} Coord;
		
		enum color {
			DARK_BLUE = "\x1B[34m", GREEN = "\x1B[32m", DARK_CYAN = "\x1B[36m", 
			DARK_RED = "\x1B[31m", DARK_MAGENTA = "\x1B[35m", DARK_YELLOW = "\x1B[33m", 
			LIGHT_GREY "\x1B[37m", GREY = "\x1B[90m", BLUE = "\x1B[94m", LIME = "\x1B[92m", CYAN = "\x1B[96m", 
			RED = "\x1B[91m", MAGENTA = "\x1B[95m", YELLOW = "\x1B[93m", WHITE = "\x1B[97m"
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