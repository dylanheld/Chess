#include <iostream>
#include "queen.h"
#include "pieces.h"
using namespace std;

Queen::Queen(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> Queen::potentialMoves(Coord stc){
  #ifdef DEBUG
  cout << "Queen Potential moves called" << endl;
  #endif
  vector<Coord> v;

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      if((x != 0) || (y != 0)) {
        //Going across all 8 possible directions
        int mag = 1;
        bool continueForward = true;
        while(continueForward) {
          Coord c = Coord(stc.getX() + x*mag, stc.getY() + y*mag);
          //cout << "Cord analized: x = " << c.getX() << " y = " << c.getY() << endl;
          //cout << c.inBounds() << endl; 
          if (!(c.inBounds())) {
            continueForward = false;
          } else if(gb->getPiece(c) == NULL) {
            v.push_back(c);
            mag++;
          } else if(gb->getPiece(c)->getColour() != colour) {
            v.push_back(c);
            continueForward = false;
          } else {
            continueForward = false;
          }
        }
      }
    }
  } 
  //cout << "Not stuck in queen loop";
  return v;
}
