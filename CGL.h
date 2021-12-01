#ifndef CGL_H
	#define CGL_H
	#ifdef __cplusplus
		extern "C" {
	#endif
	
	#include <stdio.h>
	#include <stdlib.h>
	
	// os testing
	#ifdef _WIN32
		#include <Windows.h>
		#define gotopos(X, Y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ X, Y });
		#define clrscr() system("cls")
		typedef COORD Coord;

	#elif defined(uniX) || defined(__uniX__) || defined(__uniX)*/	
		#define gotopos(X, Y) printf("%c[%d;%df", 0X1B, Y, X)	
		#define clrscr() system("clear")
		
		typedef struct coord {
			int X, Y;
		} Coord;
  
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
	
	// functions
	
	void drawrect(Rect rect, char fillCharacter, int mode);
	void drawline(int X1, int Y1, int X2, int Y2, char fillCharacter);
	void drawtriangle(int X1, int Y1, int X2, int Y2, int X3, int Y3, char fillCharacter, int mode);
	
	#ifdef __cplusplus
		}
	#endif
#endif