#include "../include/codegen.h"

static void add_inst(FILE * out, int inst, char prefixe, int reg);

static void codegenNB(ast* p);
static void codegenOP(ast* p);
static void codegenID(ast* p);
static void codegenTQ(ast* p);
static void codegenAFFECT(ast* p);
static void codegenLINST(ast* p);
static void codegenEQ(ast* p);
static void codegenDIFF(ast* p);
static void codegenSUP(ast* p);
static void codegenINF(ast* p);
static void codegenSUPEGAL(ast* p);
static void codegenINFEGAL(ast* p);
static void codegenET(ast* p);
static void codegenOU(ast* p);
static void codegenNON(ast* p);
static void codegenSI(ast* p);

void codegen(ast*);
void codegenINIT();

extern ts TABSYMB;
extern int mem_res;
int PILE=__PREMIERE_ADR__;
static int nb_inst = 0;

void codegenINIT(){
    PILE+=mem_res+1;
}

void add_inst(FILE * out, int inst, char prefixe, int reg){
    switch(inst){
        case __READ__:
            fprintf(out,"%s %c%d\n","READ",prefixe, reg);
            break;
        case __WRITE__:
            fprintf(out,"%s %c%d\n","WRITE",prefixe, reg);
            break;
        case __ADD__:
            fprintf(out,"%s %c%d\n","ADD",prefixe, reg);
            break;
        case __SUB__:
            fprintf(out,"%s %c%d\n","SUB",prefixe, reg);
            break;
        case __MUL__:
            fprintf(out,"%s %c%d\n","MUL",prefixe, reg);
            break;
        case __DIV__:
            fprintf(out,"%s %c%d\n","DIV",prefixe, reg);
            break;
        case __MOD__:
            fprintf(out,"%s %c%d\n","MOD",prefixe, reg);
            break;
        case __JUMZ__:
            fprintf(out,"%s %d\n","JUMZ", reg);
            break;
        case __JUMP__:
            fprintf(out,"%s %d\n","JUMP", reg);
            break;
        case __JUML__:
            fprintf(out,"%s %d\n","JUML", reg);
            break;
        case __JUMG__:
            fprintf(out,"%s %d\n","JUMG", reg);
            break;
        case __LOAD__:
            fprintf(out,"%s %c%d\n","LOAD",prefixe, reg);
            break;
        case __STORE__:
            fprintf(out,"%s %c%d\n","STORE",prefixe, reg);
            break;
        case __INC__:
            fprintf(out,"%s %d\n","INC", reg);
            break;
        case __DEC__:
            fprintf(out,"%s %d\n","DEC", reg);
            break;
        case __STOP__:
            fprintf(out,"%s\n","STOP");
            break;
        case __NOP__:
            fprintf(out,"%s\n","NOP");
            break; 
    }
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
        case AST_DIFF:
            codegenDIFF(p);
            break;
        case AST_SUP:
            codegenSUP(p);
            break;
        case AST_INF:
            codegenINF(p);
            break;
        case AST_SUPEGAL:
            codegenSUPEGAL(p);
            break;
        case AST_INFEGAL:
            codegenINFEGAL(p);
            break;
        case AST_ET:
            codegenET(p);
            break;
        case AST_OU:
            codegenOU(p);
            break;
        case AST_NON:
            codegenNON(p);
            break;
        case AST_SI:
            codegenSI(p);
            break;
    }
}

static void codegenNB(ast* p){
    add_inst(out,__LOAD__,'#',p->valeur);
    EMPILER();
}

static void codegenOP(ast* p){
    codegen(p->noeud[0]);
    codegen(p->noeud[1]);
    DEPILER();
    add_inst(out,__STORE__, '\0',__REG_TMP__);
    DEPILER();
    switch(p->op){
        case '+':
            add_inst(out,__ADD__,'\0',__REG_TMP__);
            break;
        case '-':
            add_inst(out,__SUB__,'\0',__REG_TMP__);
            break;
        case '*':
            add_inst(out,__MUL__,'\0',__REG_TMP__);
            break;
        case '/':
            add_inst(out,__DIV__,'\0',__REG_TMP__);
            break;
        case '%':
            add_inst(out,__MOD__,'\0',__REG_TMP__);
            break;
    }
    EMPILER();
}

static void codegenID(ast* p){
    add_inst(out,__LOAD__,'\0',chercher_id(TABSYMB,p->id)+__PREMIERE_ADR__);
    EMPILER();
}

