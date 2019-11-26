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
    Board* opponent;
    Vector<Vector<Cell>> board;
    Vector<SpecialAction> specialActions;
    unique_ptr<Level> level;
    GraphicDisplay* graphicDisplay;
    TextDisplay* textDisplay;
    fstream fileInput;
    int currlvl;
    int score;

    public:
    int getScore();
    void setScore(int);

    Board::Board();
    void setOpponent(Board*);
    
    std::istream setFile(String);

    void processSpecialActions(); // applies specialActions
    void applySpecialActions(BlindAction);
    void applySpecialActions(AddHeavyAction);
    void applySpecialActions(ForceBlockAction);
    void addSpecialAction(SpecialAction);

    Block* SpawnBlock(); // spawn a new block
    void moveBlock(); // move the block until it drops
    int clearRows(); // clears filled rows, returns # of clear rows
};

#endif
