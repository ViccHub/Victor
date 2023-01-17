#include "board.hpp"
#include <iostream>

/// @brief Builds an 8x8 empty board.
Board::Board()
{
  constexpr int rows = Board::upperBoundRow - Board::lowerBoundRow + 1;
  constexpr int cols = Board::upperBoundCol - Board::lowerBoundCol + 1;

  state = vector<vector<Piece> >{rows,vector<Piece>{cols,Piece::NONE}};
}

/// @brief A way to translate the positions from the othello coordinate system to
/// the board coordinate system.
/// @param p untranslated position
/// @return Either the translated position provided that the input is correct or an error
/// signaling the bad input.
/// @note time complexity O(1).
OptionalLog<Position> Board::translate(UntranslatedPosition p) const{
  auto row = get<0>(p);
  auto col = get<1>(p);

  /* Error message generation */
  auto badRow       = [](int row){
    return "Row number should be between " 
      + to_string(Board::lowerBoundRow) + " and " + to_string(Board::upperBoundRow) 
      + ". Given: " + to_string(row);
  };
  auto badColumn    = [](char col){
    return "Column letter should be between '" 
      + string(1,Board::lowerBoundCol)
      + "' and '" 
      + string(1,Board::upperBoundCol)
      + "'. Given: " + to_string(col);
  };

  /* Validation checks */
  auto inRowBounds =  Board::lowerBoundRow <= row && row <= Board::upperBoundRow;
  auto inColBounds = Board::lowerBoundCol <= col && col <= Board::upperBoundCol;
  
  if (!inRowBounds)
    throw badRow(row);
  if (!inColBounds)
    throw badColumn(col);

  /* Translations */
  auto translatedRow = row - Board::lowerBoundRow;
  auto translatedCol = col - Board::lowerBoundCol;

  return Position{translatedRow,translatedCol};
}

/// @brief Access a position in the board which might be empty. 
/// @param row Position of the row in the othello coordinate system
/// @param col Position of the col in the othello coordinate system
/// @return Either an error if the othello coordinates were
/// incorrect, or a piece if the position is not empty.
/// @note time complexity O(1).
OptionalLog<Piece> Board::getPos(UntranslatedPosition p) const{
  auto row = get<0>(p);
  auto col = get<1>(p);
  auto mTranslated = translate(make_tuple(row,col));    
  auto trow = get<0>(mTranslated);
  auto tcol = get<1>(mTranslated);

  return state[trow][tcol];
}

/// @brief Forcefully sets a position in the board, disregarding whether or not
/// that position already held a piece
/// @param pos Position in the othello coordinate system
/// @param p Piece to position
/// @return Either an error if the othello coordinates were
/// incorrect, or unit type.
/// @note time complexity O(1).
OptionalLog<monostate> Board::setPos(UntranslatedPosition pos, Piece p){
  auto row = get<0>(pos);
  auto col = get<1>(pos);
  auto mTranslated = translate(make_tuple(row,col));
  auto trow = get<0>(mTranslated);
  auto tcol = get<1>(mTranslated);

  state[trow][tcol] = p;

  return monostate{};
}

/// @brief Forcefully clears a position in the board, disregarding whether or not
/// that position already held a piece
/// @param pos Position in the othello coordinate system
/// @return Either an error if the othello coordinates were
/// incorrect, or unit type.
/// @note time complexity O(1).
OptionalLog<monostate> Board::clearPos(UntranslatedPosition pos){
  auto row = get<0>(pos);
  auto col = get<1>(pos);
  auto mTranslated = translate(make_tuple(row,col));
  auto trow = get<0>(mTranslated);
  auto tcol = get<1>(mTranslated);

  state[trow][tcol] = Piece::NONE;

  return monostate{};
}


/// @brief Sets an empty position in the board, if a piece already holds
/// that position, returns an error.
/// @param row Position of the row in the othello coordinate system
/// @param col Position of the col in the othello coordinate system
/// @param p Piece to position
/// @return Either an error if the othello coordinates were
/// incorrect or the position is occupied, or unit type.
/// @note time complexity O(1).
OptionalLog<monostate>Board::checkIfEmpty(UntranslatedPosition pos, Piece p){
  auto row = get<0>(pos);
  auto col = get<1>(pos);

  auto mTranslated = translate(make_tuple(row,col));
  auto trow = get<0>(mTranslated);
  auto tcol = get<1>(mTranslated);

  // check if position is not empty.
  if (has_value(state[trow][tcol]))
    throw "Position: " + to_string(row) + col + " is already occupied";

  //state[trow][tcol] = p;

  return monostate{};
}

