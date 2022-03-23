# TerminalGraphicsLibrary

A wrapper around the linux api which allows you to draw to the terminal. Support for Macintosh and Windows has been removed, as there are other libraries which work on those operating systems with the same basic functionality. Support for double buffering has also been implemented, as terminal applications are hardly functional without it.

### Sample Code
To give an idea of what you can do with this library, I've created a simple demo which renders a rectangle for 3 seconds, and then stops. It's quite simple, to try it out for yourself simply copy the following code:

```
#include "CGL.h"

int main(int argc, char **argv) {
	Rect rectangle = (Rect){ 10, 10, 10, 5 };
        clrscr();
	drawrect(rectangle, '#', CGL_FILL, RED);
	gotopos(0, 21);
}
```
