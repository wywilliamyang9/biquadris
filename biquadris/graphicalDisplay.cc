//#define DEBUG
#include "window.h"
#include "graphicalDisplay.h"
#include "info.h"
#include <iostream>
#include "colour.h"
#include <string>
#include <vector>
using namespace std;

GraphicalDisplay::GraphicalDisplay(bool printheld): printheld{printheld}{
    //theDisplay.clear();
    for (int i = 0; i < gridHeight; ++i){
#ifdef DEBUG
cout << "graphical display created" << endl;
#endif
        vector<int> temp1;
        vector<int> temp2;
        for (int j = 0; j < gridWidth; ++j){
            temp1.emplace_back(Xwindow::Black);
            temp2.emplace_back(Xwindow::Black);
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
        heldblock.emplace_back('A');
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
    } else if (colour == Colour::Fuchia){
        return Xwindow::Fuchia;
    } else {
        return Xwindow::Black;
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
            board1[currinfo.coord.row][currinfo.coord.col] = converttoXColour(Colour::Fuchia);
        } else {
            board1[currinfo.coord.row][currinfo.coord.col] = converttoXColour(currinfo.colour);
        }
    } else if (currinfo.boardnum == 2){
        if (currinfo.blinded){
            board2[currinfo.coord.row][currinfo.coord.col] = converttoXColour(Colour::Fuchia);
        } else {
            board2[currinfo.coord.row][currinfo.coord.col] = converttoXColour(currinfo.colour);
        }
    }
}

void GraphicalDisplay::updateHeldBlock(NextBlock heldBlockInfo){
    if (heldBlockInfo.boardnum == 1){
        heldblock[0] = convertColour(heldBlockInfo.colour);
    } else if (heldBlockInfo.boardnum == 2){
        heldblock[1] = convertColour(heldBlockInfo.colour);
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
    if (printheld){
        displayHeldBlock();
    }
    
#ifdef DEBUG
    cout << "GraphicalDisplay::display() ends"<<endl;
#endif
}

void GraphicalDisplay::displayLevel() {
    window.fillRectangle(0, 0, 350, 50, Xwindow::White);
	string level = "LEVEL: " + to_string(levels[0]);
    window.drawString(25, 25, level);
    window.fillRectangle(375, 0, 350, 50, Xwindow::White);
    level =  "LEVEL: " + to_string(levels[1]);
    window.drawString(375, 25, level);
}

void GraphicalDisplay::displayHighScore() {	
    window.fillRectangle(25, 50, 350, 25, Xwindow::White);
    string hiscore = "HISCORE: " + to_string(scores[2]);
    window.drawString(25, 50, hiscore);
    window.fillRectangle(375, 50, 350, 25, Xwindow::White);
    hiscore =  "HISCORE: " + to_string(scores[2]);
    window.drawString(375, 50, hiscore);
}

void GraphicalDisplay::displayScore() {
    window.fillRectangle(25, 75, 350, 25, Xwindow::White);
    string score = "SCORE: " + to_string(scores[0]);
    window.drawString(25, 75, score);
    window.fillRectangle(375, 75, 350, 25, Xwindow::White);
    score =  "SCORE: " + to_string(scores[1]);
    window.drawString(375, 75, score);
}

void GraphicalDisplay::displayBoards() {
	for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            window.fillRectangle(25 + j * 25, 80 + i * 25, 25, 25, board1[i][j]);
        }
    }
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            window.fillRectangle(j * 25 + 375, 80 + i * 25, 25, 25, board2[i][j]);
        }
    }
}

void GraphicalDisplay::displayWinner(string winner) {
     window.fillRectangle(125, 200, 425, 275, Xwindow::White);
    string winstr = "WINNER: " + winner;
    window.drawString(280, 337, winstr);
}


void GraphicalDisplay::displayBlock(char type, int boardnum, bool held){
    int num = 15;
    if (boardnum == 2){
        num = 385;
    }
    int num2 = 0;
    if (held){
        num2 = 135;
    }
    if (type == 'I'){
        window.fillRectangle(10 + num + num2, 25 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 25 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(60 + num + num2, 25 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(85 + num + num2, 25 + 550, 25,25, converttoXColour(convertChar(type)));
    } else if (type == 'J'){
        window.fillRectangle(10 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(10 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(60 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
    } else if (type == 'L'){
        window.fillRectangle(60 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(10 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(60 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
    } else if (type == 'O'){
        window.fillRectangle(10 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(10 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
    } else if (type == 'Z'){
        window.fillRectangle(10 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(60 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
    } else if (type == 'S'){
        window.fillRectangle(35 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(60 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(10 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
    } else if (type == 'T'){
        window.fillRectangle(10 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(60 + num + num2, 12 + 550, 25,25, converttoXColour(convertChar(type)));
        window.fillRectangle(35 + num + num2, 37 + 550, 25,25, converttoXColour(convertChar(type)));
    }
}

void GraphicalDisplay::displayNextBlock() {
    window.fillRectangle(10, 550, 135, 75, Xwindow::Black);
    window.fillRectangle(375, 550, 135, 75, Xwindow::Black);
    displayBlock(nextblock[0], 1, false);
    displayBlock(nextblock[1], 2, false);
}

void GraphicalDisplay::displayHeldBlock() {
    window.fillRectangle(155, 550, 125, 75, Xwindow::White);
    window.fillRectangle(510, 550, 125, 75, Xwindow::White);
    displayBlock(heldblock[0], 1, true);
    displayBlock(heldblock[1], 2, true);
}