/// @brief Given a position in the board, and a direction, returns
/// the position that would be yielded if we were walking in that direction
/// without regarding bounds.
/// @param pos base position
/// @param dir direction of movement
/// @return position + dir.
/// @note time complexity O(1).
UntranslatedPosition moveTo(UntranslatedPosition pos, Move dir){
  auto row = get<0>(pos);
  auto col = get<1>(pos);
  switch (dir)
  {
  case Move::U:
    return make_tuple(row-1,col);
  
  case Move::D:
    return make_tuple(row+1,col);
  
  case Move::L:
    return make_tuple(row,col-1);
  
  case Move::R:
    return make_tuple(row,col+1);
  
  case Move::DLU:
    return make_tuple(row-1,col-1);
  
  case Move::DRU:
    return make_tuple(row-1,col+1);
  
  case Move::DLD:
    return make_tuple(row+1,col-1);
  
  case Move::DRD:
    return make_tuple(row+1,col+1);
  }
}

/// @brief Returns a pretty string representation of the board.
/// @param b the current board
/// @return Pretty string representation of the board.
/// @note time complexity O(size(board)).
string to_string(const Board& b){
  string stringBoard;

  auto to_string_pos = [](Piece mp){
    return has_value(mp) 
      ? to_string(value(mp))
      : "  ";
  };

  string topBorder = "  -";
  for (int _ = 0; _ < 8; _++)
    topBorder += "---";
  
  stringBoard += topBorder + "\n";

  for (int row = Board::lowerBoundRow; row <= Board::upperBoundRow ; row++)
  {
    stringBoard += to_string(row) + " ";
    for (char col = Board::lowerBoundCol; col <= Board::upperBoundCol ; col++){
      stringBoard += "|" 
        + to_string_pos(b.getPos(make_tuple(row,col)));
    }
    stringBoard += "|\n";
  }

  stringBoard += topBorder + "\n  ";
  for (char col = Board::lowerBoundCol; col <= Board::upperBoundCol ; col++){
    stringBoard += " " 
      + string(1, col)
      + " ";
  }
  
  stringBoard += " \n";
  return stringBoard;

}


/// @brief Returns the longest path that contains just pieces
/// @param b The current board
/// @param pos The starting position
/// @param dir The direction
/// @return longest path that contains just pieces
/// @note time complexity O(rows + cols).
vector<tuple<UntranslatedPosition,Piece>> getByDir(const Board& b, UntranslatedPosition pos, Move dir, Piece p){
  vector<tuple<UntranslatedPosition,Piece>> path;
  pos = moveTo(pos,dir);
  Piece mp;
  try
  {
    mp = b.getPos(pos);
  }
  catch(...)
  {
    mp = nullopt;
  }
   

  bool seen = true;
  while (has_value(mp)){
    Piece p2 = value(mp);
    if (p == p2){
      if (seen) return path;
      seen = true;
    }
    seen = false;
    path.push_back(make_tuple(pos,p2));
    pos = moveTo(pos,dir);
    try
    {
      mp = b.getPos(pos);
    }
    catch(...)
    {
      mp = nullopt;
    }
    
  }

  if (seen) return path;

  while (!path.empty() && get<1>(path.back())!=p)
    path.pop_back();

  return path;

}

