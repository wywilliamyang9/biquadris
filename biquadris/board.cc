//#define DEBUG
//#define DEBUG2
#define DEBUG3
#include "board.h"
#include "subject.h"

#include "block.h"
#include "IBlock.h" 
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "textDisplay.h"
#include "graphicalDisplay.h"
#include "TBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "DotBlock.h"
using namespace std;
Level* Board::getLevelptr() {
	return &(*level);
}

// default ctor, requires manual set of opponent and filestream.
Board::Board(int boardnum, TextDisplay *td, GraphicalDisplay *gd, bool textOnly, int seed,
    string scriptFile, int startLevel) : boardnum{boardnum}, opponent {nullptr}, level {nullptr},
     graphicDisplay {gd}, textDisplay {td}, fileInput {scriptFile},currlvl {startLevel}, score{0}, 
     nextBlockColour {Colour::White},cmdDictionary{new CommandInterpreter}, currBlock {nullptr}, currColour {Colour::White},
     seed {seed}, textOnly{textOnly} {
    if (startLevel == 0) {
        currlvl = 0;
		level.reset(new Level0{seed, scriptFile, 0});
    } else if (currlvl == 1) {
        currlvl = 1;
		level.reset(new Level1{seed,1});
    } else if (currlvl == 2) {
        currlvl = 2;
        level.reset(new Level2{seed,2});
    } else if (currlvl == 3) {
        currlvl = 3;
        level.reset(new Level3{seed,3});
    } else {
        currlvl = 4;
        level.reset(new Level4{seed,4});
	}
    srand(seed);

    for (int i = 0; i < 18; ++i) { // row
		vector<Cell> newRow;
			for (int j = 0; j < 11; ++j) { // column
            Cell newCell {i,j, boardnum};
            if (!textOnly) newCell.attach(graphicDisplay);
            newCell.attach(textDisplay); // subject <Info>
            newRow.emplace_back(newCell);
        }
        board.emplace_back (newRow);
    }

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
#ifdef DEBUG
    cout << "processSpecialActions starts" << endl;
#endif
#ifdef DEBUG
    cout << "specialActions size is: " << specialActions.size() << endl;
#endif
    while (specialActions.size()) {
		if (specialActions.back() == SpecialAction::Heavy) {
#ifdef DEBUG
    cout << "new action is heavy action" << endl;
#endif
            level->addHeavy();
            specialActions.pop_back();
        } else if  (specialActions.back() == SpecialAction::Blind) {
#ifdef DEBUG
    cout << "new action is blind action" << endl;
#endif
            for (int i = 2; i < 12; ++i) {
		        for (int j = 2; j < 9; ++j) {
			    board.at(i).at(j).blindCell();
                }
            }
            specialActions.pop_back();

		} else if  (specialActions.back() == SpecialAction::ForceI) {
            level->forceBlock(convertString("I"));
            specialActions.pop_back();

		}  else if  (specialActions.back() == SpecialAction::ForceJ) {
            level->forceBlock(convertString("J"));
            specialActions.pop_back();

		} else if  (specialActions.back() == SpecialAction::ForceL) {
            level->forceBlock(convertString("L"));
            specialActions.pop_back();         

		} else if  (specialActions.back() == SpecialAction::ForceO) {
            level->forceBlock(convertString("O"));
                specialActions.pop_back();

		} else if  (specialActions.back() == SpecialAction::ForceS) {
            level->forceBlock(convertString("S"));
                specialActions.pop_back();

		} else if  (specialActions.back() == SpecialAction::ForceZ) {
            level->forceBlock(convertString("Z"));
                specialActions.pop_back();

		} else if  (specialActions.back() == SpecialAction::ForceT) {
            level->forceBlock(convertString("T"));
                specialActions.pop_back();

		} 
    }
}

// to add a new special action
void Board::addSpecialAction(SpecialAction sa) {
    specialActions.emplace_back(sa);
}

