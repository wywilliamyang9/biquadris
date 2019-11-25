#ifndef _BOARD_
#define _BOARD_
#include "block.h"
#include "specialAction.h"
#include "level.h"
#include "graphicDisplay.h"
#include "specialAction.h"
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
    std::istream setFile(String);

    void processSpecialActions(); // applies specialActions
    void ApplySpecialActions(GraphicActions);
    void ApplySpecialActions(AddHeavyAction);
    void ApplySpecialActions(ForceBlockAction);

    void SpawnBlock(); // spawn a new block
    void moveBlocks(); // move the block until it drops
    int clearRow(); // clears filled rows, returns # of clear rows
};

#endif
