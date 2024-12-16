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
  else {							\
    p->type = 0;						\
    p->type_str[0] = '\0';					\
    p->valeur = 0;						\
    p->ope = 0;							\
    p->id[0] = '\0';						\
    p->noeud[2] = NULL;						\
  }								\

enum {AST_NB = 256, TYPE_OP, TYPE_ID} ;

typedef struct ast{
  int  type;
  char type_str[32];
  int valeur;
  int ope;
  char id[32];
  struct ast * noeud[2];
} ast;

ast * CreerNoeudOP(int ope, ast* p1, ast* p2);	
ast * CreerFeuilleNB(int nb);
ast * CreerFeuilleID(char *id);

void FreeAst(ast * p);

void PrintAst(ast * p);
void ErrorAst(const char * errmsg);


#endif
