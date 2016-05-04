#ifndef AI3_H
#define AI3_H
#include "ai.h"
#include "gameboard.h"
class AI3 : public AI {
public:
	AI3(GameBoard*, int);
	void makeMove();
};
#endif
