#include "cell.h"
Cell::Cell(int r,int c): blinded{false},  
colour {Colour::White}, boardnum{boardnum}{
    coordinates = Coordinates{r,c};
}

Info Cell::getinfo() {
    return Info {coordinates, colour, blinded, boardnum};
}

void Cell::setinfo(cosnt Info& info) {
    coordinates = info.coordiantes;
    colour = info.colour;
    blinded = info.blinded;
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

