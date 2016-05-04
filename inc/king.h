#ifndef KING_H
#define KING_H
#include <iostream>
#include <vector>
#include "pieces.h"
class GameBoard;

class King : public Pieces{
public:
        King(char tp, GameBoard *gb, int colour);
	std::vector<Coord> potentialMoves(Coord);
};
#endif
