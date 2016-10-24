#include "textdisplay.h"
#include "gameboard.h"
#include "graphicdisplay.h"
using namespace std;

/*********** notify ************
Purpose: Notifies the grid at [row][column] to have its state updated to ch
Returns: Void
*******************************/
void TextDisplay::notify(int row, int column, char ch) 
{
	theDisplay[row][column] = ch;
	gd->notifyG(row, column, ch);
}

/*********** print **************
Purpose: prints grid via out
Returns: Void
Side Effects: Prints grid via out
*********************************/
void TextDisplay::print(std::ostream &out) const 
{
	// Loop runs until reaching gridsize
	//NOTE: The messages will be addresssed by main.
	if (gb->isReadingFile()) 
		return;		// Dont print changes from reading a file
	for(int i = gridSize - 1; i >= 0; --i) 
	{
		out << i + 1 << " ";				// Loop runs until reaching gridsize
		for(int j = 0; j < gridSize; ++j) 
		{
			if (theDisplay[j][i] == '_') 
			{
				if((j+i)%2 == 0) 
					cout << '_';
				else 
					cout << ' ';
			} 
			else 
				out << theDisplay[j][i];	// output the cell at [i][j]'s state
		}
		out << endl;
	}
	out << "  ";
	for (char i = 'a'; i < 'i'; ++i)
		out << i;
	out << endl;
}

// TextDisplay Destructor
TextDisplay::~TextDisplay() 
{
	for(int i = 0; i < gridSize; ++i)
		delete[] theDisplay[i];
	delete[] theDisplay;
}

// TextDisplay constructor
TextDisplay::TextDisplay(int n, GameBoard *G, Xwindow *q): View(n), gb(G) 
{
	theDisplay = new char*[n];	// Dynamically allocate theDisplay
	for(int i = 0; i < n; ++i) 
	{
		theDisplay[i] = new char[n];	// allocate columns for this row
		for(int j = 0; j < n; j++)
			theDisplay[i][j] = '-';		// set initialize state of grid cells to be 0
	}
	gd = new GraphicDisplay(q);
}
