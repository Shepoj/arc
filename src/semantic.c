#include "semantic.h"

void semantic(ast* p){
    if(p==NULL)return;
    switch(p->type){
        case AST_NB:
            p->codelen = 1 + NB_INST_EMPILER;
            break;
        case AST_ID:
            p->codelen = 1 + NB_INST_EMPILER;
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
            p->codelen = p->noeud[0]->codelen;
            if (p->noeud[1] != NULL){
                semantic(p->noeud[1]);
                p->codelen += p->noeud[1]->codelen;
            }
            break;
        case AST_TQ:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2 + NB_INST_EMPILER; //jumz et jump
            break;
        case AST_EQ:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 6; 
            break;
        case AST_DIFF:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 6; 
            break;
        case AST_SUP:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 6; 
            break;
        case AST_INF:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 6; 
            break;
        case AST_SUPEGAL:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 7; 
            break;
        case AST_INFEGAL:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 2*NB_INST_EMPILER + 2*NB_INST_DEPILER + 7; 
            break;
        case AST_ET:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + NB_INST_EMPILER + 5; 
            break;
        case AST_OU:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + NB_INST_EMPILER + 6; 
            break;
        case AST_NON:
            semantic(p->noeud[0]);
            p->codelen = p->noeud[0]->codelen + NB_INST_EMPILER + 4; 
            break;
        case AST_SI:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            if(p->noeud[2] != NULL)
                semantic(p->noeud[2]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + 1 + NB_INST_EMPILER;
            if(p->noeud[2] != NULL)
                p->codelen += p->noeud[2]->codelen + 1;
            break;
        case AST_FOR:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            semantic(p->noeud[2]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen + p->noeud[2]->codelen + 5;
            break;
        case AST_MAIN:
            semantic(p->noeud[0]);
            p->codelen = p->noeud[0]->codelen + 1;
            break;
        case AST_NEG:
            semantic(p->noeud[0]);
            p->codelen = p->noeud[0]->codelen + 1 + NB_INST_EMPILER;
            break;
        case AST_DECFUNC:
            semantic(p->noeud[0]);
            semantic(p->noeud[1]);
            p->codelen = p->noeud[0]->codelen + p->noeud[1]->codelen;
            break;
    }
}