#ifndef AI4_H
#define AI4_H

#include "ai.h"
#include "gameboard.h"

class AI4 : public AI 
{
public:
	AI4(GameBoard*, int);
	void makeMove();
};

#endif //AI4_H
