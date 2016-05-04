#include <iostream>
#include "history.h"
#include "pieces.h"
#include "coord.h"
#include <vector>
#include <fstream>
using namespace std;

void History::addHistory(Coord BL, Coord EL, char MP) 
{
	char letterCoordBL = BL.getX() + 'a';
	char numberCoordBL = BL.getY() + '1';
	char letterCoordEL = EL.getX() + 'a';
	char numberCoordEL = EL.getY() + '1';
	char space = 32;
	string returnStr = string() + MP + space + letterCoordBL + numberCoordBL + space + letterCoordEL + numberCoordEL;
#ifdef DEBUG
	cout << "HIST:: Added history: " << returnStr << endl;
#endif
	hist.push_back(returnStr);
}

bool History::ckMoved(char kingP, Coord RP) 
{
	bool castling = true;
	char rookP = 'r';
	if (isupper(kingP))
		rookP = 'R';
	for(vector<string>::iterator it = hist.begin(); it != hist.end(); ++it) 
	{
#ifdef DEBUG
		cout << "checking history string: " << *it << endl;
#endif
		string currHist = *it;
		if(currHist[0] == kingP) 
		{
			castling = false;
			break;
		}
		else if (currHist[0] == rookP && currHist[2] - 'a' == RP.getX() && currHist[3] - '1' == RP.getY()) 
		{
			castling = false;
			break;
		}
	}
	return castling;
}
bool History::canEnPassant(Coord stc, Coord endc, char Que) 
{
	string lastMove = *hist.rbegin();
	if(lastMove[0] == Que && lastMove[2] - 'a' == stc.getX() && lastMove[3] - '1' == stc.getY() && lastMove[5] - 'a' == endc.getX() && lastMove[6] - '1' == endc.getY())
		return true;
	else 
		return false;
}
