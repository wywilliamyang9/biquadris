#ifndef _COLOUR_
#define _COLOUR_

enum class Colour {Red, Orange, Yellow, 
Green, Blue, Purple, LightBlue, White}
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

#endif
