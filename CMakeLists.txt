cmake_minimum_required(VERSION 3.12)
project(tetris)

set(CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SOURCES src/*.c)
add_executable(tetris ${SOURCES})

set(CMAKE_C_FLAGS
    "-fsanitize=address -fsanitize=undefined -fstack-protector-strong -Wno-unused-result -Wall -Wextra -Wconversion -Werror=uninitialized -Werror=vla -Werror=return-type -Wshadow -Wnull-dereference -Wformat -Wformat-security -Wstrict-overflow -Wstrict-prototypes -Wcast-align -Wredundant-decls -Wpedantic -Werror"
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_include_directories(tetris PRIVATE /opt/homebrew/include)
endif()

target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(tetris PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
