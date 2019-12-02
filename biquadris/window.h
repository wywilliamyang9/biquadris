#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];

public:
	Xwindow(int width=675, int height=650);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.
	Xwindow(const Xwindow&) = delete;
	Xwindow &operator=(const Xwindow&) = delete;

	enum {White=0, Black, Red, Green, Blue, Orange, Yellow, Purple, Cyan, Brown}; // Available colours.

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

	// Draws a string
	void drawString(int x, int y, std::string msg);

	// Draws a line from (x1, y1) to (x2, y2)
	void drawLine(int x1, int y1, int x2, int y2);

};

#endif