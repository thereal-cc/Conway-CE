#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timers.h>
#include <sys/util.h>

// Sizing
#define TILE_SIZE 20
#define SCREEN_ROWS 10
#define SCREEN_COLS 16

typedef uint8_t u8;
typedef uint16_t u16;
typedef int8_t i8;

typedef struct v2
{
    u8 x;
    u8 y;
} v2;

#endif