#ifndef WINDOW_H
#define WINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  int width, height;

 public:
  Xwindow(int width=584, int height=584);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);
void drawString(int x, int y, std::string msg, unsigned long colour);
  // Draws a string
  void drawBigString(int x, int y, std::string msg, int colour=Black);
void fillRectangle(int x, int y, int width, int height, unsigned long colour);
  // Prints the first 10000 available fonts
  void showAvailableFonts();
};

#endif
