/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#1
* ListTest.c 
* Test client for List ADT 
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"List.h"


int main(int argc, char* argv[]){

    List A = newList();
    List B = newList();
    List C = NULL;
    int i;

    for(i=1; i<6; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A); //1 2 3 4 5 
   printf("\n");
   printf("The front of List A: %d\n", front(A)); // 1
   printList(stdout,B); // 5 4 3 2 1
   printf("\n");
   printf("The back of List B: %d\n", back(B)); // 1


   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
    }
    printf("\n");// 1 2 3 4 5
    for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
    }
    printf("\n"); // 1 2 3 4 5

    C = copyList(A);
    printf("%s\n", equals(C,A)?"true":"false");//true
    printf("%s\n", equals(B,C)?"true":"false");//false
    printf("The length of List C: %d\n", length(C));//5
    clear(C);
    printf("After calling clear(C), the length of List C: %d\n", length(C));//0
    moveFront(A);
    set(A, 2);//at index 0, 1 was set to 0
    insertAfter(A, 0);// 0 was inserted after index 0
    moveBack(A);
    insertBefore(A, 10);// 10 was inserted befor index 5
    printList(stdout, A); // 2 0 2 3 4 10 5
    printf("\n");
    
    deleteFront(A);
    deleteBack(A);
    printList(stdout, A);
    printf("\n"); // 0 2 3 4 10
    
    moveBack(A);
    for (i = 0; i < 2; i++){
        movePrev(A);
    }
    delete(A); // cursor pointed at 3, 3 was delete
    printList(stdout, A); // 0 2 4 10
    printf("\n");

    freeList(&A);
    freeList(&B);
    freeList(&C);

    return(0);
}


/*
Output of this program:
1 2 3 4 5 
The front of List A: 1
5 4 3 2 1 
The back of List B: 1
1 2 3 4 5 
1 2 3 4 5 
true
false
The length of List C: 5
After calling clear(C), the length of List C: 0
2 0 2 3 4 10 5 
0 2 3 4 10 
0 2 4 10 
*/
