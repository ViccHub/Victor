#pragma once 
#include <string>
#include <tuple>
#include <exception>
using namespace std;

/// @brief For simplicity, we shall not do error handling, thus every error 
/// shall propagate to the client as a string.
typedef string error;

/// @brief C++11 does not include variants, so this is the best we can do.
/// @tparam A return type of the computation that may fail.
template <typename A>
using OptionalLog = A ;

/// @brief C++11 doesnt include optionals, nor generics over sums. 
/// @tparam A 
template <typename A>
using Optional = A ;

/// @brief C++11 doesnt include optional library, thus we are mocking it in an inferior
/// but good enough for our purposes way.
struct monostate{};
