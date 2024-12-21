#include "semantic.h"

void semantic(ast* p){
    if(p==NULL)return;
    switch(p->type){
        case AST_NB:
            p->codelen = 2;
            break;
        case AST_ID:
            p->codelen = 2;
            break;
        case AST_OP:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + NB_INST_DEPILER + 2;
            break;
        case AST_AFFECT:
            semantic(p->noeud[0]);
            p->codelen = NB_INST_DEPILER + p->noeud[0]->codelen + 1 + NB_INST_EMPILER;
            break;
        case AST_LINST:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen;
            break;
        case AST_TQ:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2 + NB_INST_EMPILER; //jumz et jump
            break;
        case AST_EQ:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 6; //jumz et jump
            break;
    }
}