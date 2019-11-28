#ifndef _COLOUR_
#define _COLOUR_
#include <string>

enum class Colour {
	Red, Orange, Yellow,
	Green, Blue, Purple, LightBlue, White
};
//LightBlue = I
//Blue = J
//Orange = L
//Yellow = O
//Green = S
//Purple = T
//Red = Z
//White = empty
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

Colour convertString(std::string type){
    if (type == "Z"){
        return Colour::Red;
    } else if (type == "L"){
        return Colour::Orange;
    } else if (type == "I"){
        return Colour::LightBlue;
    } else if (type == "J"){
        return Colour::Blue;
    } else if (type == "O"){
        return Colour::Yellow;
    } else if (type == "S"){
        return Colour::Green;
    } else if (type == "T"){
        return Colour::Purple;
    } else if (type == " "){
        return Colour::White;
    }
}

#endif
