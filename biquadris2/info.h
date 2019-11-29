#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>
#include "colour.h"
#include "coordinates.h"

struct Info {
  Coordinates coord;
  Colour colour;
  bool blinded;
  int boardnum;
};

#endif
