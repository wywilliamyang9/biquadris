#ifndef _BOARD_
#define _BOARD_
#include "level.h"
#include "level0.h"
#include "level1.h"

//#include "graphicDisplay.h"
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
#include "forceBlockAction.h"
#include "addHeavyAction.h"
#include "blindAction.h"
#include "textDisplay.h"
#include "cell.h"
#include <iostream>
#include <sstream>
#include "IBlock.h" 
class Block;


class Board : public Subject <NextBlock> {
    int boardnum;
    Board* opponent;
    std::vector<std::vector<Cell>> board;
    std::vector<SpecialAction> specialActions;
    std::unique_ptr<Level> level;
    //GraphicDisplay* graphicDisplay;
    TextDisplay* textDisplay;
    std::string fileInput;
    int currlvl;
    int score;
    Colour nextBlockColour;
    CommandInterpreter cmdDic;
    std::unique_ptr<CommandInterpreter> cmdDictionary;
    std::unique_ptr<Block> currBlock;
    int seed;
    int textOnly;

    public:
    NextBlock getinfo() const override;
	Level* getLevelptr();

    int getScore();
    void setScore(int);
    std::vector<std::vector<Cell>>& getBoard();

    Board(int boardnum, TextDisplay *td,/* GraphicDisplay *gd,*/ bool textOnly, int seed,
    std::string scriptFile, int startLevel);
    void setOpponent(Board*);
    
    void processSpecialActions(); // applies specialActions
    void addSpecialAction(SpecialAction);

    std::string play();
	std::unique_ptr<Block> createBlock();
	bool newBlockCheck(Colour colour);
    //bool placeBlock(); // place the newly spawned block
    std::string moveBlock(); // move the block until it drops
    bool dropCheck(); // checks if a block has reached ground.
    int clearRows(); // clears filled rows, returns # of clear rows

    void levelUp();
    void levelDown();
    int getLevel();




    void attach (Observer<NextBlock>*)override;
};

#endif
