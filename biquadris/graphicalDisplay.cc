//#define DEBUG
#include "window.h"
#include "graphicalDisplay.h"
#include "info.h"
#include <iostream>
#include "colour.h"
#include <vector>
using namespace std;

GraphicalDisplay::GraphicalDisplay(){
    //theDisplay.clear();
    for (int i = 0; i < gridHeight; ++i){
        vector<int> temp1;
        vector<int> temp2;
        for (int j = 0; j < gridWidth; ++j){
            temp1.emplace_back(Xwindow::White);
            temp2.emplace_back(Xwindow::White);
        }
        
        board1.emplace_back(temp1);
        board2.emplace_back(temp2);
    }
    for(int i = 0; i < 3; i++){
		scores.emplace_back(0);
    }
    for(int i = 0; i < 2; i++){
		levels.emplace_back(0);
        nextblock.emplace_back('A');
	}
}

int converttoXColour(Colour colour){
    if (colour == Colour::Red){
        return Xwindow::Red;
    } else if (colour == Colour::Orange){
        return Xwindow::Orange;
    } else if (colour == Colour::Cyan){
        return Xwindow::Cyan;
    } else if (colour == Colour::Blue){
        return Xwindow::Blue;
    } else if (colour == Colour::Yellow){
        return Xwindow::Yellow;
    } else if (colour == Colour::Green){
        return Xwindow::Green;
    } else if (colour == Colour::Purple){
        return Xwindow::Purple;
    } else if (colour == Colour::Brown){
        return Xwindow::Brown;
    } else {
        return ' ';
    }
}

void GraphicalDisplay::notify(Subject &whoNotified) {
#ifdef DEBUG
    cout << "GraphicalDisplay::notify() starts"<<endl;
#endif
    // if called upon a row clear, return.
    if (whoNotified.getCleared()) return;
    
    Info currinfo{whoNotified.getinfo()};
    if (currinfo.boardnum == 1){
        if (currinfo.blinded){
            board1[currinfo.coord.row][currinfo.coord.col] = '?';
        } else {
            board1[currinfo.coord.row][currinfo.coord.col] = converttoXColour(currinfo.colour);
        }
    } else if (currinfo.boardnum == 2){
        if (currinfo.blinded){
            board2[currinfo.coord.row][currinfo.coord.col] = '?';
        } else {
            board2[currinfo.coord.row][currinfo.coord.col] = converttoXColour(currinfo.colour);
        }
    }
}

void GraphicalDisplay::updateNextBlock(NextBlock nextBlockInfo){
    if (nextBlockInfo.boardnum == 1){
        nextblock[0] = convertColour(nextBlockInfo.colour);
    } else if (nextBlockInfo.boardnum == 2){
        nextblock[1] = convertColour(nextBlockInfo.colour);
    }
}

void GraphicalDisplay::updateScore(vector<int> newScores){
    scores[0] = newScores[0];
    scores[1] = newScores[1];
    scores[2] = newScores[2];
}


void GraphicalDisplay::updateScore(int newScore, int boardnum){
    if (boardnum == 1){
        scores[0] = newScore;
    } else if (boardnum) {
        scores[1] = newScore;
    }
    if (newScore > scores[2]){
        scores[2] = newScore;
    }
}

void GraphicalDisplay::updateLevel(vector<int> newLevels){
    levels[0] = newLevels[0];
    levels[1] = newLevels[1];
}

void GraphicalDisplay::updateLevel(int newLevel, int boardnum){
    if (boardnum == 1){
        levels[0] = newLevel;
    } else if (boardnum) {
        levels[1] = newLevel;
    }
}

void GraphicalDisplay::display() {
#ifdef DEBUG
    cout << "GraphicalDisplay::display() starts"<<endl;
#endif
	displayLevel();
    displayHighScore();
	displayScore();
	displayBoards();
	displayNextBlock();
    
#ifdef DEBUG
    cout << "GraphicalDisplay::display() ends"<<endl;
#endif
}

void GraphicalDisplay::displayLevel() {
    window.fillRectangle(25, 25, 100, 25, Xwindow::White);
	string level = "LEVEL: " + levels[0];
    window.drawString(25, 25, level);
    window.fillRectangle(375, 25, 100, 25, Xwindow::White);
    level =  "LEVEL: " + levels[1];
    window.drawString(375, 25, level);
}

void GraphicalDisplay::displayHighScore() {	
    window.fillRectangle(25, 50, 100, 25, Xwindow::White);
    string hiscore = "HISCORE: " + scores[3];
    window.drawString(25, 50, hiscore);
    window.fillRectangle(375, 50, 100, 25, Xwindow::White);
    hiscore =  "HISCORE: " + scores[3];
    window.drawString(375, 50, hiscore);
}

void GraphicalDisplay::displayScore() {
    window.fillRectangle(25, 75, 100, 25, Xwindow::White);
    string score = "SCORE: " + scores[0];
    window.drawString(25, 75, score);
    window.fillRectangle(375, 75, 100, 25, Xwindow::White);
    score =  "SCORE: " + scores[1];
    window.drawString(375, 75, score);
}

void GraphicalDisplay::displayBoards() {
	for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            window.fillRectangle(25 + j * 25, 75 + i * 25, 25, 25, board1[j][17 - i]);
        }
    }
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            window.fillRectangle(25 + j * 25+350, 75 + i * 25, 25, 25, board2[j][17 - i]);
        }
    }
}

string displayBlock(char type, int line){
    if (type == 'J' && line == 1){
        return "J   ";
    } else if (type == 'J' && line == 2){
        return "JJJ ";
    } else if (type == 'I' && line == 1){
        return "    ";
    } else if (type == 'I' && line == 2){
        return "IIII";
    } else if (type == 'L' && line == 1){
        return "  L ";
    } else if (type == 'L' && line == 2){
        return "LLL ";
    } else if (type == 'O' && line == 1){
        return "OO  ";
    } else if (type == 'O' && line == 2){
        return "OO  ";
    } else if (type == 'S' && line == 1){
        return " SS ";
    } else if (type == 'S' && line == 2){
        return "SS  ";
    } else if (type == 'Z' && line == 1){
        return "ZZ  ";
    } else if (type == 'Z' && line == 2){
        return " ZZ ";
    } else if (type == 'T' && line == 1){
        return "TTT ";
    } else if (type == 'T' && line == 2){
        return " T  ";
    }
	return "";
}

void GraphicalDisplay::displayNextBlock() {
	cout << "Next:         Next:" << endl;
    cout << displayBlock(nextblock[0], 1) << "          " << displayBlock(nextblock[1], 1) << endl;
    cout << displayBlock(nextblock[0], 2) << "          " << displayBlock(nextblock[1], 2) << endl;
}
