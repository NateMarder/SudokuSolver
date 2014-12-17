/***********************************************************************
************************************************************************
**   
**	 Author: Nathan Marder
**	 Program Description: This program solves sudoku puzzles through
**		using recursive backtracking -  such as is used within the
**		classic programming '8 queens' assignment. Solution prints
**		to terminal and to output file, with time stamp of when solution
**		was generated.
** 	    	-needed input file is called: "input.txt"
**			  -needed output file is called: "solved.txt"
** 
**    NOTE:
**      There are five files associated with this program (input,output,
**      main.cc, sudoku.cc, and sudoku.h). The .cc and .h files are
*       all listed below... 
**
************************************************************************
************************************************************************/



/*******************************************************************
 ** Header File...
 *****************************************************************/
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

/*******************************************************************
 ** Sudoku.cc File...
 *****************************************************************/
#include "Sudoku.h"

void printBoard(const std::string& filename, int** sudo_array) throw()
{
    //for timestamping
  	time_t rawtime;
  	struct tm* timeinfo;
  	time (&rawtime);
  	timeinfo = localtime (&rawtime);
  	std::string timestamp = asctime(timeinfo);
	  std::ofstream out(OUTPUT_FILE);
    out << "The Board: " << timestamp << std::endl;
    std::cout << "\nThe Board: " << timestamp << std::endl;

    //print board to file and to terminal
  	for(int row=0; row<9; ++row) {
  		  std::cout << " ";
  		  out<<" ";
  		  for(int col=0; col<9; ++col) {
  			   if (col==2 || col==5){
  			    out << sudo_array[row][col] << " | ";
  				  std::cout << sudo_array[row][col] << " | ";}
  			   else{
  				  out << sudo_array[row][col] << " ";
  				  std::cout << sudo_array[row][col] << " ";}
  		  }
  		if (row==2 || row==5){
  			out <<"\n ---------------------" <<std::endl; 
  			std::cout <<"\n ---------------------" <<std::endl; }
  		else{
  			out << std::endl; 
  			std::cout << std::endl; }
	 }
	   //make it pretty
	   std::cout <<"\n"<<std::endl;
	   //close file
	   out.close();
}

void printBoard(int** sudo_array) throw()
{
	//for time stamp on output file
  	time_t rawtime;
  	struct tm* timeinfo;
  	time (&rawtime);
  	timeinfo = localtime (&rawtime);
  	std::string timestamp = asctime(timeinfo);
    std::cout << "\nThe Board: " << timestamp << std::endl;

    //print board to terminal
	for(int row=0; row<9; ++row) {
		std::cout << " ";
		for(int col=0; col<9; ++col) {
			if (col==2 || col==5){ std::cout << sudo_array[row][col] << " | "; }
			else{ std::cout << sudo_array[row][col] << " "; }

		}
			if (row==2 || row==5){ std::cout <<"\n ---------------------" <<std::endl; } //to terminal for convenience
			else{ std::cout << std::endl; }
	}
}

bool testMove(int** sudo_array, int& row, int& col, int& move) throw()
{
     //row test  
     for (int c = 0; c < 9; c++) {//test each item within row
         if (sudo_array[row][c] == move && c != col) {
             return false;
         }
     }

     //col test
     for (int r = 0; r < 9; r++) {//test each item within col
         if (sudo_array[r][col] == move && r != col) {
             return false;
         }
     }
     
     //testing small grids (row-row%3 == the beginning of small test row)
     for (int r = (row - row % 3); r < (row - row % 3) + 3; r++) {
         for (int c = (col - col % 3); c < (col - col % 3) + 3; c++) {
             if (sudo_array[r][c] == move && ((r != row) && (c != col))) {
                 return false;
             }
         }
     }

     // if nothing failed its a good move so return true
     return true;
}

void populate(const std::string& filename, int** sudo_array) throw()
{
	std::ifstream in(INPUT_FILE);
	for(int row=0; row<9; ++row) {
		for(int col=0; col<9; ++col) {
			if(in.good()) {
				in >> sudo_array[row][col];
			}
		}
	}
	in.close();
}

void findSolution(int** sudo_array, int row, int col) throw()
{
    //base case 
    if(row == 9){ 
      printBoard(OUTPUT_FILE,sudo_array);
      delete [] *sudo_array;
      delete [] sudo_array;
      sudo_array = NULL;
      exit (0); //stop everything, we just need one solution
      }

    //recursive case: not empty need to go to next
    if(sudo_array[row][col] != 0){
          if (col < 8) { findSolution(sudo_array, row, col + 1);}
          else { findSolution(sudo_array, row + 1, 0);}
    }
    
    //recursive case: empty spot, need solution
    else{
      for(int i = 1; i < 10; i++){
          if(testMove(sudo_array,row,col,i)){
             sudo_array[row][col] = i ; //assign value & move on
             if (col < 8) { findSolution(sudo_array, row, col+1);} 
             else {findSolution(sudo_array, row+1, 0);}
          }
      }
      //need to backtrack -->set recursive branch to zero
      sudo_array[row][col] = 0 ;

      }//ends non-zero nothing gets below this...
}





/*******************************************************************
 ** main.cc File...
 *****************************************************************/
#include "Sudoku.h"

int main(int argc, char** argv){

	//2d array allocated here is destroyed within 'findSolution' method
	int** sudo_array = new int*[9]; 		
	*sudo_array = new int[81]; 			
	for(int j=1; j<9; ++j) {				
		sudo_array[j] = sudo_array[j-1] + 9;
	}

	//grab integers from input file for sudokuboard
	populate(INPUT_FILE,sudo_array);

	//print the unsolved version to the terminal
	printBoard(sudo_array);

	//recursive backtracking method
	findSolution(sudo_array,0,0);

	return 0;
}//ends main class
