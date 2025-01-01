#include "ast.h"

static void PrintNB(ast *p, char * indent);
static void PrintOP(ast *p, char * indent);
static void PrintID(ast *p, char * indent);
static void PrintLINST(ast *p, char * indent);
static void PrintAFFECT(ast *p, char * indent);
static void PrintTQ(ast *p, char * indent);
static void PrintEQ(ast *p, char * indent);
static void PrintDIFF(ast *p, char * indent);
static void PrintSUP(ast *p, char * indent);
static void PrintINF(ast *p, char * indent);
static void PrintSUPEGAL(ast *p, char * indent);
static void PrintINFEGAL(ast *p, char * indent); 
static void PrintET(ast *p, char * indent);
static void PrintOU(ast *p, char * indent);
static void PrintNON(ast *p, char * indent);
static void PrintSI(ast *p, char * indent);
static void PrintFOR(ast *p, char * indent);
static void PrintDECFUNC(ast *p, char * indent);
static void PrintFUNC(ast *p, char * indent);
static void PrintMAIN(ast *p, char * indent);


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

ast* CreerNoeudDIFF(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_DIFF;
  strcpy(p->type_str,"DIFF");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudSUP(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_SUP;
  strcpy(p->type_str,"SUP");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudINF(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_INF;
  strcpy(p->type_str,"INF");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudSUPEGAL(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_SUPEGAL;
  strcpy(p->type_str,"SUPEGAL");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudINFEGAL(ast* p1, ast* p2){
  ast* p;
  INIT_NOEUD(p);
  p->type = AST_INFEGAL;
  strcpy(p->type_str,"INFEGAL");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudET(ast * p1, ast * p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_ET;
  strcpy(p->type_str,"ET");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudOU(ast * p1, ast * p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_OU;
  strcpy(p->type_str,"OU");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
}

ast* CreerNoeudNON(ast * t){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_NON;
  strcpy(p->type_str,"NON");
  p->noeud[0] = t;
  return p;
}

ast* CreerNoeudSI(ast * p1, ast * p2, ast * p3){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_SI;
  strcpy(p->type_str,"SI");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  p->noeud[2] = p3;
  return p;
}

ast* CreerNoeudFOR(char* id, ast * p2, ast * p3, ast * p4){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_FOR;
  strcpy(p->type_str,"FOR");
  strcpy(p->id,id);
  p->noeud[0] = p2;
  p->noeud[1] = p3;
  p->noeud[2] = p4;
  return p;
}

ast* CreerNoeudDECFUNC(ast * p1, ast * p2){
  ast * t;
  INIT_NOEUD(t);
  t->type = AST_DECFUNC;
  strcpy(t->type_str,"DECFUNC");
  t->noeud[0] = p1;
  t->noeud[1] = p2;
  return t;
}

ast* CreerNoeudFUNC(char * nom, ast * p){
  ast * t;
  INIT_NOEUD(t);
  t->type = AST_FUNC;
  strcpy(t->type_str,"FUNC");
  strcpy(t->nom,nom);
  t->noeud[0] = p;
  return t;
}


ast* CreerNoeudMAIN(ast * p){
  ast * t;
  INIT_NOEUD(t);
  t->type = AST_MAIN;
  strcpy(t->type_str,"MAIN");
  t->noeud[0] = p;
  return t;
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
  case AST_SUP:
    PrintSUP(p,indent);
    break;
  case AST_INF:
    PrintINF(p,indent);
    break;
  case AST_DIFF:
    PrintDIFF(p,indent);
    break;
  case AST_SUPEGAL:
    PrintSUPEGAL(p,indent);
    break;
  case AST_INFEGAL:
    PrintINFEGAL(p,indent);
    break;
  case AST_ET:
    PrintET(p,indent);
    break;
  case AST_OU:
    PrintOU(p,indent);
    break;
  case AST_NON:
    PrintNON(p,indent);
    break;
  case AST_SI:
    PrintSI(p,indent);
    break;
  case AST_FOR:
    PrintFOR(p,indent);
    break;
  case AST_DECFUNC:
    PrintDECFUNC(p,indent);
    break;
  case AST_FUNC:
    PrintFUNC(p,indent);
    break;
  case AST_MAIN:
    PrintMAIN(p,indent);
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

static void PrintSUP(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintINF(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintDIFF(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintSUPEGAL(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintINFEGAL(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintET(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintOU(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

static void PrintNON(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  profondeur--;
}

static void PrintSI(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  if(p->noeud[2] != NULL)
    PrintAst(p->noeud[2]);
  profondeur--;
}

static void PrintFOR(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Identificateur:   " TXT_NULL "%s\n",indent, p->id);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  PrintAst(p->noeud[2]);
  profondeur--;
}

static void PrintDECFUNC(ast *p, char *indent){
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
}

static void PrintFUNC(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Nom:   " TXT_NULL "%s\n",indent, p->nom);
  profondeur++;
  PrintAst(p->noeud[0]);
  profondeur--;
}

static void PrintMAIN(ast *p, char *indent){
  PrintAst(p->noeud[0]);
}