#include "board.h"
using namespace std;

NextBlock Board::getinfo() {
    return NextBlock {boardNextColour,boardNum};
}

// default ctor, requires manual set of opponent and filestream.
Board::Board(int boardnum, TextDisplay *td, GraphicDisplay *gd, bool textOnly, int seed,
    String scriptFile, int startLevel) : boardnum{boardnum}, seed {seed}, 
    cmdDictionary{new CommandInterpreter},
graphicDisplay {gd}, textDisplay {td}, fileInput {scriptFile}, textOnly{textOnly},
currlvl {startLevel}, score{0}, seed{seed} {
    if (startLevel == 0) {
        currlvl = 0;
        level.reset(new level0);
    } else if (currlvl == 1) {
        currlvl = 1;
        level.reset(new level1);
    } else if (currlvl == 2) {
        currlvl = 2;
        level.reset(new level2);
    } else if (currlvl == 3) {
        currlvl = 3;
        level.reset(new level3);
    } else {
        currlvl = 4;
        level.reset(new level4);


    for (int i = 0; i < 18; ++i) { // row
        vector<Cell> newRow;
        for (j = 0; j < 11; ++j) { // column
            Cell newCell {i,j, boardnum};
            if (!textOnly) newCell.attach(graphicDisplay);
            newCell.attach(textDisplay);
            newRow.emplace_Back(newCell);
        }
        board.emplace_back (newRow);
    }

    attach(textDisplay);
    if (!textOnly) attach(graphicDisplay);
}

int getScore() {
    return score;
}

void setScore(int newScore) {
    score = newScore;
}

Vector<Vector<Cell>>& getBoard() {
    return board;
}

void Board::setOpponent (Board* newOpponent) {
    oopponent = newOpponent;
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
    Colour newBlockColour = fa.getForceBlock();
    level->forceBlock(newBlockColour);
}
// to add a new special action
void Board::addSpecialAction(SpecialAction sa) {
    specialActions.emplace_back(sa);
}

String Board::play(){
    if (!spawnBlock()) return "lost!";
    // if the restart cmd is taken, return false to Game.
    string moveResult = moveBlock();
    if (moveResult == "continue!"){
        return "continue!";
    } else if (moveResult == "restart!") {
        return "restart!";
    } else {
        return "eof!";
    }
    setScore(level->calculateScore(clearRows()));
    return "continue!";
}

// level checks win/lose conditions upon spawn.
bool Board::spawnBlock() {
    // generateNextBlock gives the new block
    currBlock = level->generateNextBlock();
    // checks if the new block can be placed on the board
    if (!(placeBlock())) return false;
    nextBlockColour = level->getNextBlock();
    notifyObservers();   
    return true;
}
bool Board::placeBlock() {
    vector<Cell>& cells = currBlock->getCells();
    for (int i = 0; i < 4; ++i) {
        int row = cells.at(i).getinfo().coordinates.row;
        int col = cells.at(i).getinfo().coordinates.col;
        if (board.at(row).at(col).getinfo().colour != Colour::White){
            return false;
        }
    }

    // if it passes the check
    cells.clear();
    for (int i = 0; i < 4; ++i) {
        int row = cells.at(i).getinfo().coordinates.row;
        int col = cells.at(i).getinfo().coordinates.col;
        Cell & onBoardCell = board.at(row).at(col);
        onBoardCell.setInfo(Coordinates{row, col},
        currBlock.getColour(), onBoardCell.getinfo().blinded,
        onBoardCell.getinfo().boardnum);
        onBoardCell.setCurrBlock(true);
        cells.emplace_back (onBoardCell);
    }
    return true;
}
// moves the block until it drops
string Board::moveBlock(Block* newBlock) {
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
        for (int i = 0; i < cmdCount; i++) {
            if (cmdDictionary->interpretCMD(cmd) == Command::Left) {
                newBlock->moveLeft();
                if (dropCheck(newBlock)) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Right) {
                newBlock->moveRight();
                if (dropCheck(newBlock)) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Down) {
                newBlock->moveDown();
                if (dropCheck(newBlock)) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::ClockWise) {
                newBlock->CWRotate();    
                if (dropCheck(newBlock)) return "continue!";    
            } else if (cmdDictionary->interpretCMD(cmd) == Command::CounterClockWise) {
                newBlock->CounterCWRotate();   
                if (dropCheck(newBlock)) return "continue!";     
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Drop) {
                newBlock->drop();
                return "continue!";
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
                return "restart!";
            } else if 
        }
    }
    return "eof!";
}

int clearRows() {
    int rowsCleared = 0;
    // scans from top
    for (int i = 0; i < 18; ++j) {
        int fullCount = 0;
        for (int j = 0; j < 11; ++j) {
            // if the value is not empty, fullCount ++
            if (board.at(i).at(j).getinfo().colour != Colour::White) fullCount++; 
        }
        if (fullCount == 11) {
            // from current row to row 1 (not row 0), move cells down by 1
            for (int k = i; k > 0; --k) {
                for (int l = 0; l < 11; ++l) {
                    board.at(k).at(l).setinfo(board.at(k).at(l-1).getinfo());
                }
            }
            // makes row 0 blank
            rowsCleared++;
        }
    }
    return rowsCleared;
}

bool Board::dropCheck(const Block& block) {
    vector<Cells>& cells = block.getCells();
    for (int j = 0; j < 4; ++j) {
        Cell& currCell = cells.at(i);
        Info& currInfo = currCell.getinfo();
        if (currInfo.coord.col == 17) return true;
        if (board.at(currInfo.coord.row).at(currInfo.coord.col+1).getinfo().colour
            != Colour::White) {
            return true;
        }
    }
    return false;
}

void Board::levelUp() {
    if (currlvl == 0) {
        currlvl = 1;
        level.reset(new level1);
    } else if (currlvl == 1) {
        currlvl = 2;
        level.reset(new level2);
    } else if (currlvl == 2) {
        currlvl = 3;
        level.reset(new level3);
    } else if (currlvl == 3) {
        currlvl = 4;
        level.reset(new level4);
    } else {
        return;
    }
    return;
}

void Board::levelDown() {
    if (currlvl == 1) {
        currlvl = 0;
        level.reset(new level0);
    } else if (currlvl == 2) {
        currlvl = 1;
        level.reset(new level1);
    } else if (currlvl == 3) {
        currlvl = 2;
        level.reset(new level2);
    } else if (currlvl == 4) {
        currlvl = 4;
        level.reset(new level3);
    } else {
        return;
    }
    return;
}

int Board::getLevel(){
    return currlvl;
}

