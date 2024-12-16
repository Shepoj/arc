#ifndef CODE_H
#define CODE_H
#include "ast.h"
#include "tabsymb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __PREMIERE_ADR__ 9
#define EMPILER(){\
    fprintf(out,"STORE %d\n",PILE++);\
}




extern FILE * out; 

#endif