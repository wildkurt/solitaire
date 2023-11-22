cmake_minimum_required(VERSION 3.13)
project(Solitaire)
set(CMAKE_STANDARD 14)

set(COMMON_FILES
        commonfiles/card.c
        commonfiles/card.h
        commonfiles/foundations.c
        commonfiles/foundations.h
        commonfiles/gameconfiguration.c
        commonfiles/gameconfiguration.h
        commonfiles/rules.c
        commonfiles/rules.h
        commonfiles/stockwaste.c
        commonfiles/stockwaste.h
        commonfiles/tableau.c
        commonfiles/tableau.h
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
)