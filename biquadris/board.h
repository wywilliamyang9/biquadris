#ifndef _BOARD_
#define _BOARD_
#include "block.h"
#include "specialAction.h"
#include "level.h"
#include "graphicDisplay.h"
#include "specialAction.h"
#include "info.h"
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
    unique_ptr<CommandInterpreter> cmdDictionary;
    unique_ptr<Block> currBlock;
    int seed;
    int textOnly;

    public:
    int getScore();
    void setScore(int);

    Board::Board();
    void setOpponent(Board*);
    
    void processSpecialActions(); // applies specialActions
    void applySpecialActions(BlindAction);
    void applySpecialActions(AddHeavyAction);
    void applySpecialActions(ForceBlockAction);
    void addSpecialAction(SpecialAction);

    bool play();
    Block* SpawnBlock(); // spawn a new block
    void moveBlock(); // move the block until it drops
    bool dropCheck(const Block&); // checks if a block has reached ground.
    int clearRows(); // clears filled rows, returns # of clear rows

    void levelUp();
    void levelDown();
};

#endif
