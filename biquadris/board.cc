#include "board.h"
using namespace std;

// default ctor, requires manual set of opponent and filestream.
Board::Board(bool textOnly): {
    // opponent = ???
    // level = ???
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

void processSpecialActions() {
    while (!(specialActions.size())) {
        applySpecialActions(specialActions.back());
        specialActions.pop_back();        
    }
}

void applySpecialActions(BlindAction) {
    for (int i = 2; i < 12; ++i) {
        for (int j = 2; j < 9; ++j) {
            board.at(i).at(j).blindCell();
        }
    }
}
void applySpecialActions(AddHeavyAction) {
    level->addHeavy();
}
void applySpecialActions(ForceBlockAction) {

}
void addSpecialAction(SpecialAction sa) {
    specialActions.emplace_back(sa);
}
