﻿#ifndef _COLOUR_
#define _COLOUR_
#include <string>

enum class Colour {
	Red, Orange, Yellow,
	Green, Blue, Purple, Cyan, White, Brown, Fuchia
};
//Cyan = I
//Blue = J
//Orange = L
//Yellow = O
//Green = S
//Purple = T
//Red = Z
//White = empty
//Brown = dot
char convertColour(Colour colour);
Colour convertString(std::string type);
Colour convertChar(char type);
#endif
