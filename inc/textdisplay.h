#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <sstream>
#include "view.h"

class GameBoard;
class GraphicDisplay;
class TextDisplay : public View 
{
	char **theDisplay;          //the n x n display 
	GameBoard *gb;
public:
	TextDisplay(int n, GameBoard*);
	~TextDisplay();
	/*
	* The Controller calls notify to update the (row,column) location to be ch
	*/
	virtual void notify(int row, int column, char ch);
	/*
	* Prints the grid as specified in the assignment specification.
	*/
	void print(std::ostream &out) const ;
};

#endif	//TEXTDISPLAY_H
