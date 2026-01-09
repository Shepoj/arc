# ARC - Algo RAM Compiler

ARC est un compilateur de langage Algorithmique vers Machine RAM. Il reste très sommaire et pourrait être grandement amélioré mais j'ai pas trop le temps (j'y reviendrai peut-être qui sait) 


# Arborescence
Les fichiers source se trouvent dans /src/, et sont liés aux fichiers dans /include/. Des fichiers de test sont présents dans /test/ et de la documentation plus précise se trouve dans /doc/.

## Ce que j'ai fait/pas fait

Certains trucs valent pas le coup d'être lus (les fichiers générés par flex et bison) : /src/parser.c , /src/lexer.c
Le reste a été codé par moi.

# Fonctionnement

Pour utiliser ARC, il faut d'abord exécuter le makefile (commande `make` à la racine du projet). Les programmes écrits en langage Algo doivent être compilés en utilisant la commande `./bin/arc [fichier algo] [fichier de sortie (optionnel)]`depuis la racine du projet. En cas d'absence de fichier de sortie, le code RAM sera écrit à la racine dans le fichier ram.txt.

## Structure du programme

Les programmes en Algo doivent être écrits sous la forme :

    MAIN()
	[declaration de variable]
	DEBUT
		[liste d'instructions]
	FIN

## Fonctionnalités

Les fonctionnalités implémentées sont :

 - Affectation de variable :

		a<-0;
	
 - Opérations arithmétiques :
 

		((6+1)*(2-1)/8)%6;
- Opérations logiques :

		1+2=3 ET 2!=3 OU NON 5<6;
- Boucles "tant que" :

		TQ item<=5 FAIRE
				item<-item+1;
		FINTQ
- Boucles "pour" :

		POUR i DE 1 A 5 FAIRE
				a<-a+1;
		FINPOUR

# Suite

Il aurait fallu que j'implémente les fonctions et les pointeurs mais par manque de temps, de courage, et d'énergie, j'ai décidé de me contenter d'une version édulcorée de ARC. L'analyse syntaxique des fonctions est effectuée, mais le code n'est pas généré.
