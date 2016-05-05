#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <vector>
#include <map>
#include "coord.h"
#include "gameboard.h"

class Pieces;
class Pieces 
{
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

#endif	//PIECES_H
