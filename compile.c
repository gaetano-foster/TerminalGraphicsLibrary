#include <stdlib.h>

void main(void) {
    system("gcc -c CGL.c");
    system("ar -rc libCGL.a CGL.o");
    system("ranlib libCGL.a");
}