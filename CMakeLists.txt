cmake_minimum_required(VERSION 3.10)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Directory per gli header
include_directories(include)

# Lista dei file sorgente
file(GLOB SOURCES "src/*.c")

# Creazione dell'eseguibile
add_executable(sudoku ${SOURCES})
