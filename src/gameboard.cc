#include <iostream>
#include <locale>
#include "gameboard.h"
#include "pawn.h"
#include "queen.h"
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "view.h"
#include "textdisplay.h"
#include "coord.h"
#include "history.h"
#include "player.h"
using namespace std;

GameBoard::GameBoard() {
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			theBoard[i][j] = NULL;
		}
	}
        inCheck = false;
        resign = false;
//        playingGame = false;
        readingFile = false;
	td = new TextDisplay(8, this);
	moveHistory = new History();
}

GameBoard::~GameBoard() {
	for(int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if(theBoard[i][j] != NULL) {
				delete theBoard[i][j];
			}
		}
	}
	delete moveHistory;
	delete td;
}


int GameBoard::readFile(ifstream& ifs) {
	string line;
	for(int i = 0; i < 8; ++i) {
		getline(ifs, line);
		for(int j = 0; j < 8; ++j) {
			if (line[j] != '-') {
				this->setPiece(j, 7 - i, line[j]);
			}
		}
	}
	getline(ifs, line);
	if (line[0] == 'W') {
		return 0;
	}
	else {
		return 1;
	}
}

void GameBoard::setPiece(int i, int j, char x) {
	removePiece(i, j);
	int colour;
	if (isupper(x)) {
		colour = 0;
	}
	else {
		colour = 1;
	}
	if (x == 'p' || x == 'P') {	
		theBoard[i][j] = new Pawn(x, this, colour);
	}
	else if(x == 'r' || x == 'R') {
		theBoard[i][j] = new Rook(x, this, colour);
	}
	else if(x == 'k' || x == 'K') {
		theBoard[i][j] = new King(x, this, colour);
	}
	else if(x == 'q' || x == 'Q') {
		theBoard[i][j] = new Queen(x, this, colour);
	}
	else if(x == 'b' || x == 'B') {
		theBoard[i][j] = new Bishop(x, this, colour);
	}
	else if(x == 'n' || x == 'N') {
		theBoard[i][j] = new Knight(x, this, colour);
	}
	notify(i, j, x);
	print();
}

void GameBoard::notify(int row, int column, char piece) {
        td->notify(row, column, piece);
}

void GameBoard::print() {
	td->print(cout);
}

void GameBoard::removePiece(int i, int j, bool ace) {
        if(theBoard[i][j] != NULL) {
                delete theBoard[i][j];
                theBoard[i][j] = NULL;
                notify(i,j, '_');
		if(ace) {
                	print();
		}
        }
}

Pieces* GameBoard::getPiece(Coord loc) {
	return theBoard[loc.getX()][loc.getY()];
}

void GameBoard::commitMove(Coord stc, Coord endc) {
  bool castling = false;
  bool passant = false;
  bool pPromote = false;
  if(getPiece(stc)->getPiece() == 'K' || getPiece(stc)->getPiece() == 'k') {
	int moveOrientation = endc.getX() - stc.getX();
	if (moveOrientation == -2 || moveOrientation == 2) {
		castling = true;
		if(moveOrientation < 0) {
			Coord rookstc(0, stc.getY());
			Coord rookendc(stc.getX() - 1 ,stc.getY());
			commitMove(rookstc, rookendc);
		}
		else {
			Coord rookstc(7, stc.getY());
			Coord rookendc(stc.getX() + 1, stc.getY());
			commitMove(rookstc, rookendc);
		}
	}
  }
  if(getPiece(stc)->getPiece() == 'p' || getPiece(stc)->getPiece() == 'P') {
	int moveOrientation = endc.getX() - stc.getX();
	if (getPiece(endc) == NULL && (moveOrientation == -1 || moveOrientation == 1)) {
		passant = true;
		if(moveOrientation == -1) {
			removePiece(stc.getX() - 1, stc.getY());
                	theBoard[stc.getX() - 1][stc.getY()] = NULL;
                	notify(stc.getX() - 1, stc.getY(), '_');
		}
		else if(moveOrientation == 1) {
			removePiece(stc.getX() + 1, stc.getY());
                	theBoard[stc.getX() + 1][stc.getY()] = NULL;
                	notify(stc.getX() + 1, stc.getY(), '_');
		}	
	}
	else if((endc.getY() == 0 && getPiece(stc)->getPiece() == 'p') || (endc.getY() == 7 && getPiece(stc)->getPiece() == 'P')) {
		pPromote = true;
	}
  }
  moveHistory->addHistory(stc, endc, getPiece(stc)->getPiece());
  removePiece(endc.getX(), endc.getY());
  theBoard[endc.getX()][endc.getY()] = theBoard[stc.getX()][stc.getY()];
  theBoard[stc.getX()][stc.getY()] = NULL;
  notify(endc.getX(), endc.getY(), getPiece(endc)->getPiece());
  notify(stc.getX(), stc.getY(), '_');
  
  // Checking for Castling...
 
	if(!(castling || passant || pPromote)) {
  		print();
	}
}

