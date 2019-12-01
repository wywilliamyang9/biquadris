#include "colour.h"

char convertColour(Colour colour){
    if (colour == Colour::Red){
        return 'Z';
    } else if (colour == Colour::Orange){
        return 'L';
    } else if (colour == Colour::Cyan){
        return 'I';
    } else if (colour == Colour::Blue){
        return 'J';
    } else if (colour == Colour::Yellow){
        return 'O';
    } else if (colour == Colour::Green){
        return 'S';
    } else if (colour == Colour::Purple){
        return 'T';
    } else {
        return ' ';
    }
}
Colour convertString(std::string type){
    if (type == "Z"){
        return Colour::Red;
    } else if (type == "L"){
        return Colour::Orange;
    } else if (type == "I"){
        return Colour::Cyan;
    } else if (type == "J"){
        return Colour::Blue;
    } else if (type == "O"){
        return Colour::Yellow;
    } else if (type == "S"){
        return Colour::Green;
    } else if (type == "T"){
        return Colour::Purple;
    } else {
        return Colour::White;
    }
}

