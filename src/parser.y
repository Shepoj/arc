%debug

%{
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  
  #include "ast.h"  
  #include "semantic.h"
  #include "codegen.h"

  extern int yylex();
  static void print_file_error(char * s, char *errmsg);

  struct ast * ARBRE_ABSTRAIT = NULL;

  void yyerror(const char * s);
  void codegen(ast*);
  void codegenINIT(); 
  void semantic(ast*);

  ts TABSYMB;

  char srcname[64];
  char exename[64] = "ram.txt";
  FILE * exefile;
%}

%union{
  int nb;
  char id[32];
  struct ast* arbre;
 };


%define parse.error detailed
%locations

%type <arbre> FONCTIONS
%type <arbre> MAINFUNC
%type <arbre> FONCTION
%type <arbre> parametres

%type <arbre> INST
%type <arbre> LINST
%type <arbre> EXP
%type <arbre> AFFECT
%type <arbre> TANTQUE
%type <arbre> CONDITION
%type <arbre> FORLOOP


%token <nb> NB
%token <id> ID
%token VAR
%token FLECHE "<-"
%token DIFFERENT "!="
%token INFERIEUR "<="
%token SUPERIEUR ">="
%token MAIN ALGO DEBUT FIN
%token TQ FAIRE FINTQ
%token SI ALORS SINON FINSI
%token POUR DE A FINPOUR

%start PROGRAMME

%right "<-"

%left ET OU NON
%left '=' "!=" '<' '>' "<=" ">="

%left '+' '-'
%left '*' '/' '%'

%%

PROGRAMME:
  FONCTIONS           
  MAINFUNC            { ARBRE_ABSTRAIT = $2; PrintAst($1); PrintAst(ARBRE_ABSTRAIT);}
;

FONCTIONS:
  FONCTION FONCTIONS  { $$ = CreerNoeudDECFUNC($1, $2);}
| %empty              { $$ = NULL;}
;



FONCTION: 
  ALGO ID'('parametres')'
    DECLA
    DEBUT
      LINST
    FIN                 { $$ = CreerNoeudFUNC($2, $8); }
;

MAINFUNC : 
  MAIN'('')'
    DECLA
    DEBUT
      LINST  
    FIN                   { $$ = CreerNoeudMAIN($6); }
;                       

INST : EXP';'           { $$ = $1;}
| AFFECT                { $$ = $1;}
| TANTQUE               { $$ = $1;}
| CONDITION             { $$ = $1;}
| FORLOOP               { $$ = $1;}
;

LINST : INST            { $$ = CreerNoeudLINST($1, NULL);}
| INST LINST            { $$ = CreerNoeudLINST($1, $2);}
;

DECLA : %empty
| VAR ID ';' DECLA      { ajouter_id(TABSYMB, $2);}
;

AFFECT : ID "<-" EXP';' { $$ = CreerNoeudAffect($1,$3);}
;

TANTQUE : 
  TQ EXP FAIRE
    LINST
  FINTQ                 { $$ = CreerNoeudTQ($2, $4);}
;

CONDITION :
  SI EXP ALORS
    LINST
  SINON
    LINST
  FINSI                 {$$ = CreerNoeudSI($2,$4,$6);}
| SI EXP ALORS
    LINST
  FINSI                   {$$ = CreerNoeudSI($2,$4, NULL);}
;

FORLOOP :
  POUR ID DE EXP A EXP FAIRE
    LINST
  FINPOUR                {$$ = CreerNoeudFOR($2,$4,$6,$8);}
;

EXP : NB                {$$ = CreerFeuilleNB($1);}
| EXP '+' EXP           {$$ = CreerNoeudOP('+',$1,$3);}
| EXP '-' EXP           {$$ = CreerNoeudOP('-',$1,$3);}
| EXP '*' EXP           {$$ = CreerNoeudOP('*',$1,$3);}
| EXP '/' EXP           {$$ = CreerNoeudOP('/',$1,$3);}
| EXP '%' EXP           {$$ = CreerNoeudOP('%',$1,$3);}
| '('EXP')'             {$$ = $2;}
| ID                    {$$ = CreerFeuilleID($1);}
| EXP '=' EXP           {$$ = CreerNoeudEQ($1,$3);}
| EXP "!=" EXP          {$$ = CreerNoeudDIFF($1,$3);}
| EXP '<' EXP           {$$ = CreerNoeudINF($1,$3);}
| EXP '>' EXP           {$$ = CreerNoeudSUP($1,$3);}
| EXP "<=" EXP          {$$ = CreerNoeudINFEGAL($1,$3);}
| EXP ">=" EXP          {$$ = CreerNoeudSUPEGAL($1,$3);}
| EXP ET EXP            {$$ = CreerNoeudET($1,$3);}
| EXP OU EXP            {$$ = CreerNoeudOU($1,$3);}
| NON EXP               {$$ = CreerNoeudNON($2);}
;


parametres:
  ID                    { $$ = CreerFeuilleID($1);}
| NB                    { $$ = CreerFeuilleNB($1);}
| ID ',' parametres     { $$ = CreerNoeudLINST(CreerFeuilleID($1), $3);}
| NB ',' parametres     { $$ = CreerNoeudLINST(CreerFeuilleNB($1), $3);}
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
  INIT_NOEUD(ARBRE_ABSTRAIT);
  yyparse();
  print_table(TABSYMB);
  codegenINIT();
  semantic(ARBRE_ABSTRAIT);
  codegen(ARBRE_ABSTRAIT);
  fclose(yyin);
  fclose(exefile);
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
