#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "info.h"
#include <vector>
#include "nextBlock.h"
#include "observer.h"

class Block;
class GraphicalDisplay : public Observer {
    Xwindow window;
    const int displaywidth = 675;
    const int displayheight = 650;
    std::vector<std::vector<int>> board1;
    std::vector<std::vector<int>> board2;
    const int gridWidth = 11;
    const int gridHeight = 18;
    std::vector<int> scores;
    std::vector<int> levels;
    std::vector<char> nextblock;
    void displayLevel();
    void displayHighScore();
    void displayScore();
    void displayBoards();
    void displayNextBlock();
    public:
    GraphicalDisplay();
    void notify(Subject &whoNotified) override;
    void updateNextBlock(NextBlock nextBlockInfo) override;
    void updateScore(std::vector<int> scores) override;
    void updateScore(int newScore, int boardnum) override;
    void updateLevel(std::vector<int> levels) override;
    void updateLevel(int newLevel, int boardnum) override;
    void display();
};

#endif