#ifndef _BOARD_
#define _BOARD_
#include "block.h"
#include "specialAction.h"
#include "level.h"
#include "graphicDisplay.h"
#include "specialAction.h"
#include <vector>
#include <fstream>
#include <memory>

class Board {
    auto_ptr<Board> opponent;
    Vector<Vector<Cell>> board;
    Vector<SpecialAction> specialActions;
    auto_ptr<Level> level;
    auto_ptr<GraphicDisplay> graphicDisplay;
    auto_ptr<TextDisplay> textDisplay;
    fstream fileInput;
    int currlvl;

    public:
    Board::Board();
    
    std::istream setFile(String);

    void processSpecialActions(); // applies specialActions
    void applySpecialActions(BlindAction);
    void applySpecialActions(AddHeavyAction);
    void applySpecialActions(ForceBlockAction);
    void addSpecialAction(SpecialAction);

    void SpawnBlock(); // spawn a new block
    void moveBlocks(); // move the block until it drops
    int clearRow(); // clears filled rows, returns # of clear rows
};

#endif
