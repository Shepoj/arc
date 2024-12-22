#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();
void semantic(ast*);


int main(void){
    out=stdout;
    ast * p1 = CreerFeuilleNB(1);
    ast * p3 = CreerNoeudNON(p1);
    codegenINIT();
    semantic(p3);
    PrintAst(p3);
    codegen(p3);
    return 0;
}