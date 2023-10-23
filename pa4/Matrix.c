/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#4
* Matrix.c
* C source code for Matrix ADT program
*********************************************************************************/ 
#include<stdlib.h>
#include<stdio.h>
#include"Matrix.h"

typedef struct EntryObj{
    int column;
    double value;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj{
    List row[200000];
    int size;
    int nnz;
} MatrixObj;

typedef MatrixObj* Matrix;

Entry newEntry(void){
    Entry E = malloc(sizeof(EntryObj));
    E->column = 0;
    E->value = 0;
    return E;
}

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    for(int i=1; i<=n; i++){
        M->row[i] = newList();
    }
    M->nnz = 0;
    M->size = n;
    return M;
}

void freeEntry(Entry* pE){
    (*pE)->column = 0;
    (*pE)->value = 0;
    (*pE) = NULL;
    free(*pE);
}

void freeMatrix(Matrix* pM){
    int n = (*pM)->size;
    for(int i=1; i<=n; i++){
        if(length((*pM)->row[i])!=0){
            for(moveFront((*pM)->row[i]);index((*pM)->row[i])>=0; moveNext((*pM)->row[i])){
                Entry E = (Entry)get((*pM)->row[i]);
                freeEntry(&E);
            }
        }
        List L = (*pM)->row[i];
        freeList(&L);
    }
    (*pM)->size = 0;
    (*pM)->nnz = 0;
    (*pM) = NULL;
    free(*pM);
}

int size(Matrix M){
    if(M == NULL){
        printf("Error: calling size() in a NULL Matrix\n");
        exit(1);
    }
    return M->size;
}

int NNZ(Matrix M){
    if(M == NULL){
        printf("Error: calling NNZ() in a NULL Matrix\n");
        exit(1);
    }
    return M->nnz;
}

int equals(Matrix A, Matrix B){
    if(A == NULL){
        printf("Error: calling euqal() with a NULL Matrix A\n");
        exit(1);
    }
    else if(B == NULL){
        printf("Error: calling equal() with a NULL Matrix B\n");
        exit(1);
    }
    if(size(A) != size(B) || NNZ(A) != NNZ(B)){
        return false;
    }
    int eq = true;
    for(int i=1; i<=size(A); i++){
        eq = (length(A->row[i]) == length(B->row[i]));
        moveFront(A->row[i]);
        moveFront(B->row[i]);
        while(eq && index(A->row[i])!=-1){
            Entry a = (Entry)get(A->row[i]);
            Entry b = (Entry)get(B->row[i]);
            eq = (a->column == b->column);
            eq = (a->value == b->value);
            moveNext(A->row[i]);
            moveNext(B->row[i]);
	    }
        if(eq == false){
            return eq;
        }
    }
    return eq; 
}

void makeZero(Matrix M){
    if(M == NULL){
        printf("Error: calling makeZero() with a NULL Matrix\n");
        exit(1);
    }
    for(int i=1; i<=size(M); i++){
        clear(M->row[i]);
    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        printf("Error: calling changeEntery() with a NULL Matrix\n");
        exit(1);
    }
    else if(i<1 || i>size(M)){
        printf("Error: calling changeEntery() with index i is out of range\n");
        exit(1);
    }
    else if(j<1 || j>size(M)){
        printf("Error: calling changeEntery() with index j is out of range\n");
        exit(1);
    }
    if(x == 0){
        for(moveFront(M->row[i]); index(M->row[i])>=0; moveNext(M->row[i])){
            Entry E = (Entry)get(M->row[i]);
            if(E->column == j){
                delete(M->row[i]);
                M->nnz--;
            }
        }
    }
    else{
        if(length(M->row[i])==0){
            Entry E = newEntry();
            E->column = j;
            E->value = x;
            append(M->row[i], E);
            M->nnz++;
        }
        else{
            for(moveFront(M->row[i]); index(M->row[i])>=0; moveNext(M->row[i])){
                Entry E = (Entry)get(M->row[i]);
                if(E->column == j){
                    E->value = x;
                    break;
                }
                if(E->column > j){
                    Entry F = newEntry();
                    F->column = j;
                    F->value = x;
                    insertBefore(M->row[i], F);
                    M->nnz++;
                    break;
                }
                if(index(M->row[i]) == length(M->row[i])-1 && E->column < j){
                    Entry F = newEntry();
                    F->column = j;
                    F->value = x;
                    append(M->row[i], F);
                    M->nnz++;
                    break;
                }
            }
        }
    }
}

Matrix copy(Matrix A){
    if(A == NULL){
        printf("Error: calling copy() with a NULL Matrix\n");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for(int i=1; i<=size(A); i++){
        B->row[i] = A->row[i];
    }
    B->size = A->size;
    B->nnz = A->nnz;
    return B;
}

Matrix transpose(Matrix A){
    if(A == NULL){
        printf("Error: calling transpose() with a NULL Matrix\n");
        exit(1);
    }
    Matrix B = newMatrix(size(A));
    for(int i=1;i<=size(A);i++){
		for(moveFront(A->row[i]); index(A->row[i])>=0; moveNext(A->row[i])){
            Entry E = (Entry)get(A->row[i]);
            double val = E->value;
            Entry F = newEntry();
            F->column = i;
            F->value = val;
            append(B->row[E->column], F);
        }
	}
    B->nnz = A->nnz;
	return B;
}

Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        printf("Error: calling scalarMult() with a NULL Matrix\n");
        exit(1);
    }
    Matrix B = newMatrix(size(A));

    for(int i=1;i<=size(A);i++){
		for(moveFront(A->row[i]); index(A->row[i])>=0; moveNext(A->row[i])){
            Entry E = (Entry)get(A->row[i]);
            double val = E->value;
            Entry F = newEntry();
            F->column = E->column;
            F->value = x * val;
            append(B->row[i], F);
        }
	}
    B->nnz = A->nnz;
    return B;
}

