#pragma once 
#include <string>
using namespace std;


enum class Piece { BLACK, WHITE, NONE };

Piece flip(Piece p);
string to_string(Piece p);
Piece nextPiece(Piece p);

bool has_value(Piece p);

Piece value(Piece p);

const Piece nullopt = Piece::NONE;