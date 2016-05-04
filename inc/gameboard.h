#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <fstream>
#include <map>
#include "view.h"
#include "coord.h"
#include "history.h"
class Pieces;
class Player;

class GameBoard {
	std::map <int, std::map<int, Pieces*> > theBoard;
	View *td;
	History *moveHistory;
	bool inCheck;
//	bool playingGame;	
	bool readingFile;
	bool resign;
	
public:
	GameBoard();
	~GameBoard();
	void setPiece(int i, int j, char x);
	void removePiece(int i, int j, bool ace = false);
	void commitMove(Coord, Coord);
	int readFile(std::ifstream& ifs);
	void notify(int row, int column, char piece);
	void print();
	Pieces* getPiece(Coord);
	std::map<int, std::map<int, Pieces*> > makeTempBoard(Coord, Coord);
	std::map<int, std::map<int, Pieces*> > makeTempBoard();
	bool gameOver(Player*);
	int getWinner(Player*, int);
	History* getHistory();
	void promotePawn(Coord endc, std::string toChange);
//	bool isPlayingGame();
	bool isResigned();
	bool isReadingFile();
 //       void setPlayingGame(bool);
        void setResigned(bool);
        void setReadingFile(bool);
};
#endif
