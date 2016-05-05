#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include <vector>
#include "pieces.h"

class GameBoard;
class Queen : public Pieces
{
public:
	Queen(char tp, GameBoard *gb, int colour);
	std::vector<Coord> potentialMoves(Coord);
};

#endif	//QUEEN_H
