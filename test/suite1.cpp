#include <iostream>
#include "../src/board/pieces.hpp"
#include "../src/board/board.hpp"

void printing_empty_board(){
  Board b;
  cout << "----------------------------------" << endl;
  cout << "Printing empty board: " << endl;
  cout << to_string(b) << endl;
  cout << "End test" << endl;
  cout << "----------------------------------" << endl;
}


void printing_semiFilled_board(){
  Board b;
  b.setPos({1,'A'},Piece::BLACK);
  b.setPos({1,'B'},Piece::WHITE);
  b.setPos({1,'H'},Piece::WHITE);
  b.setPos({5,'C'},Piece::BLACK);
  b.setPos({5,'D'},Piece::BLACK);
  b.setPos({5,'B'},Piece::WHITE);

  cout << "----------------------------------" << endl;
  cout << "Printing semi filled board: " << endl;
  cout << to_string(b) << endl;
  cout << "End test" << endl;
  cout << "----------------------------------" << endl;
}

int main(int argc, char const *argv[])
{
  cout 
    << "This test suite covers basic printing/string functionality and judges visuals only" 
    << endl;
  cout << "test starts!" << endl;
  printing_empty_board();
  printing_semiFilled_board();
  return 0;
}
