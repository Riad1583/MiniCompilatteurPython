%{
   #include <stdio.h>
   #include <stdlib.h>    
   #include "quad.h"
 
   int yylex();
  

   void yyerror(char*msg);
   int count = 0 ; 
   char tmp1[100];
   char tmp2[100];
   char operateur[100];
   int cond1 = 0 ;
   int cond2 = 0;
   int SauvSpace = 0;
   int SauveElse =  0 ;
   int init = 0 ;

%}

%union {
char *str; 
int ent;
float real;  	
}

%token FIN 
%token IF  
%token space 
%token jump 
%token tiret8  
%token DeuxPoints
%token Equal  
%token Apostrophe 
%token <str>variable
%token PrO 
%token PrF 
%token Int
%token Float
%token Char
%token <str>Entier
%token Real
%token Vergule
%token Character
%token Plus
%token Minus
%token PointExclamation
%token Sup
%token Inf
%token ELSE
%token ELIF
%token Div
%token Mul
%token OR
%token AND
%token Commenter
%token tab
%token ANDC
%token ORC


%start START

%%//automate

START : BEGIN_BLOC { 
                            remplire_quadruplet("" ,"","",""); 
                            Save_Quadr(0,qc-1);
                            printf("Affichage des quads :\n");
                            afficher_quadruplet();
                            Optimisation(quad,qc);
                            printf("Optimisation :\n");
                            afficher_quadruplet();
                            printf("Code machine :\n");
                            assembleur(quad);
                   } 
                |  { 
                            remplire_quadruplet("" ,"","",""); 
                            Save_Quadr(0,qc-1);
                            afficher_quadruplet();
                            Optimisation(quad,qc);
                            afficher_quadruplet();
                            assembleur(quad);
                   }

BEGIN_BLOC : INDENTATION Block_Code jump { 
                                          if(SauveElse==1)
                                          {
                                            Save_Quadr(count,qc); SauveElse=0;
                                          }

                                          else
                                          {
                                            Save_Quadr(count,qc-1);
                                          }
                                         
                                          if(SauvSpace==1)
                                          {
                                            SauvSpace =0; 
                                            Save_BLOCK_INDENTATION(count, qc-1);
                                          } 
                                          
                                          count=0 ;  
                                      } BEGIN_BLOC2 

            | INDENTATION Block_Code jump { 
                                          if(SauveElse==1)
                                          {
                                            Save_Quadr(count,qc); SauveElse=0;
                                          }

                                          else
                                          {
                                            Save_Quadr(count,qc-1);
                                          }
                                         
                                          if(SauvSpace==1)
                                          {
                                            SauvSpace =0; 
                                            Save_BLOCK_INDENTATION(count, qc-1);
                                          } 
                                          
                                          count=0 ;  
                                      } 

BEGIN_BLOC2 : JUMPS BEGIN_BLOC

JUMPS : jump JUMPS |

SPACES : space SPACES   | tab SPACES  |

Block_Code :  AFF {addTE( "inst" ,count,0);  } | CONDITION_IF_OR_ELIF   | Commenter  | CONDITION_ELSE | DEC {addTE( "inst" ,count,0);}

CONDITION_IF_OR_ELIF : IF_OR_ELIF CONDITION  SPACES      

CONDITION : SPACES PrO SPACES EXP_LOGIQUE PrF  SPACES  DeuxPoints  
   
CONDITION_ELSE : ELSE {addTE( "else" ,count,0);  remplire_quadruplet("BR" ,"", "" , "");SauveElse=1; SauvSpace=1;}  SPACES DeuxPoints SPACES 

EXP_LOGIQUE    : EXP_LOGIQUE_B  EXP { 
                                      cond2=TriterInstruction(1); 
                                      strcpy(operateur,OPERATEUR(operateur));  
                                      SauvSpace=1;                     
                                      
                                      if(cond2==1)
                                      {
                                        strcpy(tmp2,quad[qc-1].op1); 
                                        qc--;
                                      }
                                      
                                      else
                                      {
                                        strcpy(tmp2,quad[qc-1].res);
                                      }

                                      cond1=0;
                                      cond2=0;                         
                                      remplire_quadruplet(operateur,tmp1 ,tmp2 ,""); 
                                     }
  
EXP_LOGIQUE_B : EXP_LOGIQUE_A OPERATEUR_COMPARAISON SPACES 

EXP_LOGIQUE_A  : EXP { cond1 =TriterInstruction(1);if(cond1==1){strcpy(tmp1,quad[qc-1].op1);
                                                                            qc--;}else{
                                                                            strcpy(tmp1,quad[qc-1].res);}  }  
       
AFF   : variable SPACES Equal SPACES EXP  {TriterInstruction(0); Add_Quadr(qc-1, 3, $1) ;}  
 
EXP:VALEUR_OR_VARIABLE SPACES OP SPACES EXP|VALEUR_OR_VARIABLE SPACES|Pro_EXP_PrF_B  PrF  { empiler(")");} | PrO_EXP_PrF_OPIRATEUR_SPACES_EXP_D  OP SPACES EXP

PrO_EXP_PrF_OPIRATEUR_SPACES_EXP_D :  Pro_EXP_PrF_B PrF  { empiler(")");}

Pro_EXP_PrF_B : Pro_EXP_PrF_A EXP

Pro_EXP_PrF_A : PrO { empiler("(");}

IF_OR_ELIF : IF {addTE( "if" ,count,0); }   | ELIF {addTE( "elif" ,count,0);}
 
DEC : TYPE DECLARER 

DECLARER : SPACES_OR_TAB SPACES variable SPACES INISIALISATION {if(init ==1){TriterInstruction(0); Add_Quadr(qc-1, 3, $3) ; init=0;}}  
                                                      MOR_DECLARATION 
 
MOR_DECLARATION : Vergule SPACES variable SPACES INISIALISATION {
                                                       if(init ==1){ TriterInstruction(0); Add_Quadr(qc-1, 3, $3) ;
                                                            init= 0;
                                                         }
                                                       }  
                                                     MOR_DECLARATION | 

INISIALISATION :  INI { init = 1 ;} | 

INI : Equal SPACES EXP 

//Les Type Exist
TYPE : Int 

VALEUR_OR_VARIABLE : VALEUR | variable {empiler($1);}
 
VALEUR : Entier {empiler($1);}

OPERATEUR_COMPARAISON : PointExclamation Equal {strcpy(operateur,"!=");} | 
Equal Equal {strcpy(operateur,"==");}   | Inf  {strcpy(operateur,"<");}  | 
Sup {strcpy(operateur,">");} | Sup Equal {strcpy(operateur,"<=");} | Inf Equal {strcpy(operateur,">=");} 

OP : Plus { empiler("+");} | Minus { empiler("-");} | Div { empiler("/");} | Mul { empiler("*");}

SPACES_OR_TAB : space | tab

INDENTATION : space INDENTATION {count++ ;}  | tab INDENTATION { count= count+8;  } |
            
%%

void yyerror(char* s){

	printf ("Error %s\n",s);

}

int yywrap(){
    return 1;
}


int main(void){ return yyparse();}
