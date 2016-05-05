#include <stdlib.h>
#include <iostream>
#include "ai1.h"
#include "player.h"
#include <map>
#include <vector>
#include "pieces.h"
#include <ctime>
using namespace std;

AI1::AI1(GameBoard* gb, int colour): AI(gb, colour) {}

void AI1::makeMove() 
{
#ifdef DEBUG
	cout << "running ai move" << endl;
#endif
	map<Coord*, vector<Coord> > allMoves;
	string canMove;
	while(cin >> canMove) 
	{
		if (canMove == "move") 
		{
			for(int i = 0; i < 8; ++i) 
				for(int j = 0; j < 8; ++j) 
				{
					Coord temp(i, j);
					if(isMyPiece(gb->getPiece(temp))) 
					{
						vector<Coord> v;
						v = gb->getPiece(temp)->potentialMoves(temp);
						for(vector<Coord>::iterator it = v.begin(); it != v.end();) 
						{
							if(wouldPutInCheck(temp, *it)) 
								it = v.erase(it);
							else
								++it;
						}
						if (!(v.empty())) 
						{
							Coord* temp2 = new Coord(i,j);
							allMoves[temp2] = v;		
						}
					}
				}
		// Do Random move
		srand (time(NULL));
		map<Coord*, vector<Coord> >::iterator it = allMoves.begin();
		std::advance(it, rand() % allMoves.size());
		Coord* randKey = it->first;
#ifdef DEBUG
		cout << "Random Coord is: " << randKey->getX() << " " << randKey->getY() << endl;
#endif
		vector<Coord>::iterator et = allMoves[randKey].begin();
		std::advance(et, rand() % allMoves[randKey].size());
		Coord randVal = *et;
#ifdef DEBUG
		cout << "Random move is: " << randVal.getX() << " " << randVal.getY() << endl;	
#endif
		string promotedPiece;
		bool canPP = false;
		if (colour == 0 && randVal.getY() == 7 && gb->getPiece(*randKey)->getPiece() == 'P') 
		{
			string possiblePromotions[4] = {"R", "N", "B", "Q"};
			promotedPiece = possiblePromotions[rand() % 4];
			canPP = true;
		}
		else if(!(canPP) && colour == 1 && randVal.getY() == 0 && gb->getPiece(*randKey)->getPiece() == 'p') 
		{
			string possiblePromotions[4] = {"r", "n", "b", "q"};
			promotedPiece = possiblePromotions[rand() % 4];
			canPP = true;
		}
		gb->commitMove(*randKey, randVal);
		if(canPP)
			gb->promotePawn(randVal, promotedPiece);
		for(map<Coord*, vector<Coord> >::iterator it = allMoves.begin(); it != allMoves.end(); ++it)
			delete it->first;
		break;
		}
		else if (canMove == "resign") 
		{ 
			gb->setResigned(true); 
			break; 
		}
		else 
			cerr << "Invalid input request, please enter either move or resign" << endl; 
	}
}
