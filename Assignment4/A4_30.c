#include <stdio.h>
extern int yyparse();
// extern int yydebug;
int main(){
    printf("... Beginning the parsing process ...\n\n");
    // yydebug = 1;
    yyparse();
    return 0;
}