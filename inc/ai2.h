#ifndef AI2_H
#define AI2_H
#include "ai.h"
#include "gameboard.h"
class AI2 : public AI {
public:
	AI2(GameBoard*, int);
	void makeMove();
};
#endif
