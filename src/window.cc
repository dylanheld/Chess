#include <X11/Xlib.h>
#include <X11/Xlocale.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height): width(width), height(height) {
//	cout << "running window initializer" << endl;
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
//	cout << xcolour.pixel << endl;
      colours[i]=xcolour.pixel;
  }
//  unsigned long p = 9394209;
  XSetForeground(d,gc,colours[Black]);
//  unsigned long p = 9394209;
  //fillRectangle(0, 0, width, height, p);
  // Make window non-resizeable.
  unsigned long p = 9394209;
        fillRectangle(0, 0, 584, 584, p);
  unsigned long c = 16436379;
        //string index = "87654321";
        char index = '8';
        for(int x = 18; x < 19; ++x) {
                for(int y = 80; y < 584;) {
                        string a = string() + index;
                        drawString(x, y, a, c);
                        --index;
                        y = y + 63;
                }
        }
        index = 'a';
        for(int y = 570; y < 571; ++y) {
                for(int x = 67; x < 540;) {
                        string a = string() + index;
                        drawString(x, y, a, c);
                        ++index;
                        x = x + 63;
                }
        }
//unsigned long p = 9394209;
//        fillRectangle(0, 0, 584, 584, p);

  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);
  usleep(2500);
  XSelectInput(d,w,ExposureMask);
  XFlush(d);
  XEvent event;
  XNextEvent(d,&event); //Hang until the window is ready.
  XSelectInput(d,w,0);
//  fillRectangle(0, 0, width, height, p);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, unsigned long colour) {
  XSetForeground(d, gc, colour);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, unsigned long colour) {
  XSetForeground(d, gc, colour);
  Font f = XLoadFont(d, "-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1");
 // Font f = XLoadFont(d, "-adobe-helvetica-bold-r-normal--20-0-400-400-p-0-iso8859-10");
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  //char *a = new char('a');
  //a = 'a';
//  Xutf8DrawString(d, w, NULL, gc, x, y, a, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  Font f = XLoadFont(d, "-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1"); 
// Font f = XLoadFont(d, "-adobe-helvetica-bold-r-normal--20-0-400-400-p-0-iso8859-10");
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  //char *a = new char('a');
  //a = 'a';
//  Xutf8DrawString(d, w, NULL, gc, x, y, a, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  //set default font
//  Font f = XLoadFont(d, "9x15");
	Font f = XLoadFont(d, "6x13");  
// Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

  XFontStruct * fStruct = XLoadQueryFont(d, name.str().c_str());

  if (fStruct) { //font was found, replace default
    f = fStruct->fid;
  }


  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
//  ti.font = f->fid;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
//  delete f;
	//font_extra(f)-> = fnt;
}

void Xwindow::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}
