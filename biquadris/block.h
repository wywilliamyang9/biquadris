#ifndef _BLOCK_
#define _BLOCK_
#include <vector>
#include "colour.h"
#include "coordinates.h"
#include "observer.h"
//#include "board.h"
class Cell;
class Board;
class Subject;
class Block : public Observer{
protected:
	std::vector<Cell*> cells;
	int heavy;
	Colour colour;
	int state;
    int spawnLevel;

    public:
    ~Block()=default;
    Block (Cell*, Cell*, Cell*, Cell*,
         int heavy, Colour,int);

    std::vector<Cell*> getCells();
    void setCells(const std::vector<Cell*>);
    Colour getColour();

    void moveDown(Board& playerBoard);
    void moveLeft(Board&);
    void moveRight(Board &);
	void moveDownByOne(Board&);
    virtual void CWRotate(Board &) ;
    virtual void CounterCWRotate(Board &) ;

// new code
    void setSpawnLevel(int);
    int getSpawnLevel();
    void notify(Subject &caller) override;
    void updateNextBlock(NextBlock nextBlockInfo) override;
    void updateScore(std::vector<int> scores) override;
    void updateLevel(std::vector<int> levels) override;
    void updateLevel(int newLevel, int boardnum) override;
    void referenceBelow(Board&); // called upon row clear, cells will own cells down by 1.
};
#endif
