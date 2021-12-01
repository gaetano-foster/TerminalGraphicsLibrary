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