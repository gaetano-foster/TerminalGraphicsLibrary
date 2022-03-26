# TerminalGraphicsLibrary

A wrapper around the linux api which allows you to draw to the terminal. Support for Macintosh and Windows has been removed, as there are other libraries which work on those operating systems with the same basic functionality. Support for double buffering has also been implemented, as terminal applications are hardly functional without it. 

## How to use

Compile using `make && make lib` in your terminal in the directory you of the folder. You should get a library called "libTGL.a". You can use this for any program with the "TGL.h" header, and the compiler flag `-lTGL`.

### Sample Code
Here is how the code would be used. This program renders a triangle to the terminal in an infinite loop, to show off the new double buffering.

```
#include <stdio.h>
#include "TGL.h"

int main() {
	Renderer renderer;
	renderer_makenew(&renderer);
	renderer_setpixel(&renderer, '@', FG_RED, BG_BLUE);
	renderer.mode = FILL;
	system("clear");
	while (1) {
		clrscr(&renderer);
		draw_triangle(&renderer, (Triangle) { (Vec2i) { 10, 5 }, (Vec2i) { 10, 10 }, (Vec2i) { 5, 5 } });
		renderer_present(&renderer);
	}
	renderer_destroy(&renderer);
}
```
