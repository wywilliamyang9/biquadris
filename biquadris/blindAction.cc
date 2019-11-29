#include "blindAction.h"
#include "board.h"

void BlindAction::applySpecialAction(Board& playerBoard) {
	for (int i = 2; i < 12; ++i) {
		for (int j = 2; j < 9; ++j) {
			playerBoard.getBoard().at(i).at(j).blindCell();
		}
	}
}