map<int, map<int, Pieces*> > GameBoard::makeTempBoard(Coord stc, Coord endc) {
  map<int, map<int, Pieces*> > tempBoard;
  for(int x = 0; x <=7; x++) {
    for(int y = 0; y <= 7; y++) {
      tempBoard[x][y] = theBoard[x][y];
    }
  }
  tempBoard[endc.getX()][endc.getY()] = tempBoard[stc.getX()][stc.getY()];
  tempBoard[stc.getX()][stc.getY()] = NULL;
  return tempBoard;
}

map<int, map<int, Pieces*> > GameBoard::makeTempBoard() {
  map<int, map<int, Pieces*> > tempBoard;
  for(int x = 0; x <=7; x++) {
    for(int y = 0; y <= 7; y++) {
      tempBoard[x][y] = theBoard[x][y];
    }
  }
  return tempBoard;
}


bool GameBoard::gameOver(Player *currPlayer) {
  if (resign == true) {
    return true;
  }
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      Coord temp(i,j);
      if((getPiece(temp) != NULL) && currPlayer->isMyPiece(getPiece(temp))) {
        vector<Coord> v;
        v = getPiece(temp)->potentialMoves(temp);
        for(vector<Coord>::iterator it = v.begin(); it != v.end();) {
	  if(currPlayer->wouldPutInCheck(temp, *it)) { 
	    it = v.erase(it);
	  } else {
	    ++it;
	  }
	}
	if(!(v.empty())) {
	  return false;
	}
      }
    }
  }
   return true;
}

int GameBoard::getWinner(Player *C, int colorOfC) {
  if (resign == true) {
	return colorOfC;
  }
  else if (C->wouldPutInCheck(Coord(0,0),Coord(0,0))) { //Having the same coord check if the current board is in check
    return 1 - colorOfC;
  } 
   else {
  	return -1;
   }  
}

History* GameBoard::getHistory() { 
	return moveHistory;
}

void GameBoard::promotePawn(Coord endc, string toChange) {
	removePiece(endc.getX(), endc.getY());
	setPiece(endc.getX(), endc.getY(), toChange[0]);
	notify(endc.getX(), endc.getY(), getPiece(endc)->getPiece());
  	moveHistory->addHistory(endc, endc, getPiece(endc)->getPiece());
}
/*
bool GameBoard::isPlayingGame() {
  return playingGame;
}
*/
bool GameBoard::isResigned() {
  return resign;
}

bool GameBoard::isReadingFile() {
  return readingFile;
}
/*
void GameBoard::setPlayingGame(bool setTo) {
  playingGame = setTo;
}
*/
void GameBoard::setResigned(bool setTo) {
  resign = setTo;
}

void GameBoard::setReadingFile(bool setTo) {
  readingFile = setTo;
}
