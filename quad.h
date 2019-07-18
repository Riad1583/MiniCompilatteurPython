#include <string.h>

typedef struct Pile Pile;
struct Pile
{
			  char chaine[50];
			  Pile *svt;
};

Pile *pile;
Pile *pile2;

int chainebre = 1 ;

void empiler( char chaine[]){
    Pile *tmp = malloc(sizeof(*tmp));
    strcpy(tmp->chaine,chaine);
    tmp->svt = pile;
    pile = tmp;
}

char* depiler(){
	char chaine[50];
    Pile *tmp = pile;
    if (pile != NULL)
    {
       strcpy(chaine,tmp->chaine);
        pile = tmp->svt;
        free(tmp);
    }
    return strdup(chaine);
}

void empiler2( char chaine[]){
    Pile *tmp = malloc(sizeof(*tmp));
    strcpy(tmp->chaine,chaine);
    tmp->svt = pile2;
    pile2= tmp;
}

char* depiler2(){
	char chaine[50];
    Pile *tmp = pile2;
    if (pile2 != NULL)
    {
       strcpy(chaine,tmp->chaine);
        pile2 = tmp->svt;
        free(tmp);
    }
    return strdup(chaine);
}


typedef struct ESPACE ESPACE;
struct ESPACE
{			  
   char chaine[50];
   int espace ;
   int fin ;
   int instruction ;
   int eliff ;
   int elsee ;
};


ESPACE TableEspace[1000];

int SizeTableSpace = 0;

typedef struct QDR QDR;
struct QDR
{			  
   char oper[100];
   char op1[100];
   char op2[100];
   char res[100]; 
};


QDR quad[1000];

int qc = 0;

typedef struct TABLIND TABLIND;
struct TABLIND
{      
  int espace ;
  int qc ;
};


TABLIND TableINDENTATION[1000];

int SizeTableINDENTATION = 0;

typedef struct INSTRUCTION INSTRUCTION;
struct INSTRUCTION
{       
   char valeur[100]; 
};


INSTRUCTION instruction[1000];

int SizeInstruction = 0;

void Save_BLOCK_INDENTATION(int espace , int qc){ 
  
  TableINDENTATION[SizeTableINDENTATION].espace = espace ;
  TableINDENTATION[SizeTableINDENTATION].qc = qc ;
 
  SizeTableINDENTATION++;
};

void  Save_Quadr(int espace, int qcc){ 
  int i ;
  char sauv[10];
  char num_sauv[10];
  
  
  for( i =0; i<SizeTableINDENTATION ; i++)
  {  
    if(espace <= TableINDENTATION[i].espace ){
         if(strcmp(quad[TableINDENTATION[i].qc].res ,"")==0){
           strcpy(sauv,"");
           sprintf(num_sauv,"%d",qcc);
              
           strcpy(quad[TableINDENTATION[i].qc].res ,strcat(sauv,num_sauv)); }
    }

  
  }
}

void Add_Quadr(int num_quad, int colon_quad, char val []){	
  if (colon_quad==0) strcpy(quad[num_quad].oper , val);
  else if (colon_quad==1) strcpy(quad[num_quad].op1 , val);
  else if (colon_quad==2) strcpy(quad[num_quad].op2 ,val);
  else if (colon_quad==3) strcpy(quad[num_quad].res , val);
}

void remplire_Instruction(char valeur[]){ 
   strcpy(instruction[SizeInstruction].valeur , valeur); 
   
   SizeInstruction ++ ; 
}

void  remplire_quadruplet(char oper[] ,char op1[], char op2[] , char res[]){  
  strcpy(quad[qc].oper , oper);
  strcpy(quad[qc].op1 , op1);
  strcpy(quad[qc].op2 , op2);
  strcpy(quad[qc].res , res);

   
  qc++;
}

char * OPERATEUR(char opr[100]){
	     if(strcmp(opr,"<")==0) { return "BNL" ;}
	     if(strcmp(opr,">")==0) { return "BNG" ; }
	     if(strcmp(opr,"==")==0){ return "BNE";}
	     if(strcmp(opr,"<=")==0){ return "BG" ;}
	     if(strcmp(opr,">=")==0){ return "BL" ;}
	     if(strcmp(opr,"!=")==0){ return "BE" ;}
        
       return "";
}

