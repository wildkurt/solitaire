cmake_minimum_required(VERSION 3.21)
project(Solitaire)

set(CMAKE_C_STANDARD 99)

add_executable(check checkfile/check.c checkfile/card.c checkfile/foundation.c checkfile/tableau.c checkfile/stockWaste.c checkfile/checkf.c)
add_executable(advance checkfile/card.c checkfile/foundation.c checkfile/tableau.c checkfile/stockWaste.c checkfile/checkf.c advancefile/advance.c advancefile/advance.h advancefile/moves.c advancefile/moves.h advancefile/printGame.c advancefile/printGame.h advancefile/printGameToFile.c advancefile/printGameToFile.h)

set(CMAKE_CXX_STANDARD 14)
add_executable(winnable winnablefile/winnable.cpp winnablefile/winnable.h winnablefile/gameBoard.cpp winnablefile/gameBoard.h winnablefile/gameRules.cpp winnablefile/gameRules.h winnablefile/gameFoundations.cpp winnablefile/gameFoundations.h winnablefile/gameTableau.cpp winnablefile/gameTableau.h winnablefile/gameStock.cpp winnablefile/gameStock.h winnablefile/card.cpp winnablefile/card.h winnablefile/searchParameters.cpp winnablefile/searchParameters.h)
add_dependencies(winnable check advance)