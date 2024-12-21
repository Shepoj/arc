#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();
void semantic(ast*);


int main(void){
    out=stdout;
    ajouter_id(TABSYMB,"a");
    ast *t1 = CreerNoeudAffect("a",CreerFeuilleNB(1));
    ast * p1 = CreerFeuilleNB(1);
    ast* p = CreerNoeudAffect("a",p1);
    ast* p2 = CreerFeuilleNB(1);
    ast* p3 = CreerNoeudOP('+',p,p2);
    ast* p4 = CreerNoeudAffect("a",p3);
    ast *p5 = CreerFeuilleNB(2);
    ast *a = CreerFeuilleID("a");
    ast *p6 = CreerNoeudEQ(a,p5);
    ast* p7 = CreerNoeudTQ(p6,p4);
    ast *p8 = CreerNoeudLINST(t1,p7);
    codegenINIT();
    semantic(p8);
    PrintAst(p8);
    codegen(p8);
    return 0;
}