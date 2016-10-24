//#include "window.cc"
#include "graphicdisplay.h"
#include <iostream>
#include <locale>
using namespace std;

GraphicDisplay::~GraphicDisplay() {
//	delete w;
//	w = new Xwindow;
}

GraphicDisplay::GraphicDisplay(Xwindow *q): w(q) { 
	unsigned long p = 9394209;
    w->fillRectangle(0, 0, 584, 584, p);
	int dimension = 63;
//      void fillRectangle(int x, int y, int width, int height, int colour=Black);
    unsigned long c = 16436379;
        //string index = "87654321";
        /*char index = '8';
        for(int x = 18; x < 19; ++x) {
                for(int y = 80; y < 584;) {
                        string a = string() + index;
                        w->drawString(x, y, a, c);
                        --index;
                        y = y + 63;
                }
        }
        index = 'a';
        for(int y = 570; y < 571; ++y) {
                for(int x = 67; x < 540;) { 
                        string a = string() + index;
                        w->drawString(x, y, a, c);
                        ++index;
                        x = x + 63;
                }
        } */
	for(int x = 40; x < 540;) {
                for(int y = 40; y < 540;) {
                        w->fillRectangle(x, y, dimension, dimension, c);
                        //unsigned long blueee = 2003199;
                        //w.fillRectangle(x, y, dimension, dimension, blueee);
                        if (c == 16436379) { c = 13404743; }
                        else { c = 16436379; }
                        y = y + 63;
                }
                if (c == 16436379) { c = 13404743; }
                else { c = 16436379; }
                x = x + 63;
        }              
}

void GraphicDisplay::notifyG(int row, int column, char ch) {
	unsigned long c = 16436379;
	if((((row + 2) % 2 == 0) && ((column + 2) % 2 == 0)) || (((row + 1) % 2 == 0) && ((column + 1) % 2 == 0))) {
		c = 13404743;
	}
	if (ch == '_') {
		w->fillRectangle(row*63 + 40, (7 - column)*63 + 40, 63, 63, c);
	}
	else {
		int c = w->Black;
		if(isupper(ch)) {
			c = w->White;
		}
		//cout << "row/col is: " << row << " " << column << endl;
		//int x = 7 - row;
		string inputPiece = string() + ch;
		//cout << "outing: " << column << " " << x << endl;
		w->drawBigString(row*63 + 59, (7 - column)*63 + 85, inputPiece, c);
	}
}



//GraphicDisplay::resetBoard
