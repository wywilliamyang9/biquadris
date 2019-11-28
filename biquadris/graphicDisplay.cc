//#define DEBUG
#include "graphicdisplay.h"
using namespace std;

void GraphicsDisplay::notify(Subject<Info, State>& whoFrom) {
    State s = whoFrom.getState();
    if (s.type == StateType::NewPiece || s.type == StateType::Reply) {
        const int r = whoFrom.getInfo().row;
        const int c = whoFrom.getInfo().col;
        const Colour co = whoFrom.getInfo().colour;

        int gridSize = 500/getSize();
        if (co == Colour::Black) {
            window->fillRectangle(c*gridSize,r*gridSize,gridSize,gridSize,Xwindow::Black);
        } else {
            window->fillRectangle(c*gridSize,r*gridSize,gridSize,gridSize,Xwindow::White);
        }
    }
}                                               

void GraphicsDisplay::displayWinMessage(Colour colour) {
    if (colour == Colour::NoColour) {
		window->drawString(250, 250, "Tie!");
	}
	else if (colour == Colour::Black){
        window->drawString(250, 250, "Black wins!");
	}
	else {
        window->drawString(250, 250, "White wins!");
    }
}

int GraphicsDisplay::getSize() const {return size;}

GraphicsDisplay::GraphicsDisplay (int s) : size{s} {
    window = new Xwindow();
#ifdef DEBUG
    cout << "GraphicDisplay cotr body runs" << endl;
#endif
    window->fillRectangle(0,0,500,500,Xwindow::Blue);
#ifdef DEBUG
    cout << "GraphicDisplay cotr body ends" << endl;
#endif
}

GraphicsDisplay::~GraphicsDisplay () {
    delete window;
}
