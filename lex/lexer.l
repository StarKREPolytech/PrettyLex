%{
    #include <header.h>
%}

%%
[F|f][R|r][O|o][M|m][^a-zA-Z0-9]+               from_count++;
[S|s][E|e][L|l][E|e][C|c][T|t][^a-zA-Z0-9]+     select_count++;
[W|w][H|h][E|e][R|r][E|e][^a-zA-Z0-9]+          where_count++;
.|\n                                            ;
%%

unsigned from_count;

unsigned select_count;

unsigned where_count;

int yywrap(void)
{
	return 1;
}