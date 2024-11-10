cmake_minimum_required(VERSION 3.12)
project(tetris)

set(CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)

file(GLOB SOURCES src/*.c)
add_executable(tetris ${SOURCES})

add_compile_options(tetris PRIVATE
    -fsanitize=address
    -fsanitize=undefined
    -fstack-protector-strong
    -D_FORTIFY_SOURCE=2
    -Wno-unused-result
    -Wall
    -Wextra
    -Wconversion
    -Werror=uninitialized
    -Werror=vla
    -Werror=return-type
    -Wshadow
    -Wnull-dereference
    -Wformat
    -Wformat-security
    -Wstrict-overflow
    -Wstrict-prototypes
    -Wcast-align
    -Wredundant-decls
    -Wpedantic
    -Werror
    -lm
)

target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(tetris ${SDL2_LIBRARIES})
