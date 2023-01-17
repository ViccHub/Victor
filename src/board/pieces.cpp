#include "pieces.hpp"

/// @brief Flips a piece
/// @param p piece to be flipped
/// @return White if the piece was black, and black otherwise.
Piece flip(Piece p){
  switch (p)
  {
  case Piece::BLACK :
    return Piece::WHITE;
  default:
    return Piece::BLACK;
  }
}

/// @brief (Pretty) String representation of a piece
/// @param p 
/// @return Either an unicode red circle or an unicode white circle
string to_string(Piece p){
  switch (p)
  {
  case Piece::WHITE:
    return "⚪";
  case Piece::BLACK:
    return "🔴";
  default:
    return "  ";
  }
}


/// @brief Checks whether a piece is not none.
/// @param p 
/// @return True if not None, false otherwise.
bool has_value(Piece p){
  return p != Piece::NONE;
}


Piece value(Piece p){
  return p;
}