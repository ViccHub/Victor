#include <iostream>
#include "../src/board/pieces.hpp"
#include "../src/board/board.hpp"

void end_ex_1(){
  Board b;
  for (int i = 1; i <= 8; i++)
  {
    for (char c = 'A'; c <= 'H'; c++)
      b.setPos({i,c},Piece::WHITE);
  }
  
  b.clearPos({4,'H'});
  b.clearPos({5,'G'});
  b.clearPos({5,'H'});
  b.clearPos({6,'G'});
  b.setPos({6,'H'},Piece::BLACK);
  b.clearPos({7,'H'});
  
  vector<UntranslatedPosition> valid_white = b.validMoves(Piece::WHITE);
  vector<UntranslatedPosition> valid_black = b.validMoves(Piece::BLACK);

  cout << "----------------------------------" << endl;
  cout << "Example 1 board: " << endl;
  cout << to_string(b) << endl;
  cout << "Are there valid moves?" << endl;
  if (valid_white.empty() && valid_black.empty()){
    cout << "No!" << endl;
    cout << "Test Passed" << endl;
  } else
  {
    cout << "Yes! the moves are: " << endl;
    if (!valid_black.empty()){
      cout << "For " << to_string(Piece::BLACK) << ":" << endl;
      for(auto pos : valid_black)
      {
        auto [row,col] = pos;
        cout << row << col << endl;
      }
    }

    if (!valid_white.empty()){
      cout << "For " << to_string(Piece::WHITE) << ":" << endl;
      for(auto pos : valid_white)
      {
        auto [row,col] = pos;
        cout << row << col << endl;
      }
    }
    
    cout << "Test Failed" << endl;

  }
  
  cout << "End test" << endl;
  cout << "----------------------------------" << endl;
}

void end_ex_2(){
  Board b;
  for (int i = 1; i <= 8; i++)
  {
    for (char c = 'A'; c <= 'H'; c++)
      b.setPos({i,c},Piece::WHITE);
  }
  
  b.clearPos({1,'A'});
  b.clearPos({2,'A'});
  b.clearPos({8,'A'});
  b.clearPos({2,'G'});
  b.clearPos({8,'G'});
  b.clearPos({8,'H'});

  for (char c = 'B'; c <= 'H'; c++)
    b.setPos({1,c},Piece::BLACK);
  
  for (int i = 1; i <= 7; i++)
    b.setPos({i,'H'},Piece::BLACK);

  
  vector<UntranslatedPosition> valid_white = b.validMoves(Piece::WHITE);
  vector<UntranslatedPosition> valid_black = b.validMoves(Piece::BLACK);

  cout << "----------------------------------" << endl;
  cout << "Example 1 board: " << endl;
  cout << to_string(b) << endl;
  cout << "Are there valid moves?" << endl;
  if (valid_white.empty() && valid_black.empty()){
    cout << "No!" << endl;
    cout << "Test Passed" << endl;
  } else
  {
    cout << "Yes! the moves are: " << endl;
    if (!valid_black.empty()){
      cout << "For " << to_string(Piece::BLACK) << ":" << endl;
      for(auto pos : valid_black)
      {
        auto [row,col] = pos;
        cout << row << col << endl;
      }
    }

    if (!valid_white.empty()){
      cout << "For " << to_string(Piece::WHITE) << ":" << endl;
      for(auto pos : valid_white)
      {
        auto [row,col] = pos;
        cout << row << col << endl;
      }
    }
    
    cout << "Test Failed" << endl;

  }
  
  cout << "End test" << endl;
  cout << "----------------------------------" << endl;
}

void end_ex_3(){
  Board b;

  b.setPos({1,'E'},Piece::WHITE);
  b.setPos({2,'E'},Piece::WHITE);
  b.setPos({2,'F'},Piece::WHITE);

  for (char c = 'A'; c <= 'G'; c++)
   b.setPos({3,c},Piece::WHITE);
  
  b.setPos({3,'H'},Piece::BLACK);
  b.setPos({4,'H'},Piece::BLACK);
  b.setPos({5,'H'},Piece::BLACK);

  for (char c = 'C'; c <= 'F'; c++)
   b.setPos({4,c},Piece::WHITE);
  
  for (char c = 'C'; c <= 'E'; c++)
   b.setPos({5,c},Piece::WHITE);

  vector<UntranslatedPosition> valid_white = b.validMoves(Piece::WHITE);
  vector<UntranslatedPosition> valid_black = b.validMoves(Piece::BLACK);

  cout << "----------------------------------" << endl;
  cout << "Example 1 board: " << endl;
  cout << to_string(b) << endl;
  cout << "Are there valid moves?" << endl;
  if (valid_white.empty() && valid_black.empty()){
    cout << "No!" << endl;
    cout << "Test Passed" << endl;
  } else
  {
    cout << "Yes! the moves are: " << endl;
    if (!valid_black.empty()){
      cout << "For " << to_string(Piece::BLACK) << ":" << endl;
      for(auto pos : valid_black)
      {
        auto [row,col] = pos;
        cout << row << col << endl;
      }
    }

    if (!valid_white.empty()){
      cout << "For " << to_string(Piece::WHITE) << ":" << endl;
      for(auto pos : valid_white)
      {
        auto [row,col] = pos;
        cout << row << col << endl;
      }
    }
    
    cout << "Test Failed" << endl;

  }
  
  cout << "End test" << endl;
  cout << "----------------------------------" << endl;
}

int main(int argc, char const *argv[])
{
  cout 
    << "This test suite covers some useful functions over board." 
    << endl;
  cout << "test starts!" << endl;
  end_ex_1();
  end_ex_2();
  end_ex_3();
  return 0;
}