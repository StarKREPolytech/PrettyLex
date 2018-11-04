%{
    #include <header.h>
%}
%option nounput yylineno

%%
[a-zA-Z0-9]{2,} { check_word(yytext); }
.|\n ;
%%

int yywrap(void)
{
	return 1;
}