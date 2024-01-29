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
add_executable(check
        checkfile/main.c
        ${COMMON_FILES}
        checkfile/check.c
        checkfile/check.h
)
