#include <iostream>
#include "queen.h"
#include "pieces.h"
using namespace std;

Queen::Queen(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> Queen::potentialMoves(Coord stc)
{
#ifdef DEBUG
	cout << "Queen Potential moves called" << endl;
#endif
	vector<Coord> v;
	for (int x = -1; x <= 1; x++) 
		for (int y = -1; y <= 1; y++) 
			if((x != 0) || (y != 0)) 
			{
				//Check all 8 possible orientations of movement
				int mag = 1;	// Magnitude of movement (e.g. number of tiles stepped)
				bool continueForward = true;
				while(true) 
				{
					Coord c = Coord(stc.getX() + x*mag, stc.getY() + y*mag);
					if (!(c.inBounds()))
						break;
					else if(gb->getPiece(c) == NULL) 
					{
						// Move possible and can move further
						v.push_back(c);
						mag++;
					} 
					else if(gb->getPiece(c)->getColour() != colour) 
					{
						// Move possible, can not move further
						v.push_back(c);
						break;
					} 
					else
						break;
				}
			}
	return v;
}
