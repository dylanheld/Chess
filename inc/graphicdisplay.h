#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "window.h"
//class Xwindow;

class GraphicDisplay {
	Xwindow *w;
public: 
	GraphicDisplay(Xwindow *);
	~GraphicDisplay();
	void notifyG(int row, int column, char ch);
};

#endif
