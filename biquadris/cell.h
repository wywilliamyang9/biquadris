#ifndef _CELL_
#define _CELL_
#include "coordinates.h"
#include "info.h"
#include "colour.h"
class Cell : public Subject <Info> {
    Observer observers;
    Colour colour;
    bool blinded;
    Coordinates coordinates;

    public:
    Cell(int r,int c);

    Info getinfo() const override;
    void setInfo (const Info&);

    void blindCell();
    void unblindCell();
};
#endif
