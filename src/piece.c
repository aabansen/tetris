#include "piece.h"

long counter;

Piece find_piece_type(char piece_id, Piece *pieces)
{
	Piece piece_type;

	for (int i = 0; i < 7; i++)
	{
		if (pieces[i].type == piece_id)
			piece_type = pieces[i];
	}

	return piece_type;
}

Piece create_piece(int x, int y, int rot_state, const int W, char piece_id, Piece *pieces, Tile tiles[][W])
{
	Piece piece;
	Piece piece_type = find_piece_type(piece_id, pieces);

	counter++;

	piece = piece_type;
	piece.pos = (Vector2){x, y};
	piece.rot_state = rot_state;
	piece.id = counter;

	for (int i = 0; i < 4; i++)
	{
		int x_pos = piece.pos.x + piece.coords[piece.rot_state][i][1];
		int y_pos = piece.pos.y + piece.coords[piece.rot_state][i][0];

		tiles[y_pos][x_pos].color = piece.color;
		tiles[y_pos][x_pos].occupied = counter;
	}

	return piece;
}

void translate_piece(int x, int y, int rot_state, const int W, Piece *piece, Piece *pieces, Tile tiles[][W])
{
	for (int i = 0; i < 4; i++)
	{
		int old_x_pos = piece->pos.x + piece->coords[piece->rot_state][i][1];
		int old_y_pos = piece->pos.y + piece->coords[piece->rot_state][i][0];

		tiles[old_y_pos][old_x_pos].color = BLACK;
		tiles[old_y_pos][old_x_pos].occupied = 0;
	}

	*piece = create_piece(x, y, rot_state, W, piece->type, pieces, tiles);
}
