%{  
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>	
	#include "synt.tab.h"

%}

Number [0-9]
Character \'[a-zA-Z]\'
%%
 
"fin" {return(FIN);}

"int" {return(Int);}

"float" {return(Float);}

"char" {return(Char);}

"if" {return(IF);}

"elif" {return(ELIF);}

"else" {return(ELSE);}

"or" {return(OR);}

"and" {return(AND);}

{Number}+ { yylval.str = strdup(yytext);    return(Entier);}

{Number}+[.]{Number}+ {return(Real);}

{Character}  { return(Character);}

[ ] { return(space);}


[\t] { return(tab);}

[\n] {return(jump);}

[_]   {return(tiret8) ; }

[\(] {return(PrO) ; }

[\=]{1}  {return(Equal);}

[\!]  {return(PointExclamation) ; }

[\>]  {return(Sup) ; }

[\<]  {return(Inf) ; }


[ \&]{1} 	    {  return(ANDC);}

[ \|]{1} 	    {  return(ORC);}

[ \)] {return(PrF ) ; }

[a-zA-Z_]{1}[a-zA-Z0-9_]* {  yylval.str = strdup(yytext); return (variable);}

#[^\n]*  { return (Commenter);}

[ :]  {return(DeuxPoints);}

[ \,]  { return(Vergule);}

[ \+]{1} 	    {  return(Plus);}

[ \-]{1}		{  return(Minus);}

[ \*]{1}        { return (Mul);}

[ \/]{1}        { return (Div);}

[ \']{1}  {printf ("Apostrophe"); return(Apostrophe);}
