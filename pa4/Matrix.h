/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#4
* Matrix.h 
* Header file for Matrix ADT program
*********************************************************************************/ 
#include <stdlib.h>
#include"List.h"

typedef struct MatrixObj* Matrix;

Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);

//Access functions
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);

//Manipulation procedures
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

//Matrix Arithmetic operations
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
void printMatrix(FILE* out, Matrix M);