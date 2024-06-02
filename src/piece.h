#ifndef PIECE_H_
#define PIECE_H_

#include "tile.h"

typedef struct
{
	Vector2 pos;
	char type;
	Color color;
	int rot_state;
	int id;
	int coords[4][4][2];
} Piece;

long counter;

Piece find_piece_type(char piece_id, Piece *pieces);
Piece create_piece(int x, int y, int rot_state, const int W, char piece_id, Piece *pieces, Tile tiles[][W]);
void translate_piece(int x, int y, int rot_state, const int W, Piece *piece, Piece *pieces, Tile tiles[][W]);
void rotate_piece(int dir, const int W, Piece *piece, Tile tiles[][W]);

#endif
