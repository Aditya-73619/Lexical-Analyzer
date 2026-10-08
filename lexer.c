#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    if(get_next_character(lexinfo) == e_failure)
        return e_failure;

    while(lexinfo->ch != EOF){
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
    /* Preprocessor directive */
    if(lexinfo->ch == '#')
    {
        if(identify_preprocessor_directive(lexinfo) == e_failure){
            printf("Error : Invalid Preprocessor Directive\n");
            return e_failure;
        }
    }

    /* Keyword / Identifier*/
    else if((isalpha(lexinfo->ch)) || (lexinfo->ch == '_'))
    {
        if(identify_keyword_or_identifer(lexinfo) == e_failure){
            printf("Error : Invalid Keyword or Identifier\n");
            return e_failure;
        }
    }

    /* int / float / char / string Literals */
    else if(isdigit(lexinfo->ch) ||
            (lexinfo->ch == '.') || (lexinfo->ch == '\'') ||
            (lexinfo->ch == '"'))
    {
        if(identify_literals(lexinfo) == e_failure){
            printf("Error : Invalid Literal\n");
            return e_failure;
        }
    }

    /* Operators + brackets + ; */
    else if(lexinfo->ch != ' ' && lexinfo->ch != '\n' && lexinfo->ch != '\t' && lexinfo->ch != '#')
    {
        if(identify_operators(lexinfo) == e_failure){
            printf("Error : Invalid Operator\n");
            return e_failure;
        }
    }

    else
        get_next_character(lexinfo);

    return e_success;
}

Status identify_preprocessor_directive(LexInfo *lexinfo)
{
    int i = 0;

    lexinfo->token[i++] = lexinfo->ch;      // Storing #

    if(get_next_character(lexinfo) == e_failure)     // Getting next character
        return e_failure;
    
    /* storing #include */
    while(lexinfo->ch != ' ')
    {
        
        lexinfo->token[i++] = lexinfo->ch;      // Storing characters

        if(get_next_character(lexinfo) == e_failure)     // Getting next character
        return e_failure;
    }

    /* Get '<' */
    if(get_next_character(lexinfo) == e_failure)     // Getting next character
        return e_failure;

    /* Storing <stdio.h> */
    while(lexinfo->ch != '>')
    {
        lexinfo->token[i++] = lexinfo->ch;      // Storing characters

        if(get_next_character(lexinfo) == e_failure)     // Getting next character
        return e_failure;
        
    }

    /* Storing '>' */
    lexinfo->token[i++] = lexinfo->ch;

    lexinfo->token[i] = '\0';

    printf("Preprocessor Directive\t:\t%s\n",lexinfo->token);

    if(get_next_character(lexinfo) == e_failure)     // Getting next character
        return e_failure;
    
    return e_success;
}

Status identify_keyword_or_identifer(LexInfo *lexinfo)
{
    int i = 0;

    /* Getting and storing all characters in token */
    while((isalpha(lexinfo->ch)) || (isdigit(lexinfo->ch)) || (lexinfo->ch == '_'))
    {
        lexinfo->token[i++] = lexinfo->ch;  //Storing character in token
        
        if(get_next_character(lexinfo) == e_failure)     // Getting next character
            return e_failure;
    }

    lexinfo->token[i] = '\0';

    /* Check whether token is keyword */
    if(check_keyword(lexinfo) == e_success)
        printf("Keyword\t\t\t:\t%s\n",lexinfo->token);
    else
        printf("Identifier\t\t:\t%s\n",lexinfo->token);


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
    int dec_count = 0;
    /* int / float literal */
    if(isdigit(lexinfo->ch)){
        while(isdigit(lexinfo->ch) || (lexinfo->ch == '.'))
        {
            if(lexinfo->ch == '.')
                dec_count++;

            lexinfo->token[i++] = lexinfo->ch;

            if(get_next_character(lexinfo) == e_failure){
                printf("Error : Invalid int/float literal\n");
                return e_failure;
            }
        }

        lexinfo->token[i] = '\0';

        if(dec_count > 0)
            printf("Float Literal\t\t:\t%s\n",lexinfo->token);
        else
            printf("Integer Literal\t\t:\t%s\n",lexinfo->token);

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
        
        if(get_next_character(lexinfo) == e_failure)    // getting next character
                return e_failure;

        lexinfo->token[i] = '\0';

        printf("String Literal\t\t:\t%s\n",lexinfo->token);
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

        if(get_next_character(lexinfo) == e_failure)    // getting next character
                return e_failure;

        lexinfo->token[i] = '\0';

        printf("Character Literal\t:\t%s\n",lexinfo->token);
    }

    else{
        printf("Error : Invalid literal\n");
        return e_failure;
    }
    

    return e_success;
}

Status identify_operators(LexInfo *lexinfo)
{
    char op_buffer[4] = {'\0'};          // buffer string with all 4 character as NULL
    char operator[] = "+-*/%=<>!&|^~?:(){}[];,.";       // string of operators

    op_buffer[0] = lexinfo->ch;         // storing first character in buffer string

    get_next_character(lexinfo);

    if((lexinfo->ch == '=') || (lexinfo->ch == op_buffer[0]) || 
       (op_buffer[0] == '-' && lexinfo->ch == '>'))
    {
        op_buffer[1] = lexinfo->ch;         // storing second character in buffer string
        
        get_next_character(lexinfo);

        if((op_buffer[0] == '<' || op_buffer[0] == '>') &&
           (op_buffer[0] == op_buffer[1]))
        {
            get_next_character(lexinfo);

            if(lexinfo->ch == '='){
                op_buffer[2] = lexinfo->ch;         // storing 3rd character in buffer string
            }
        }   
    }

    if(strchr(operator,op_buffer[0])){
        printf("Operator\t\t:\t%s\n",op_buffer);
        return e_success;
    }

    printf("Error : Invalid operator\n");
    return e_failure;
}