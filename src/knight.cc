#include <iostream>
#include "knight.h"
#include "pieces.h"
#include <vector>
using namespace std;

Knight::Knight(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> Knight::potentialMoves(Coord stc){
	#ifdef DEBUG
	cout << "knight potential moves called" << endl;
	#endif
	vector<Coord> v;
	for(int dirx = 1;;) {
		//Coord temp = stc;
		for(int diry = 1;;) {
			for(int i = 1, j = 2; i < 3; ++i, --j) {
				Coord temp = stc;
				int testx = i*dirx;
				int testy = j*diry;
				//cout << "x is: " << testx << " , y is: " << testy << endl;
				temp = temp.addCoord(testx, testy);
				if(temp.inBounds() && (gb->getPiece(temp) == NULL || gb->getPiece(temp)->getColour() != colour)) {
                               		v.push_back(temp);
                       		}
			}
			if(diry == -1) { break; }
			else { diry = -1; }
		}
		if(dirx == -1) { break; }
                else { dirx = -1; }
	}
	return v;	
}
