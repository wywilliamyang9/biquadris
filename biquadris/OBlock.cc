#include "OBlock.h"
#include "board.h"
#include "cell.h"

using namespace std;

OBlock::OBlock (Cell* c1, Cell* c2, Cell* c3, Cell* c4,
int heavy, Colour colour): Block{c1,c2,c3,c4,heavy,colour} {}

void OBlock::CWRotate(Board & playerBoard) {
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}

void OBlock::CounterCWRotate(Board & playerBoard) {
    for (int i = 0; i < heavy; ++i) moveDownByOne(playerBoard);
}
