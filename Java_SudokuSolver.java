import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Java_SudokuSolver {

   private static int[][] theboard;
   private final static String FILENAME = "input.txt";

   public static void main(String[] args) {
        
    theboard = getBoard(FILENAME);//grab the board    
    System.out.print("\nInput:\n");
    print(theboard);
    
    //recursive method
    findSolution(0,0);
    
    }   

   private static void findSolution(int row, int col) {
      
    //base case 
    if(row == 9){ 
      System.out.print("Solved:");
      print(theboard);
      System.exit(0);//stop everything, we just need one solution
      }

    //recursive case: not empty need to go to next
    if(theboard[row][col] != 0){
          if (col < 8) { findSolution(row, col + 1);}
          else { findSolution(row + 1, 0);}
    }
    
    //recursive case: empty spot, need solution
    else{
      for(int i = 1; i < 10; i++){
          if(testMove(row,col,i)){
             theboard[row][col] = i ; //assign value & move on
             if (col < 8) { findSolution(row, col+1);} 
             else {findSolution(row+1, 0);}
          }
      }
      //need to backtrack -->set recursive branch to zero
      theboard[row][col] = 0 ;

    }//ends non-zero nothing gets below this...
   }
  
   private static boolean testMove(int row, int col, int move) {

     //row test  
     for (int c = 0; c < 9; c++) {//test each item within row
         if (theboard[row][c] == move && c != col) {
             return false;
         }
     }

     //col test
     for (int r = 0; r < 9; r++) {//test each item within col
         if (theboard[r][col] == move && r != col) {
             return false;
         }
     }
     
     //testing small grids (row-row%3 == the beginning of small test row)
     for (int r = (row - row % 3); r < (row - row % 3) + 3; r++) {
         for (int c = (col - col % 3); c < (col - col % 3) + 3; c++) {
             if (theboard[r][c] == move && ((r != row) && (c != col))) {
                 return false;
             }
         }
     }
     
     return true;
    }
   
   private static int[][] getBoard(String filename){
    int temp;
    int[][] board=new int[9][9];
    try (Scanner scanner = new Scanner(new BufferedReader
       (new FileReader(filename)))) {
        while (scanner.hasNextLine()) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    temp = scanner.nextInt();
                    board[i][j] = temp;
                }
            }
        }
        scanner.close();
    } catch (IOException e) {
        System.err.println(e.getMessage());
    }
    return board;
}
    
   private static void print(int [][] printme){
    System.out.print("\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            System.out.print(" "+printme[i][j]);
            if (j==2 || j==5){System.out.print(" |");}
        }
        System.out.print("\n");
        if (i==2 || i==5){System.out.print(" ---------------------\n");}
    }
    System.out.print("\n");
    }   
    
}//ends public class
