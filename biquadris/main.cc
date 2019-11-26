#include "game.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]){
    argc = argc - 1;
    int seed = 0;
    bool textOnly = false;
    string scriptFile1 = "biquadris_sequence1.txt";
    string scriptFile2 = "biquadris_sequence2.txt";
    int startLevel = 0;
    for (int i = 1; i <= argc; i++){
        string tmparg = argv[i];
        if (tmparg == "-seed"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> width)){
            }
            i++;
        } else if (tmparg == "-text"){
            textonly = true;
        } else if (tmparg == "-scriptfile1"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> scriptfile1)){
            }
            i++;
        } else if (tmparg == "-seed"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> scriptfile2)){
            }
            i++;
        } else if (tmparg == "-startlevel"){
            string tmp = argv[i+1];
            stringstream temp(tmp);
            if (!(temp >> startlevel)){
            }
            i++;
        }
    }
}
