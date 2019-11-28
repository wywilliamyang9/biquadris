#ifndef _BOARD_
#define _BOARD_
#include "block.h"
#include "specialAction.h"
#include "level.h"
#include "graphicDisplay.h"
#include "specialAction.h"
#include "commandInterpreter.h"
#include <vector>
#include <fstream>
#include <memory>
#include <sstream>
#include "info.h"
#include "colour.h"
#include <vector>
#include <fstream>
#include <memory>
#include "nextBlock.h"

class Board : public Subject <NextBlock> {
    int boardnum;
    Board* opponent;
    Vector<Vector<Cell>> board;
    Vector<SpecialAction> specialActions;
    unique_ptr<Level> level;
    GraphicDisplay* graphicDisplay;
    TextDisplay* textDisplay;
    std::string fileInput;
    int currlvl;
    int score;
    Colour nextBlockColour;
    CommandInterpreter cmdDic;
    unique_ptr<CommandInterpreter> cmdDictionary;
    unique_ptr<Block> currBlock;
    int seed;
    int textOnly;

    public:
    NextBlock getinfo();

    int getScore();
    void setScore(int);
    Vector<Vector<Cell>>& getBoard();

    Board::Board(int boardnum, TextDisplay *td, GraphicDisplay *gd, bool textOnly, int seed,
    std::string scriptFile, int startLevel);
    void setOpponent(Board*);
    
    void processSpecialActions(); // applies specialActions
    void applySpecialActions(BlindAction);
    void applySpecialActions(AddHeavyAction);
    void applySpecialActions(ForceBlockAction);
    void addSpecialAction(SpecialAction);

    std::string play();
    bool spawnBlock(); // spawn a new block
    bool placeBlock(); // place the newly spawned block
    std::string moveBlock(); // move the block until it drops
    bool dropCheck(const Block&); // checks if a block has reached ground.
    int clearRows(); // clears filled rows, returns # of clear rows

    void levelUp();
    void levelDown();
    int getLevel();
};

#endif
