#include <math.h>
#include "CGL.h"

void drawrect(Rect rect, char fillCharacter, int mode) {
	if (mode == CGL_WIREFRAME) {
		drawline(rect.x, rect.y, rect.x + rect.w, rect.y, fillCharacter);
		drawline(rect.x, rect.y, rect.x, rect.y + rect.h, fillCharacter);
		drawline(rect.x + rect.w, rect.y + rect.h, rect.x, rect.y + rect.h, fillCharacter);
		drawline(rect.x + rect.w, rect.y + rect.h, rect.x + rect.w, rect.y, fillCharacter);
	} else if (mode == CGL_FILL) {
		for (int Y = rect.y; Y < rect.y + rect.h; Y++) {
			for (int X = rect.x; X < rect.x + rect.w; X++) {
				setchar(X, Y, fillCharacter);
			}
		}
	}
}

void drawtriangle(int X0, int Y0, int X1, int Y1, int X2, int Y2, char fillCharacter, int mode) {
	if (mode == CGL_WIREFRAME) {
		drawline(X0, Y0, X1, Y1, fillCharacter);
		drawline(X1, Y1, X2, Y2, fillCharacter);
		drawline(X2, Y2, X0, Y0, fillCharacter);
	} else if (mode == CGL_FILL) {
		int X, Y, dX, dY, dX1, dY1, pX, pY, Xe, Ye, i;

		dX = X2 - X1; dY = Y2 - Y1;
		dX1 = abs(dX); dY1 = abs(dY);
		pX = 2 * dY1 - dX1;	pY = 2 * dX1 - dY1;
	
		if (dY1 <= dX1) {
			if (dX >= 0) {
				X = X1; Y = Y1; Xe = X2;
			}
			else {
				X = X2; Y = Y2; Xe = X1;
			}
			drawline(X0, Y0, X, Y, fillCharacter);
	
			for (i = 0; X < Xe; i++)
			{
				X = X + 1;
				if (pX < 0)
					pX = pX + 2 * dY1;
				else {
					if ((dX < 0 && dY < 0) || (dX > 0 && dY > 0))
						Y = Y + 1;
					else
						Y = Y - 1;
					pX = pX + 2 * (dY1 - dX1);
				}
				drawline(X0, Y0, X, Y, fillCharacter);
			}
		}
		else {
			if (dY >= 0) {
				X = X1; Y = Y1; Ye = Y2;
			}
			else {
				X = X2; Y = Y2; Ye = Y1;
			}
	
			drawline(X0, Y0, X, Y, fillCharacter);
	
			for (i = 0; Y < Ye; i++) {
				Y = Y + 1;
				if (pY <= 0)
					pY = pY + 2 * dX1;
				else {
					if ((dX < 0 && dY < 0) || (dX > 0 && dY > 0))
						X = X + 1;
					else
						X = X - 1;
					pY = pY + 2 * (dX1 - dY1);
				}
				drawline(X0, Y0, X, Y, fillCharacter);
			}
		}
	}
}

void drawline(int X1, int Y1, int X2, int Y2, char fillCharacter) {
	int X, Y, dX, dY, dX1, dY1, pX, pY, Xe, Ye, i;

	dX = X2 - X1; dY = Y2 - Y1;
	dX1 = abs(dX); dY1 = abs(dY);
	pX = 2 * dY1 - dX1;	pY = 2 * dX1 - dY1;

	if (dY1 <= dX1) {
		if (dX >= 0) {
			X = X1; Y = Y1; Xe = X2;
		}
		else {
			X = X2; Y = Y2; Xe = X1;
		}
		setchar(X, Y, fillCharacter);

		for (i = 0; X < Xe; i++)
		{
			X = X + 1;
			if (pX < 0)
				pX = pX + 2 * dY1;
			else {
				if ((dX < 0 && dY < 0) || (dX > 0 && dY > 0))
					Y = Y + 1;
				else
					Y = Y - 1;
				pX = pX + 2 * (dY1 - dX1);
			}
			setchar(X, Y, fillCharacter);
		}
	}
	else {
		if (dY >= 0) {
			X = X1; Y = Y1; Ye = Y2;
		}
		else {
			X = X2; Y = Y2; Ye = Y1;
		}

		setchar(X, Y, fillCharacter);

		for (i = 0; Y < Ye; i++) {
			Y = Y + 1;
			if (pY <= 0)
				pY = pY + 2 * dX1;
			else {
				if ((dX < 0 && dY < 0) || (dX > 0 && dY > 0))
					X = X + 1;
				else
					X = X - 1;
				pY = pY + 2 * (dX1 - dY1);
			}
			setchar(X, Y, fillCharacter);
		}
	}
}

void exp_drawshape(Shape shape, char fillCharacter, int mode) {
    if (mode == CGL_WIREFRAME) {
        for (int i = 0; i < shape.numpts; i++) {
            if (i == 0) {
                drawline(shape.points[shape.numpts - 1].X, shape.points[shape.numpts - 1].Y, shape.points[0].X, shape.points[0].Y, fillCharacter);   
            } else {
                drawline(shape.points[i - 1].X, shape.points[i - 1].Y, shape.points[i].X, shape.points[i].Y, fillCharacter);   
            }
        }
    } else if (mode == CGL_FILL) {
        for (int i = 0; i < shape.numpts; i++) {
            int i1 = i + 1 , i2 = i + 2;
            if (i2 > shape.numpts) {
                if (i1 > shape.numpts) {
                    i2 = 1;
                    i1 = 0;
                } else {
                    i2 = 0;
                }
            }
            
            drawtriangle(shape.points[i].X, shape.points[i].Y, shape.points[i1].X, shape.points[i1].Y, shape.points[i2].X, shape.points[i2].Y, fillCharacter, mode);
        }
    }
}

void newshape(Shape *shape, Coord *points, size_t numpts) {
    shape = (Shape *)malloc(sizeof(Shape));
    shape->points = (Coord *)malloc(numpts * sizeof(Coord));
    shape->numpts = numpts;
    
    for(int i = 0; i < numpts; i++) {
        *(shape->points + i) = points[i];
    }
}

void freeshape(Shape *shape) {
    free(shape);
    free(shape->points);   
}