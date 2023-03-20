cmake_minimum_required(VERSION 3.21)
project(Solitaire)

set(CMAKE_C_STANDARD 99)

add_executable(check checkfile/check.c checkfile/card.c checkfile/foundation.c checkfile/tableau.c checkfile/stockWaste.c checkfile/checkf.c)
add_executable(advance checkfile/card.c checkfile/foundation.c checkfile/tableau.c checkfile/stockWaste.c checkfile/checkf.c advancefile/advance.c advancefile/advance.h advancefile/moves.c advancefile/moves.h advancefile/printGame.c advancefile/printGame.h advancefile/printGameToFile.c advancefile/printGameToFile.h)

set(CMAKE_CXX_STANDARD 20)
add_executable(winnable winnablefile/winnable.cpp winnablefile/winnable.h winnablefile/parseFile.cpp winnablefile/parseFile.h winnablefile/SearchSettings.cpp winnablefile/SearchSettings.h winnablefile/gameConfiguration.cpp winnablefile/gameConfiguration.h winnablefile/rules.cpp winnablefile/rules.h winnablefile/card.cpp winnablefile/card.h winnablefile/foundations.cpp winnablefile/foundations.h winnablefile/tableau.cpp winnablefile/tableau.h winnablefile/stockWaste.cpp winnablefile/stockWaste.h winnablefile/moves.cpp winnablefile/moves.h winnablefile/Move.cpp winnablefile/Move.h)
add_dependencies(check advance)