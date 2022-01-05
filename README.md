# ConsoleGraphicsLibrary

A simple, yet effective graphics library targetting all major operating systems.

## Features

Read the CGL.h file for documentation, because I'm tired of updating this readme.

***MAKE SURE YOU HAVE GCC INSTALLED ONTO YOUR COMPUTER***

To compile your code to an executable, simply execute the following command in your console/terminal, making sure you are in the directory of your project:
`gcc [filename].c -L. -lCGL -o [filename]`

### Sample Code
To give an idea of what you can do with this library, I've created a simple demo which renders a rectangle for 3 seconds, and then stops. It's quite simple, to try it out for yourself simply copy the following code:

```
#include "CGL.h"

int main(int argc, char **argv) 
{
	Rect rectangle = (Rect){ 10, 10, 10, 5 };
        clrscr();
	drawrect(rectangle, '#', CGL_FILL, RED);
	gotopos(0, 21);
}
```
