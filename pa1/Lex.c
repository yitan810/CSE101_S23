/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#1 
* Lex.c 
* Main program for calling List.c functions
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include<string.h>
#include<stdbool.h>


int main(int argc, char* argv[]){

    FILE *fptr;
    char line[255];

    fptr = (fopen(argv[1], "r"));

    if (fptr == NULL){
        printf("Error: file is not existed\n");
        exit(1);
    };
    
    int i = 0;
    char **array = malloc(100 * sizeof(char *));


    while(fgets(line, 255, fptr)){
        int stringsize = strlen(line);
        array[i] = (char *)malloc(stringsize + 1);
        strcpy(array[i], line);
        i++;
    }

    int arraysize = i;
    List A = newList();
    
    append(A, 0);
    for(i = 1; i < arraysize; i++){
        if(strcmp(array[i], array[get(A)]) < 0){
            if(index(A) == 0){
                prepend(A, i);
            }else{
                while(strcmp(array[i], array[get(A)]) < 0 && index(A) != 0){
                    movePrev(A);
                }
                if(index(A) == 0){
                    if(strcmp(array[i], array[get(A)]) < 0){
                        prepend(A, i);
                    }else{
                        insertAfter(A, i);
                    }
                }else{
                    insertAfter(A, i);
                }
            }        
        
            
        }else{
            if(index(A) == length(A)-1){
                append(A, i);
            }else{
                while(strcmp(array[i], array[get(A)]) > 0 && index(A) != length(A)-1){
                    moveNext(A);
                }
                if(index(A) == length(A)-1){
                    if(strcmp(array[i], array[get(A)]) > 0){
                        append(A, i);
                    }else{
                        insertBefore(A, i);
                    }

                }else{
                    insertBefore(A, i);
                }

            }
        }
    }

    fclose(fptr);

    fptr = (fopen(argv[2], "w"));
    if (fptr == NULL){
        printf("Output file Error\n");
        exit(1);
    };

    for(moveFront(A); index(A)>=0; moveNext(A)){
        fprintf(fptr,"%s",array[get(A)]);
    }

    fclose(fptr);
    freeList(&A);

    for(i = 0; i < arraysize; i ++){
        if(array[i] != NULL){
            free(array[i]);
            array[i] = NULL;
        }
    }
    free(array);
    array = NULL;

    return 0;
}