int ListAdd(List L, List P, List S, int eq){
    moveFront(L);
    moveFront(P);
    int count = 0;
    while(index(L)>=0 && index(P)>=0){
        Entry l = (Entry)get(L);
        Entry p = (Entry)get(P);
        if(l->column < p->column){
            Entry E = newEntry();
            E->column = l->column;
            E->value = l->value;
            append(S, E);
            count++;
            moveNext(L);
        }
        else if(p->column < l->column){
            Entry E = newEntry();
            E->column = p->column;
            E->value = p->value;
            append(S, E);
            count++;
            moveNext(P);
        }
        else if(l->column == p->column){
            Entry E = newEntry();
            E->column = l->column;
            E->value = l->value + p->value;
            if(E->value != 0){
                append(S, E);
                count++;
            }
            else{
                freeEntry(&E);
            }
            if(eq == 1){
                moveNext(L);
            }
            else{
                moveNext(L);
                moveNext(P); 
            }
        }
    }
    while(index(L)>=0){
        Entry l = (Entry)get(L);
        Entry E = newEntry();
        E->column = l->column;
        E->value = l->value;
        append(S, E);
        count++;
        moveNext(L);
    }
    while(index(P)>=0){
        Entry p = (Entry)get(P);
        Entry E = newEntry();
        E->column = p->column;
        E->value = p->value;
        append(S, E);
        count++;
        moveNext(P);
    }
    return count;
}

Matrix sum(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Error: calling sum() with a NULL Matrix\n");
        exit(1);
    }
    else if(size(A) != size(B)){
        printf("Error: calling sum() with two matrixs that don't have equal size\n");
    }

    Matrix C = newMatrix(size(A));
    int count = 0;
    int eq = equals(A, B);

    for(int i=1;i<=size(A);i++){
        int num = ListAdd(A->row[i], B->row[i], C->row[i], eq);
        count = count + num;
    }
    C->nnz = count;
    return C;
}

int ListDiff(List L, List P, List S){
    moveFront(L);
    moveFront(P);
    int count = 0;
    while(index(L)>=0 && index(P)>=0){
        Entry l = (Entry)get(L);
        Entry p = (Entry)get(P);
        if(l->column < p->column){
            Entry E = newEntry();
            E->column = l->column;
            E->value = l->value;
            append(S, E);
            count++;
            moveNext(L);
        }
        else if(p->column < l->column){
            Entry E = newEntry();
            E->column = p->column;
            E->value = -1 * p->value;
            append(S, E);
            count++;
            moveNext(P);
        }
        else if (l->column == p->column){
            Entry E = newEntry();
            E->column = l->column;
            E->value = l->value - p->value;
            if(E->value != 0){
                append(S, E);
                count++;
            }
            else{
                freeEntry(&E);
            }
            moveNext(L);
            moveNext(P);
        }
    }
    while(index(L)>=0){
        Entry l = (Entry)get(L);
        Entry E = newEntry();
        E->column = l->column;
        E->value = l->value;
        append(S, E);
        count++;
        moveNext(L);
    }
    while(index(P)>=0){
        Entry p = (Entry)get(P);
        Entry E = newEntry();
        E->column = p->column;
        E->value = -1 * p->value;
        append(S, E);
        count++;
        moveNext(P);
    }
    return count;
}

Matrix diff(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Error: calling diff() with a NULL Matrix\n");
        exit(1);
    }
    else if(size(A) != size(B)){
        printf("Error: calling diff() with two matrixs that don't have equal size\n");
    }
    Matrix C = newMatrix(size(A));
    int count = 0;
    for(int i=1;i<=size(A);i++){
        int num = ListDiff(A->row[i], B->row[i], C->row[i]);
        count = count + num;
    }
    C->nnz = count;
    return C;
}

double vectorDot(List P, List Q){
    moveFront(P);
    moveFront(Q);
    double sum = 0;
    while(index(P)>=0 && index(Q)>=0){
        Entry p = (Entry)get(P);
        Entry q =(Entry)get(Q);
        if(p->column < q->column){
            moveNext(P);
        }
        else if(p->column > q->column){
            moveNext(Q);
        }
        else if (p->column == q->column){
            sum = sum + (p->value * q->value);
            moveNext(P);
            moveNext(Q);
        }
    }
    return sum;
}

Matrix product(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Error: calling product() with a NULL Matrix\n");
        exit(1);
    }
    else if(size(A) != size(B)){
        printf("Error: calling product() with two matrixs that don't have equal size\n");
    }

    Matrix C = transpose(B);
    
    Matrix D = newMatrix(size(A));

    for(int i=1; i<=size(A); i++){
        for(int j=1; j<=size(C); j++){
            if(length(A->row[i])!=0 && length(C->row[j])!=0){
                Entry E = newEntry();
                E->column = j;
                E->value = vectorDot(A->row[i], C->row[j]);
                if(E->value != 0){
                    append(D->row[i], E);
                    D->nnz++;
                }
                else{
                    freeEntry(&E);
                }
            }
        }
    }
    freeMatrix(&C);
    return D;
}


void printMatrix(FILE* out, Matrix M){
    for(int i=1; i<=size(M); i++){
        if(length(M->row[i])!=0){
            fprintf(out, "%d: ", i);
            for(moveFront(M->row[i]); index(M->row[i])>=0; moveNext(M->row[i])){
                Entry E = (Entry)get(M->row[i]);
                int col = E->column;
                double val = E->value;
                fprintf(out, " (%d, %0.1f)", col, val);
            }
            fprintf(out, "\n");
        }
    }
}