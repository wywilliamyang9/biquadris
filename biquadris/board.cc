#include "board.h"
#include "block.h"
#include "subject.h"
using namespace std;

Level* Board::getLevelptr() {
	return &(*level);
}

NextBlock Board::getinfo()const {
    return NextBlock { nextBlockColour,boardnum};
}

// default ctor, requires manual set of opponent and filestream.
Board::Board(int boardnum, TextDisplay *td, /*GraphicDisplay *gd,*/ bool textOnly, int seed,
    string scriptFile, int startLevel) : boardnum{boardnum}, seed {seed}, 
    cmdDictionary{new CommandInterpreter},
 /*graphicDisplay {gd},*/ textDisplay {td}, fileInput {scriptFile}, textOnly{textOnly},
currlvl {startLevel}, score{0} {
    if (startLevel == 0) {
        currlvl = 0;
		level.reset(new Level0{seed, scriptFile});
    } else if (currlvl == 1) {
        currlvl = 1;
		level.reset(new Level1{ seed});
    } /*else if (currlvl == 2) {
        currlvl = 2;
        level.reset(new Level2);
    } else if (currlvl == 3) {
        currlvl = 3;
        level.reset(new Level3);
    } else {
        currlvl = 4;
        level.reset(new Level4);
	}*/


    for (int i = 0; i < 18; ++i) { // row
		vector<Cell> newRow;
			for (int j = 0; j < 11; ++j) { // column
            Cell newCell {i,j, boardnum};
            //if (!textOnly) newCell.attach(graphicDisplay);
            newCell.attach(td); // subject <Info>
            newRow.emplace_back(newCell);
        }
        board.emplace_back (newRow);
    }

    attach(td); // subject <...>
    //if (!textOnly) attach(graphicDisplay);
}

int Board::getScore() {
    return score;
}

void Board::setScore(int newScore) {
    score = newScore;
}

void Board::setOpponent (Board* newOpponent) {
    opponent = newOpponent;
}

void Board::processSpecialActions() {
    while (!(specialActions.size())) {
		specialActions.back().applySpecialAction(*this);
        specialActions.pop_back();        
    }
}

// to add a new special action
void Board::addSpecialAction(SpecialAction sa) {
    specialActions.emplace_back(sa);
}

