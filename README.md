# ConsoleGraphicsLibrary

A simple, yet effective graphics library targetting all major operating systems.

## Features

### Warnings: 
Any function, macro, or structure prefixed with _exp\__ is **experimental/unfinished**. They may not be very efficient, fast or well implemented. Use at your own risk.

### Structures:
* struct coord - A coordinate
  * Members: 
    * X - coordinate along x axis
    * Y - coordinate along y axis
  * Type Definitions: Coord
* struct rect - A rectangle
  * Members: 
    * x - coordinate along x axis
    * y - coordinate along y axis
    * w - width of the rectangle
    * h - height of the rectangle 
  * Type Definition: Rect
* struct tri - A triangle
  * Members: 
    * points[3] - the triangle's vertices
  * Type Definition: Tri
* struct shape - A shape with an undefined amount of vertices
  * Members:
    * \*points - the shape's vertices
    * mid - the shape's mid point (average of all points)
    * numpts - the amount of verties (numpts -> number of points)  
  * Type Definition: Shape
 
### Functions/Macros:
* drawrect - draws specified rectangle
* drawline - draws a line between specified coordinates
* drawtriangle - draws triangle using specified vertices
* drawshape - draws the specified shape
* newshape - allocates memory needed for a shape
* freeshape - frees memory used by shape
* drawtri - draws specified triangle
* setchar - prints char at specified coordinates
* clrscr - clears screen
* gotopos - goes to specified coordinates

## Usage

Using this library in your project could not be easier! Simply download the source, execute the `win32_compile` or `unix_compile` file, and drag the "CGL.h" and "libCGL.a" files into your projects folder.

***MAKE SURE YOU HAVE GCC INSTALLED ONTO YOUR COMPUTER***

To compile your code to an executable, simply execute the following command in your console/terminal, making sure you are in the directory of your project:
`gcc [filename].c -L. -lCGL -o [filename]`

### Sample Code
To give an idea of what you can do with this library, I've created a simple demo which renders a rectangle for 3 seconds, and then stops. It's quite simple, to try it out for yourself simply copy the following code:

```
#include "CGL.h"

void main(void) {
	Rect rectangle = (Rect){ 10, 10, 10, 5 };
        clrscr();
	drawrect(rectangle, '#', CGL_FILL, RED);
	gotopos(0, 21);
}
```
