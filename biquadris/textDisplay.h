#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "board.h"
#include "window.h"
#include "subject.h"
#include "coordinates.h"

class TextDisplay : public Observer {
    vector<vector<string>> td;

    public:
    // notified when "next block" is changed.
    void notify(Subject<char> &caller) override;
    // notified when scores have changed 
    void notify(Subject<vector<int>> &caller) override;
    
    TextDisplay();
    ~TextDisplay();
};

#endif
