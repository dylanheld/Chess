#include <iostream>
#include "rook.h"
#include "pieces.h"
#include <vector>
#include "coord.h"
using namespace std;

Rook::Rook(char tp, GameBoard *gb, int colour): Pieces(tp, gb, colour) {}

vector<Coord> Rook::potentialMoves(Coord stc){
	#ifdef DEBUG
        cout << "Rook potential moves called" << endl;
	#endif	
        vector<Coord> v;
        for(int dir = 1;;) {
                Coord temp = stc;
                // Check Vertical moves
                while(temp.addCoord(0, dir).inBounds()) {
                        temp = temp.addCoord(0, dir);
                        if(gb->getPiece(temp) == NULL) {
                                v.push_back(temp);
                        }
                        else {
                                if (gb->getPiece(temp)->getColour() != colour) {
                                        v.push_back(temp);
                                }
                                break;
                        }
                }
                temp = stc;
                // Check horizontal moves
                while(temp.addCoord(dir, 0).inBounds()) {
                        temp = temp.addCoord(dir, 0);
                        if(gb->getPiece(temp) == NULL) {
                                v.push_back(temp);
                        }
                        else {
                                if (gb->getPiece(temp)->getColour() != colour) {
                                        v.push_back(temp);
                                }
                                break;
                        }
                }
                if (dir == -1) { break;}
                else { dir = -1; }
        }
        return v;
}
