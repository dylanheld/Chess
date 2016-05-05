#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "gameboard.h"

class Human : public Player 
{
public:
	Human(GameBoard*, int);
	void makeMove();
};

#endif //HUMAN_H
