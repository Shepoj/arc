#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();


int main(void){
    out=stdout;
    ajouter_id(TABSYMB,"a");
    ast* p1=CreerFeuilleNB(3);
    ast* p2=CreerFeuilleNB(4);
    ast* p5=CreerFeuilleNB(5);
    ast* p3=CreerNoeudOP('+',p1,p2);
    ast* p7=CreerNoeudOP('*',p3,p5);
    ast* p4=CreerNoeudAffect("a",p7);
    ast* p6=CreerNoeudAffect("b",p4);
    codegenINIT();
    semantic(p6);
    printf("%d",p6->codelen);
    PrintAst(p6);
    codegen(p6);
    return 0;
}