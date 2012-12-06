/****************************************************************************************
*  Copyright 2012 Thayne McCombs
* 
*  This file is part of cjson.
*  
*      cjson is free software: you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation, either version 3 of the License, or
*      (at your option) any later version.
*  
*      cjson is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*  
*      You should have received a copy of the GNU General Public License
*      along with cjson.  If not, see <http://www.gnu.org/licenses/>.
*/
%{

    #include <stdlib.h>

    #include "json_types.h"
    #include "json.tab.h"


    int buffer_length;
    char *buf;
    size_t buf_count;

    void read_char(char c);


    void terminate_buffer();
    
    void start_STRINGSTATE();
    void end_STRINGSTATE();

%}


%x STRINGSTATE



%option noyywrap


%%


    /*Brackets for containing objects */
"{" { return LBRACKET; }
"}" { return RBRACKET; }
"[" { return LARRAY; }
"]" { return RARRAY; }
"," { return COMMA; }
":" { return COLON; }

    /* Boolean values */
true    { yylval.bVal = true; return BOOL; }
false   { yylval.bVal = false; return BOOL; } 

    /* null value */

null|NULL   { return NULL_TOKEN; }

[-+]?[0-9]+  {yylval.iVal = atoi(yytext); return INT; }

[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?  {yylval.fVal =atof(yytext); return FLOAT; }



"\""          { start_STRINGSTATE(); }

<STRINGSTATE>"\\n" { read_char('\n'); }
<STRINGSTATE>"\\r" { read_char('\r'); }
<STRINGSTATE>"\\t" { read_char('\t'); }
<STRINGSTATE>"\\b"   { read_char('\b'); }
<STRINGSTATE>"\\f"   { read_char('\f'); }
<STRINGSTATE>"\\/"   { read_char('/'); }
<STRINGSTATE>"\\\\" { read_char('\\'); }
<STRINGSTATE>\\u[0-9A-Fa-f]{4}  { printf("wide chars currently unsupported"); }
<STRINGSTATE>"\\\"" { read_char('"'); }

<STRINGSTATE>"\"" { 
                    end_STRINGSTATE();
                    return STRING;
                }
<STRINGSTATE>.  { read_char(*yytext); }

[ \t\n\r]+ {/*ignore whitespace */ }





%%

void start_STRINGSTATE(){
    BEGIN STRINGSTATE;
    buffer_length=128;
    buf = (char *) malloc(buffer_length*sizeof(char));   
    if(!buf){
        fprintf(stderr,"Memory failure\n");
        exit(0);
    }
    buf_count=0;

}

void end_STRINGSTATE(){
    BEGIN 0;
    yylval.sVal = strndup(buf,buf_count);
    free(buf);
}




void read_char(char c){
    if(buf_count >= buffer_length) {
        buffer_length *= 2;
        buf=(char*)realloc( buf, buffer_length*sizeof(char));
    }


    buf[buf_count++]=c;
    
}


