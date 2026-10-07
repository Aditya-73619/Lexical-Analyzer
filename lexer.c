#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "types.h"

Status read_and_validate_args(char *argv[], LexInfo *lexinfo)
{
    /* Validating extension as .c */
    char *extn = strchr(argv[1],'.');

    if(extn == NULL || (strcmp(extn,".c") != 0)){
        printf("Error : File must be with .c extension\n");
        return e_failure;
    }

    lexinfo->file_name = argv[1];       // Storing file name in structure member

    /* Opening the file in read mode */
    lexinfo->fptr = fopen(lexinfo->file_name,"r");

    if(lexinfo->fptr == NULL){
        printf("Error : File not opened\n");
        return e_failure;
    }

    printf("Open\t: %s : Success\n",lexinfo->file_name);
    printf("Parsing\t: %s : Started\n\n",lexinfo->file_name);

    return e_success;
}

Status do_lexical_analysis(LexInfo *lexinfo)
{
    while(get_next_character(lexinfo) == e_success){
        if(identify_token(lexinfo) == e_failure){
            printf("Error : Invalid token\n");
            return e_failure;
        }
    }

    printf("\nParsing\t: %s : Done\n",lexinfo->file_name);
    return e_success;
}

Status get_next_character(LexInfo *lexinfo)
{
    /* Getting next character */
    lexinfo->ch = fgetc(lexinfo->fptr);

    if(lexinfo->ch == EOF)
        return e_failure;
    
    return e_success;
}

Status identify_token(LexInfo *lexinfo)
{
    /* Keyword / Identifier*/
    if((lexinfo->ch >= 'A' && lexinfo->ch <= 'Z') ||
       (lexinfo->ch >= 'a' && lexinfo->ch <= 'z') ||
       (lexinfo->ch == '_'))
    {
        if(identify_keyword_or_identifer(lexinfo) == e_failure)
            return e_failure;
    }

    /* int / float / char / string Literals */
    else if((lexinfo->ch >= '0' && lexinfo->ch <= '9') ||
            (lexinfo->ch == '.') || (lexinfo->ch == '\'') ||
            (lexinfo->ch == '"'))
    {
        if(identify_literals(lexinfo) == e_failure)
            return e_failure;
    }


    return e_success;
}

Status identify_keyword_or_identifer(LexInfo *lexinfo)
{
    int i = 0;

    /* Getting and storing all characters in token */
    while((lexinfo->ch >= 'A' && lexinfo->ch <= 'Z') ||
          (lexinfo->ch >= 'a' && lexinfo->ch <= 'z') ||
          (lexinfo->ch >= '0' && lexinfo->ch <= '9') || lexinfo->ch == '_')
    {
        lexinfo->token[i++] = lexinfo->ch;  //Storing character in token
        
        if(get_next_character(lexinfo) == e_failure)     // Getting next character
            break;
    }

    lexinfo->token[i] = '\0';

    /* Check whether token is keyword */
    if(check_keyword(lexinfo) == e_success)
        printf("Keyword\t\t: %s\n",lexinfo->token);
    else
        printf("Identifier\t: %s\n",lexinfo->token);


    return e_success;
}

Status check_keyword(LexInfo *lexinfo)
{
    /* Check wheather token is keyword or not */
    if ((strcmp(lexinfo->token,"char") == 0) ||
        (strcmp(lexinfo->token,"short") == 0) ||
        (strcmp(lexinfo->token,"int") == 0) ||
        (strcmp(lexinfo->token,"float") == 0) ||
        (strcmp(lexinfo->token,"double") == 0) ||
        (strcmp(lexinfo->token,"long") == 0) ||
        (strcmp(lexinfo->token,"void") == 0) ||
        (strcmp(lexinfo->token,"signed") == 0) ||
        (strcmp(lexinfo->token,"unsigned") == 0) ||
        (strcmp(lexinfo->token,"if") == 0) ||
        (strcmp(lexinfo->token,"else") == 0) ||
        (strcmp(lexinfo->token,"switch") == 0) ||
        (strcmp(lexinfo->token,"case") == 0) ||
        (strcmp(lexinfo->token,"default") == 0) ||
        (strcmp(lexinfo->token,"for") == 0) ||
        (strcmp(lexinfo->token,"while") == 0) ||
        (strcmp(lexinfo->token,"do") == 0) ||
        (strcmp(lexinfo->token,"break") == 0) ||
        (strcmp(lexinfo->token,"continue") == 0) ||
        (strcmp(lexinfo->token,"return") == 0) ||
        (strcmp(lexinfo->token,"auto") == 0) ||
        (strcmp(lexinfo->token,"register") == 0) ||
        (strcmp(lexinfo->token,"static") == 0) ||
        (strcmp(lexinfo->token,"extern") == 0) ||
        (strcmp(lexinfo->token,"struct") == 0) ||
        (strcmp(lexinfo->token,"union") == 0) ||
        (strcmp(lexinfo->token,"enum") == 0) ||
        (strcmp(lexinfo->token,"typedef") == 0) ||
        (strcmp(lexinfo->token,"const") == 0) ||
        (strcmp(lexinfo->token,"volatile") == 0) ||
        (strcmp(lexinfo->token,"goto") == 0) ||
        (strcmp(lexinfo->token,"sizeof") == 0))
    {
        return e_success;
    }

    return e_failure;
}

Status identify_literals(LexInfo *lexinfo)
{
    int i = 0;
    
    /* int / float literal */
    if(lexinfo->ch >= '0' && lexinfo->ch <= '9'){
        while((lexinfo->ch >= '0' && lexinfo->ch <= '9') || (lexinfo->ch == '.'))
        {
            lexinfo->token[i++] = lexinfo->ch;

            if(get_next_character(lexinfo) == e_failure){
                printf("Error : Invalid int/float literal\n");
                return e_failure;
            }
        }
    }
    
    /* String literal */
    else if(lexinfo->ch == '"')
    {
        lexinfo->token[i++] = lexinfo->ch;      // storing starting " (double quote)

        if(get_next_character(lexinfo) == e_failure)    // getting next character
                return e_failure;

        while(lexinfo->ch != '"')
        {
            lexinfo->token[i++] = lexinfo->ch;

            if(get_next_character(lexinfo) == e_failure)        // getting next character
            {
                printf("Error : Invalid string literal\n");
                return e_failure;
            }
        }

        lexinfo->token[i++] = lexinfo->ch;      // Storing ending " (double quote)
    }

    /* Character literal */
    else if(lexinfo->ch == '\'')
    {
        lexinfo->token[i++] = lexinfo->ch;        // storing starting ' (single quote)  

        if(get_next_character(lexinfo) == e_failure)    // getting next character
                return e_failure;

        while(lexinfo->ch != '\'')
        {
            lexinfo->token[i++] = lexinfo->ch;

            if(get_next_character(lexinfo) == e_failure)        // getting next character
            {
                printf("Error : Invalid character literal\n");
                return e_failure;
            }    
        }

        lexinfo->token[i++] = lexinfo->ch;      // Storing ending " (double quote)
    }

    else{
        printf("Error : Invalid literal\n");
        return e_failure;
    }
    

    lexinfo->token[i] = '\0';

    printf("Literal\t\t: %s\n",lexinfo->token);

    return e_success;
}
