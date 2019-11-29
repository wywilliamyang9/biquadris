#include "addHeavyAction.h"
#include "board.h"

void AddHeavyAction::applySpecialAction(Board& playerBoard) {
	playerBoard.getLevelptr()->addHeavy();
}
