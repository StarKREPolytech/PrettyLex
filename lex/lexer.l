%{
    #include <lexer.h>
%}

%%
[-|+]*[0-9]+[.]+[0-9]+                      handle_number(yytext, yyleng);
.|\n                                        ;
%%

int yywrap(void)
{
	return 1;
}