#include "client.hpp"

// https://stackoverflow.com/questions/34474627/linux-equivalent-for-conio-h-getch
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
int getChar(){
  return _getch();
}
#else
int getChar(){
  char buf = 0;
  struct termios old = { 0 };
  fflush(stdout);
  if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
  old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
  old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
  old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
  old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
  if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0) perror("read()");
  old.c_lflag    |= ICANON;    // local modes = Canonical mode
  old.c_lflag    |= ECHO;      // local modes = Enable echo. 
  if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
  return buf;
}
#endif


// https://forums.codeguru.com/showthread.php?466009-Reading-from-stdin-(without-echo)
// https://stackoverflow.com/questions/3213037/determine-if-linux-or-windows-in-c
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
void disable_echo(){
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
}
#else
void disable_echo(){
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
void enable_echo(){
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & (ENABLE_ECHO_INPUT));
}
#else
void enable_echo(){
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}
#endif


Client::Client()
{
  board.init();
  currentTurn = Piece::BLACK;
  whites = board.whitePieces();
  blacks = board.blackPieces();
}

void Client::playRound(function<void(Board&,Piece)> p1, function<void(Board&,Piece)> p2 ){
  if (board.validMoves(Piece::BLACK).empty()){
    cout << "There are no possible moves, turn skipped " << endl;
  } else
  {
    p1(board,Piece::BLACK);
  }

  if (board.validMoves(Piece::BLACK).empty()){
    cout << "There are no possible moves, turn skipped " << endl;
  } else
  {
    p2(board,Piece::WHITE);
  }
  
}

void Client::play(function<void(Board&,Piece)> p1,function<void(Board&,Piece)> p2){
  while(!board.validMoves(Piece::BLACK).empty() && !board.validMoves(Piece::BLACK).empty()){
    playRound(p1,p2);
    whites = board.whitePieces();
    blacks = board.blackPieces();
  }

  cout << "\nMatch finished! Scores: " << endl;
  cout << to_string(Piece::WHITE) << ": " << to_string(whites.size()) << endl;
  cout << to_string(Piece::BLACK) << ": " << to_string(blacks.size()) << endl;

  if (whites.size() > blacks.size()){
    cout << to_string(Piece::WHITE) << " is the winner!" << endl;
  } else if (whites.size() > blacks.size())
  {
    cout << to_string(Piece::BLACK) << " is the winner!" << endl;
  } else
  {
    cout << "It's a draw!" << endl;
  }
}

void delete_char(){
  cout << '\b' << ' ' << '\b';
}

UntranslatedPosition getCoordinate(){
  vector<char> optsRow{'1','2','3','4','5','6','7','8'};
  vector<char> optsCol{
    'a','b','c','d','e','f','g','h',
    'A','B','C','D','E','F','G','H'
  };

  char c;
  int row = -1;
  char col = '~';
  bool printChar = false;
  auto toUpper = [](char c){
    if ('a' <= c && c <= 'z')
      return static_cast<char>(c - 'a' + 'A');
    return c;
  };

  auto is_valid = [](vector<char> opts, char c){
    for(auto _c : opts)
    { 
      if (_c == c) return true;
    }
    return false;
  };

  auto toDigit = [](char c){
    return c - '0';
  };

  while (true)
  {
    printChar = false;
    disable_echo();
    c = getChar();
    enable_echo();

    if (c == 27 || c == 24 || c == 3)
      throw "Thanks for playing!";

    if (c == '\n' || c == '\r' || c == '\r\n' || cin.eof() || c == -1){
      if (col != '~') return make_tuple(row,col);
      continue;
    }

    if (c == '\b' || c == 127){
      if (row != -1){
        delete_char();
        printChar = false;
      }
      if (col != '~'){
        col = '~';
      } else if (row != -1)
      {
        row = -1;
      }
    }
    if (is_valid(optsRow,c) && row == -1){
      printChar = true;
      row = c - '0';
    }
      
    
    if (is_valid(optsCol,c) && row!= -1 && col == '~'){
      printChar = true;
      col = toUpper(c);
    }

    if (printChar){
      cout << c;
    } 
    
    
    
  }
  

}


void playerPlay(Board& b, Piece p){
  string err = "";
  bool keep = true;
  UntranslatedPosition pos;
  
  

  while (keep)
  {
    cout << to_string(b) << endl;
    cout << err << endl;
    cout << to_string(p) << " Input a move in format XX (i.e: 1A): " << endl;
    cout << ">> ";
    pos = getCoordinate();
    try
    {
      b.playMove(pos,p);
      keep = false;
      clear_screen();
    }
    catch(string _err)
    {
      err = _err;
      keep = true;
    }
  }
}

void pcPlay(Board& b, Piece p){
  char c;
  b.playMove(minmax(b,p),p);
  cout << to_string(b) << endl;
  cout << "Press any key to continue" << endl;
  disable_echo();
  c = getChar();
  enable_echo();
  clear_screen();
}


void clear_screen(){
  cout << "\033c";
}