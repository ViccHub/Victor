IF EXIST g++ (
  g++ -I -g -w -Wall -std=c++11 -o ./bin/othello src/main.cpp src/types/types.hpp src/board/pieces.cpp src/board/board.cpp src/client/client.cpp src/ai/minmax.cpp
  GOTO :eof
) ELSE (
  IF EXIST "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" (
    "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" -I -g -w -Wall -std=c++11 -o ./bin/othello src/main.cpp src/types/types.hpp src/board/pieces.cpp src/board/board.cpp src/client/client.cpp src/ai/minmax.cpp
    goto :eof
  )
)

echo "g++ not found, please make sure its on your path"

:eof
END && EXIT
 