string Board::play(){
#ifdef DEBUG
    cout << "Board::play() starts"<<endl;
#endif

    processSpecialActions();
    BlockInfo newBlockInfo = level->generateNextBlock();
    if (newBlockInfo.spawnDot) {
        unique_ptr<Block> newDotBlock;
        newDotBlock.reset(createDotBlock());
        blocks.emplace_back(move(newDotBlock));
    }
    if (!newBlockCheck(newBlockInfo.colour)){
        #ifdef DEBUG
        cout << "Board::createBlock - lost!" << endl;
        #endif
        return "lost!";
    }

    if (convertColour(newBlockInfo.colour) == 'I') {
        currBlock.reset(createIBlock(newBlockInfo));
        int num = rand()%2;
        for(int i = 0; i < num; i++){
            currBlock->CWRotate(*this);
        }
    } else if (convertColour(newBlockInfo.colour) == 'L') {
        currBlock.reset(createLBlock(newBlockInfo));        
        int num = rand()%4;
        for(int i = 0; i < num; i++){
            currBlock->CWRotate(*this);
        }
    } else if (convertColour(newBlockInfo.colour) == 'J') {
        currBlock.reset(createJBlock(newBlockInfo));
        int num = rand()%4;
        for(int i = 0; i < num; i++){
            currBlock->CWRotate(*this);
        }
    }else if (convertColour(newBlockInfo.colour) == 'O') {
        currBlock.reset(createOBlock(newBlockInfo));
    }else if (convertColour(newBlockInfo.colour) == 'S') {
        currBlock.reset(createSBlock(newBlockInfo));
        int num = rand()%2;
        for(int i = 0; i < num; i++){
            currBlock->CWRotate(*this);
        }
    }else if (convertColour(newBlockInfo.colour) == 'Z') {
        currBlock.reset(createZBlock(newBlockInfo));
        int num = rand()%2;
        for(int i = 0; i < num; i++){
            currBlock->CWRotate(*this);
        }
    }else if (convertColour(newBlockInfo.colour) == 'T') {
        currBlock.reset(createTBlock(newBlockInfo));
        int num = rand()%4;
        for(int i = 0; i < num; i++){
            currBlock->CWRotate(*this);
        }
    }

#ifdef DEBUG
    cout << "Board::createBlock starts" << endl;
#endif
    #ifdef DEBUG
    cout << "new block is " << newBlockInfo.heavy << convertColour(newBlockInfo.colour) << endl;
    #endif

    textDisplay->print();
    if (!textOnly) graphicDisplay->display();
	if (!currBlock) return "lost!";
	string moveResult = moveBlock();
    
    // undo blind
    for (int i = 0; i < 18;++i) {
        for (int j = 0; j < 11; ++j) {
            board.at(i).at(j).unblindCell();
        }
    }
    if (moveResult == "continue!"){
        //setScore(level->calculateScore(clearRows()));
#ifdef DEBUG3
    int i = level->calculateScore(clearRows());
    cout << "new score is : " <<i << endl;
    setScore (i);
    cout << ""<<endl;
#endif
        return "continue!";
    } else if (moveResult == "restart!") {
        return "restart!";
    } else {
        return "eof!";
    }
    return "continue!";
}
// moves the block until it drops
string Board::moveBlock() {
#ifdef DEBUG
    cout << "Board::moveBlock() starts"<<endl;
#endif

#ifdef DEBUG
for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 11; j++) {
        cout << convertColour(board.at(i).at(j).getinfo().colour);
    }
    cout << endl;
}
    cout << "Board::moveBlock() starts"<<endl;
