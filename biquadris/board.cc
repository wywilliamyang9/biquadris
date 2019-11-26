#include "board.h"
using namespace std;

// default ctor, requires manual set of opponent and filestream.
Board::Board(TextDisplay *td, GraphicDisplay *gd, bool textOnly, int seed, String scriptFile, int startLevel) : 
level {new Level(startLevel)}, 
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

void Board::moveBlock() {
    Block currBlock = level->generateNextBlock();
    for (int i = 0; i < 4; ++i) {
        currBlock.getinfo()
    }
    String cmd;
    while (cin >> cmd) {

    }
}

