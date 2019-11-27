#include "cell.h"
Cell::Cell(int r,int c): blinded{false},  
colour {Colour::White}{
    coordinates = Coordinates{r,c};
}

Info Cell::getinfo() {
    return Info {coordinates, colour, blinded};
}

void Cell::setinfo(cosnt Info& info) {
    coordinates = info.coordiantes;
    colour = info.colour;
    blinded = info.blinded;
}

void blindCell() {
    blinded = true;
    notifyObservers();
}

void unblindCell(){
    blinded = false;
    notifyObservers();
}

