%{
    #include <header.h>
%}
%option nounput yylineno

%%
([S|s][E|e][L|l][E|e][C|c][T|t])|([W|w][H|h][E|e][R|r][E|e])|([F|f][R|r][O|o][M|m]) { put_word(yytext); }
.|\n ;
%%

int yywrap(void)
{
	return 1;
}