LEX=lex
a3: lex.yy.c
	gcc -o a3 lex.yy.c -lfl
lex.yy.c: a3.lex
	lex a3.lex
