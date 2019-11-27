#include "board.h"
using namespace std;

// default ctor, requires manual set of opponent and filestream.
Board::Board(TextDisplay *td, GraphicDisplay *gd, bool textOnly, int seed, String scriptFile, int startLevel) : 
level {new Level(startLevel)}, cmdDictionary{new CommandInterpreter}
{
    graphicDisplay ()
    for (int i = 0; i < 18; ++i) { // row
        vector<Cell> newRow;
        for (j = 0; j < 12; ++j) { // column
            Cell newCell {i,j};
            if (!textOnly) newCell.attach(graphicDisplay);
            newCell.attach(textDisplay);
            newRow.emplace_Back(newCell);
        }
        board.emplace_back (newRow);
    }
}

void Board::setOpponent (Board* opponent) {
    opponent.reset()
}
void Board::processSpecialActions() {
    while (!(specialActions.size())) {
        applySpecialActions(specialActions.back());
        specialActions.pop_back();        
    }
}
// when Special Action is a Blind Action
void Board::applySpecialActions(BlindAction ba) {
    for (int i = 2; i < 12; ++i) {
        for (int j = 2; j < 9; ++j) {
            board.at(i).at(j).blindCell();
        }
    }
}
// when Special Action is a Heavy Action
void Board::applySpecialActions(AddHeavyAction ha) {
    level->addHeavy();
}
// when Special Action is a Force Action
void Board::applySpecialActions(ForceBlockAction fa) {
    char newBlock = fa.getForceBlock();
    level->forceBlock(newBlock);
}
// to add a new special action
void Board::addSpecialAction(SpecialAction sa) {
    specialActions.emplace_back(sa);
}

// level checks win/lose conditions upon spawn.
Block* Board::SpawnBlock() {
    return level->generateNextBlock();
}

// moves the block until it drops
bool Board::moveBlock(Block* newBlock) {
    String cmd;
    char cmdCount;
    while (cin >> cmd) {
        cmdCount = '1';
        // check if there's a num at the front; process the num
        if (!(cmdDictionary->checkCMD(cmd))) {
            sstream ss {cmd};
            ss >> cmdCount;
            ss >> cmd;
            // if the command is not valid, continue.
            if (!(cmdDictionary->checkCMD(cmd))) continue;
        }

        // repeat the command for cmdCount times.
        // the following cmds are invalid: sequence,I,J,L,O,S,Z,T,Blind,Heavy,Force
        if (cmdDictionary->interpretCMD(cmd) == Command::Left) {
            newBlock->moveLeft(cmdCount);
        } else if (cmdDictionary->interpretCMD(cmd) == Command::Right) {
            newBlock->moveRight(cmdCount);
        } else if (cmdDictionary->interpretCMD(cmd) == Command::Down) {
            newBlock->moveDown(cmdCount);
        } else if (cmdDictionary->interpretCMD(cmd) == Command::ClockWise) {
            newBlock->CWRotate(cmdCount);        
        } else if (cmdDictionary->interpretCMD(cmd) == Command::CounterClockWise) {
            newBlock->CounterCWRotate(cmdCount);        
        } else if (cmdDictionary->interpretCMD(cmd) == Command::Drop) {
            newBlock->drop(cmdCount);       
        } else if (cmdDictionary->interpretCMD(cmd) == Command::LevelUp) {
            levelUp();
        } else if (cmdDictionary->interpretCMD(cmd) == Command::LevelDown) {
            levelDown();
        } else if (cmdDictionary->interpretCMD(cmd) == Command::NoRandom) {
            level->setRandom(false);
        } else if (cmdDictionary->interpretCMD(cmd) == Command::Random) {
            level->setRandom(true);
        } else if (cmdDictionary->interpretCMD(cmd) == Command::Restart) {
            // when it returns false, game knows it needs to restart
            return false;
        } else if (cmdDictionary->interpretCMD(cmd) == Command::LevelUp) {
    }
}

string Board::play(){
    Player* currplayer = board1;
    while (true) {
        processSpecialActions();
        SpawnBlock();
        moveBlock();
        int linesCleared = clearRows();
        setScore(linesCleared);
        if (currplayer = board1){
            currplayer = board2;
        } else {
            currplayer = board1;
        }
        if (linesCleared >= 2){
            string specialAction;
            cin >> specialAction;
            addSpecialAction(SpecialAction(specialAction));
        }
    }
}

