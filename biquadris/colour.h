#ifndef _COLOUR_
#define _COLOUR_
#include <string>

enum class Colour {
	Red, Orange, Yellow,
	Green, Blue, Purple, Cyan, White    
};
//Cyan = I
//Blue = J
//Orange = L
//Yellow = O
//Green = S
//Purple = T
//Red = Z
//White = empty
char convertColour(Colour colour);
Colour convertString(std::string type);

#endif