#endif
    string cmd;
    char cmdCount;
    while (cin >> cmd) {
        cmdCount = '0';
        bool cmdnotFound = false;
        int cmdCountint = 0;
        bool enteredloop = false;
        // check if there's a num at the front; process the num
        if (!(cmdDictionary->checkCMD(cmd))) {
#ifdef DEBUG
            cout << "enters checkCMD"  << endl;
#endif
            stringstream ss {cmd};
            while(ss >> cmdCount){
    
                ss >> cmd;     
#ifdef DEBUG
            cout << cmd << endl;
#endif
//n,I,J,L,O,S,Z,T,b,h,f

                if ((cmd != "n" && cmd != "I" && cmd != "J" && cmd != "L" && cmd != "O"
                && cmd != "S" && cmd != "Z" && cmd != "T" && cmd != "b" && cmd != "h"
                 && cmd != "f"&&  cmd.length() == 1)||cmd == ""){
                    //enteredloop = false;
                    cmdnotFound = true;
                    break;
                }
                enteredloop = true;
                cmdCountint = (cmdCountint * 10) + (cmdCount - '0');
                // if the command is not valid, continue.
                if (!(cmdDictionary->checkCMD(cmd))) {
                    ss.str("");
                    ss.str(cmd);
                    ss.clear();

                } else {
                    break;
                }
            }

        }
        //cout << "cmd not found is :" << cmdnotFound << endl;
        if (cmdnotFound) continue;

        if(!enteredloop){
            cmdCountint = 1;
        }
        // repeat the command for cmdCount times.
        // the following cmds are invalid: sequence,I,J,L,O,S,Z,T,Blind,Heavy,Force
        for (int i = 0; i < cmdCountint; i++) {
            if (cmdDictionary->interpretCMD(cmd) == Command::Left) {
                currBlock->moveLeft(*this);
                if (dropCheck()) {
                    return "continue!";
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Right) {
				currBlock->moveRight(*this);
                if (dropCheck()) return "continue!";
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Down) {
				currBlock->moveDown(*this);
                if (dropCheck()) {
                    return "continue!";
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::ClockWise) {
				currBlock->CWRotate(*this);
                if (dropCheck()){
                    return "continue!";    
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::CounterClockWise) {
				currBlock->CounterCWRotate(*this);
                if (dropCheck()) return "continue!";     
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Drop) {
                while (true) {
                    if (dropCheck()) break;
                    currBlock->moveDown(*this);
                }
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
            } else if (cmdDictionary->interpretCMD(cmd) == Command::I) {
                level->forceBlock(convertString("I"));
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock();
                currBlock.reset(createIBlock(newBlockInfo));
                int num = rand()%2;
                for(int i = 0; i < num; i++){
                    currBlock->CWRotate(*this);
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::J) {
                level->forceBlock(convertString("J")); 
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock();
                currBlock.reset(createJBlock(newBlockInfo));
                int num = rand()%4;
                for(int i = 0; i < num; i++){
                    currBlock->CWRotate(*this);
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::L) {
                level->forceBlock(convertString("L"));
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock();
                currBlock.reset(createLBlock(newBlockInfo));        
                int num = rand()%4;
                for(int i = 0; i < num; i++){
                    currBlock->CWRotate(*this);
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::O) {
                level->forceBlock(convertString("O"));
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock();
                currBlock.reset(createOBlock(newBlockInfo));
            } else if (cmdDictionary->interpretCMD(cmd) == Command::S) {
                level->forceBlock(convertString("S"));
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock();
                currBlock.reset(createSBlock(newBlockInfo));
                int num = rand()%2;
                for(int i = 0; i < num; i++){
                    currBlock->CWRotate(*this);
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Z) {
                level->forceBlock(convertString("Z"));
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock();
                currBlock.reset(createZBlock(newBlockInfo));
                int num = rand()%2;
                for(int i = 0; i < num; i++){
                    currBlock->CWRotate(*this);
                }
            } else if (cmdDictionary->interpretCMD(cmd) == Command::T) {
                level->forceBlock(convertString("T"));
                for(int i = 0; i < 4; i++){
                    currBlock->getCells().at(i)->setCurrBlock(false);
                    currBlock->getCells().at(i)->setColour(Colour::White);
                    currBlock->getCells().at(i)->dettach(currBlock.get());
                }
                BlockInfo newBlockInfo = level->generateNextBlock(); 
                currBlock.reset(createTBlock(newBlockInfo));
                int num = rand()%4;
                for(int i = 0; i < num; i++){
                    currBlock->CWRotate(*this);
                }
            }
        }
        textDisplay->print();
        if (!textOnly) graphicDisplay->display();
    }
    return "eof!";
}

int Board::clearRows() {

#ifdef DEBUG
    cout << "clearRows starts"<<endl;
    cout << "blocks size is :" << blocks.size()<<endl;
    cout << "they are: ";
    for (int i = 0; i < blocks.size(); ++i) {
        cout << convertColour(blocks.at(i)->getCells().at(1)->getinfo().colour);
    }
    cout << endl;
#endif
    for (int i = 0; i < 4; ++i) {
        currBlock->getCells().at(i)->attach(currBlock.get());
    }

    blocks.emplace_back(move(currBlock));
    int rowsCleared = 0;
    // scans from top
    for (int i = 17; i >= 0; --i) {
        
        int fullCount = 0;
        for (int j = 0; j < 11; ++j) {
            // if the value is not empty, fullCount ++
            if (board.at(i).at(j).getinfo().colour != Colour::White) fullCount++; 
        }
#ifdef DEBUG
    cout << i<< " row is " << fullCount<<endl;
#endif  
        // new code -----------------------------------------
        if (fullCount == 11) {
            // set  first
            
            for (int m = 0; m < 11; ++m) {
                board.at(i).at(m).setCleared(true);
#ifdef DEBUG
    cout << i << m << board.at(i).at(m).getCleared()<<endl;
#endif  
                board.at(i).at(m).notifyObservers();
                board.at(i).at(m).setCleared(false);
            }
            // clear empty blocks.
            for (int i = 0; (unsigned)i < blocks.size(); ++i) {
                if (blocks.at(i)->getCells().size() == 0) {
#ifdef DEBUG3
    cout << "BlockCleared!!!"<<endl;
#endif
                    score += (blocks.at(i)->getSpawnLevel()+1)*(blocks.at(i)->getSpawnLevel()+1);
                    blocks.erase(blocks.begin()+i);
                    --i;
                    textDisplay->updateScore(score, boardnum);
                    textDisplay->print();
                    if (!textOnly) {
                        graphicDisplay->updateScore(score, boardnum);
                        graphicDisplay->display();
                    }
                }
            }
#ifdef DEBUG
    cout << "emptyblocks cleared"<<endl;
    cout << "blocks size is :" << blocks.size()<<endl;
    cout << "they are: ";
    for (int i = 0; i < blocks.size(); ++i) {
        cout << convertColour(blocks.at(i)->getCells().at(0)->getinfo().colour);
        cout << " " << blocks.at(i)->getCells().size() << " ";
    }
#endif
#ifdef DEBUG
    cout << i << "row is full"<<endl;
#endif
            // from current row to row 1 (not row 0), move cells down by 1
            for (int k = i; k > 0; --k) {
                for (int l = 0; l < 11; ++l) {
                    board.at(k).at(l).setColour(board.at(k-1).at(l).getColour());
#ifdef DEBUG
   // cout << k<<l<< "info is:"<< board.at(k).at(l).getinfo().colour <<endl;
#endif
                }
            }
            // newcode ------------------------
            // update blocks' cells

#ifdef DEBUG
    cout << "checkpoint"<<endl;
#endif
            for (int nn = 0; (unsigned)nn < blocks.size(); ++nn) {
#ifdef DEBUG
    cout << "checking: "<< convertColour(blocks.at(nn)->getCells().at(0)->getinfo().colour) << endl;
#endif          
                bool below = 0;
                for (int kk = 0; (unsigned)kk < blocks.at(nn)->getCells().size(); ++kk) {
#ifdef DEBUG
cout << blocks.at(nn)->getCells().at(kk)->getinfo().coord.row << endl;
#endif
                    if (blocks.at(nn)->getCells().at(kk)->getinfo().coord.row >= i) {
                        below = 1;
    #ifdef DEBUG
    cout << "below modified"<< endl;
#endif
                    }
                }
                if (below) continue;
                blocks.at(nn)->referenceBelow(*this);
            }
#ifdef DEBUG
    cout << "checkpoint2"<<endl;
#endif
            i++;
            // makes row 0 blank
            rowsCleared++;
        }
    }
    if (rowsCleared > 1) {
        cout << "Select a Special Action." << endl;
        string cmd;
        while (cin >> cmd) {
            if (cmdDictionary->interpretCMD(cmd) == Command::Blind) {
                opponent->addSpecialAction(SpecialAction::Blind);
                break;
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Force) {
                char type;
                cin >> type;
				SpecialAction newColour;
				if (type == 'I') {
					newColour = SpecialAction::ForceI;
				}
				else if (type == 'J') {
					newColour = SpecialAction::ForceJ;
				}
				else if (type == 'L') {
					newColour = SpecialAction::ForceL;
				}
				else if (type == 'O') {
					newColour = SpecialAction::ForceO;
				}
				else if (type == 'S') {
					newColour = SpecialAction::ForceS;
				}
				else if (type == 'T') {
					newColour = SpecialAction::ForceT;
				}
				else if (type == 'Z') {
					newColour = SpecialAction::ForceZ;
				}
                opponent->addSpecialAction(newColour);
                break;
            } else if (cmdDictionary->interpretCMD(cmd) == Command::Heavy) {
                opponent->addSpecialAction(SpecialAction::Heavy);
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
        if (currInfo.coord.row == 17) {
            for (int i = 0; i < 4; ++i) {
                currBlock->getCells().at(i)->setCurrBlock(false);
            }
            return true;
        }
#ifdef DEBUG
    cout << "-----------------not 17" << endl;
#endif
#ifdef DEBUG
    cout <<"nextrow is " <<  currInfo.coord.row+1 << endl;
#endif
#ifdef DEBUG
    cout <<"getCurrBlock is " <<  (board.at(currInfo.coord.row+1).
            at(currInfo.coord.col).getCurrBlock()) << endl;
#endif
        if (board.at(currInfo.coord.row+1).at(currInfo.coord.col).getinfo().colour
            != Colour::White
            && !(board.at(currInfo.coord.row+1).
            at(currInfo.coord.col).getCurrBlock())) {
#ifdef DEBUG
    cout << "----------------- next filled" << endl;
#endif
            for (int i = 0; i < 4; ++i) {
                currBlock->getCells().at(i)->setCurrBlock(false);
            }
            return true;
        }
#ifdef DEBUG
    cout << "-----------------not next filled" << endl;
#endif
    }
    return false;
}

void Board::levelUp() {
    if (currlvl == 0) {
        currlvl = 1;
		level.reset(new Level1{seed,1});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    }else if (currlvl == 1) {
        currlvl = 2;
        level.reset(new Level2{seed,2});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    } else if (currlvl == 2) {
        currlvl = 3;
        level.reset(new Level3{seed,3});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    }  else if (currlvl == 3) {
        currlvl = 4;
        level.reset(new Level4{seed,4});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    } else {
        return;
    }
    return;
}

void Board::levelDown() {
    if (currlvl == 1) {
        currlvl = 0;
        level.reset(new Level0{ seed, fileInput,0 });
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    } else if (currlvl == 2) {
        currlvl = 1;
        level.reset(new Level1{seed,1});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    } else if (currlvl == 3) {
        currlvl = 2;
        level.reset(new Level2{seed,2});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    } else if (currlvl == 4) {
        currlvl = 3;
        level.reset(new Level3{seed,3});
        textDisplay->updateLevel(currlvl, boardnum);
        if (!textOnly)graphicDisplay->updateLevel(currlvl, boardnum);
        Colour nextBlockColour = level->getNextBlock();
        textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
        if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    } /*else {
        return;
    }*/
    return;
}

int Board::getLevel(){
    return currlvl;
}

bool Board::newBlockCheck(Colour colour) {
#ifdef DEBUG
    cout << "newBlockCheck starts" << convertColour(colour)<<endl;
#endif

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
#ifdef DEBUG
    cout << "checkpoint1 " << convertColour(colour)<<endl;
for (int i = 0; i < 18; ++i) {
    for (int j = 0; j < 11; ++j) {
        cout << convertColour(board.at(i).at(j).getColour());

    }
    cout << endl;

}

#endif
		if (board.at(2).at(0).getColour() != Colour::White
			|| board.at(2).at(1).getColour() != Colour::White
			|| board.at(3).at(1).getColour() != Colour::White
			|| board.at(3).at(0).getColour() != Colour::White) {
#ifdef DEBUG
    cout << "checkpoint2 " << convertColour(colour)<<endl;
#endif
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

IBlock* Board::createIBlock(const BlockInfo& newBlockInfo) {
    IBlock* block = new IBlock{&board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), &board.at(3).at(3), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<IBlock> block = make_unique<IBlock>(&board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), &board.at(3).at(3), newBlockInfo.heavy, newBlockInfo.colour);
    level->clearHeavy();
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
    Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}
JBlock* Board::createJBlock(const BlockInfo& newBlockInfo) {
    JBlock* block = new JBlock{&board.at(2).at(0), &board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<JBlock> block = make_unique<JBlock>(&board.at(2).at(0), &board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), newBlockInfo.heavy, newBlockInfo.colour);
    level->clearHeavy();
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
    Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}
LBlock* Board::createLBlock(const BlockInfo& newBlockInfo) {
    LBlock* block = new LBlock{&board.at(2).at(2), &board.at(3).at(2), &board.at(3).at(1), &board.at(3).at(0), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<LBlock> block = make_unique<LBlock>(&board.at(2).at(2), &board.at(3).at(2), &board.at(3).at(1), &board.at(3).at(0), newBlockInfo.heavy, newBlockInfo.colour);
    level->clearHeavy();
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
    Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly) graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}

SBlock* Board::createSBlock(const BlockInfo& newBlockInfo) {
    SBlock* block = new SBlock{&board.at(3).at(0), &board.at(3).at(1), &board.at(2).at(1), &board.at(2).at(2), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<SBlock> block = make_unique<SBlock>(&board.at(3).at(0), &board.at(3).at(1), &board.at(2).at(1), &board.at(2).at(2), newBlockInfo.heavy, newBlockInfo.colour);
    level->clearHeavy();
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
    Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}

ZBlock* Board::createZBlock(const BlockInfo& newBlockInfo) {
    ZBlock* block = new ZBlock{&board.at(2).at(0), &board.at(2).at(1), &board.at(3).at(1), &board.at(3).at(2), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<ZBlock> block = make_unique<ZBlock>(&board.at(2).at(0), &board.at(2).at(1), &board.at(3).at(1), &board.at(3).at(2), newBlockInfo.heavy, newBlockInfo.colour);
    level->clearHeavy();
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
            Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}

OBlock* Board::createOBlock(const BlockInfo& newBlockInfo) {
    OBlock* block = new OBlock{&board.at(2).at(0), &board.at(2).at(1), &board.at(3).at(0), &board.at(3).at(1), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<OBlock> block = make_unique<OBlock>(&board.at(2).at(0), &board.at(2).at(1), &board.at(3).at(0), &board.at(3).at(1), newBlockInfo.heavy, newBlockInfo.colour);
    level->clearHeavy();
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
    Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly) graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}
TBlock* Board::createTBlock(const BlockInfo& newBlockInfo) {
    TBlock* block = new TBlock{&board.at(2).at(0), &board.at(2).at(1), &board.at(2).at(2), &board.at(3).at(1), newBlockInfo.heavy, newBlockInfo.colour,currlvl};
    //unique_ptr<TBlock> block = make_unique<TBlock>(&board.at(2).at(0), &board.at(2).at(1), &board.at(2).at(2), &board.at(3).at(1), newBlockInfo.heavy, newBlockInfo.colour);level
    level->clearHeavy();   
    for (int i = 0; i < 4; ++i) {
        block->getCells().at(i)->setColour(newBlockInfo.colour);
        block->getCells().at(i)->setCurrBlock(true);
    }
    Colour nextBlockColour = level->getNextBlock();
    textDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    if (!textOnly)graphicDisplay->updateNextBlock(NextBlock{nextBlockColour, boardnum});
    return block;
}
DotBlock* Board::createDotBlock() {
    int row = 0;
    for (int i = 17; i >= 0; --i) {
        if (board.at(i).at(5).getinfo().colour == Colour::White){
            row = i;
            break;
        }
    }

    DotBlock* block = new DotBlock{&board.at(row).at(5)};
    block->getCells().at(0)->setColour(Colour::Brown);
    block->getCells().at(0)->attach(block);
    return block;
}
/*
unique_ptr<Block> Board::createBlock() {
#ifdef DEBUG
    cout << "Board::createBlock starts" << endl;
#endif
    BlockInfo newBlockInfo = level->generateNextBlock();
    #ifdef DEBUG
    cout << "new block is " << newBlockInfo.heavy << convertColour(newBlockInfo.colour) << endl;
    #endif
    // checks if there is enough space to allocate the block.
    if (!newBlockCheck(newBlockInfo.colour)){
        #ifdef DEBUG
        cout << "Board::createBlock - lost!" << endl;
        #endif
        unique_ptr<Block> unique_null = make_unique<IBlock>(&board.at(3).at(0), &board.at(3).at(1), &board.at(3).at(2), &board.at(3).at(3), newBlockInfo.heavy, newBlockInfo.colour);
        unique_null.reset();
        return unique_null;
    }
*/

vector<vector<Cell>>& Board::getBoard() {
    return board;
}

