#include <iostream>
#include <string>
#include "gameboard.h"
#include "pieces.h"
#include "human.h"
using namespace std;

bool checkValidPosition(string inputCommand)
{
	bool isValidPosition = false;
	for(char i = 'a'; i < 'i'; ++i) 
	{
		for(char j = '1'; j < '9'; ++j) 
		{
			string a;
			a = a + i + j;
			if (inputCommand == a) 
			{
				isValidPosition = true;
				break;
			}
		}
	}
	return isValidPosition;
}


bool checkBoard(GameBoard *G) 
{
	int numWK = 0;
	int numBK = 0;
	Coord BkCoord(0,0);
	Coord WkCoord(0,0);
	for(int i = 0; i < 8; ++i)
		for(int j = 0; j < 8; ++j) 
		{
			Coord temp(i ,j);
			if(G->getPiece(temp) != NULL) 
			{
				char a = G->getPiece(temp)->getPiece();
				if(a == 'k') { ++numBK; BkCoord.addCoord(temp.getX(), temp.getY()); }
				else if(a == 'K') { ++numWK; WkCoord.addCoord(temp.getX(), temp.getY()); }
				else if(a == 'p' && j == 0)  return false; 
				else if(a == 'P' && j == 7)  return false; 
			}
		}
	if(numWK != 1 || numBK != 1)  
		return false; 
	else {
		Player *temp = new Human(G, 0);
		Player *temp2 = new Human(G, 1);
		if (temp->wouldPutInCheck(WkCoord, WkCoord) || temp2->wouldPutInCheck(BkCoord, BkCoord))
		{
			delete temp; delete temp2;
			return false;
		}
		else
		{
			delete temp;
			delete temp2;
			return true;
		}
	}
}

void setupINIT(GameBoard *G, int *curr) 
{
	string inputline[3];
	int index = 0;
	string inputCommand;
	while(cin >> inputCommand) 
	{
		if(index == 0) 
		{
			if (inputCommand == "done") 
			{
				if(checkBoard(G))  
					break; 
				else  
					cerr << "Cannot leave setup mode, board is presently invalid" << endl;
			}
			else if (inputCommand == "=" || inputCommand == "+" || inputCommand == "-")
			{
				inputline[index] = inputCommand;
				++index;
			}
			else 
				cerr << "Command " << inputCommand << " is invalid" << endl;
		}
		else if (index == 1) 
		{
			if(inputline[0] == "-") 
			{
				bool isValidPosition = checkValidPosition(inputCommand);
				if (isValidPosition) 
				{
					int i = inputCommand[0] - 'a';
					int j = inputCommand[1] - '1';
					G->removePiece(i, j, true);	
				}
				else
					cerr << "Inputted position is not valid" << endl;
				index = 0;
			}
			else if(inputline[0] == "+") 
			{
				if(inputCommand == "p" || inputCommand == "P" || inputCommand == "k" || 
					inputCommand == "K" || inputCommand == "r" || inputCommand == "R" || 
					inputCommand == "n" || inputCommand == "N" || inputCommand == "b" || 
					inputCommand == "B" || inputCommand == "q" || inputCommand == "Q") 
				{
					inputline[index] = inputCommand;
					++index;
				}
				else 
				{
					cerr << "Inputted piece is invalid" << endl;
					index = 0;
				}
			}
			else 
			{
				if(inputCommand == "white")
					*curr = 0;
				else if(inputCommand == "black") 
					*curr = 1;					
				index = 0;
			}
		}
		else 
		{
			bool isValidPosition = checkValidPosition(inputCommand);
			if (isValidPosition) 
				G->setPiece(inputCommand[0] - 'a', (inputCommand[1] - '1'), inputline[1][0]);	
			else
				cerr << "Inputted position in invalid" << endl;              
			index = 0; 
		}
	}
}
