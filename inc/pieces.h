#ifndef PIECES_H
#define PIECES_H
#include <iostream>
#include <vector>
#include <map>
#include "coord.h"
#include "gameboard.h" //Instead of forward declair, becuase the subclasses need it

class Pieces;

class Pieces {
protected:
	char tp;
	GameBoard *gb;
	int colour;
public:
	Pieces(char tp, GameBoard *gb, int colour);
	~Pieces();
	int getColour();
        char getPiece();
	virtual std::vector<Coord> potentialMoves(Coord) = 0;
};

#endif
