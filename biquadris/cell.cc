#include "cell.h"
Cell::Cell(int r,int c, int boardnum): blinded{false},
colour {Colour::White}, boardnum{boardnum}{
    coordinates = Coordinates{r,c};
}

Info Cell::getinfo() const {
    return Info {coordinates, colour, blinded, boardnum};
}

void Cell::setInfo(const Info& info) {
    coordinates = info.coord;
    colour = info.colour;
    blinded = info.blinded;
    boardnum = info.boardnum;
    notifyObservers();
}

void Cell::setCurrBlock(bool b){
    currBlock = b;
}
bool Cell::getCurrBlock(){return currBlock;}
void Cell::blindCell() {
    blinded = true;
    notifyObservers();
}

void Cell::unblindCell(){
    blinded = false;
    notifyObservers();
}

void Cell::setColour(Colour colour) {
	this->colour = colour;
    notifyObservers();
}
Colour Cell::getColour() {
	return colour;
}
