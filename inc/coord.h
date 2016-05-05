#ifndef COORD_H
#define COORD_H

#include <iostream>

class Coord 
{
  int x;
  int y;

public:
  Coord(int x = 0, int y = 0);
  int getX();
  int getY();
  Coord addCoord(int, int);
  bool inBounds();
  std::istream &operator>>(std::istream &in); 
};

#endif //COORD_H
