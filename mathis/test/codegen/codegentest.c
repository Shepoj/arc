#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();
void semantic(ast*);


int main(void){
    out=stdout;
    ajouter_id(TABSYMB,"truc");
    ast * p1 = CreerFeuilleNB(1);
    ast * p2 = CreerFeuilleNB(2);
    ast * p6 = CreerFeuilleNB(3);
    ast * p3 = CreerNoeudAffect("truc",p2);
    ast * p5 = CreerNoeudAffect("truc",p6);
    ast * p4 = CreerNoeudSI(p1,p3,p5);
    codegenINIT();
    semantic(p4);
    PrintAst(p4);
    codegen(p4);
    return 0;
}