#include "codegen.h"
FILE * out;
ts TABSYMB;

void codegen(ast*);
void codegenINIT();


int main(void){
    out=stdout;
    ajouter_id(TABSYMB,"lol");
    ajouter_id(TABSYMB,"mdr");
    ast* p1=CreerFeuilleID("lol");
    ast* p2=CreerFeuilleID("mdr");
    codegenINIT();
    codegen(p1);
    codegen(p2);
    return 0;
}