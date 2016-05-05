#ifndef PLAYER_H
#define PLAYER_H

#include "coord.h"
#include "gameboard.h"

class Player 
{
  protected:
  GameBoard *gb;
  int colour;
  public:
  bool wouldPutInCheck(Coord, Coord, bool a = false, bool isKing = true);
  Player(GameBoard*, int);
  bool isMyPiece(Pieces*);
  virtual void makeMove()=0;
};

#endif	//PLAYER_H
