SOURCES := $(shell find . -type f -iname "*.c")
CFLAGS  := -g -flto -fexpensive-optimizations -Ofast -DUNICODE
LIBS    := -L. -lm

all:
	@gcc -c $(SOURCES) $(CFLAGS) $(LIBS)

OBJECTS := $(shell find . -type f -iname "*.o")

lib:
	ar -rc libTGL.a $(OBJECTS)
	rm -rf $(OBJECTS)
	ranlib libTGL.a
