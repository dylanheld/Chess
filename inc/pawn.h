#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include <vector>
#include "pieces.h"

class GameBoard;
class Pawn : public Pieces
{
public:
  Pawn(char tp, GameBoard *gb, int colour);
  std::vector<Coord> potentialMoves(Coord);
};

#endif	//PAWN_H
