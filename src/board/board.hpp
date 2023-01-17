#pragma once 
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include "pieces.hpp"
#include "../types/types.hpp"
using namespace std;

/// @brief A board is a 2D matrix which can be filled with a piece or be empty.
typedef vector<vector<Piece>> BoardState;

/// @brief In othello, positions are a pair `(a,b)` where `1 <= a <= 8` and `'A' <= b <= 'H'`.
typedef tuple<int,char> UntranslatedPosition;
/// @brief Positions in a board are pairs `(a,b)` such that `0 <= a,b < 8`.
typedef tuple<int,int> Position;



class Board
{
private:
  /// @brief The current state of the board.
  BoardState state;
  OptionalLog<Position> translate(UntranslatedPosition p) const;
  vector<tuple<UntranslatedPosition,Piece>> pieces();
  OptionalLog<vector<vector<tuple<UntranslatedPosition, Piece>>>> flips(UntranslatedPosition pos, Piece p);
public:
  // Constructors and Destructors 

  Board();

  // Accesors 

  OptionalLog<Piece>getPos(UntranslatedPosition p) const;
  
  // Setters

  OptionalLog<monostate>setPos(UntranslatedPosition pos, Piece p);
  OptionalLog<monostate>clearPos(UntranslatedPosition pos);
  OptionalLog<monostate>checkIfEmpty(UntranslatedPosition pos, Piece p);

  // Client functions

  OptionalLog<monostate> playMove(UntranslatedPosition pos, Piece p);
  vector<UntranslatedPosition> validMoves(Piece p);
  void init();

  // Useful for the programmer

  static const int upperBoundRow  = 8;
  static const char upperBoundCol = 'H';
  static const int lowerBoundRow  = 1;
  static const char lowerBoundCol = 'A';

  vector<UntranslatedPosition> whitePieces();
  vector<UntranslatedPosition> blackPieces();
};



enum class Move { U, D, L, R, DLU, DRU, DLD, DRD  };
UntranslatedPosition moveTo(UntranslatedPosition pos, Move dir);

constexpr Move MlowerBound = Move::U;
constexpr Move MupperBound = Move::DRD;

string to_string(const Board& b);

