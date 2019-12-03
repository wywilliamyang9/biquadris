#include "DotBlock.h"
#include "board.h"
#include "cell.h"

using namespace std;

DotBlock::DotBlock (Cell* c1) : Block{} {
    cells.emplace_back(c1);
}

void DotBlock::CWRotate(Board & playerBoard) {}

void DotBlock::CounterCWRotate(Board &playerBoard) {}
