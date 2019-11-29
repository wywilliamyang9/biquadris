#include "forceBlockAction.h"
#include "board.h"

ForceBlockAction::ForceBlockAction(Colour colour):
colour{colour} {}

void ForceBlockAction::applySpecialAction(Board& playerBoard) {
	playerBoard.getLevelptr()->forceBlock(colour);
}
