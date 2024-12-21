#include "codegen.h"


static void codegenNB(ast* p);
static void codegenOP(ast* p);
static void codegenID(ast* p);
static void codegenTQ(ast* p);
static void codegenAFFECT(ast* p);
static void codegenLINST(ast* p);
static void codegenEQ(ast* p);
void codegen(ast*);
void codegenINIT();

extern ts TABSYMB;
extern int mem_res;
int PILE=__PREMIERE_ADR__;
static int nb_inst = 0;

void codegenINIT(){
    PILE+=mem_res+1;
}

void add_inst(FILE * out, char * inst){
    fprintf(out,"%s\n",inst);
    nb_inst++;
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
        case AST_TQ:
            codegenTQ(p);
            break;
        case AST_LINST:
            codegenLINST(p);
            break;
        case AST_EQ:
            codegenEQ(p);
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

static void codegenTQ(ast* p){
    codegen(p->noeud[0]);
    semantic(p->noeud[0]);
    semantic(p->noeud[1]);
    fprintf(out,"JUMZ %d\n", p->noeud[0]->codelen + 1 + p->noeud[1]->codelen + 1); //les 2 +1 c jumz et jump 
    codegen(p->noeud[1]);
    fprintf(out,"JUMP %d\n", p->noeud[0]->codelen);
    EMPILER();
}

static void codegenLINST(ast* p){
    codegen(p->noeud[0]);
    codegen(p->noeud[1]);
}

static void codegenEQ(ast *p){
    codegen(p->noeud[0]);
    EMPILER();
    codegen(p->noeud[1]);
    fprintf(out,"STORE %d\n",__REG_TMP__);
    DEPILER();
    DEPILER();
    fprintf(out,"SUB %d\n",__REG_TMP__);
    fprintf(out,"JUMZ %d\n",(p->noeud[0]->codelen)+(p->noeud[1]->codelen)+NB_INST_EMPILER+2*NB_INST_DEPILER+5);
    fprintf(out,"LOAD #0\n");
    fprintf(out,"JUMP %d\n",(p->noeud[0]->codelen)+(p->noeud[1]->codelen)+NB_INST_EMPILER+2*NB_INST_DEPILER+6);
    fprintf(out,"LOAD #1\n");
    EMPILER();
}