#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
//#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "info.h"
#include <vector>
#include "nextBlock.h"
#include "observer.h"
class Board;
class TextDisplay : public Observer<Info>{
    std::vector<std::vector<char>> board1;
    std::vector<std::vector<char>> board2;
    const int gridWidth = 11;
    const int gridHeight = 18;
    std::vector<int> scores;
    std::vector<int> levels;
    std::vector<char> nextblock;
    void printLevel();
    void printHighScore();
    void printScore();
    void printBoards();
    void printNextBlock();
    public:
    TextDisplay();
    void notify(Subject<Info> &whoNotified) override;
    void updateNextBlock(NextBlock nextBlockInfo);
    void updateScore(std::vector<int> scores);
    void updateLevel(std::vector<int> levels);

    void print();
};

#endif
