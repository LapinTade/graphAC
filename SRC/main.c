/*
**********************************************************
*
* Programme : 	main.c
*
* ecrit par : 	Mariaux Cédric et Roze Nicolas
*
* resume : 		Fichier principal
*
* date : 		02/10/13
*
***********************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include "libprojet.h"

typedef enum { CHARGER = 0, AFFICHER = 1, ENREGISTRER = 2, AFFICHERDATE = 3, AFFICHERCHEMIN = 4 } CHOIX; /* Enumeration des 
															choix utilisateurs
															 pour le menu */


/*
* Fonction : 	flush
*
* Parametres : 	rien
*
* Retour : 		rien
*
* Description : Permet l'utilisation de scanf
*
*/
void flush(){
	while(getchar() != '\n')
		continue;
}


/*
* Fonction : 	menu
*
* Parametres : 	rien
*
* Retour : 		rien
*
* Description : Menu principal permetant d'executer la librairie de projets.
*
*/
void menu() {
	char 	nomFichier[50];	/* Nom de fichier choisi par l'utilisateur */
    char 	c;				/* Reponse utilisateur pour continuer ou pas */
    int 	res;			/* Reponse utilisateur pour le choix primaire */
    int		nbTacheProjet;		/* Reponse utilisateur pour le nombre de tacheProjet */
    int		indice;			/* Reponse utilisateur pour les indices tacheProjet */
    int 	tache;			/* Reponse utilisateur pour le tache choisi */
    int		duree;			/* Reponse utilisateur pour le duree du tache */
    Projet 	projet;			/* Projet creer pendant l'interaction utilisateur */
   	FILE 	*fichier;		/* Fichier ouvert par l'utilisateur */

    while (c != 'n') {
        printf("\t [0] Charger un projet \n");
        printf("\t [1] Afficher le graphe\n");
        printf("\t [2] Enregistrer le graphe\n");
        printf("\t [3] Afficher les dates au plus courts et au plus tard du chantier\n");
        printf("\t [4] Afficher les chemins critiques\n");

        scanf( "%d", &res);
        flush();

        switch (res) {
        case CHARGER :
            printf("Entrez le chemin d'accès au fichier a charger : ");
            scanf( "%s", nomFichier);
            projet = lecture(nomFichier);
			creationInitFin(projet);
			recupDuree(projet);
			printf("Fichier de chantier charger avec succes.\n");
			flush();
        	break;
        case AFFICHER :
            affichage(projet, stdout);
        	break;
        case ENREGISTRER :
            printf("Entrez le nom du nom du fichier de sauvegarde : ");
            scanf("%s", nomFichier);
            flush();
            fichier = fopen(nomFichier, "w");
            affichage(projet, fichier);
            fclose(fichier);
            printf("Chantier enregistre dans : %s", nomFichier);
        break;
            case AFFICHERDATE :
            printf("La date au plus court du chantier est : %d \n",
            dureePlusGrande(projet, 
							projet->nbMaxTaches-2,
							projet->tacheProjet[projet->nbMaxTaches-1]
								->tacheSuivant->tache
							));
            printf("La date au plus tard du chantier est : %d \n", sommeDuree(projet));
        	break;
        case AFFICHERCHEMIN :      
            printf("Le chemin le plus court du chantier est : ");
            //tableau d'entier a afficher
            printf("\n");
            printf("Duree du chemin le plus court : %d\n", 
                        dureePlusCourte(projet,
							projet->nbMaxTaches-2,
							projet->tacheProjet[projet->nbMaxTaches-1]
								->tacheSuivant->tache
							));
							
            printf("Le chemin le plus long du chantier est : ");
            //tableau d'entier a afficher
            printf("\n");
            printf("Duree du chemin le plus long : %d\n", 
            dureePlusGrande(projet,
							projet->nbMaxTaches-2,
							projet->tacheProjet[projet->nbMaxTaches-1]
								->tacheSuivant->tache
							));
        	break;
        	default : printf("Veuillez saisir un chiffre correct\n");
        }

        printf("\nVoulez vous continuer ? (o pour oui / n pour non)\n");
        c = getchar();
    }
}


/*
* Fonction : 	main
*
* Parametres : 	rien
*
* Retour : 		Valeur de sortie
*
* Description : Main du programme.
*
*/
int main() {
    menu();

    //menu();
    int i;
    int* tabdPC = (int*) malloc(sizeof(int));
    int* tabdPG = (int*) malloc(sizeof(int));
    Projet 	projet;			/* Projet creer pendant l'interaction utilisateur */
    //FILE * file = fopen("save.txt", "r");
    printf("\n=========================\n\n--------LECTURE---------------\n");
    projet = lecture("save.txt");
    
    printf("\n=========================\n\n--------AFFICHAGE-------------\n");
    affichage(projet, stdout);
    
    printf("\n=========================\n\n--------INITFIN---------------\n");
    creationInitFin(projet);
    
    printf("\n=========================\n\n--------AFFICHAGE-------------\n");
    affichage(projet, stdout);
    
    printf("\n=========================\n\n--------MIN-------------------\n");
    int min = dureePlusCourte(projet,11,10);
    printf("Plus court chemin : %d", min);
    
    printf("\n=========================\n\n--------MAX-------------------\n");
    int max = dureePlusGrande(projet,11,10);
    printf("Plus long chemin: %d", max);
    
    printf("\n=========================\n\n--------MAX-------------------\n");
    int min2 = dureeProjetPlusCourt(projet,11,10);
    printf("Date au plus court: %d", min2);
    
    printf("\n=========================\n\n--------MAX-------------------\n");
    int max2 = dureeProjetPlusLong(projet,11,10);
    printf("Date au plus long: %d", max2);
    
    ListeTaches test = (ListeTaches) malloc(projet->nbMaxTaches * sizeof(TypTache));
    cheminCritique(projet, 11, 10, test);

    return 0;
}
