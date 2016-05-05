#include <iostream>
#include "pawn.h"
#include "pieces.h"
#include "history.h"
using namespace std;

Pawn::Pawn(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> Pawn::potentialMoves(Coord stc)
{
#ifdef DEBUG
	cout << "Pawn Potential moves called" << endl;
#endif
	vector<Coord> v;
	int dir = 1; //Set the direction of the pawn
	if (colour == 1) 
		dir = -1; //ASSUMPTION: White is always starting at the bottom

	//Checking potential vertical moves
	if (stc.addCoord(0, dir*1).inBounds()  && (gb->getPiece(stc.addCoord(0,dir*1)) == NULL))
		v.push_back(stc.addCoord(0,dir*1));
	if ((dir == 1) && (stc.getY() == 1) && (gb->getPiece(stc.addCoord(0,dir*1)) == NULL) && 
      (gb->getPiece(stc.addCoord(0,2)) == NULL))
	  v.push_back(stc.addCoord(0,2));
	if ((dir == -1) && (stc.getY() == 6) && (gb->getPiece(stc.addCoord(0,dir*1)) == NULL) && 
      (gb->getPiece(stc.addCoord(0,-2)) == NULL))
	  v.push_back(stc.addCoord(0,-2));

  //Diagonal Move
  if (stc.addCoord(1, dir*1).inBounds() && (gb->getPiece(stc.addCoord(1,dir*1)) != NULL) && 
      (gb->getPiece(stc.addCoord(1,dir*1))->getColour() != colour))
	  v.push_back(stc.addCoord(1,dir*1));
  if (stc.addCoord(-1, dir*1).inBounds() && (gb->getPiece(stc.addCoord(-1,dir*1)) != NULL) && 
      (gb->getPiece(stc.addCoord(-1,dir*1))->getColour() != colour))
	  v.push_back(stc.addCoord(-1,dir*1));
  
  for (int coord = 1;;) 
  {
	  Coord testCoord(stc.getX() + coord, stc.getY());
	  char pieceIQ = 'p';
	  if (colour == 1)  
		  pieceIQ = 'P'; 
	  if(testCoord.inBounds() && gb->getPiece(testCoord) != NULL && 
           gb->getPiece(testCoord)->getColour() != colour && gb->getPiece(testCoord)->getPiece() == pieceIQ) 
	  {
		  Coord testCoordStc(testCoord.getX(), testCoord.getY() + 2*dir);
#ifdef DEBUG
		  cout << "Checking enCoord: " << testCoordStc.getX() << " " << testCoordStc.getY() << endl;
#endif
		  if(testCoordStc.inBounds() && gb->getPiece(testCoordStc) == NULL) 
		  {
			  char inQue = gb->getPiece(testCoord)->getPiece();
			  bool canEP = gb->getHistory()->canEnPassant(testCoordStc, testCoord, inQue);
			  if (canEP) 
			  {
#ifdef DEBUG
				cout << "Possible En-Passant" << endl;
#endif
				Coord finalCoord(stc.getX() + coord, stc.getY() + dir);
				v.push_back(finalCoord);
			  }
		  }
	  }
	  if(coord == -1)  
		  break; 
	  else 
		  coord = -1; 
  }
  return v;
}
