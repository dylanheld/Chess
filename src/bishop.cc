#include <iostream>
#include "bishop.h"
#include "pieces.h"
using namespace std;

Bishop::Bishop(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> Bishop::potentialMoves(Coord stc){
	#ifdef DEBUG
	cout << "Bishop potential moves called" << endl;
	#endif
	vector<Coord> v;
	for (int dir = 1;;) {
		Coord temp = stc;
		// Check right moves
		while(temp.addCoord(1, dir).inBounds()) {
			temp = temp.addCoord(1, dir);
			if(gb->getPiece(temp) == NULL) {
				v.push_back(temp);
			
			}
			else {
				if(gb->getPiece(temp)->getColour() != colour) {
					v.push_back(temp);
				}
				break;
			}
		}
		temp = stc;
		// Check left diagonals
		while(temp.addCoord(-1, dir).inBounds()) {
                        temp = temp.addCoord(-1, dir);
                        if(gb->getPiece(temp) == NULL) {
                                v.push_back(temp);
                        }
                        else {
                                if(gb->getPiece(temp)->getColour() != colour) {
                                        v.push_back(temp);
                                }
                                break;
                        }
                }
		if (dir == -1) { break; }
		else { dir = -1; }
	}
	return v;
}
