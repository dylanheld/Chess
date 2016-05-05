#include <iostream>
#include "king.h"
#include "pieces.h"
using namespace std;

King::King(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> King::potentialMoves(Coord stc)
{
#ifdef DEBUG
	cout << " king Potential moves called" << endl;
#endif
	vector<Coord> v;
	for (int x = -1; x <= 1; x++) 
		for (int y = -1; y <= 1; y++) 
			if((x != 0) || (y != 0)) 
				if(stc.addCoord(x,y).inBounds() && ((gb->getPiece(stc.addCoord(x,y)) == NULL) || 
					(gb->getPiece(stc.addCoord(x,y))->getColour() != colour))) //A piece cannot move to its own spot
				{
					Coord test(stc.getX() + x, stc.getY() + y);
#ifdef DEBUG
					cout << "adding to king PM: " << test.getX() << test.getY() << endl;
#endif
					v.push_back(stc.addCoord(x,y));
				}
	int kStartX = 4;
	int kStartY = 7;
	char rookIQ = 'r';
	if(tp == 'K') 
	{
		kStartY = 0;
		rookIQ = 'R';
	}
	if(stc.getX() == kStartX && stc.getY() == kStartY) 
	{
		for(int i = 0;;) 
		{
			Coord rookPosition(i, kStartY);
			if(gb->getPiece(rookPosition) != NULL && gb->getPiece(rookPosition)->getPiece() == rookIQ) 
			{
				bool isEmpty = true;
				if(i == 0) 
				{
					for(int j = 1; j < 4; ++j) 
					{
						Coord emptySide(j, kStartY);
#ifdef DEBUG
						cout << "KIN:: Checking if pos: " << j << " " << kStartY << " is empty or not" << endl;
#endif
						if (gb->getPiece(emptySide) != NULL) 
						{
							isEmpty = false;
							break;
						}
					}
				}
				else 
				{
					for(int j = 6; j > 4; --j) 
					{
						Coord emptySide(j, kStartY);
#ifdef DEBUG
						cout << "KIN:: Checking if pos: " << j << " " << kStartY << " is empty or not" << endl;
#endif
						if (gb->getPiece(emptySide) != NULL) 
						{
							isEmpty = false;
							break;
						}
					}
				}
				if(isEmpty) 
				{
					bool canC = gb->getHistory()->ckMoved(tp, rookPosition);
					if (canC) 
					{
						int kMovement = 2;
						if (rookPosition.getX() == 0) 
							kMovement = -2;
						v.push_back(stc.addCoord(kMovement, 0));
					}
				}
			}
			if(i == 7)  
				break;
			else 
				i = 7;
		}
	}
	return v;
} 