#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "board.h"
#include "window.h"
#include "subject.h"
#include "coordinates.h"

class TextDisplay : public Observer {
    vector<vector<char>> theDisplay;
    const int gridWidth;
    const int gridHeight;

    public:
    TextDisplay();
    // notified when "next block" is changed.
    void notify(Subject<char> &whoNotified) override;
    // notified when scores have changed 
    void notify(Subject<vector<int>> &whoNotified) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
