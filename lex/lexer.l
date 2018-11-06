%{
    #include <header.h>
%}

%%
[a-zA-Z0-9]{2,}     check_word(yytext);
.|\n                ;
%%

int yywrap(void)
{
	return 1;
}