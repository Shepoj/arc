static void codegenNB(ast*);
int PILE=__PREMIERE_ADR__;



void codegen(ast *p){
    if(p==NULL)return;
    switch(p->type){
        case AST_NB:
            codegenNB(p);
            break;
        case AST
    }
}

static void codegenNB(ast* p){
    fprintf(out,"LOAD #%d\n",p->valeur);
    EMPILER();
}