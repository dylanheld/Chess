#include <iostream>
#include <vector>
#include "pieces.h"
using namespace std;

Pieces::Pieces(char tp, GameBoard *gb, int colour): tp(tp), gb(gb), colour(colour)
{
#ifdef DEBUG
	cout << "Made Piece with char: " << this->tp << endl;
#endif
}

Pieces::~Pieces() {}

int Pieces::getColour() 
{
	return colour;
}

char Pieces::getPiece() 
{
	return tp;
}
