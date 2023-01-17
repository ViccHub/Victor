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
using namespace std;


const int MAX_DEPTH = 3;

UntranslatedPosition minmax(Board& b, Piece p);