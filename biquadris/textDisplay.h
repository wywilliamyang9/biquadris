#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "board.h"
#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "info.h"
#include "state.h"
#include <vector>

class TextDisplay : public Observer<Info>,
public Observer<State>, public Observer<NextBlock> {
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
    void printBoard();
    void printNextBlock();
    public:
    TextDisplay();
    // notified when "next block" is changed.
    void notify(Subject<Info> &whoNotified) override;
    // notified when scores have changed 
    void notify(Subject<State> &whoNotified) override;
    void notify(Subject<NextBlock> &whoNotified) override;

    void print();
};

#endif
