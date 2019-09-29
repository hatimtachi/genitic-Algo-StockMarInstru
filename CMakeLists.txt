cmake_minimum_required(VERSION 3.12)
project(AlgoGene C)

set(CMAKE_C_STANDARD 11)

add_executable(AlgoGene main.c DataFunctions.c DataFunctions.h Structure.h GeneticFunctions.c GeneticFunctions.h)