#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include "pieces.h"
#include <vector>
class GameBoard;

class Rook : public Pieces{
public:
	Rook(char tp, GameBoard *gb, int colour);
	std::vector<Coord> potentialMoves(Coord stc);
};

#endif
