Lex.l synt.y
bison -d synt.y
flex Lex.l
gcc -o compil synt.tab.c lex.yy.c -lfl
.\compil <code.txt >resu.txt