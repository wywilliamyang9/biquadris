#ifndef _GRAPHICDISPLAY_
#define _GRAPHICDISPLAY_
#include "board.h"
#include "window.h"
#include "subject.h"
#include "coordinates.h"
#include "state.h"

class GraphicDisplay : public Observer<State> {
    Xwindow* window;

    public:
    void notify(Subject<Coordinates> &caller) override;
    
    GraphicDisplay();
    ~GraphicDisplay();
};


#endif
