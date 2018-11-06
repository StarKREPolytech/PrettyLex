%{
    #include <lexer.h>
%}

%%
[a-zA-Z0-9]{2,}     check_word(yytext, yyleng);
.|\n                ;
%%

int yywrap(void)
{
	return 1;
}