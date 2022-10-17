#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "matrix/matrix.h"
#include "output/output.h"
#include "solver/solver.h"
#include "mpi.h"
#include <mpi.h>

#define ROWS 8
#define COLS 8

int main(int argc, char* argv[]) {
    if(4 != argc) {
        return EXIT_FAILURE;
    }

    int num_procs;
    int rank;
    int problemChoice;
    int initialValue;
    int numberIterations;
    initialValue=atoi(argv[2]);
    numberIterations=atoi(argv[3]);

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    struct timeval timestamp_s;
    struct timeval timestamp_e;
    struct timespec ts_sleep;
    ts_sleep.tv_sec=0;
    ts_sleep.tv_nsec=1000000L;

    int **matrix = allocateMatrix(1,4);
    int **rcvMatrix=allocateMatrix(1,4);
    fillMatrix(1,4,initialValue,matrix);
    int * finalMatrix = NULL; 

    gettimeofday(&timestamp_s, NULL);

    //solveFirst(4,ts_sleep,rank,numberIterations,matrix);
    matrix = solveSecond(1,4,numberIterations,rank,ts_sleep,matrix,NULL);
   
    if(rank == 0){
        finalMatrix = (int *) malloc((ROWS*COLS) * sizeof(int));
    }
    if(rank%2==0){
        printMatrix(1,4,*matrix);
        MPI_Send((*matrix),4,MPI_INT,rank+1,1,MPI_COMM_WORLD);
    }else {
        MPI_Recv((*rcvMatrix),4,MPI_INT,rank-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        solveSecond(1,4,numberIterations,rank,ts_sleep,matrix,rcvMatrix);
    }

    MPI_Gather((*matrix), 4, MPI_INT, finalMatrix, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        gettimeofday(&timestamp_e, NULL);
        printMatrix(8,8,finalMatrix);
        printRuntime(timestamp_s, timestamp_e);
    }
   
    
    

    MPI_Finalize();


   
    return EXIT_SUCCESS;
}
