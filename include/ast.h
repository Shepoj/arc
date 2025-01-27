#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  TXT_RED    "\x1b[31m"
#define  TXT_GREEN  "\x1b[32m"
#define  TXT_BLUE   "\x1b[34m"
#define  TXT_BOLD   "\x1b[1m"
#define  TXT_NULL   "\x1b[0m"

#define INIT_NOEUD(p)   if ((p = malloc(sizeof(ast))) == NULL)	\
    ErrorAst("echec allocation mémoire");			\
  else {							      \
    p->type = 0;						\
    p->type_str[0] = '\0';	\
    p->valeur = 0;          \
    p->op = 0;              \
    p->id[0] = '\0';        \
    p->noeud[0] = NULL;     \
    p->noeud[1] = NULL;			\
    p->noeud[2] = NULL;			\
    p->codelen = 0;         \
    p->nom[0] = '\0';       \
  }								          \

enum {AST_NB = 256, AST_OP, \
AST_ID, AST_LINST, AST_AFFECT,\
AST_TQ, AST_EQ, AST_DIFF,\
AST_INF, AST_SUP, AST_SUPEGAL,\
AST_INFEGAL, AST_ET, AST_OU,\
AST_NON, AST_SI, AST_FOR, \
AST_DECFUNC, AST_FUNC,\
AST_MAIN, AST_NEG};

typedef struct ast{
  int  type;
  char type_str[32];
  int valeur;
  int op;
  char id[32];
  struct ast* noeud[3];
  int codelen;
  char nom[32];
} ast;


ast* CreerFeuilleNB(int nb);

ast* CreerNoeudOP(int op, ast* p1, ast* p2);

ast* CreerNoeudLINST(ast* p1, ast* p2);

ast* CreerNoeudAffect(char* id, ast* p2);

ast* CreerFeuilleID(char * id);

ast* CreerNoeudTQ(ast* p1, ast* p2);

ast* CreerNoeudEQ(ast* p1, ast* p2);

ast* CreerNoeudDIFF(ast* p1, ast* p2);

ast* CreerNoeudINF(ast* p1, ast* p2);

ast* CreerNoeudSUP(ast* p1, ast* p2);

ast* CreerNoeudSUPEGAL(ast* p1, ast* p2);

ast* CreerNoeudINFEGAL(ast* p1, ast* p2);

ast* CreerNoeudET(ast * p1, ast * p2);

ast* CreerNoeudOU(ast * p1, ast * p2);

ast* CreerNoeudNON(ast * p);

ast* CreerNoeudSI(ast * p1, ast * p2, ast * p3);

ast* CreerNoeudFOR(char* id, ast * p2, ast * p3, ast * p4);

ast* CreerNoeudDECFUNC(ast * p1, ast * p2);

ast* CreerNoeudFUNC(char* nom, ast * p1);

ast* CreerNoeudMAIN(ast * p);

ast * CreerNoeudNEG(ast * p);

void FreeAst(ast * p);

void PrintAst(ast * p);

void ErrorAst(const char * errmsg);


#endif
