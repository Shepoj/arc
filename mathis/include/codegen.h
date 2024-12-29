#ifndef CODE_H
#define CODE_H
#include "ast.h"
#include "tabsymb.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



extern FILE * out; 

#define __READ__ 1
#define __WRITE__ 2
#define __ADD__ 3
#define __SUB__ 4
#define __MUL__ 5
#define __DIV__ 6
#define __MOD__ 7
#define __JUMZ__ 8
#define __JUMP__ 9
#define __JUML__ 10
#define __JUMG__ 11
#define __LOAD__ 12
#define __STORE__ 13
#define __INC__ 14
#define __DEC__ 15
#define __STOP__ 16
#define __NOP__ 17


#define __PREMIERE_ADR__ 10
#define __REG_TMP__ 1
#define __REG_TMP2__ 2

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