
struct tabsymb{
    char id[32];
    int adresse;
};
typedef struct tabsymb ts[128];

int chercher_id(ts tab_symb, char *id);

int ajouter_id(ts tab_symb, char *id);

void print_table(ts tab_symb);