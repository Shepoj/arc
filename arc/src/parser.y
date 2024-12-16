%{
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  
  #include "ast.h"
    
  extern int yylex();
  static void print_file_error(char * s, char *errmsg);

  struct ast * ARBRE_ABSTRAIT = NULL;

  void yyerror(const char * s);

  char srcname[64];
  char exename[64] = "a.out";
  FILE * exefile;
%}

%union{
  int nb;
  char id[32];
  struct ast* arbre;
 };
 
%type <arbre> EXP

%define parse.error detailed
%locations

%token <nb> NB
%token <id> ID
%token MAIN DEBUT FIN

%right '='

%left '+' '-'
%left '*' '/' '%'

%start PROGRAMME

%%

PROGRAMME: 
	MAIN '(' ')'
	DEBUT
		EXP ';'
	FIN 			{ARBRE_ABSTRAIT=$5;PrintAst(ARBRE_ABSTRAIT);}

EXP : NB 			{$$=CreerFeuilleNB($1);}
| ID				{$$=CreerFeuilleID($1);}
| ID '=' EXP			{}
| EXP '+' EXP			{$$=CreerNoeudOP('+',$1,$3);}
| EXP '-' EXP 			{$$=CreerNoeudOP('-',$1,$3);}
| EXP '*' EXP 			{$$=CreerNoeudOP('*',$1,$3);}
| EXP '/' EXP 			{$$=CreerNoeudOP('/',$1,$3);}
| EXP '%' EXP 			{$$=CreerNoeudOP('%',$1,$3);}
| '(' EXP ')' 			{$$=$2;}
;

%%

int main( int argc, char * argv[] ) {
  extern FILE *yyin;
  
  if (argc > 1){
    strcpy(srcname, argv[1]);
    if ( (yyin = fopen(srcname,"r"))==NULL ){
      char errmsg[256];
      sprintf(errmsg,"fichier \x1b[1m\x1b[33m' %s '\x1b[0m introuvable",srcname);
      print_file_error(argv[0],errmsg);
      exit(1);
    }
  }  else {
    print_file_error(argv[0],"aucun fichier en entree");
    exit(1);
  }
  if (argc == 3){
    strcpy(exename, argv[2]);
  }
  exefile = fopen(exename,"w");
  yyparse();
  fclose(yyin);
}



static void print_file_error(char * prog, char *errmsg){
  fprintf(stderr,
	  "\x1b[1m%s:\x1b[0m \x1b[31m\x1b[1merreur fatale:\x1b[0m %s\nechec de la compilation\n",
	  prog, errmsg);
}

void yyerror(const char * s)
{
  fprintf(stderr, "\x1b[1m%s:%d:%d:\x1b[0m %s\n", srcname, yylloc.first_line, yylloc.first_column, s);
  exit(0);
}
