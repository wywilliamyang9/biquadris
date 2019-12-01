#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "info.h"
#include <vector>
#include "nextBlock.h"
#include "observer.h"

class Board;
class GraphicalDisplay : public Observer {
    const int displaywidth = 675
    
    std::vector<std::vector<char>> board1;
    std::vector<std::vector<char>> board2;
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
    void updateNextBlock(NextBlock nextBlockInfo);
    void updateScore(std::vector<int> scores);
    void updateLevel(std::vector<int> levels);
    void updateLevel(int newLevel, int boardnum);
    void display();
};

#endif
