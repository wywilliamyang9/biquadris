#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "board.h"
#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "info.h"

class TextDisplay : public Observer {
    vector<vector<char>> theDisplay;
    const int gridWidth = 11;
    const int gridHeight = 15;
    std::vector<int> scores;

    public:
    TextDisplay();
    // notified when "next block" is changed.
    void notify(Subject<Info> &whoNotified) override;
    // notified when scores have changed 
    void notify(Subject<vector<int>> &whoNotified) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
