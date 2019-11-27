#include "textdisplay.h"
#include "info.h"
#include "colour.h"
#include <vector>

using namespace std;

char convertColour(Colour colour){
    if (colour == Colour::Red){
        return 'Z';
    } else if (colour == Colour::Orange){
        return 'L';
    } else if (colour == Colour::LightBlue){
        return 'I';
    } else if (colour == Colour::Blue){
        return 'J';
    } else if (colour == Colour::Yellow){
        return 'O';
    } else if (colour == Colour::Green){
        return 'S';
    } else if (colour == Colour::Purple){
        return 'T';
    } else if (colour == Colour::White){
        return ' ';
    }
}

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

void TextDisplay::notify(Subject<Info> &whoNotified) override{
    Info currinfo{whoNotified.getInfo()};
    theDisplay[currinfo.row][currinfo.col] = convertColour(currinfo.coloru);
}

void TextDisplay::notify(Subject<vector<int>> &whoNotified) override{
    vector<int> currinfo{whoNotified.getInfo()};
    scores[0] = currinfo[0];
    scores[1] = currinfo[1];
    scores[2] = currinfo[2];
}

void TextView::print() {
	printLevel();
	printScore();
	cout << "-----------   -----------" << endl;
	printBoards();
	cout << "-----------   -----------" << endl;
	printNext();
}

void TextView::printLevel() {
	cout << "Level: " << model->getBoardOne()->getLvl();
	cout << "      ";
    cout << "Level: " << model->getBoardTwo()->getLvl() << endl;
}
void TextView::printScore() {
	cout << "Score: " << model->getBoardOne()->getScore();
	cout << "      ";
	cout << "Score: " << model->getBoardTwo()->getScore() << endl;
}
void TextView::printBoards() {
	
	for (int i = 17; i >= 0; i--) {
		for (int j = 0; j < 25; j++) {
			if (j < 11) {
				cout << model->getBoardOne()->getType(j, i);
			}
			else if (j < 14) {
				cout << " ";
			}
			else {
				cout << model->getBoardTwo()->getType(j-14, i);
			}
		}
		cout << endl;
	
	}
	
}
void TextView::printNext() {
	cout << "Next:         Next:" << endl;
	cout << model->getBoardOne()->getNextType();
	cout << "             " << model->getBoardTwo()->getNextType() << endl;
}