void Align(i){  
   int espace =2 ;
   int pos ;
   while(espace !=0){
    pos = i ;
      while(pos<SizeInstruction-1){
        instruction[pos] = instruction[pos+1];
        pos++;
      }
      SizeInstruction = SizeInstruction-1;
      espace--;
   }
}

char* Get_Sauv(int chainebre){
	char sauv[10];
	char num_sauv[10];

	strcpy(sauv,"t");
	sprintf(num_sauv,"%d",chainebre);
	
	return strcat(sauv,num_sauv); 
}

char* resulta(){   
           
  char val [10]; 
  int i= 1;
  char t[10];  
     
  if(SizeInstruction==1){

      remplire_quadruplet("=",instruction[0].valeur,"","");
 
      SizeInstruction = 0 ;
  }

  while(i<SizeInstruction)
  { 

 	  if(Prio(instruction[i].valeur)==2) 
    {  
      strcpy(t,Get_Sauv(chainebre));
   	  chainebre++;
      remplire_quadruplet(instruction[i].valeur,instruction[i-1].valeur,instruction[i+1].valeur ,t); 
      strcpy(instruction[i-1].valeur,t);       
      Align(i);
    
      i=i-2;
    }

    i=i+2;
  }
 

  i= 1;
  
   
   
  while(i<SizeInstruction)
  { 

    if(Prio(instruction[i].valeur)==1) 
    {  
      strcpy(t,Get_Sauv(chainebre));
     	chainebre++;
      remplire_quadruplet(instruction[i].valeur,instruction[i-1].valeur,instruction[i+1].valeur ,t); 
      strcpy(instruction[i-1].valeur,t);       
      Align(i);
       
      i=i-2;
    }
  
    i=i+2;

  }
 
  SizeInstruction = 0;
       
  char sauv[10];
	char num_sauv[10];

	chainebre--;
	return  Get_Sauv(chainebre) ;
}

void afficher_quadruplet(){
    int i ;
  
  for(i=0;i<qc;i++)
  {
    printf(" %d - ( %s , %s , %s , %s)\n",i,quad[i].oper,quad[i].op1,quad[i].op2,quad[i].res);
  }
}

int Prio(char chaine[]){
   if(strcmp(chaine ,"+")==0) return 1 ;
   if(strcmp(chaine ,"-")==0) return 1 ;
   if(strcmp(chaine ,"/")==0) return 2 ;
   if(strcmp(chaine ,"*")==0) return 2 ;
    
   return 0;

}

int TriterInstruction(int Condition){ 
  int PrO =0;
  int PrF =0 ;
  int exist =0 ; 
  char valeur[100];
  char valeur2[100];
  char OneValeurAndCondition =0; 
    strcpy(valeur,depiler());  
     if(pile==NULL && Condition==1) 
      { 
        OneValeurAndCondition=1;
       
       }
   
   empiler(valeur);

  while(pile!=NULL){
      
      strcpy(valeur,depiler());  
      empiler2(valeur);
       
    if(strcmp(")", valeur)==0){
       exist =1;
       
      while(pile!=NULL && strcmp(valeur,"(")!=0){      
           
           strcpy(valeur,depiler());
           if(strcmp(valeur,"(")!=0)
          { empiler2(valeur); }         
      }
         if(strcmp(valeur,"(")==0){
               

        strcpy(valeur2,depiler2());
          
        while(pile2 !=NULL && exist==1)
        {  
           if(strcmp(valeur2,")")!=0)
           { remplire_Instruction(valeur2); 
          	strcpy(valeur2,depiler2());                         
           }else{
           	exist =0 ;
           }

        }
         
             empiler2(resulta()); 
              chainebre++;    
              
           while(pile2!=NULL)
           { strcpy(valeur2,depiler2()); 
             empiler(valeur2);
           }       
   
        }
     }     
   

   }

 while(pile2!=NULL){
  
  strcpy(valeur,depiler2());
  remplire_Instruction(valeur);       
 }
  
 resulta();
 chainebre++;


 return OneValeurAndCondition ;  
}

void Block_Fini(int espace , char chaine[]){
  int i= 0;
    
   while(i<SizeTableSpace)
   {    
   	      if(TableEspace[i].espace >=espace ){
   	   	    TableEspace[i].fin =1 ;
          if(strcmp("elif", chaine)==0 ){
                   int y = TableEspace[i].espace -espace ;
                   if(y ==0 ){
                   TableEspace[i].eliff++;     
                }}
            


             if(strcmp("else", chaine)==0 ){
                  
                  int y = TableEspace[i].espace -espace ;
                  
                   if(y ==0 ){
                   TableEspace[i].elsee++;     
                }}
          
       }
      
       i++;
   }	
}

