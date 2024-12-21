#ifndef CODE_H
#define CODE_H
#include "ast.h"
#include "tabsymb.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



extern FILE * out; 



#define __PREMIERE_ADR__ 9
#define __REG_TMP__ 1

#define EMPILER(){\
    fprintf(out,"STORE %d\n",PILE++);\
    nb_inst++;\
}

#define DEPILER(){\
    fprintf(out,"LOAD %d\n",--PILE);\
    nb_inst++;\
}


void codegen(ast* p);

void codegenINIT();

#endif