/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#5
* Shuffle.cpp 
* C++ source code file for List ADT program
*********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include"List.h"

using namespace std;

void shuffle(List& D){
    List L;
    int i;
    int n = D.length() / 2;
    
    D.moveFront();
    for(i=1; i<=n; i++){
        L.insertBefore(D.moveNext());
        D.eraseBefore();
    }

    L.moveFront();
    while(L.position() != L.length()){
    D.moveNext();
    D.insertBefore(L.moveNext());
    } 

}

int main(int argc, char** argv){
    int i, j, k, n = atoi(argv[1]);
    List L1, L2;

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    for(i=1; i<=n; i++){
        int len = 0;
        k = i;
        while(k){
            k /= 10;
            len++;
        }
        for(j=1; j<=i; j++){
            L1.insertBefore(j);
        }
        L2 = L1;
        bool eq = false;
        int count = 0;
        while(!eq){
            shuffle(L2);
            count++;
            eq = (L2 == L1);
        }
        cout << " " << i;
        len = 15 - len;
        for(k = 0; k < len; k++){
            cout << " ";
        }
        L1.clear();
        cout << count << endl;
    }

    return (EXIT_SUCCESS);
}