#ifndef TILE_H_
#define TILE_H_

#include <raylib.h>

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	Color color;
	long occupied;
} Tile;

void create_tiles(const int W, const int H, const int TILE, Tile tiles[][W]);
void draw_tiles(const int W, const int H, Tile tiles[][W]);

#endif