static void codegenAFFECT(ast* p){
    codegen(p->noeud[0]);
    DEPILER();
    add_inst(out,__STORE__,'\0',chercher_id(TABSYMB, p->id)+__PREMIERE_ADR__);
    EMPILER();
}

static void codegenTQ(ast* p){
    int nbjump=nb_inst;
    codegen(p->noeud[0]);
    int nbjumz=nb_inst+p->noeud[1]->codelen+2;
    add_inst(out,__JUMZ__,'\0',nbjumz);
    codegen(p->noeud[1]);
    add_inst(out,__JUMP__,'\0',nbjump);
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
    add_inst(out,__STORE__,'\0',__REG_TMP__);
    DEPILER();
    DEPILER();
    add_inst(out,__SUB__,'\0',__REG_TMP__);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',0);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',1);
    EMPILER();
}

static void codegenDIFF(ast* p){
    codegen(p->noeud[0]);
    EMPILER();
    codegen(p->noeud[1]);
    add_inst(out,__STORE__,'\0',__REG_TMP__);
    DEPILER();
    DEPILER();
    add_inst(out,__SUB__,'\0',__REG_TMP__);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',1);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',0);
    EMPILER();
}

static void codegenSUP(ast *p){
    codegen(p->noeud[0]);
    EMPILER();
    codegen(p->noeud[1]);
    add_inst(out,__STORE__,'\0',__REG_TMP__);
    DEPILER();
    DEPILER();
    add_inst(out,__SUB__,'\0',__REG_TMP__);
    add_inst(out,__JUMG__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',0);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',1);
    EMPILER();
}

static void codegenINF(ast *p){
    codegen(p->noeud[0]);
    EMPILER();
    codegen(p->noeud[1]);
    add_inst(out,__STORE__,'\0',__REG_TMP__);
    DEPILER();
    DEPILER();
    add_inst(out,__SUB__,'\0',__REG_TMP__);
    add_inst(out,__JUML__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',0);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',1);
    EMPILER();
}

static void codegenSUPEGAL(ast *p){
    codegen(p->noeud[0]);
    EMPILER();
    codegen(p->noeud[1]);
    add_inst(out,__STORE__,'\0',__REG_TMP__);
    DEPILER();
    DEPILER();
    add_inst(out,__SUB__,'\0',__REG_TMP__);
    add_inst(out,__JUMG__,'\0',nb_inst+4);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',0);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',1);
    EMPILER();
}

static void codegenINFEGAL(ast *p){
    codegen(p->noeud[0]);
    EMPILER();
    codegen(p->noeud[1]);
    add_inst(out,__STORE__,'\0',__REG_TMP__);
    DEPILER();
    DEPILER();
    add_inst(out,__SUB__,'\0',__REG_TMP__);
    add_inst(out,__JUML__,'\0',nb_inst+4);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',0);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',1);
    EMPILER();
}

static void codegenET(ast *p){
    codegen(p->noeud[0]);   
    int nbjumz=p->noeud[1]->codelen+nb_inst+4;
    add_inst(out,__JUMZ__,'\0',nbjumz);
    codegen(p->noeud[1]);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',1);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',0);
    EMPILER();
}

static void codegenOU(ast *p){
    codegen(p->noeud[0]);
    add_inst(out,__JUMZ__,'\0',nb_inst+2);
    int nbjump=p->noeud[1]->codelen+nb_inst+2;
    add_inst(out,__JUMP__,'\0',nbjump);
    codegen(p->noeud[1]);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',1);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',0);
    EMPILER();
}

static void codegenNON(ast *p){
    codegen(p->noeud[0]);
    add_inst(out,__JUMZ__,'\0',nb_inst+3);
    add_inst(out,__LOAD__,'#',0);
    add_inst(out,__JUMP__,'\0',nb_inst+2);
    add_inst(out,__LOAD__,'#',1);
    EMPILER();
}

static void codegenSI(ast *p){
    codegen(p->noeud[0]);
    int nbjumz=nb_inst+p->noeud[1]->codelen+2;
    add_inst(out,__JUMZ__,'\0',nbjumz);
    codegen(p->noeud[1]);
    if (p->noeud[2]!=NULL){
        int nbjump=nb_inst+p->noeud[2]->codelen+1;
        add_inst(out,__JUMP__,'\0',nbjump);
        codegen(p->noeud[2]);
    }
    EMPILER();
}

static void codegenFOR(ast* p){
    int adresse=chercher_id(TABSYMB,p->noeud[0]->id);
    codegen(p->noeud[0]);
    int nbjump=nb_inst;
    //je sais pas quoi faire lol
}