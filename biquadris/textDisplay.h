#ifndef _TEXTDISPLAY_
#define _TEXTDISPLAY_
//#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "info.h"
#include <vector>
#include "nextBlock.h"
#include "observer.h"

class Block;
class TextDisplay : public Observer {
    std::vector<std::vector<char>> board1;
    std::vector<std::vector<char>> board2;
    const int gridWidth = 11;
    const int gridHeight = 18;
    std::vector<int> scores;
    std::vector<int> levels;
    std::vector<char> nextblock;
    std::vector<char> heldblock;
    bool printheld;
    void printLevel();
    void printHighScore();
    void printScore();
    void printBoards();
    void printNextBlock();
    void printHeldBlock();
    public:
    TextDisplay(bool printheld = false);
    void notify(Subject &whoNotified) override;
    void updateHeldBlock(NextBlock heldBlockInfo);
    void updateNextBlock(NextBlock nextBlockInfo) override;
    void updateScore(std::vector<int> scores)override;
    void updateScore(int newScore, int boardnum) override;
    void updateLevel(std::vector<int> levels)override;
    void updateLevel(int newLevel, int boardnum)override;
    void print();
};

#endif
