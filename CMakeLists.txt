cmake_minimum_required(VERSION 3.12)
project(tetris)

set(CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)

file(GLOB SOURCES src/*.c)
add_executable(tetris ${SOURCES})

set(CMAKE_C_FLAGS
    "-fsanitize=address -fsanitize=undefined -fstack-protector-strong -Wno-unused-result -Wall -Wextra -Wconversion -Werror=uninitialized -Werror=vla -Werror=return-type -Wshadow -Wnull-dereference -Wformat -Wformat-security -Wstrict-overflow -Wstrict-prototypes -Wcast-align -Wredundant-decls -Wpedantic -Werror"
)

target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(tetris ${SDL2_LIBRARIES})
