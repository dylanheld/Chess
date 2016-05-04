#ifndef AI1_H
#define AI1_H
#include "ai.h"
#include "gameboard.h"
class AI1 : public AI {
public:
	AI1(GameBoard*, int);
	void makeMove();
};
#endif
