#ifndef _BOARD_
#define _BOARD_
#include "block.h"
#include "specialAction.h"
#include "level.h"
#include "graphicDisplay.h"
#include <vector>
#include <fstream>

class Board {
    Board* opponent;
    Vector<Vector<Cell>> board;
    Vector<SpecialAction> specialActions;
    Level level;
    GraphicDisplay graphicDisplay;
    TextDisplay textDisplay;
    fstream filesream;

    public:
    int clearRow(); // clears filled rows, 
}

#endif
