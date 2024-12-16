#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();


int main(void){
    out=stdout;
    ajouter_id(TABSYMB,"lol");
    ajouter_id(TABSYMB,"mdr");
    ajouter_id(TABSYMB,"xd");
    ast* p1=CreerFeuilleNB(3);
    ast* p2=CreerFeuilleNB(4);
    ast* p3=CreerNoeudOP('+',p1,p2);
    ast* p4=CreerNoeudAffect("mdr",p3);
    codegenINIT();
    codegen(p4);
    return 0;
}