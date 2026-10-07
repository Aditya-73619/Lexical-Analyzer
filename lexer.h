#ifndef LEXER_H
#define LEXER_H

#include "types.h"


typedef struct{
    /* File info */
    char *file_name;
    FILE *fptr;

    /* Character & Token info */
    char ch;
    char token[100];

} LexInfo;


/* Validate arguments */
Status read_and_validate_args(char *argv[], LexInfo *lexinfo);

/* Perform the Lexical Analysis */
Status do_lexical_analysis(LexInfo *lexinfo);

/* Get next character from the file */
Status get_next_character(LexInfo *lexinfo);

/* Identify the token */
Status identify_token(LexInfo *lexinfo);

/* Check if token is keyword or identifier */
Status identify_keyword_or_identifer(LexInfo *lexinfo);

/* Check token is keyword or not */
Status check_keyword(LexInfo *lexinfo);

/* Checking the literals */
Status identify_literals(LexInfo *lexinfo);

/* Identifying the operators */
Status identify_operators(LexInfo *lexinfo);


#endif