/* Existance Block Elif If */
int quitIfElif(int espace){

  int i =0 ;
  while(i<SizeTableSpace )
    {     
       if(strcmp("if", TableEspace[i].chaine)==0 || strcmp("elif", TableEspace[i].chaine)==0 ){
           
            if (TableEspace[i].espace==espace &&  TableEspace[i].elsee==1)
            {
                     
            TableEspace[i].elsee=2;
    
        return 1 ;
           }
           
             if (TableEspace[i].espace==espace &&  TableEspace[i].elsee==0 && TableEspace[i].eliff==1 )
            {
                     
            TableEspace[i].eliff=2;
    
        return 2 ;
           }
      }
        i++;
    }   
    return 0 ;
}

/* Verifier Block Else*/
int chekel(char chaine[]){
  
    if(strcmp("else", chaine)==0)
     { return 1 ;
     }
       return 0 ;
}

/* Ajouter TableEspace */

int addTE( char chaine[] ,int espace,int fin){ 
  Block_Fini(espace,chaine);
  if(SizeTableSpace==0  &&  espace!=0){

      printf("\nError syntaxique Vous ne devriez pas ecrire d espace quand vous commencez \n");
      exit(0);
 }else{
   if(avaInstru()==1 && espace != TableEspace[SizeTableSpace-1].espace ){
      printf("\nError syntaxique il faut aligner le code  \n");  
      exit(0);
   }else{
     if(ComenceIFCOND(espace)==0){
         printf("\nError syntaxique  l instruction %s est vide  \n",TableEspace[SizeTableSpace-1].chaine);    
         exit(0);
      }else{
        if(DansCndBlock(espace)==0 && espace!=0){

          printf("\nError syntaxique il faut aligner le code \n");  
          exit(0);
        }else{
            
              if(  chekel(chaine)==1 && quitIfElif(espace)!=1){
                   printf("\nError syntaxique else sans if ou bien elif \n");
                   exit(0);
              }else{

                 if(voirelif(chaine)==1 && quitIfElif(espace)!=2){
                   printf("\nError syntaxique elif sans if ou bien elif \n");
                    exit(0);
                 }

              }
        }



      } 
   } 

 } 

  strcpy(TableEspace[SizeTableSpace].chaine ,chaine);
  TableEspace[SizeTableSpace].espace = espace;
  TableEspace[SizeTableSpace].fin = 0;
  TableEspace[SizeTableSpace].instruction = 0;
  TableEspace[SizeTableSpace].eliff=0;
  TableEspace[SizeTableSpace].elsee=0;
  SizeTableSpace ++ ;
}    

/* Verifier Elif */ 

int voirelif(char chaine[] )
 { 
     if(strcmp("elif", chaine)==0)
     { return 1 ;
     }
       return 0 ;
 } 

/* Instruction Avant */

int avaInstru(){
 int i = 0 ;
   while(i<SizeTableSpace)
   { 
      if(strcmp("inst", TableEspace[i].chaine)!=0){
         return 0 ; 
      }
         i++;  
   }
         return 1;
}

/* COMMENCEMENT Block Condition */

int ComenceIFCOND(int espace){
   int i = 0 ;
   while(i<SizeTableSpace)
   { 
     if(strcmp("if", TableEspace[i].chaine)==0 || strcmp("elif", TableEspace[i].chaine)==0 || 
      strcmp("else", TableEspace[i].chaine)==0){
         if(i==(SizeTableSpace-1)){
         if( espace <= TableEspace[SizeTableSpace - 1].espace){
            
          return 0;}  
           else{
               
                 TableEspace[SizeTableSpace - 1].instruction = espace ;
               }
             }                                                
           }
             i++;  
       }

             return 1; 
}

/* CONDITION*/

int DansCndBlock(int espace){
    int i = 0 ;
    while(i<SizeTableSpace)
    {  
     if(strcmp("if", TableEspace[i].chaine)==0 || strcmp("elif", TableEspace[i].chaine)==0 || 
      strcmp("else", TableEspace[i].chaine)==0)
      {
        
          if(espace ==TableEspace[i].instruction && TableEspace[i].fin==0)
          {     
              return 1 ;  
          }
      }
      i++;
    }
      return 0;
}

/* Supprimer Quadruplet */

