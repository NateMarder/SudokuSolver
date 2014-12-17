#ifndef SUDOKU
#define SUDOKU
#define OUTPUT_FILE "solved.txt"
#define INPUT_FILE "input.txt"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

void printBoard(const std::string& filename, int** array) throw(); 
void printBoard(int** array) throw(); 
bool testMove(int** sudo_array, int& row, int& col, int& move) throw();
void populate(const std::string& filename, int** array) throw();
void findSolution(int** sudo_array, int row, int col) throw();
#endif
