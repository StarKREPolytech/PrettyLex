%{
    #include <lexer.h>
%}

%%
[-|+]*[0-9]*[.]+[0-9]+E[+-]*[0-9]{2,} handle_number(yytext, yyleng);
.                                     printf("DOUBLE POINT!\n");
\n                                   ;
%%

int yywrap(void)
{
	return 1;
}