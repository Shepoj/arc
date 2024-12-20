#include "ast.h"

static void PrintNB(ast *p, char * indent);
static void PrintOP(ast *p, char * indent);
static void PrintID(ast *p, char * indent);
static void PrintLINST(ast *p, char * indent);
static void PrintAFFECT(ast *p, char * indent);
static void PrintTQ(ast *p, char * indent);
static void PrintEQ(ast *p, char * indent);
int profondeur = 0;

ast * CreerFeuilleNB(int nb){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_NB;
  strcpy(p->type_str,"NB");
  p->valeur = nb;
  return p;
}

ast* CreerNoeudOP(int op, ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_OP;
  strcpy(p->type_str,"OP");
  p->op = op;
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudAffect(char* id, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_AFFECT;
  strcpy(p->type_str,"AFFECT");
  p->noeud[0] = p2;
  strcpy(p->id,id);
  return p;
}

ast* CreerFeuilleID(char * id){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_ID;
  strcpy(p->type_str,"ID");
  strcpy(p->id,id);
  return p;
}

ast* CreerNoeudLINST(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_LINST;
  strcpy(p->type_str,"LINST");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudTQ(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_TQ;
  strcpy(p->type_str,"TQ");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudEQ(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_EQ;
  strcpy(p->type_str,"EQ");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

void FreeAst(ast * p){
  if (p == NULL) return;
  FreeAst(p->noeud[0]);
  FreeAst(p->noeud[1]);
  free(p);
}

void PrintAst(ast * p){
  if (p == NULL) return;
  char indent[32] ="";
  int i;
  for(i = 0 ; i < profondeur ; i++)
    indent[i] = '\t';
  indent[i] = '\0';
  switch(p->type){
  case AST_NB:
    PrintNB(p,indent);
    break;
  case AST_OP:
    PrintOP(p,indent);
    break;
  case AST_ID:
    PrintID(p,indent);
    break;
  case AST_LINST:
    PrintLINST(p,indent);
    break;
  case AST_AFFECT:
    PrintAFFECT(p,indent);
    break;
  case AST_TQ:
    PrintTQ(p,indent);
    break;
  case AST_EQ:
    PrintEQ(p,indent);
    break;
  default:
    fprintf(stderr,"[Erreur] type <%d>: %s non reconnu\n",p->type,p->type_str);
    break;
  }
}

void ErrorAst(const char * errmsg){
  fprintf(stderr,"[AST error] %s\n",errmsg);
  exit(1);
}

static void PrintNB(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Valeur: " TXT_NULL "%d\n",indent, p->valeur);
}

static void PrintOP(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Opérateur:   " TXT_NULL "%c\n",indent, p->op);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintAFFECT(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Identificateur:   " TXT_NULL "%s\n",indent, p->id);
  profondeur++;
  PrintAst(p->noeud[0]);
  profondeur--;
}

static void PrintID(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Identificateur:   " TXT_NULL "%s\n",indent, p->id);
}

static void PrintLINST(ast *p, char *indent){
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
}

static void PrintTQ(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintEQ(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}