string Board::play(){
	currBlock = createBlock();
	if (!currBlock) return "lost!";
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
/*
bool Board::spawnBlock() {
	if (!newBlockCheck(nextBlockColour)) return false;
	currBlock.reset(Block{})
    // generateNextBlock gives the new block
    BlockInfo newBlockInfo = level->generateNextBlock();

    // checks if the new block can be placed on the board
    if (!(placeBlock())) return false;
    nextBlockColour = level->getNextBlock();
    notifyObservers();   
    return true;
}
/*
bool Board::placeBlock() {
    vector<Cell>.at& ).at(l)ock->getCells();
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
*/
// moves the block until it drops
string Board::moveBlock() {
    string cmd;
    char cmdCount;
    while (cin >> cmd) {
        cmdCount = '1';
        // check if there's a num at the front; process the num
        if (!(cmdDictionary->checkCMD(cmd))) {
            stringstream ss {cmd};
            ss >> cmdCount;
            ss >> cmd;
            // if the command is not valid, continue.
            if (!(cmdDictionary->checkCMD(cmd))) continue;
        }

        // repeat the command for cmdCount times.
        // the following cmds are invalid: sequence,I,J,L,O,S,Z,T,Blind,Heavy,Force
        for (int i = 0; i < cmdCount; i++) {
            if (cmdDictionary->interpretCMD(cmd) == Command::Left) {
                currBlock->moveLeft(*this);
                if (dropCheck()) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Right) {
				currBlock->moveRight(*this);
                if (dropCheck()) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Down) {
				currBlock->moveDown(*this);
                if (dropCheck()) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::ClockWise) {
				currBlock->CWRotate(*this);
                if (dropCheck()) return "continue!";    
            } else if (cmdDictionary->interpretCMD(cmd) == Command::CounterClockWise) {
				currBlock->CounterCWRotate(*this);
                if (dropCheck()) return "continue!";     
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Drop) {
                currBlock->drop(*this);
                return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::LevelUp) {
                levelUp();
            } else if (cmdDictionary->interpretCMD(cmd) == Command::LevelDown) {
                levelDown();
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Sequence) {
                string file;
                cin >> file,
                level->setSequence(file);
            } else if (cmdDictionary->interpretCMD(cmd) == Command::NoRandom) {
                string file;
                cin >> file,
                level->setSequence(file);
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Random) {
                level->setRandom();
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Restart) {
                // when it returns false, game knows it needs to restart
                return "restart!";
            }
        }
    }
    return "eof!";
}

int Board::clearRows() {
    int rowsCleared = 0;
    // scans from top
    for (int i = 0; i < 18; ++i) {
        int fullCount = 0;
        for (int j = 0; j < 11; ++j) {
            // if the value is not empty, fullCount ++
            if (board.at(i).at(j).getinfo().colour != Colour::White) fullCount++; 
        }
        if (fullCount == 11) {
            // from current row to row 1 (not row 0), move cells down by 1
            for (int k = i; k > 0; --k) {
                for (int l = 0; l < 11; ++l) {
                    board.at(k).at(l).setInfo(board.at(k).at(l-1).getinfo());
                }
            }
            // makes row 0 blank
            rowsCleared++;
        }
    }
    if (rowsCleared > 1) {
        cout << "Select a Special Action." << endl;
        string cmd;
        while (cin >> cmd) {
            if (cmdDictionary->interpretCMD(cmd) == Command::Blind) {
                opponent->addSpecialAction(BlindAction{});
                break;
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Force) {
                char type;
                cin >> type;
				Colour newColour;
				if (type == 'I') {
					newColour = Colour::LightBlue;
				}
				else if (type == 'J') {
					newColour = Colour::Blue;
				}
				else if (type == 'L') {
					newColour = Colour::Orange;
				}
				else if (type == 'O') {
					newColour = Colour::Yellow;
				}
				else if (type == 'S') {
					newColour = Colour::Green;
				}
				else if (type == 'T') {
					newColour = Colour::Purple;
				}
				else if (type == 'Z') {
					newColour = Colour::Red;
				}
                opponent->addSpecialAction(ForceBlockAction{ newColour });
                break;
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Heavy) {
                opponent->addSpecialAction(AddHeavyAction{});
                break;
            } else {
                cout << "Invalid Action, select a Special Action." << endl;
                continue;
            }
        }
    }
    return rowsCleared;
}

bool Board::dropCheck() {
    for (int j = 0; j < 4; ++j) {
        Info currInfo = currBlock->getCells().at(j)->getinfo();
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
		level.reset(new Level1{ seed });
    } /*else if (currlvl == 1) {
        currlvl = 2;
        level.reset(new Level2);
    } else if (currlvl == 2) {
        currlvl = 3;
        level.reset(new Level3);
    } else if (currlvl == 3) {
        currlvl = 4;
        level.reset(new Level4);
    } else {
        return;
    }*/
    return;
}

void Board::levelDown() {
    if (currlvl == 1) {
        currlvl = 0;
        level.reset(new Level0{ seed, fileInput });
    } else if (currlvl == 2) {
        currlvl = 1;
        level.reset(new Level1{ seed});
    } /*else if (currlvl == 3) {
        currlvl = 2;
        level.reset(new Level2);
    } else if (currlvl == 4) {
        currlvl = 4;
        level.reset(new Level3);
    } else {
        return;
    }*/
    return;
}

int Board::getLevel(){
    return currlvl;
}

bool Board::newBlockCheck(Colour colour) {
    if (convertColour(colour) == 'I') {
		if (board.at(3).at(0).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(2).getColour() != Colour::White
			|| board.at(3).at(3).getColour() != Colour::White) {
			return false;
		}
    } else if (convertColour(colour) == 'J') {
		if (board.at(2).at(0).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(2).getColour() != Colour::White
			|| board.at(3).at(0).getColour() != Colour::White) {
			return false;
		}
    } else if (convertColour(colour) == 'L') {
		if (board.at(2).at(2).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(2).getColour() != Colour::White
			|| board.at(3).at(0).getColour() != Colour::White) {
			return false;
		}
    } else if (convertColour(colour) == 'O') {
		if (board.at(2).at(0).getColour() != Colour::White
			|| board.at(2).at(1).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(0).getColour() != Colour::White) {
			return false;
		}
    } else if (convertColour(colour) == 'S') {
		if (board.at(2).at(2).getColour() != Colour::White
			|| board.at(2).at(1).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(0).getColour() != Colour::White) {
			return false;
		}
    } else if (convertColour(colour) == 'Z') {
		if (board.at(2).at(0).getColour() != Colour::White
			|| board.at(2).at(1).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(2).getColour() != Colour::White) {
			return false;
		}
    } else if (convertColour(colour) == 'T') {
		if (board.at(2).at(0).getColour() != Colour::White
			|| board.at(2).at(1).getColour() != Colour::White
			|| board.at(2).at(2).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White) {
			return false;
		}
    }
    return true;
}

	
unique_ptr<Block> Board::createBlock() {
    BlockInfo newBlockInfo = level->generateNextBlock();
    // checks if there is enough space to allocate the block.
    if (!newBlockCheck(newBlockInfo.colour)){
        unique_ptr<Block> unique_null = make_unique<IBlock>(&board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), &board.at(3).at(3), newBlockInfo.heavy, newBlockInfo.colour);
        unique_null.reset();
        return unique_null;
    }

    // if there is, spawn the block.
    if (convertColour(newBlockInfo.colour) == 'I'){
        unique_ptr<Block> block = make_unique<IBlock>(&board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), &board.at(3).at(3), newBlockInfo.heavy, newBlockInfo.colour);
        return block;
    } /*else if (convertColour(newBlockInfo.colour) == 'J'){
        unique_ptr<Block> block = make_unique<JBlock>(&board.at(2).at(0), &board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), newBlockInfo.heavy, newBlockInfo.colour);
        level->clearHeavy();
        return block;
    } else if (convertColour(newBlockInfo.colour) == 'L'){
        unique_ptr<Block> block = make_unique<LBlock>(&board.at(2).at(2), &board.at(3).at(2), &board.at(3).at(1), &board.at(3).at(0),newBlockInfo.heavy, newBlockInfo.colour);
		level->clearHeavy();
		return block;
    } else if (convertColour(newBlockInfo.colour) == 'O'){
        unique_ptr<Block> block = make_unique<OBlock>(&board.at(2).at(0), &board.at(2).at(1), &board.at(3).at(0), &board.at(3).at(1),newBlockInfo.heavy, newBlockInfo.colour);
		level->clearHeavy();
		return block;
    } else if (convertColour(newBlockInfo.colour) == 'S'){
        unique_ptr<Block> block = make_unique<SBlock>(&board.at(3).at(0), &board.at(3).at(1), &board.at(2).at(1), &board.at(2).at(2),newBlockInfo.heavy, newBlockInfo.colour);
		level->clearHeavy();
		return block;
    } else if (convertColour(newBlockInfo.colour) == 'Z'){
        unique_ptr<Block> block = make_unique<JBlock>(&board.at(2).at(0), &board.at(2).at(1), &board.at(3).at(1), &board.at(3).at(2),newBlockInfo.heavy, newBlockInfo.colour);
		level->clearHeavy();
		return block;
    } else if (convertColour(newBlockInfo.colour) == 'T'){
        unique_ptr<Block> block = make_unique<JBlock>(&board.at(2).at(0), &board.at(2).at(1), &board.at(2).at(2), &board.at(3).at(1),newBlockInfo.heavy, newBlockInfo.colour);
		level->clearHeavy();
		return block;
    }*/
}

vector<vector<Cell>>& Board::getBoard() {
    return board;
}

void Board::attach (Observer<NextBlock>*o){
    observers.emplace_back (o);
}