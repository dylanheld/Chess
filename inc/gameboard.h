#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <fstream>
#include <map>
#include "view.h"
#include "coord.h"
#include "history.h"

class Pieces;
class Player;
class GameBoard 
{
	std::map <int, std::map<int, Pieces*> > theBoard;
	View *td;
	History *moveHistory;
	bool inCheck;
	bool readingFile;
	bool resign;
	
public:
	GameBoard();
	~GameBoard();
	void setPiece(int, int, char);
	void removePiece(int, int, bool ace = false);
	void commitMove(Coord, Coord);
	int readFile(std::ifstream&);
	void notify(int, int, char);
	void print();
	Pieces* getPiece(Coord);
	std::map<int, std::map<int, Pieces*> > makeTempBoard(Coord, Coord);
	std::map<int, std::map<int, Pieces*> > makeTempBoard();
	bool gameOver(Player*);
	int getWinner(Player*, int);
	History* getHistory();
	void promotePawn(Coord, std::string);
	bool isResigned();
	bool isReadingFile();
	void setResigned(bool);
	void setReadingFile(bool);
};

#endif //GAMEBOARD_H
