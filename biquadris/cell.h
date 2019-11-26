#ifndef _CELL_
#define _CELL_
#include "coordinates.h"

class Cell : public Subject <Info> {
    Observer observers;

    char value;
    bool blinded;
    Coordinates coordinates;

    public:
    Coordinates getinfo() const override;

    void blindCell();
    void unblindCell();
    void setValue();
    void getValue();

    Cell (Coordinates);
};
#endif
