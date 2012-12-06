%code requires{

#include "json_types.h"
#include "parse_helper.h"


}

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


#include "json.tab.h"
#include "parse.h"


extern FILE *yyin;

JSON yy_json_result=NULL;

JSON_llist start_llist(JSON j);
JSON_llist push_llist(JSON_llist, JSON j);

JSON_array llist2array(JSON_llist);

void yyerror(char const *s);


%}


%union {
    int iVal;
    bool bVal;
    char *sVal;
    double fVal;
    JSON_object oVal;
    JSON_array aVal;
    JSON jVal;
    JSON_llist llVal;
}

%error-verbose

%token <iVal> INT
%token <sVal> STRING
%token <fVal> FLOAT
%token <bVal> BOOL
%token LBRACKET RBRACKET LARRAY RARRAY COMMA COLON NULL_TOKEN

%type <jVal> expr 
%type <oVal> object pairs pair
%type <aVal> array
%type <llVal> expr_list

%%


top_expr:
        expr    { yy_json_result = $1; }
    ;

expr:
        object  { $$ = json_object($1); }
    |   array   { $$ = json_array($1); }
    |   BOOL    { $$ = json_bool($1); }
    |   FLOAT   { $$ = json_float($1); }
    |   INT     { $$ = json_int($1); }
    |   STRING  { $$ = json_string($1); }
    |   NULL_TOKEN  { $$ = json_null(); }
    ;

object:
        LBRACKET pairs RBRACKET {$$ = $2; }
    ;

pairs:
        pair                { $$ = $1; }
    |   pairs COMMA pair    { 
            json_object_add_pair(&($1),$3); 
            $$=$1;
            }
    ;

pair:
    STRING COLON expr { 
        $$ = json_make_pair($1,$3);
        free($1);
        }
    ;

array:
     LARRAY expr_list RARRAY {$$ = llist2array($2); }
    ;

expr_list:
         expr   {$$ = start_llist($1); }
    |   expr_list COMMA expr    { $$ = push_llist($1,$3); }
    ;
%%

JSON json_parse_str(const char *input) {
    int error;
    //create a string stream 
    yyin=fmemopen((void *)input,strlen(input),"r");
    //parse the string
    error = yyparse();
    fclose(yyin); //close the stream

    if(error){
        return NULL;
    } else {
        return yy_json_result; //return the result
    }
}

JSON json_parse_file( FILE *f) {
    yyin=f;
    yyparse();
    return yy_json_result;
}



JSON_llist start_llist(JSON j){
    JSON_llist result;
    result = (JSON_llist) malloc(sizeof(json_llist_node));
    if(! result) return NULL;
    result->index=0;
    result->value=j;
    result->next=NULL;
    return result;
}

JSON_llist push_llist(JSON_llist list, JSON j){
    JSON_llist new_element = start_llist(j);
    if(! new_element) return NULL;
    new_element->index = (list->index)+1;
    new_element->next = list;
    
    return new_element;

}

//converts a linked list of array nodes into an actual array
//note that this destroys the linked list
//since we want to free the memory
//and in this application we won't need that memory any more
JSON_array llist2array(JSON_llist list){
    JSON_array result;
    size_t length;
    if(! list ) {
        //if the list is empty 
        //then we create an array with a single element whic points to a null pointer
        result=(JSON_array) malloc(sizeof(JSON));
        *result=NULL;
        return result;
    }
    
    /* the size of the list is the index of the top element plus one
     * since the array is zero indexed
     */
    length = list->index+1; 

    /* we allocate memory for all of the objects, plus one for the 
     * null sentinel value
     */
    result = (JSON_array) calloc((length+1),sizeof(JSON));
    JSON_llist prev;
    JSON_llist curr = list;
    while( curr != NULL ) {
        assert(curr->index < length);
        result[curr->index]=curr->value; //set the value at the index 
        prev=curr;
        curr=curr->next; //move to the next element
        free(prev);
    }
    result[length]=NULL; //set the sentinnel value
    return result;
    
    
}

//simple error handler, we will make this more robust later
void yyerror(char const *s){
    fprintf(stderr,"%s\n",s);
}
