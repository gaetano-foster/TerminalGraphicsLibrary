#ifndef __TGL_TYPES_H__
#define __TGL_TYPES_H__
#include <stdint.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef enum {
	FG_BLACK = 30,
	FG_RED,
	FG_GREEN,
	FG_YELLOW,
	FG_BLUE,
	FG_MAGENTA,
	FG_CYAN,
	FG_WHITE,
	FG_HBLACK = 90,
	FG_HRED,
	FG_HGREEN,
	FG_HYELLOW,
	FG_HBLUE,
	FG_HMAGENTA,
	FG_HCYAN,
	FG_HWHITE
} FG_COLOR;

typedef enum {
	BG_BLACK = 40,
	BG_RED,
	BG_GREEN,
	BG_YELLOW,
	BG_BLUE,
	BG_MAGENTA,
	BG_CYAN,
	BG_WHITE,
	BG_HBLACK = 100,
	BG_HRED,
	BG_HGREEN,
	BG_HYELLOW,
	BG_HBLUE,
	BG_HMAGENTA,
	BG_HCYAN,
	BG_HWHITE
} BG_COLOR;

#endif // __TGL_TYPES_H__