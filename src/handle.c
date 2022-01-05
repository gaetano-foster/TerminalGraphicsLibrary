#include "CGL.h"

void setcolor(uint8_t color)
{
    #ifdef _WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	#elif defined(unix) || defined(__unix__) || defined(__unix)	
		printf("\x1B[%dm", color);
	#endif
}

void gotopos(int16_t x, int16_t y)
{
    #ifdef _WIN32
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ x, y });
	#elif defined(unix) || defined(__unix__) || defined(__unix)	
        printf("%c[%d;%df", 0x1B, y, x);
	#endif
}	
void setchar(int16_t x, int16_t y, char character)
{
    gotopos(x, y); 
    putchar(character); 
    gotopos(0, 0);
} 
void clrscr()
{
    #ifdef _WIN32
		system("cls");
	#elif defined(unix) || defined(__unix__) || defined(__unix)	
        system("clear");
	#endif
}

void lcd_hline(int16_t x1, int16_t x2, int16_t y, char character)
{
	if (x1 >= x2) 
        SWAP(x1, x2);

	for (; x1 <= x2 ; x1++) 
        setchar(x1, y, character);
}