void Dell(QDR liste[],int i)
{
  while(i<qc){
    liste[i]=liste[i+1];
    i++;
  }

  int m=0;

  while(m<i)
  {    
    int to=atoi(liste[m].res);
    if(to!=0)
    {
      to--;
      sprintf(liste[m].res,"%d",to);
    }

    m++;
  }

  qc--;
}

void Optimisation(QDR liste[],int qcmax)
{
  int i = 0 ; 
  int j = 0;
  int boolean=1;
  int booleanUtilisee=0;

  while(boolean==1)
  {    
    boolean=0;
    booleanUtilisee=0;

    while(i<qc)
    {
      /*operation meme operande affectation*/
      if(strcmp(liste[i].oper,"=")==0 && strcmp(liste[i].op1, liste[i].res) == 0 && strcmp(liste[i].op2, "") == 0  ){
            Dell(liste,i);
            boolean=1;
      }
      else
      {
        i++;
      }
    }

    i=0;

    while(i<qc)
    {
      /*operation non commutative meme*/
      if(strcmp(liste[i].oper,"-") == 0 || strcmp(liste[i].oper,"=") == 0 || strcmp(liste[i].oper,"/") == 0 ) 
      {      
        j= i+1 ;
        while(j<qc)
        {
          if(strcmp(liste[i].res,liste[j].res) == 0 )
          {
            if(strcmp(liste[i].op1,liste[j].op1) == 0 && strcmp(liste[i].op2,liste[j].op2) == 0 && strcmp(liste[i].oper,liste[j].oper) == 0)
            {
              boolean=1;
              Dell(liste,j);j--;
            }

            else 
            {
              break;
            }
          }
          j++;
        }
      }

     else
     {
      /*operation commutative meme*/
      if(strcmp(liste[i].oper,"+") == 0 || strcmp(liste[i].oper,"*") == 0 )
      {
        j= i+1 ;
        while(j<qc)
        {
          if(strcmp(liste[i].res,liste[j].res) == 0 )
          {
            if(((strcmp(liste[i].op1,liste[j].op1) == 0 && strcmp(liste[i].op2,liste[j].op2) == 0 &&
                 strcmp(liste[i].oper,liste[j].oper) == 0)) ||
                 strcmp(liste[i].op1,liste[j].op2) == 0 && strcmp(liste[i].op2,liste[j].op1) == 0 &&
                 strcmp(liste[i].oper,liste[j].oper) == 0)
            {
              Dell(liste,j);
              j--;
            }
            else 
            {
              break;
            }
          }
          j++;
        }
      }
     }
     i++;
    }

   i=0;
   j=0;
    
    /*Simplification Algebrique*/ /*Elimination d'expression redondante*/
   while(i<qc)
   {
     
       /*Multiplier par 2*/
        if(strcmp(liste[i].oper,"*") == 0)
        {   if(strcmp(liste[i].op1,"2") == 0)
             {  strcpy(liste[i].op1,liste[i].op2);
                strcpy(liste[i].oper,"+"); 
                boolean=1;
             }
             if(strcmp(liste[i].op2,"2") == 0)
             {  strcpy(liste[i].op2,liste[i].op1);
                strcpy(liste[i].oper,"+"); 
                boolean=1;
             }           
        }

        if(strcmp(liste[i].oper,"*") == 0)
        {   if(strcmp(liste[i].op1,"1") == 0)
             {  
                Dell(liste,i);
             }
             if(strcmp(liste[i].op2,"1") == 0)
             {  
                Dell(liste,i);
             }           
        }

        if(strcmp(liste[i].oper,"*") == 0)
        {   if(strcmp(liste[i].op1,"0") == 0)
             {  strcpy(liste[i].op1,"0");
                strcpy(liste[i].op2,"");
                strcpy(liste[i].oper,"="); 
                boolean=1;
             }
             if(strcmp(liste[i].op2,"0") == 0)
             {  
                strcpy(liste[i].op1,"0");
                strcpy(liste[i].op2,"");
                strcpy(liste[i].oper,"="); 
                boolean=1;
             }           
        }

         if(strcmp(liste[i].oper,"+") == 0 || strcmp(liste[i].oper,"-") == 0 || strcmp(liste[i].oper,"/") == 0 || strcmp(liste[i].oper,"*") == 0 ) 
         {
             j= i+1 ;

             while(j<qc)
             {
                 if(strcmp(liste[j].res,liste[i].res)!=0)
                 { 
                      /*a=5+2 b=5+2 =>a=5+2 b=a*/ /*Elimination d'expression redondante*/
                      if(strcmp(liste[j].oper,liste[i].oper)==0 &&  strcmp(liste[j].op1,liste[i].op1)==0 && strcmp(liste[j].op2,liste[i].op2 ) == 0)
                      {
                           strcpy(liste[j].oper,"=");
                           strcpy(liste[j].op1,liste[i].res);
                           strcpy(liste[j].op2,""); 
                      }    

                 }
                 else
                 {
                      if(strcmp(liste[j].oper,liste[i].oper)==0 &&  strcmp(liste[j].op1,liste[i].op1)==0 && strcmp(liste[j].op2,liste[i].op2 ) == 0)
                      {
                           strcpy(liste[j].oper,"=");
                           strcpy(liste[j].op1,liste[i].res);
                           strcpy(liste[j].op2,"");
                      }else
                      {
                        j=qc ;
                      }  
                 }
               j++ ;
             }


        }   
        i++ ;
   }

   i=0;
   j=0;

   /*Variable non utilisee code inutile*/
   while(i<qc)
   {
     booleanUtilisee=0;
     if(strcmp(liste[i].oper,"=") == 0)
     {
       j=i;
       while(j<qc)
       {
        if(strcmp(liste[j].op1,liste[i].res) == 0 || strcmp(liste[j].op2,liste[i].res)==0)
        {
          booleanUtilisee=1;
          break;
        }
        j++;
       }

       if(booleanUtilisee==0)
       {
        Dell(liste,i);
        boolean=1;
       }
       else
       {
        i++;
       }       
     }
     else
     {
      i++;
     }
   }

  }
}

