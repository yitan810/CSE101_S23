/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#4
* Sparse.c 
* Main program for List ADT program
*********************************************************************************/ 
#include<stdio.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
    FILE *fptr;
    int size, n1, n2;

    fptr = fopen(argv[1],"r");
    fscanf(fptr, "%d %d %d", &size, &n1, &n2);

    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);

    for(int i=0; i<n1; i++){
        int row, col;
        double val;
        fscanf(fptr, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
    }

    for(int i=0; i<n2; i++){
        int row, col;
        double val;
        fscanf(fptr, "%d %d %lf", &row, &col, &val);
		changeEntry(B, row, col, val);
    }

    FILE* out;
    out = fopen(argv[2], "w");
    fprintf(out, "A has %d non-zero entries:\n", n1);
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", n2);
    printMatrix(out, B);
    fprintf(out, "\n");

    
    fprintf(out, "(1.5)*A =\n");
    Matrix C = scalarMult(1.5, A);
    printMatrix(out, C);
    fprintf(out, "\n");


    fprintf(out, "A+B =\n");
    Matrix D = sum(A, B);
    printMatrix(out, D);
    fprintf(out, "\n");


    fprintf(out, "A+A =\n");
    Matrix E = sum(A, A);
    printMatrix(out, E);
    fprintf(out, "\n");


    fprintf(out, "B-A =\n");
    Matrix F = diff(B, A);
    printMatrix(out, F);
    fprintf(out, "\n");


    fprintf(out, "A-A =\n");
    Matrix G = diff(A, A);
    printMatrix(out, G);
    fprintf(out, "\n");


    fprintf(out, "Transpose(A) =\n");
    Matrix H = transpose(A);
    printMatrix(out, H);
    fprintf(out, "\n");


    fprintf(out, "A*B =\n");
    Matrix I = product(A, B);
    printMatrix(out, I);
    fprintf(out, "\n");


    fprintf(out, "B*B =\n");
    Matrix J = product(B, B);
    printMatrix(out, J);


    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    fclose(fptr);
    fclose(out);
    return 0;
}