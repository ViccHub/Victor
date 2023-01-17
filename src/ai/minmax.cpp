#include "minmax.hpp"


enum class Strategy { MIN, MAX };

/// @brief Flips the given strategy, cyling it.
/// @param s 
/// @return MIN if MAX, MAX if MIN
/// @note time complexity O(1)
Strategy flip(Strategy s){
  switch (s)
  {
  case Strategy::MIN:
    return Strategy::MAX;
  
  default:
    return Strategy::MIN;
  }
}

tuple<UntranslatedPosition,int> f(Strategy s, tuple<UntranslatedPosition,int> a, tuple<UntranslatedPosition,int> b){
  if (s == Strategy::MAX){
    if (a >= b) return a;
    return b;
  } 
  if (a <= b) return a;
  return b;
};

/// @brief Given the strategy, returns the Piece (player) that holds the strategy.
/// @param s 
/// @note time complexity O(1)
Piece h(Strategy s){
  return s == Strategy::MAX ? Piece::BLACK : Piece::WHITE;
}

/// @brief Inverse function of h.
/// @note time complexity O(1)
Strategy h2(Piece p){
  return h(Strategy::MAX) == p ? Strategy::MAX : Strategy::MIN;
}

/// @brief Returns the score for the current board. Independent of who
/// holds the maximum.
/// @param b 
/// @note time complexity O(rows * cols).
int g(Board& b){
  int blacks = b.blackPieces().size();
  int whites = b.whitePieces().size();
  int res    = blacks-whites;
  return Piece::BLACK == h(Strategy::MAX) ? res : -res;
};

/// @brief min-max applies well to otello, we assign each black piece a positive
/// value, and each white piece a negative, thus the black player wants to maximize
/// its board score and the white player wants to minimize it. Since the winner
/// player is the one who holds the most pieces, this is a valid min-max heuristic.
/// @param b current board
/// @param pendingDepth  current depth (decreases up till 0, initialized at MAX_DEPTH)
/// @param s current strategy
/// @return either an int meaning the score of the play, or throws an exception
/// with the best move.
/// @note unknown time complexity (search space is hard to find out since the game may end 
/// on a non-dense board, or a dense one).
int minmax(Board& b, int pendingDepth, Strategy s){
  if (pendingDepth == 0){
    return g(b);
  }
    
  auto p     = h(s);
  auto moves = b.validMoves(p);
  

  if (moves.empty()){
    return g(b);
  }

  auto firstMove = moves.back();
  moves.pop_back();
  
  auto winner_move = firstMove;
  b.setPos(firstMove,p);
  auto res = tuple<UntranslatedPosition,int>{firstMove,minmax(b,pendingDepth-1,flip(s))};
  b.clearPos(firstMove);

  for (auto pos: b.validMoves(p))
  {
    b.setPos(pos,p);
    res = f(s,res,make_tuple(pos,minmax(b,pendingDepth-1,flip(s))));
    b.clearPos(pos);
  }
  
  if (pendingDepth == MAX_DEPTH)
    throw get<0>(res);
  return get<1>(res);
}

/// @brief min-max AI for othello.
/// @param b current board
/// @param p player that holds the MAX strategy
/// @return best possible move for the given piece.
/// @note unknown time complexity (search space is hard to find out since the game may end 
/// on a non-dense board, or a dense one).
UntranslatedPosition minmax(Board& b, Piece p){
  try
  {
    minmax(b,MAX_DEPTH,h2(p));
  }
  catch(UntranslatedPosition e)
  {
    return e;
  }
  
}