void assembleur(QDR liste[]){
  int i,type;
  printf("DATA SEGMENT \n");

  printf("DATA ENDS\n");
  printf("CODE SEGEMENT\n");
  printf("ASSUME CS:CODE, DS:DATA\n");
  printf("MAIN :\n");
  printf("MOV AX,DATA\n");
  printf("MOV DS,AX\n");

  printf("\n");

  for(i=0;i<qc;i++)
  {
        if(strcmp(liste[i].oper,"BNE")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("CMP AX, %s\n",liste[i].op2);
        printf("JNE etiquette %s\n",liste[i].res);}
    
        if(strcmp(liste[i].oper,"BE")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("CMP AX, %s\n",liste[i].op2);
        printf("JE etiquette %s\n",liste[i].res);}

        if(strcmp(liste[i].oper,"BG")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("CMP AX, %s\n",liste[i].op2);
        printf("JG etiquette %s\n",liste[i].res);}

        if(strcmp(liste[i].oper,"BL")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("CMP AX, %s\n",liste[i].op2);
        printf("JL etiquette %s\n",liste[i].res);}
       

        if(strcmp(liste[i].oper,"BNL")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("CMP AX, %s\n",liste[i].op2);
        printf("JNL etiquette %s\n",liste[i].res);}

        if(strcmp(liste[i].oper,"BNG")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("CMP AX, %s\n",liste[i].op2);
        printf("JNG etiquette %s\n",liste[i].res);}

        if(strcmp(liste[i].oper,"BR")==0){
        printf("\netiquette %d :\n",i);
        printf("JMP AX, %s\n",liste[i].res);}
      
        if(strcmp(liste[i].oper,"+")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("ADD AX, %s\n",liste[i].op2);
        printf("MOV %s, AX\n",liste[i].res);}

        if(strcmp(liste[i].oper,"-")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("SUB AX, %s\n",liste[i].op2);
        printf("MOV %s, AX\n",liste[i].res);}

        if(strcmp(liste[i].oper,"*")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("MUL AX, %s\n",liste[i].op2);
        printf("MOV %s, AX\n",liste[i].res);}

        if(strcmp(liste[i].oper,"/")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("DIV AX, %s\n",liste[i].op2);
        printf("MOV %s, AX\n",liste[i].res);}

        if(strcmp(liste[i].oper,"=")==0){
        printf("\netiquette %d :\n",i);
        printf("MOV AX, %s\n",liste[i].op1);
        printf("MOV %s, AX\n",liste[i].res);}

  }
  printf("\n");
  printf("MOV AH,4CH\n");
  printf("INT 21h\n");
  printf("CODE ENDS\n");
  printf("END MAIN\n");
}
