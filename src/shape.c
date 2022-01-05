#include "CGL.h"

void newshape(CGL_Shape *shape, CGL_Coord *points, size_t numpts) 
{
    int mx = 0, my = 0;
    shape = (CGL_Shape *)malloc(sizeof(CGL_Shape));
    shape->points = (CGL_Coord *)calloc(numpts, sizeof(CGL_Coord));
    shape->numpts = numpts;
    
    for(int i = 0; i < numpts; i++) {
        *(shape->points + i) = points[i];
        mx += points[i].x;
        my += points[i].y;
    }
    mx /= numpts;
    my /= numpts;
    
    shape->mid = (CGL_Coord){ mx, my };
}

void freeshape(CGL_Shape *shape) 
{
    free(shape);
    free(shape->points);   
}