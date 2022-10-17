#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "solver.h"

void solveFirst( int cols, struct timespec ts_sleep,int rank, int numberIterations, int ** matrix) {
   int indexStart= rank *4;
   int y= indexStart/8;
    for(int k =1; k<=numberIterations; k++){
        for( int j =0; j<cols; j++){
         int x = j+indexStart%8;
         usleep(1000);
         matrix[0][j]=matrix[0][j] + ((y)+(x)) * k ;
        }
    }

}

int ** solveSecond(int rows, int cols, int iterations,int rank, struct timespec ts_sleep, int ** matrix, int ** rcvMatrix) {
   int indexStart= rank*4;
   int y= indexStart/8;
   for(int k =1; k<=iterations;k++){
      matrix[0][0]=matrix[0][0]+y*k;
      for(int j=1; j<cols;j++ ){
         if(rank%2==0){
         matrix[0][j]=matrix[0][j] + matrix[0][j-1] *k;
         }else {
            //travaille avec les meme affaires
            //    matrix[0][j]=matrix[0][j] + rcvMatrix[0][j-1] *k;
            // //  printf("%d",rcvMatrix[0][0]);
         }
      }
   }
   return matrix;
   
}
