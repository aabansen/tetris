#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

#include "piece.h"
#include "tile.h"

#define SCR_WIDTH W * TILE
#define SCR_HEIGHT H * TILE

const int W = 10, H = 20;
const int TILE = 35;


Piece pieces[7] = {
	(const Piece) {
		(Vector2) {0, 0}, 'O', (Color){212, 166, 0, 255}, 0, 0,
		{
			{{-1, 0}, {0, 0}, {0, 1}, {-1, 1}}
		} 
	},

	(const Piece) {
		(Vector2) {0, 0}, 'I', BLUE, 0, 0,
		{
			{{0, 0}, {1, 0}, {-1, 0}, {-2, 0}},
			{{0, 0}, {0, -1}, {0, 1}, {0, 2}},
			{{0, 0}, {1, 0}, {-1, 0}, {-2, 0}},
			{{0, 0}, {0, -1}, {0, 1}, {0, 2}}
		} 
	},

	(const Piece) {
		(Vector2) {0, 0}, 'S', RED, 0, 0,
		{
			{{0, 0}, {0, 1}, {-1, 0}, {-1, -1}},
			{{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
			{{0, 0}, {0, 1}, {-1, 0}, {-1, -1}},
			{{0, 0}, {-1, 0}, {0, 1}, {1, 1}},
		} 
	},

	(const Piece) {
		(Vector2) {0, 0}, 'Z', DARKGREEN, 0, 0,
		{
			{{0, 0}, {0, -1}, {1, 0}, {1, 1}},
		    {{0, 0}, {-1, 0}, {0, -1}, {1, -1}},
			{{0, 0}, {0, -1}, {1, 0}, {1, 1}},
		    {{0, 0}, {-1, 0}, {0, -1}, {1, -1}}
		} 
	},

	(const Piece) {
		(Vector2) {0, 0}, 'L', ORANGE, 0, 0,
		{
			{{0, 0}, {0, 1}, {0, -1}, {1, -1}},
			{{0, 0}, {1, 0}, {-1, 0}, {-1, -1}},
			{{0, 0}, {0, -1}, {0, 1}, {-1, 1}},
			{{0, 0}, {-1, 0}, {1, 0}, {1, 1}}
		} 
	},

	(const Piece) {
		(Vector2) {0, 0}, 'J', PINK, 0, 0,
		{
			{{0, 0}, {0, -1}, {0, 1}, {1, 1}},
			{{0, 0}, {-1, 0}, {1, 0}, {1, -1}},
			{{0, 0}, {0, 1}, {0, -1}, {-1, -1}},
			{{0, 0}, {1, 0}, {-1, 0}, {-1, 1}}
		} 
	},

	(const Piece) {
		(Vector2) {0, 0}, 'T', PURPLE, 0, 0,
		{
			{{0, 0}, {0, -1}, {0, 1}, {1, 0}}, 
			{{0, 0}, {-1, 0}, {1, 0}, {0, -1}}, 
			{{0, 0}, {0, -1}, {0, 1}, {-1, 0}}, 
			{{0, 0}, {-1, 0}, {1, 0}, {0, 1}} 
		}
	}
};

static Piece spawn_piece(Piece *pieces, Tile tiles[][W])
{
	int r = GetRandomValue(0, 6);
	char piece_type = pieces[r].type;
	Piece piece = create_piece(5, 1, 0, W, piece_type, pieces, tiles);

	return piece;
}

static int is_on_edge(char axis, Piece *piece)
{
	for (int i = 0; i < 4; i++)
	{
		int x_pos = piece->pos.x + piece->coords[piece->rot_state][i][1];
		int y_pos = piece->pos.y + piece->coords[piece->rot_state][i][0];

		if (axis == 'Y')
			if (y_pos >= H - 1)
				return 1;
		if (axis == 'X')
			if (x_pos >= W - 1 || x_pos <= 0)
				return 1;
	}

	return 0;
}

static int is_touching_piece(char axis, Piece *piece, Tile tiles[][W])
{
	for (int i = 0; i < 4; i++)
	{
		int x_pos = piece->pos.x + piece->coords[piece->rot_state][i][1];
		int y_pos = piece->pos.y + piece->coords[piece->rot_state][i][0];

		Tile below_tile = tiles[y_pos + 1][x_pos];
		Tile left_tile = tiles[y_pos][x_pos + 1];
		Tile right_tile = tiles[y_pos][x_pos - 1];

		if (axis == 'Y')
		{
			if (below_tile.occupied != 0 && below_tile.occupied != piece->id)
				return 1;
		}

		if (axis == 'X')
		{
			if (left_tile.occupied != 0 && left_tile.occupied != piece->id)
				return 1;

			if (right_tile.occupied != 0 && right_tile.occupied != piece->id)
				return 1;
		}
	}

	return 0;
}

static void move_piece(Piece *piece, Piece *pieces, Tile tiles[][W])
{
	if (!is_on_edge('Y', piece) && !is_touching_piece('Y', piece, tiles))
	{
		translate_piece(piece->pos.x, piece->pos.y + 1, piece->rot_state, W, piece, pieces, tiles);

		if (IsKeyDown(KEY_RIGHT) && !is_on_edge('X', piece) && !is_touching_piece('X', piece, tiles))
			translate_piece(piece->pos.x + 1, piece->pos.y, piece->rot_state, W, piece, pieces, tiles);

		if (IsKeyDown(KEY_LEFT) && !is_on_edge('X', piece) && !is_touching_piece('X', piece, tiles))
			translate_piece(piece->pos.x - 1, piece->pos.y, piece->rot_state, W, piece, pieces, tiles);

		if (IsKeyDown(KEY_DOWN) && !is_on_edge('Y', piece) && !is_touching_piece('Y', piece, tiles))
			translate_piece(piece->pos.x, piece->pos.y + 1, piece->rot_state, W, piece, pieces, tiles);

		if (IsKeyPressed(KEY_Z) && piece->type != 'O' && !is_on_edge('X', piece) && !is_touching_piece('X', piece, tiles))
			translate_piece(piece->pos.x, piece->pos.y, (piece->rot_state + 1) % 4, W, piece, pieces, tiles);
	}
	else
	{
		*piece = spawn_piece(pieces, tiles);
	}
}

static void move_lines_down(int index, int row, Color color, Tile tiles[][W]) 
{
	if (tiles[row-1][index].occupied == 0) {
		return;	
	} 

	tiles[row-1][index].color = BLACK;
	tiles[row-1][index].occupied = 0;	

	tiles[row][index].color = color;
	tiles[row][index].occupied = counter++;

	move_lines_down(index, row-1, color, tiles);
}

static void clear_lines(int row, Tile tiles[][W])
{
	for (int i = 0; i < W; i++)
	{
		tiles[row][i].occupied = 0;
		Color temp = tiles[row][i].color;
		tiles[row][i].color = BLACK;

		move_lines_down(i, row, temp, tiles);	
	}
}

static int game_over(Piece *piece, Tile tiles[][W]) 
{
	for (int i = 0; i < 4; i++)
	{
		int y_pos = piece->pos.y + piece->coords[piece->rot_state][i][0];

		if (y_pos <= 0 && is_touching_piece('Y', piece, tiles)) return 1;
	}

	return 0;
}

static void search_for_clear_lines(Piece *piece, Tile tiles[][W])
{
	int col_count = 0;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (tiles[i][j].occupied != 0) col_count++;
			if (j == W - 1 && col_count != W) col_count = 0;

			if (col_count == W && is_touching_piece('Y', piece, tiles))
			{
				clear_lines(i, tiles);
				col_count = 0;
			}
		}
	}

}

static void clear_screen(Tile tiles[][W])
{
	counter = 0;	

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			tiles[i][j].color = BLACK;	
			tiles[i][j].occupied = 0;
		}
	}
}

int main()
{
	InitWindow(SCR_WIDTH + 10, SCR_HEIGHT + 10, "Tetris");
	SetTargetFPS(10);

	Tile tiles[H][W];
	create_tiles(W, H, TILE, tiles);

	Piece piece = spawn_piece(pieces, tiles);
	Rectangle border = {5, 5, SCR_WIDTH, SCR_HEIGHT};

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			draw_tiles(W, H, tiles);
			DrawRectangleLinesEx(border, 1, WHITE);

			search_for_clear_lines(&piece, tiles);

			if (!game_over(&piece, tiles)) 
			{
				move_piece(&piece, pieces, tiles);
			} 
			
			if (IsKeyPressed(KEY_R)) 
			{
				counter = 0;
				clear_screen(tiles);
				piece = spawn_piece(pieces, tiles);
			}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
