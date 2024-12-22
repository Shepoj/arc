#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();
void semantic(ast*);


int main(void){
    out=stdout;
    ast * p1 = CreerFeuilleNB(1);
    ast * p2 = CreerFeuilleNB(0);
    ast * p3 = CreerNoeudOU(p1,p2);
    codegenINIT();
    semantic(p3);
    PrintAst(p3);
    codegen(p3);
    return 0;
}