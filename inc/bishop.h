#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include <vector>
#include "pieces.h"
class GameBoard;

class Bishop : public Pieces{
public:
        Bishop(char tp, GameBoard *gb, int colour);
	std::vector<Coord> potentialMoves(Coord stc);
};

#endif
