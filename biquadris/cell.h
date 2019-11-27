#ifndef _CELL_
#define _CELL_
#include "coordinates.h"
#include "info.h"

class Cell : public Subject <Info> {
    Observer observers;

    char value; // 'e' when empty.
    bool blinded;
    Coordinates coordinates;

    public:
    Info getinfo() const override;

    void blindCell();
    void unblindCell();
    void setValue();
    void getValue();

    Cell (Coordinates);
};
#endif
