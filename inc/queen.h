#ifndef QUEEN_H
#define QUEEN_H
#include <iostream>
#include <vector>
//#include "game.h"
#include "pieces.h"
class GameBoard;
//class Pieces;

class Queen : public Pieces{
public:
        Queen(char tp, GameBoard *gb, int colour);
        std::vector<Coord> potentialMoves(Coord);
};

#endif
