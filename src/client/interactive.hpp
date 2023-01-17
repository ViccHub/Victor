#pragma once 
#include <vector>
#include <string>
#include <tuple>
#include <exception>
#include <iostream>
#include <functional>
#include "client.hpp"
#include "../board/board.hpp"
#include "../types/types.hpp"
#include "../board/pieces.hpp"
using namespace std;


class Interactive
{
private:
  Client client;
public:
  Interactive();
};


