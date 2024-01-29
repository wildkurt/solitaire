cmake_minimum_required(VERSION 3.13)
project(Solitaire)
set(CMAKE_STANDARD 14)

set(COMMON_FILES

)
add_executable(check
        checkfile/main.c
        ${COMMON_FILES}
)
