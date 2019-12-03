#ifndef _CELL_
#define _CELL_
#include "coordinates.h"
#include "info.h"
#include "colour.h"
#include "subject.h"

class Cell : public Subject {
    Colour colour;
    bool blinded;
    Coordinates coordinates;
    int boardnum;
    bool currBlock;
    public:
    Cell(int r,int c, int boardnum);


    Info getinfo() const override;
    void setInfo (const Info&);
    void setCurrBlock(bool);
    bool getCurrBlock();
    void setColour(Colour);
    Colour getColour();

    void blindCell();
    void unblindCell();
};
#endif
