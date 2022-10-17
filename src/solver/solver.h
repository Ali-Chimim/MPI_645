#ifndef SOLVER_H
#define SOLVER_H

void solveFirst(int cols, struct timespec ts_sleep,int rank, int k, int ** matrix);
int ** solveSecond(int rows, int cols, int iterations,int rank, struct timespec ts_sleep, int ** matrix, int ** rcvMatrix);

#endif
