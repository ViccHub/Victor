#pragma once 
#include <vector>
#include <string>
#include <tuple>
#include <exception>
#include <iostream>
#include <functional>

#include "../board/board.hpp"
#include "../types/types.hpp"
#include "../board/pieces.hpp"
#include "../ai/minmax.hpp"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
using namespace std;

void disable_echo();
void enable_echo();

class Client
{
private:
  Board board;
  Piece currentTurn;
  vector<UntranslatedPosition> whites;
  vector<UntranslatedPosition> blacks;
  void playRound(function<void(Board&,Piece)> p1, function<void(Board&,Piece)> p2 );
public:
  Client();
  void play(function<void(Board&,Piece)> p1, function<void(Board&,Piece)> p2 );
  
};


void playerPlay(Board& b, Piece p);
void pcPlay(Board& b, Piece p);

void clear_screen();