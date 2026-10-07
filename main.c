#include<stdio.h>
#include "types.h"
#include "lexer.h"

int main(int argc,char *argv[]){

    LexInfo lexinfo;

    if(argc != 2){
        printf("Error : Invalid input\n");
        return e_failure;
    }

    if(read_and_validate_args(argv,&lexinfo) == e_failure){
        return e_failure;
    }
    else{
        if(do_lexical_analysis(&lexinfo) == e_success){
            printf("Analysis is Success\n");
        }
    }


    return 0;
}