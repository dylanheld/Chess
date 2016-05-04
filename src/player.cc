#include <vector>
#include "player.h"
#include "pieces.h"
#include "coord.h"
#include <locale>

using namespace std;

Player::Player(GameBoard* gb, int colour): gb(gb), colour(colour) {}

bool Player::wouldPutInCheck(Coord stc, Coord endc, bool opponent, bool isKing) {
  #ifdef DEBUG
  cout << "WPIC::Running would put in CHECK" << endl;
  #endif  
  int colourConsidering = colour;
  if (opponent == true) {
    colourConsidering = 1 - colour;
  }

  map<int, map<int, Pieces*> > tempBoard;
  if ((stc.getX() == endc.getX()) && (stc.getY() == endc.getY())) {
    tempBoard = gb->makeTempBoard();
  } else {
    tempBoard = gb->makeTempBoard(stc, endc);
  }
  //Find location of the king and store it in a Coord
  int kingx;
  int kingy;
  for(int x = 0; x <= 7; x++) {
    for(int y = 0; y <= 7; y++) {
      if((tempBoard[x][y] != NULL) && 
         (tempBoard[x][y]->getColour() == colourConsidering) && 
         (tempBoard[x][y]->getPiece() == 'K' || tempBoard[x][y]->getPiece() == 'k')) {
         kingx = x;
         kingy = y;
      } 
    }
  }
  #ifdef DEBUG
  cout << "WPIC::got this king's coords, it is at: " << kingx << " " << kingy << endl;
  #endif
  Coord kc;
  if(isKing) {
 	kc = Coord(kingx, kingy);  
	}
	else {
		kc = endc;
	}

  //Find if there are people attacking the king (The Knight will need to be addressed seperately) 
  bool inCheck = false;
  for (int x = -1; x <= 1 && inCheck == false; x++) {
    for (int y = -1; y <= 1 && inCheck == false; y++) {
      if((x != 0) || (y != 0)) {
        //Going across all 8 possible directions
        int mag = 1;
        bool continueForward = true;
        while(continueForward) {
        int movex = kc.getX() + x*mag;
	int movey = kc.getY() + y*mag;
	Coord temp = Coord(movex, movey);
	#ifdef DEBUG	
	cout << "WPIC::Checking x and y for temp position: " << temp.getX() << " " << temp.getY() << endl;
        #endif  
	if(!temp.inBounds() || 
            ((tempBoard[movex][movey] != NULL) && (tempBoard[movex][movey]->getColour() == colourConsidering))) {
	  continueForward = false;
        } else if(tempBoard[movex][movey] == NULL) {
          mag++;
        } else {
          char p = tempBoard[movex][movey]->getPiece();
            if((y == 0) || (x == 0)) { //Horizontal or vertical attack
                if((p == 'Q') || (p == 'R') || (p == 'q') || (p == 'r'))  {
                  inCheck = true; 
                } else if(mag == 1) {
                  if((p == 'K') || (p == 'k')) inCheck = true; 
                }
            } else { //Diagonal Attack
              if((p == 'Q') || (p == 'B') || (p == 'q') || (p == 'b'))  {
                inCheck = true;
              } else if(mag == 1) {
                if((p == 'K') ||(p == 'k')) {
                  inCheck = true;
                } else if ((colourConsidering == 0) && (y == 1) && (p == 'p')) {
                  inCheck = true;
                } else if ((colourConsidering == 1) && (y == -1) && (p == 'P')) {
                  inCheck = true;
                }  
              }
            }
            continueForward = false;
          }
        }
      }
    }
  }
  //Special Check for Horses
  for (int x = -2; x <= 2 && inCheck == false; x++) {
    for (int y = -2; y <= 2 && inCheck == false; y++) {
      if((x != 0) && (y != 0) && (x != y) && (x != -y)) {
        Coord temp = Coord(kc.getX() + x, kc.getY() + y);
        #ifdef DEBUG
	cout << "Horse Coords check: " << temp.getX() << " " << temp.getY() << endl;
	#endif
	if(temp.inBounds() && tempBoard[temp.getX()][temp.getY()] != NULL) {
		char a = tempBoard[kc.getX()][kc.getY()]->getPiece(); //gb->getPiece(kc)->getPiece();
		char b = tempBoard[temp.getX()][temp.getY()]->getPiece(); //gb->getPiece(temp)->getPiece();

		if((isupper(a) && b == 'n') || (!(isupper(a)) && b == 'N')) {
			inCheck = true;
		}
	}
       }
    }
   }
  #ifdef DEBUG
  cout << "WPIC:: Returning: " << inCheck << endl;
  #endif
  return inCheck;
}

bool Player::isMyPiece(Pieces* p) {
  	if(p == NULL) {
		#ifdef DEBUG
		cerr << "There does not exist a piece at this location" << endl;
		#endif
		return false;
	}
	else {
		return (colour == p->getColour());
	}
}
