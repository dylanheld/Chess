#include <stdlib.h>
#include <iostream>
#include "ai2.h"
#include "player.h"
#include <map>
#include <vector>
#include "pieces.h"
#include <ctime>
using namespace std;

AI2::AI2(GameBoard* gb, int colour): AI(gb, colour) {}

/*	AI2 performs 2 loops: 1st checks if any attacking move is possible and if so exceutes it, and 2nd runs if
*	1st fails causing the AI to choose a random move
*/
void AI2::makeMove()
{
	string canMove;
	while (cin >> canMove) 
	{
		map<Coord*, vector<Coord> > allMoves;
		if (canMove == "move") 
		{
			for (int Attack = 1; Attack >= 0; Attack--) 
			{
				for (int i = 0; i < 8; ++i) 
				{
					for (int j = 0; j < 8; ++j) 
					{
						Coord temp(i, j);
						vector<Coord> v;
						if (isMyPiece(gb->getPiece(temp))) 
						{
							v = gb->getPiece(temp)->potentialMoves(temp);
							for (vector<Coord>::iterator it = v.begin(); it != v.end();) 
							{
								if (wouldPutInCheck(temp, *it))
									it = v.erase(it);
								else if (Attack && (gb->getPiece(*it) == NULL)) 
								{
									if (!(wouldPutInCheck(temp, *it, true)))
										it = v.erase(it);
									else
										++it;
								}
								else
									++it;
							}
						}
						if (!(v.empty())) 
						{
							Coord* temp2 = new Coord(i, j);
							allMoves[temp2] = v;
						}
					}
				}
				if (!allMoves.empty())  
					break; 
			}
			// No attacking moves exist - try random move
			srand(time(NULL));
			map<Coord*, vector<Coord> >::iterator it = allMoves.begin();
			std::advance(it, rand() % allMoves.size());
			Coord* randKey = it->first;
			vector<Coord>::iterator et = allMoves[randKey].begin();
			std::advance(et, rand() % allMoves[randKey].size());
			Coord randVal = *et;
			string promotedPiece;
			bool canPP = false;
			if (colour == 0 && randVal.getY() == 7 && gb->getPiece(*randKey)->getPiece() == 'P') 
			{
				string possiblePromotions[4] = { "R", "N", "B", "Q" };
				promotedPiece = possiblePromotions[rand() % 4];
				canPP = true;
			}
			else if (!(canPP) && colour == 1 && randVal.getY() == 0 && gb->getPiece(*randKey)->getPiece() == 'p') 
			{
				string possiblePromotions[4] = { "r", "n", "b", "q" };
				promotedPiece = possiblePromotions[rand() % 4];
				canPP = true;
			}
			gb->commitMove(*randKey, randVal);
			if (canPP)
				gb->promotePawn(randVal, promotedPiece);
			for (map<Coord*, vector<Coord> >::iterator it = allMoves.begin(); it != allMoves.end(); ++it)
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
