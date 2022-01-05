#include <math.h>
#include "CGL.h"

void drawrect(CGL_Rect rect, wchar_t fillchar, uint8_t mode) 
{
	if (mode == CGL_WIREFRAME) {
		drawline(rect.x, rect.y, rect.x + rect.w, rect.y, fillchar);
		drawline(rect.x, rect.y, rect.x, rect.y + rect.h, fillchar);
		drawline(rect.x + rect.w, rect.y + rect.h, rect.x, rect.y + rect.h, fillchar);
		drawline(rect.x + rect.w, rect.y + rect.h, rect.x + rect.w, rect.y, fillchar);
	} 
    else if (mode == CGL_FILL) {
		for (int y = rect.y; y < rect.y + rect.h; y++)
			for (int x = rect.x; x < rect.x + rect.w; x++)
				setchar(x, y, fillchar);
	}
}

void drawline(int16_t x1, int16_t y1, int16_t x2, int16_t y2, wchar_t fillchar)
{
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
		setchar(x, y, fillchar);

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
			setchar(x, y, fillchar);
		}
	}
	else {
		if (dy >= 0) {
			x = x1; y = y1; ye = y2;
		}
		else {
			x = x2; y = y2; ye = y1;
		}

		setchar(x, y, fillchar);

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
			setchar(x, y, fillchar);
		}
	}
}

void drawtriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, wchar_t fillchar, uint8_t mode)
{
	if (mode == CGL_WIREFRAME) {
		drawline(x1, y1, x2, y2, fillchar);
		drawline(x2, y2, x3, y3, fillchar);
		drawline(x3, y3, x1, y1, fillchar);
	} 
    else if (mode == CGL_FILL) {
		/*  Source: https://www.avrfreaks.net/sites/default/files/triangles.c  */
		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		int changed1 = 0;
		int changed2 = 0;	
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;

 	   // Sort vertices
		if (y1 > y2) { SWAP(y1,y2); SWAP(x1,x2); }
		if (y1 > y3) { SWAP(y1,y3); SWAP(x1,x3); }
		if (y2 > y3) { SWAP(y2,y3); SWAP(x2,x3); }

		t1x = t2x = x1; 
  	 	y = y1;   // Starting points

		dx1 = (x2 - x1); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
		dy1 = (y2 - y1);
 
		dx2 = (x3 - x1); if(dx2<0) { dx2=-dx2; signx2=-1; } else signx2=1;
		dy2 = (y3 - y1);
	
		if (dy1 > dx1) {   // swap values
        	SWAP(dx1,dy1);
			changed1 = 1;
		}
		if (dy2 > dx2) {   // swap values
    	    SWAP(dy2,dx2);
			changed2 = 1;
		}
	
		e2 = (dx2>>1);
    	// Flat top, just process the second half
    	if(y1==y2) goto next;
    	e1 = (dx1>>1);
	
		for (int i = 0; i < dx1;) {
			t1xp=0; t2xp=0;
			if(t1x<t2x) { minx=t1x; maxx=t2x; }
			else		{ minx=t2x; maxx=t1x; }
   	    	// process first line until y value is about to change
			while(i<dx1) {
				i++;			
				e1 += dy1;
	   		   	while (e1 >= dx1) {
					e1 -= dx1;
   	   	   			if (changed1) t1xp=signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
		// Move line
		next1:
    	    // process second line until y value is about to change
			while (1) {
				e2 += dy2;		
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp=signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if(minx>t1x) minx=t1x; if(minx>t2x) minx=t2x;
			if(maxx<t1x) maxx=t1x; if(maxx<t2x) maxx=t2x;
		   	lcd_hline(minx, maxx, y, fillchar);    // Draw line from min to max points found on the y
			// Now increase y
			if(!changed1) t1x += signx1;
			t1x+=t1xp;
			if(!changed2) t2x += signx2;
			t2x+=t2xp;
  		  	y += 1;
			if(y==y2) break;
		
 	  	}
		next:
		// Second half
		dx1 = (x3 - x2); if(dx1<0) { dx1=-dx1; signx1=-1; } else signx1=1;
		dy1 = (y3 - y2);
		t1x=x2;
 
		if (dy1 > dx1) {   // swap values
    	    SWAP(dy1,dx1);
			changed1 = 1;
		} else changed1 = 0;
	
		e1 = (dx1>>1);
	
		for (int i = 0; i<=dx1; i++) {
			t1xp=0; t2xp=0;
			if(t1x<t2x) { minx=t1x; maxx=t2x; }
			else		{ minx=t2x; maxx=t1x; }
		    // process first line until y value is about to change
			while(i<dx1) {
    			e1 += dy1;
		   	   	while (e1 >= dx1) {
					e1 -= dx1;
   	 	  	   	   	if (changed1) { t1xp=signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if(i<dx1) i++;
			}
		next3:
    	    // process second line until y value is about to change
			while (t2x!=x3) {
				e2 += dy2;
	   		   	while (e2 >= dx2) {
					e2 -= dx2;
					if(changed2) t2xp=signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}	   	   
		next4:

			if(minx>t1x) minx=t1x; if(minx>t2x) minx=t2x;
			if(maxx<t1x) maxx=t1x; if(maxx<t2x) maxx=t2x;
		   	lcd_hline(minx, maxx, y, fillchar);    // Draw line from min to max points found on the y
			// Now increase y
			if(!changed1) t1x += signx1;
			t1x+=t1xp;
			if(!changed2) t2x += signx2;
			t2x+=t2xp;
    		y += 1;
			if(y>y3) return;
		}
	}
}

void drawcircle(int xc, int yc, int r, wchar_t fillchar, uint8_t mode)
{
    if (mode == CGL_WIREFRAME) {
        int x = 0;
		int y = r;
		int p = 3 - 2 * r;
		if (!r) return;

		while (y >= x) {
			setchar(xc - x, yc - y, fillchar); // upper left left
			setchar(xc - y, yc - x, fillchar); // upper upper left
			setchar(xc + y, yc - x, fillchar); // upper upper right
			setchar(xc + x, yc - y, fillchar); // upper right right
			setchar(xc - x, yc + y, fillchar); // lower left left
			setchar(xc - y, yc + x, fillchar); // lower lower left
			setchar(xc + y, yc + x, fillchar); // lower lower right
			setchar(xc + x, yc + y, fillchar); // lower right right
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
    }
    else if (mode == CGL_FILL) {
    	int x = 0;
		int y = r;
		int p = 3 - 2 * r;
		if (!r) return;

		while (y >= x)
		{
			// Modified to draw scan-lines instead of edges
			lcd_hline(xc - x, xc + x, yc - y, fillchar);
			lcd_hline(xc - y, xc + y, yc - x, fillchar);
			lcd_hline(xc - x, xc + x, yc + y, fillchar);
			lcd_hline(xc - y, xc + y, yc + x, fillchar);
            
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
    }
}

void drawshape(CGL_Shape shape, wchar_t fillchar, uint8_t mode)
{
    if (mode == CGL_WIREFRAME) {
        for (int i = 0; i < shape.numpts; i++) {
            if (i == 0) {
                drawline(shape.points[shape.numpts - 1].x, shape.points[shape.numpts - 1].y, shape.points[0].x, shape.points[0].y, fillchar);   
            } 
			else {
                drawline(shape.points[i - 1].x, shape.points[i - 1].y, shape.points[i].x, shape.points[i].y, fillchar);   
            }
        }
    } 
    else if (mode == CGL_FILL) {
        for (int i = 0; i < shape.numpts; i++) {
            if (i == 0) {
                drawtriangle(shape.mid.x, shape.mid.y, shape.points[shape.numpts - 1].x, shape.points[shape.numpts - 1].y, shape.points[0].x, shape.points[0].y, fillchar, mode);   
            } 
			else {
                drawtriangle(shape.mid.x, shape.mid.y, shape.points[i - 1].x, shape.points[i - 1].y, shape.points[i].x, shape.points[i].y, fillchar, mode);   
            }
        }
    }
}