/// @brief Yields all the pieces that can form a path for the given piece in the given position
/// @param pos position in which the piece should be placed
/// @param p piece
/// @return Either an error if the position is occupied or no pieces are turned, or nothing.
/// @note time complexity O(rows + cols).
OptionalLog<vector<vector<tuple<UntranslatedPosition, Piece>>>> Board::flips(UntranslatedPosition pos, Piece p){
  auto merror = checkIfEmpty(pos,p);
  
  // enum classes are not iterable, thus we cannot use a for
  // loop without some tricks, and since this only
  // happens in this function, the abstraction is not
  // mandatory.

  auto upPath    = getByDir(*this,pos,Move::U,p);
  auto downPath  = getByDir(*this,pos,Move::D,p);
  auto leftPath  = getByDir(*this,pos,Move::L,p);
  auto rightPath = getByDir(*this,pos,Move::R,p);
  auto dluPath   = getByDir(*this,pos,Move::DLU,p);
  auto druPath   = getByDir(*this,pos,Move::DRU,p);
  auto dldPath   = getByDir(*this,pos,Move::DLD,p);
  auto drdPath   = getByDir(*this,pos,Move::DRD,p);
  vector<tuple<UntranslatedPosition, Piece>> ps;

  vector<vector<tuple<UntranslatedPosition, Piece>>>paths;
  
  paths.push_back(drdPath);
  paths.push_back(upPath);
  paths.push_back(downPath);
  paths.push_back(leftPath);
  paths.push_back(rightPath);
  paths.push_back(dluPath);
  paths.push_back(druPath);
  paths.push_back(dldPath);
  
  for(auto path : paths)
  {
   for(auto t : path)
   {
    auto _p = get<1>(t);
    if (p == _p) continue;
    return paths;
   } 
  }

  auto r = get<0>(pos);
  auto c = get<1>(pos);
  error message = "Cannot place stone in position: " 
    + to_string(r) 
    + string(1,c) 
    + " because it violates the: At least 1 stone must be flipped condition.";
  throw message;
}


/// @brief Returns all the pieces of the board coupled with their position.
/// @note time complexity O(rows * cols).
vector<tuple<UntranslatedPosition,Piece>> Board::pieces(){
  vector<tuple<UntranslatedPosition,Piece>> ps;
  Piece p;
  for (int row = Board::lowerBoundRow; row <= Board::upperBoundRow ; row++)
  {
    for (char col = Board::lowerBoundCol; col <= Board::upperBoundCol ; col++){
      UntranslatedPosition pos{row,col};
      p = getPos(pos);
      if (has_value(p)) ps.push_back(make_tuple(pos,value(p)));
    }
  }
  return ps;
}

/// @brief Returns all the white pieces of the board coupled with their position.
/// @note time complexity O(rows * cols).
vector<UntranslatedPosition> Board::whitePieces(){
  vector<UntranslatedPosition> whites;

  for(auto t : pieces())
  {
    auto pos = get<0>(t);
    auto p   = get<1>(t);
    if (p == Piece::WHITE)
      whites.push_back(pos);
  }

  return whites;
}

/// @brief Returns all the black pieces of the board coupled with their position.
/// @note time complexity O(rows * cols).
vector<UntranslatedPosition> Board::blackPieces(){
  vector<UntranslatedPosition> blacks;

  for(auto t : pieces())
  {
    auto pos = get<0>(t);
    auto p   = get<1>(t);
    if (p == Piece::BLACK)
      blacks.push_back(pos);
  }

  return blacks;
}

/// @brief Tries to play a piece in the given position
/// @param pos position in which the piece should be placed
/// @param p piece
/// @return Either an error if the position is occupied or no pieces are turned, or nothing.
/// @note time complexity O(rows + cols).
OptionalLog<monostate> Board::playMove(UntranslatedPosition pos, Piece p){
  auto paths = flips(pos,p);;

  setPos(pos,p);
  
  for(auto path : paths)
  {
   for(auto t : path)
   {
    auto _pos = get<0>(t);
    auto r    = get<0>(_pos);
    auto c    = get<1>(_pos);
    setPos(_pos,p);
    
   } 
  }
  return monostate{};
}

/// @brief Returns a list of all valid moves for the given piece.
/// @param p 
/// @note time complexity O((rows + cols)^3)
vector<UntranslatedPosition> Board::validMoves(Piece p){
  UntranslatedPosition pos;
  vector<UntranslatedPosition> moves;
  for (int row = Board::lowerBoundRow; row <= Board::upperBoundRow ; row++)
  {
    for (char col = Board::lowerBoundCol; col <= Board::upperBoundCol ; col++){
      pos = make_tuple(row,col);
      try{
        flips(pos,p);
        moves.push_back(pos);
      }catch(...){}
    } 
  }

  return moves;
}

void Board::init(){
  setPos(make_tuple(4,'D'),Piece::WHITE);
  setPos(make_tuple(4,'E'),Piece::BLACK);
  setPos(make_tuple(5,'D'),Piece::BLACK);
  setPos(make_tuple(5,'E'),Piece::WHITE);
}