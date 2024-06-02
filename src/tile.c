#include "tile.h"

void create_tiles(const int W, const int H, const int TILE, Tile tiles[][W])
{
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			int x = j * TILE;
			int y = i * TILE;

			Tile tile = {x + 5, y + 5, TILE, TILE, BLACK, 0};
			tiles[i][j] = tile;
		}
	}
}

void draw_tiles(const int W, const int H, Tile tiles[][W])
{
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			Rectangle tile = {
				tiles[i][j].x, tiles[i][j].y,
				tiles[i][j].w, tiles[i][j].h};

			if (tiles[i][j].occupied != 0)
				DrawRectangleGradientEx(tile, RAYWHITE, tiles[i][j].color, tiles[i][j].color, tiles[i][j].color);

		}
	}
}
