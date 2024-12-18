#include "codegen.h"

static void codegenNB(ast* p);
static void codegenOP(ast* p);
static void codegenID(ast* p);
static void codegenAFFECT(ast* p);
void codegen(ast*);
void codegenINIT();

extern int mem_res;
int PILE=__PREMIERE_ADR__;

void codegenINIT(){
    PILE;
}

void codegen(ast *p){
    if(p==NULL)return;
    switch(p->type){
        case AST_NB:
            codegenNB(p);
            break;
        case AST_OP:
            codegenOP(p);
            break;
        case AST_ID:
            codegenID(p);
            break;
        case AST_AFFECT:
            codegenAFFECT(p);
            break;
    }
}

static void codegenNB(ast* p){
    fprintf(out,"LOAD #%d\n",p->valeur);
    EMPILER();
}

static void codegenOP(ast* p){
    codegen(p->noeud[0]);
    codegen(p->noeud[1]);
    DEPILER();
    fprintf(out,"STORE %d\n",__REG_TMP__);
    DEPILER();
    switch(p->op){
        case '+':
            fprintf(out,"ADD %d\n",__REG_TMP__);
            break;
        case '-':
            fprintf(out,"SUB %d\n",__REG_TMP__);
            break;
        case '*':
            fprintf(out,"MUL %d\n",__REG_TMP__);
            break;
        case '/':
            fprintf(out,"DIV %d\n",__REG_TMP__);
            break;
        case '%':
            fprintf(out,"MOD %d\n",__REG_TMP__);
            break;
    }
    EMPILER();
}

static void codegenID(ast* p){
    fprintf(out, "LOAD %d\n",chercher_id(TABSYMB,p->id)+__PREMIERE_ADR__);
    EMPILER();
}

static void codegenAFFECT(ast* p){
    codegen(p->noeud[0]);
    DEPILER();
    fprintf(out,"STORE %d\n",chercher_id(TABSYMB, p->id)+__PREMIERE_ADR__);
    EMPILER();
}