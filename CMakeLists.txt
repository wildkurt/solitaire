cmake_minimum_required(VERSION 3.13)
project(Solitaire)
set(CMAKE_STANDARD 14)

set(COMMON_FILES
        commonfiles/gameconfiguration.c
        commonfiles/gameconfiguration.h
        commonfiles/rules.c
        commonfiles/rules.h
        commonfiles/foundations.c
        commonfiles/foundations.h
        commonfiles/Card.c
        commonfiles/Card.h
        commonfiles/tableau.c
        commonfiles/tableau.h
        commonfiles/stockwaste.c
        commonfiles/stockwaste.h
)
set(MOVE_FILES
        movefiles/moves.c
        movefiles/moves.h
)
add_executable(check
        checkfile/main.c
        checkfile/check.c
        checkfile/check.h
        ${COMMON_FILES}
)

add_executable(advance
        advancefiles/main.c
        advancefiles/advance.c
        advancefiles/advance.h
        ${COMMON_FILES}
        ${MOVE_FILES}
)
add_executable(winnable winnablefiles/main.cpp
        winnablefiles/winnable.cpp
        winnablefiles/winnable.h
        ${COMMON_FILES}
        )
