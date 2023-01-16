cmake_minimum_required(VERSION 3.21)
project(Solitaire)

set(CMAKE_C_STANDARD 99)

add_executable(check checkfile/check.c checkfile/card.c checkfile/foundation.c checkfile/tableau.c checkfile/stockWaste.c checkfile/checkf.c)
add_executable(advance checkfile/card.c checkfile/foundation.c checkfile/tableau.c checkfile/stockWaste.c checkfile/checkf.c advancefile/advance.c advancefile/advance.h advancefile/moves.c advancefile/moves.h advancefile/printGame.c advancefile/printGame.h advancefile/printGameToFile.c advancefile/printGameToFile.h)

set(CMAKE_CXX_STANDARD 14)
add_executable(winnable winnablefile/winnable.cpp winnablefile/parseGameFile.cpp winnablefile/parseGameFile.h winnablefile/gameConfiguration.cpp winnablefile/gameConfiguration.h winnablefile/tableau.cpp winnablefile/tableau.h winnablefile/rules.cpp winnablefile/rules.h winnablefile/foundation.cpp winnablefile/foundation.h winnablefile/StockWaste.cpp winnablefile/StockWaste.h winnablefile/Card.cpp winnablefile/Card.h winnablefile/Moves.cpp winnablefile/Moves.h winnablefile/Move.cpp winnablefile/Move.h)
add_dependencies(winnable check advance)