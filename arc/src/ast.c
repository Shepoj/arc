#include "ast.h"

static void PrintNB(ast *p, char * indent);
static void PrintOP(ast *p, char * indent);
static void PrintID(ast *p, char * indent);

ast * CreerFeuilleNB(int nb){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_NB;
  strcpy(p->type_str,"NB");
  p->valeur = nb;
  return p;
}

ast * CreerFeuilleID(char *id){
	ast* p;
	INIT_NOEUD(p);
	p->type = TYPE_ID;
	strcpy(p->type_str,"ID");
	strcpy(p->id,id);
	return p;
}

ast * CreerNoeudOP(int ope, ast* p1, ast* p2){
	ast* p;
	INIT_NOEUD(p);
	p->type = TYPE_OP;
	strcpy(p->type_str,"OP");
	p->ope=ope;
	p->noeud[0]=p1;
	p->noeud[1]=p2;
	return p;
}

void FreeAst(ast * p){
  if (p == NULL) return;
  FreeAst(p->noeud[0]);
  FreeAst(p->noeud[1]);
  free(p);
}

int profondeur=0;

void PrintAst(ast * p){
  if (p == NULL) return;
  char indent[32] ="";
  int i;
  for(i=0;i<profondeur;i++)
  	indent[i]='\t';
  indent[i]='\0';
  switch(p->type){
  case AST_NB:
    PrintNB(p,indent);
    break;
  case TYPE_ID:
    PrintID(p,indent);
    break;
  case TYPE_OP:
    PrintOP(p,indent);
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

static void PrintID(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Nom: " TXT_NULL "%s\n",indent, p->id);
}

static void PrintOP(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud: " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Opérateur:   " TXT_NULL "%d\n",indent, p->ope);
  profondeur++;
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  profondeur--;
}

