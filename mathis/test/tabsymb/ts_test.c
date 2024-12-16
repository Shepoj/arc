#include "tabsymb.c"

int main(){
    ts tabs;
    ajouter_id(tabs, "toto");
    print_table(tabs);
    chercher_id(tabs, "toto");
    ajouter_id(tabs, "titi");
    ajouter_id(tabs, "tutu");
    print_table(tabs);
    ajouter_id(tabs, "tutu");
    chercher_id(tabs, "tutu");
}

