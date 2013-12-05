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

typedef enum { CHARGER = 0, CREER = 1, AFFICHER = 2, AJOUTSOMMET = 3,
				AJOUTVOISIN = 4, SUPPRSOMMET = 5, SUPPRVOISIN = 6, 
				SUPPRARRETE = 7, ENREGISTRER = 8 } CHOIX; /* Enumeration des 
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
        printf("\t [1] Creer un automate\n");
        printf("\t [2] Afficher l'automate\n");
        printf("\t [3] Ajouter un tacheProjet\n");
        printf("\t [4] Ajouter un tache\n");
        printf("\t [5] Supprimer un tacheProjet\n");
        printf("\t [6] Supprimer un tache\n");
		printf("\t [7] Supprimer une arrete\n");
        printf("\t [8] Enregistrer l'automate\n");

        scanf( "%d", &res);
        flush();

        switch (res) {
        case CHARGER :
            printf("Entrez le chemin d'accès au fichier a charger : ");
            scanf( "%s", nomFichier);
            projet = lecture(nomFichier);
			flush();
        	break;
        case CREER :
            printf("Entrez le nombre de tacheProjet : ");
            scanf( "%d", &nbTacheProjet);
            projet = creation(nbTacheProjet);
            flush();
        	break;
        case AFFICHER :
            affichage(projet, stdout);
        break;
            case AJOUTSOMMET :
            printf("Entrez le numero de tacheProjet : ");
            scanf( "%d", &indice);
            flush();
            creationTacheProjet(projet, indice - 1);
        	break;
        case AJOUTVOISIN :
            printf("Entrez le numero de tacheProjet : ");
            scanf( "%d", &indice);
            flush();
            printf("Entrez le numero de tacheProjet du tache : ");
            scanf( "%d", &tache);
            flush();
            printf("Entrez le duree : ");
            scanf( "%d", &duree);
            flush();
            projet->tacheProjet[indice - 1] = ajouterTache(
            									&projet->tacheProjet[indice - 1], 
            									tache, duree);
        	break;
        case SUPPRSOMMET :
            printf("Entrez le numero de tacheProjet : ");
            scanf( "%d", &indice);
            flush();
            suppressionTacheProjet(projet, indice);
        	break;
        case SUPPRVOISIN :
            printf("Entrez le numero de tacheProjet : ");
            scanf( "%d", &indice);
            flush();
            printf("Entrez le numero de tacheProjet du tache : ");
            scanf( "%d", &tache);
            flush();
            projet->tacheProjet[indice - 1] = supprimerTache(
            									projet->tacheProjet[indice - 1], 
            									tache);
        	break;
        case SUPPRARRETE :
            printf("Entrez le numero de tacheProjet : ");
            scanf( "%d", &indice);
            flush();
            printf("Entrez le numero de tacheProjet du tache : ");
            scanf( "%d", &tache);
            flush();
            printf("Entrez le duree : ");
            scanf( "%d", &duree);
            flush();
            suppressionDependance(projet, indice, tache, duree);
        	break;
        case ENREGISTRER :
            printf("Entrez le nom du nomFichier de sauvegarde : ");
            scanf("%s", nomFichier);
            flush();
            fichier = fopen(nomFichier, "w");
            affichage(projet, fichier);
            fclose(fichier);
        	break;
        default : 
        	printf("Veuillez entrer un chiffre entre 0 et 8.\n");
        	break;
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
    //menu();
    Projet 	projet;			/* Projet creer pendant l'interaction utilisateur */
    //FILE * file = fopen("save.txt", "r");
    projet = lecture("save.txt");
    affichage(projet, stdout);
    
    	int i;	/* Iterateur */
	
	fprintf(stdout, "\n\n# nombre maximum de taches\n");
	fprintf(stdout, "%i\n", projet->nbMaxTaches);
	fprintf(stdout, "# taches : taches\n");

	for (i = 0; i < projet->nbMaxTaches; ++i) {
		if (projet->tacheProjet[i] != NULL) {
			fprintf(stdout, "%i : ", i + 1);
			afficher(projet->tacheProjet[i], stdout);
		}else{
			fprintf(stdout, "projet->tacheProjet[%d] == NULL\n", i);
		}
	}
	flush();
    
    return 0;
}
