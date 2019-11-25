#include "game.h"
#include <iostream>

int main(int argc, char *argv[]){
    argc = argc - 1;
    bool textonly = false;
    for (int i = 1; i <= argc; i++){
        string tmparg = argv[i];
        if (tmparg == "-seed"){
            string seed = argv[i+1];
            stringstream temp(str_num);
            if (!(temp >> width)){
                seed =0;
            }
            i++;
        } else if (tmparg == "-text"){
            textonly = true;
        } else if (tmparg == "-scriptfile1"){
            string scriptfile1 = argv[i+1];
            stringstream temp(str_num);
            if (!(temp >> width)){
                scriptfile1 = "biquadris_sequence1.txt";
            }
            i++;
        } else if (tmparg == "-seed"){
            string scriptfile2 = argv[i+1];
            stringstream temp(str_num);
            if (!(temp >> width)){
                scriptfile2 = "biquadris_sequence2.txt";
            }
            i++;
        }
    }
}
