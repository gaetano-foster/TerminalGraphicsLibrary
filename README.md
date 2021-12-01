# ConsoleGraphicsLibrary

A simple, yet effective graphics library targetting all major operating systems.

## Features:

### Warnings: 
Any function, macro, or structure prefixed with _exp\__ is **experimental**. They may not be very efficient, fast or well implemented. Use at your own risk.

### Structures:
* struct coord - A coordinate
  * Members: 
    * X - coordinate along x axis
    * Y - coordinate along y axis
  * Type Definitions: COORD (for compatability with Windows.h), Coord
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
* struct _exp\_shape_ - polygon with any amount of vertices, and a pre-defined middle.
  * Members: 
    * \*p - vertices
    * m - mid-point coordinate (do not modify)
    * amt - amount of vertices
  * Type Definition: Poly
 
### Functions/Macros:
