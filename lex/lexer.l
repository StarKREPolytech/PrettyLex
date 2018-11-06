%{
    #include <header.h>
%}

%%
[Ff][Rr][Oo][Mm][^a-zA-Z0-9]+                from_count++;
[Ss][Ee][Ll][Ee][Cc][Tt][^a-zA-Z0-9]+        select_count++;
[Ww][Hh][Ee][Rr][Ee][^a-zA-Z0-9]+            where_count++;
.|\n                                         ;
%%

unsigned from_count;

unsigned select_count;

unsigned where_count;

int yywrap(void)
{
	return 1;
}