#include "textdisplay.h"

TextDisplay::TextDisplay(){
        theDisplay.clear();
    for (int i = 0; i < gridHeight; ++i){
        vector<char> temp;
        for (int j = 0; j < gridWidth; ++j){
            temp.emplace_back(' ');
        }
        theDisplay.emplace_back(temp);
    }
}

void TextDisplay::notify(Subject<Info> &caller) override{

}

void TextDisplay::notify(Subject<vector<int>> &caller) override{

}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){

}
