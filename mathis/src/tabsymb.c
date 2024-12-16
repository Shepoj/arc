#include "tabsymb.h"
#include <string.h>
#include <stdio.h>

int mem_res = 0;

int chercher_id(ts tab_symb, char *id) { // Retourne la case ou se trouve id et -1 si absent
    for (int i = 0 ; i < 128 ; i++){
        if (strcmp(id, tab_symb[i].id) == 0)
            return tab_symb[i].adresse;
    }
    return -1;
}

int ajouter_id(ts tab_symb, char *id) { // Ajouter l'id a la table si absent et renvoie la case en question et -1 si la table et pleine
    if (chercher_id(tab_symb, id) == -1) {
        int i;
        for (i = 0 ; i < mem_res ; i++);
        if (mem_res < 128){
            strcpy(tab_symb[i].id, id);
            tab_symb[i].adresse = mem_res;
            mem_res++;
        }
        else{
            printf("Table de Symbole pleine");
            return -1;
        }
    }
    else
        printf("Warning : le symbole %s et deja présente a l'adresse %d\n", id, chercher_id(tab_symb, id));
    return 0;
}

void print_table(ts tab_symb) {
    printf("\n+------------------------------------------+\n");
    printf("|             Table de Symbole             |\n");
    printf("+----------------------------------+-------+\n");
    printf("|                ID                |  ADR  |\n");
    printf("+----------------------------------+-------+\n");
    for(int i = 0 ; i < mem_res; i++){
        printf("| %32s |  %3d  |\n", tab_symb[i].id, tab_symb[i].adresse);
    }
    printf("+----------------------------------+-------+\n\n");
}
