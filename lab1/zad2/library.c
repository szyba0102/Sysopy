#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ***table = NULL;
int table_size = 0;
char *temp_file = NULL;
int num_of_rows = 0;
int *tab_of_sizes;


int create_table(int size)
{
    table = (char ***) calloc(size,sizeof(char *));
    table_size = size;
    tab_of_sizes = calloc(size,sizeof(int));
    temp_file = "temp.txt";
    return 0;
}

int wc_files(int tab_files_size, char **tab_files){
    num_of_rows = tab_files_size;
    int char_size = 1;
    for(int i=0; i<tab_files_size; i++){
        char_size += sizeof(tab_files[i]) + 1;
    }
    char_size += 13;
    char con_names[char_size];
    strcpy(con_names, "wc ");

    for(int i=0; i<tab_files_size; i++){
        strcat(con_names,tab_files[i]);
        strcat(con_names," ");
    }
    strcat(con_names,">>temp.txt");
    system(con_names);
    return 0;
}

int rewrite(){
    int inx = 0;
    while(table[inx] != NULL){
        inx += 1;
    }

    FILE *f;
    f = fopen(temp_file,"r");
    if (f == NULL){
       printf("Error while opening saved file");
       return -1;
   }
    char *buffer;
    size_t bufsize = 100;
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        printf("Unable to allocate buffer");
        return -1;
    }

    if(num_of_rows == 1){
        char *buffer;
        size_t bufsize = 100;
        buffer = (char *) calloc(bufsize,sizeof(char));
        getline(&buffer,&bufsize,f);
        char **new_block = (char**) calloc(1,sizeof(char*));
        new_block[0] = buffer;
        table[inx] = new_block;
        tab_of_sizes[inx] = 1;
    }

    else if(num_of_rows>1){
        char **new_block = (char**) calloc(num_of_rows+1,sizeof(char*));
        for(int i=0; i<num_of_rows+1; i++){
            char *buffer;
            size_t bufsize = 100;
            buffer = (char *) calloc(bufsize,sizeof(char));
            getline(&buffer,&bufsize,f);
            new_block[i] = buffer;
        }
        table[inx] = new_block;
        tab_of_sizes[inx] = num_of_rows+1;
    }

    else{
        printf("ERROR");
        return -1;}

    int check = remove(temp_file);
    if(check != 0){
        printf("no file was removed");
        return -1;
    }
    return inx;
}

int remove_block(int inx){
    if(table[inx] == NULL){
        printf("no pointer");
        return -1;
    }
    for(int i=0; i<tab_of_sizes[inx]; i++){
        free(table[inx][i]);
    }
    free(table[inx]);
    table[inx] = NULL;
    tab_of_sizes[inx] = 0;
    return 0;
}

