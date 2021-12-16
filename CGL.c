#include <math.h>
#include "CGL.h"

void drawrect(Rect rect, char fillCharacter, int mode, int color) {
	if (mode == CGL_WIREFRAME) {
		drawline(rect.x, rect.y, rect.x + rect.w, rect.y, fillCharacter, color);
		drawline(rect.x, rect.y, rect.x, rect.y + rect.h, fillCharacter, color);
		drawline(rect.x + rect.w, rect.y + rect.h, rect.x, rect.y + rect.h, fillCharacter, color);
		drawline(rect.x + rect.w, rect.y + rect.h, rect.x + rect.w, rect.y, fillCharacter, color);
	} else if (mode == CGL_FILL) {
		setcolor(color);
		for (int y = rect.y; y < rect.y + rect.h; y++) {
			for (int x = rect.x; x < rect.x + rect.w; x++) {
				setchar(x, y, fillCharacter);
			}
		}
		setcolor(CGL_LIGHT_GREY);
	}
}

void drawtriangle(int x0, int y0, int x1, int y1, int x2, int y2, char fillCharacter, int mode, int color) {
	if (mode == CGL_WIREFRAME) {
		drawline(x0, y0, x1, y1, fillCharacter, color);
		drawline(x1, y1, x2, y2, fillCharacter, color);
		drawline(x2, y2, x0, y0, fillCharacter, color);
	} else if (mode == CGL_FILL) {
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

		dx = x2 - x1; dy = y2 - y1;
		dx1 = abs(dx); dy1 = abs(dy);
		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	
		if (dy1 <= dx1) {
			if (dx >= 0) {
				x = x1; y = y1; xe = x2;
			}
			else {
				x = x2; y = y2; xe = x1;
			}
			drawline(x0, y0, x, y, fillCharacter, color);
	
			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else {
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						y = y + 1;
					else
						y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				drawline(x0, y0, x, y, fillCharacter, color);
			}
		}
		else {
			if (dy >= 0) {
				x = x1; y = y1; ye = y2;
			}
			else {
				x = x2; y = y2; ye = y1;
			}
	
			drawline(x0, y0, x, y, fillCharacter, color);
	
			for (i = 0; y < ye; i++) {
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else {
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						x = x + 1;
					else
						x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				drawline(x0, y0, x, y, fillCharacter, color);
			}
		}
	}
}

void drawline(int x1, int y1, int x2, int y2, char fillCharacter, int color) {
	setcolor(color);
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;

	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = x1; y = y1; xe = x2;
		}
		else {
			x = x2; y = y2; xe = x1;
		}
		setchar(x, y, fillCharacter);

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y = y + 1;
				else
					y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			setchar(x, y, fillCharacter);
		}
	}
	else {
		if (dy >= 0) {
			x = x1; y = y1; ye = y2;
		}
		else {
			x = x2; y = y2; ye = y1;
		}

		setchar(x, y, fillCharacter);

		for (i = 0; y < ye; i++) {
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x = x + 1;
				else
					x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			setchar(x, y, fillCharacter);
		}
	}
	setcolor(CGL_LIGHT_GREY);
}

void drawshape(Shape shape, char fillCharacter, int mode, int color) {
    if (mode == CGL_WIREFRAME) {
        for (int i = 0; i < shape.numpts; i++) {
            if (i == 0) {
                drawline(shape.points[shape.numpts - 1].x, shape.points[shape.numpts - 1].y, shape.points[0].x, shape.points[0].y, fillCharacter, color);   
            } else {
                drawline(shape.points[i - 1].x, shape.points[i - 1].y, shape.points[i].x, shape.points[i].y, fillCharacter, color);   
            }
        }
    } else if (mode == CGL_FILL) {
        for (int i = 0; i < shape.numpts; i++) {
            if (i == 0) {
                drawtriangle(shape.mid.x, shape.mid.y, shape.points[shape.numpts - 1].x, shape.points[shape.numpts - 1].y, shape.points[0].x, shape.points[0].y, fillCharacter, mode, color);   
            } else {
                drawtriangle(shape.mid.x, shape.mid.y, shape.points[i - 1].x, shape.points[i - 1].y, shape.points[i].x, shape.points[i].y, fillCharacter, mode, color);   
            }
        }
    }
}

void newshape(Shape *shape, Coord *points, size_t numpts) {
    int mx = 0, my = 0;
    shape = (Shape *)malloc(sizeof(Shape));
    shape->points = (Coord *)malloc(numpts * sizeof(Coord));
    shape->numpts = numpts;
    
    for(int i = 0; i < numpts; i++) {
        *(shape->points + i) = points[i];
        mx += points[i].x;
        my += points[i].y;
    }
    mx /= numpts;
    my /= numpts;
    shape->mid = coord(mx, my);
}

void freeshape(Shape *shape) {
    free(shape);
    free(shape->points);   
}
