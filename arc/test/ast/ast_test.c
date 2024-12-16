#include "ast.h"

int main(void){
  ast * p1 = CreerFeuilleNB(1);
  ast * p2 = CreerFeuilleNB(2);
  ast * p3 = CreerFeuilleNB(3);
  
  ast * o2 = CreerNoeudOP('*',p1,p2);
  ast * o1 = CreerNoeudOP('+',o2,p3);
  
  
  PrintAst(o1);

  FreeAst(o1);

  return 0;
}


