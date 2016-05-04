#include "coord.h"
#include <iostream>
#include <sstream>

using namespace std;

//ASSUMPTION: That our coords are from (0,0) to (7,7)

Coord::Coord(int x, int y) : x(x), y(y) {}

int Coord::getX() 
{
  return x;
}

int Coord::getY() 
{
  return y;
}

Coord Coord::addCoord(int x, int y) 
{
  return Coord(this->x + x, this->y + y);
}

bool Coord::inBounds() {
  if ((getX() >= 0) && (getX() <= 7) && (getY() >= 0) && (getY() <= 7)) 
	  return true;
  return false;
}

istream &Coord::operator>>(istream &in) {
   string c;
   in >> c;
   stringstream s(c);
   char l;
   s >> l >> y;
   y--; 
   x = l - 'a';
   return in;
}
