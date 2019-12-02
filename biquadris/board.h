#ifndef _BOARD_
#define _BOARD_
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "subject.h"
#include "observer.h"
#include "specialAction.h"
#include "commandInterpreter.h"
#include <vector>
#include <fstream>
#include <memory>
#include "info.h"
#include "colour.h"
#include "nextBlock.h"
#include "cell.h"
#include <iostream>
#include <sstream>
#include "block.h"

class TextDisplay;
class GraphicalDisplay;
/*
#include "IBlock.h" 
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "TBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "DotBlock.h"
*/
class IBlock; 
class JBlock; 
class LBlock; 
class OBlock; 
class SBlock; 
class ZBlock; 
class TBlock; 
class DotBlock;
//class Block;

class Board {
    int boardnum;
    Board* opponent;
    std::vector<std::vector<Cell>> board;
    std::vector<SpecialAction> specialActions;
    std::unique_ptr<Level> level;
    GraphicalDisplay* graphicDisplay;
    TextDisplay* textDisplay;
    std::string fileInput;
    int currlvl;
    int score = 0;
    Colour nextBlockColour;
    CommandInterpreter cmdDic;
    std::unique_ptr<CommandInterpreter> cmdDictionary;
    std::unique_ptr<Block> currBlock;
    Colour currColour;
    int seed;
    int textOnly;
    std::vector<std::unique_ptr<Block>> blocks;
    public:
	Level* getLevelptr();

    int getScore();
    void setScore(int);
    std::vector<std::vector<Cell>>& getBoard();

    Board(int boardnum, TextDisplay *td, GraphicalDisplay *gd, bool textOnly, int seed,
    std::string scriptFile, int startLevel);
    void setOpponent(Board*);
    
    void processSpecialActions(); // applies specialActions
    void addSpecialAction(SpecialAction);

    std::string play();
	//std::unique_ptr<Block> createBlock();
    IBlock* createIBlock(const BlockInfo&);
    JBlock* createJBlock(const BlockInfo&);
    LBlock* createLBlock(const BlockInfo&);
    OBlock* createOBlock(const BlockInfo&);
    SBlock* createSBlock(const BlockInfo&);
    TBlock* createTBlock(const BlockInfo&);
    ZBlock* createZBlock(const BlockInfo&);
    DotBlock* createDotBlock();

	bool newBlockCheck(Colour colour);
    //bool placeBlock(); // place the newly spawned block
    std::string moveBlock(); // move the block until it drops
    bool dropCheck(); // checks if a block has reached ground.
    int clearRows(); // clears filled rows, returns # of clear rows

    void levelUp();
    void levelDown();
    int getLevel();
};

#endif