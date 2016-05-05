#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include "coord.h"

class History 
{
	std::vector<std::string> hist;
public:
	bool ckMoved(char, Coord);
	bool canEnPassant(Coord stc, Coord endc, char Que);
	void addHistory(Coord, Coord, char);
};

#endif	//HISTORY_H
