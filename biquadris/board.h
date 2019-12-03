#ifndef _BOARD_
#define _BOARD_
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <memory>

#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "commandInterpreter.h"
#include "cell.h"
#include "block.h"
#include "specialAction.h"

class TextDisplay;
class GraphicalDisplay;
class IBlock; 
class JBlock; 
class LBlock; 
class OBlock; 
class SBlock; 
class ZBlock; 
class TBlock; 
class DotBlock;

class Board {
    int boardnum;
    Board* opponent;
    std::vector<std::vector<Cell>> board;
    std::vector<SpecialAction> specialActions; // stacked when opponent clears 2+ rows
    std::unique_ptr<Level> level; // level class, as factory method
    GraphicalDisplay* graphicDisplay;
    TextDisplay* textDisplay;
    std::string fileInput; // string name of the sequence file
    int currlvl;
    int score = 0;
    Colour nextBlockColour; // colour of the next block
    Colour heldBlockColour = Colour::White;
    std::unique_ptr<CommandInterpreter> cmdDictionary; // used to interpret commands
    std::unique_ptr<Block> currBlock;
    Colour currColour; // colour of the current block
    int seed;
    bool textOnly;
    std::vector<std::unique_ptr<Block>> blocks;
    bool special; // special features switch
    void clearCurrBlock(); // used when moving & updating cells in current block.

    public:
    int getScore();
    void setScore(int);

    std::vector<std::vector<Cell>>& getBoard(); // returns board for Block classes

    // set up the board.
    Board(int boardnum, TextDisplay *td, GraphicalDisplay *gd, bool textOnly, int seed,
    std::string scriptFile, int startLevel, bool special);
    void setOpponent(Board*);
    
    void processSpecialActions(); // applies specialActions
    void addSpecialAction(SpecialAction);

    std::string play();

    // creates the corresponding blocks
    IBlock* createIBlock(const BlockInfo&);
    JBlock* createJBlock(const BlockInfo&);
    LBlock* createLBlock(const BlockInfo&);
    OBlock* createOBlock(const BlockInfo&);
    SBlock* createSBlock(const BlockInfo&);
    TBlock* createTBlock(const BlockInfo&);
    ZBlock* createZBlock(const BlockInfo&);
    DotBlock* createDotBlock();

	bool newBlockCheck(Colour colour); // checks if the new block can be spawned
    std::string moveBlock(); // move the block until it drops
    bool dropCheck(); // checks if a block has reached ground.
    int clearRows(); // clears filled rows, returns # of clear rows

    void levelUp();
    void levelDown();
    int getLevel();
};

#endif