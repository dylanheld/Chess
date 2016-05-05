#ifndef KNIGHT_H
#define	KNIGHT_H

#include <iostream>
#include "pieces.h"

class GameBoard;
class Knight : public Pieces
{
public:
	Knight(char tp, GameBoard *gb, int colour);
	std::vector<Coord> potentialMoves(Coord stc);
};

#endif	//KNIGHT_H
