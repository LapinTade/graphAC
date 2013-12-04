/*
**********************************************************
*
* Programme : 	libprojet.c
*
* ecrit par : 	Mariaux Cédric et Roze Nicolas
*
* resume : 		Décrit les fontions de la structure TypProjet
*
* date : 		02/10/13
*
***********************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libprojet.h"


/*
* Fonction : 	creation
*
* Parametres :	int nbTachesMax (parametre entier)
*
* Retour : 		le projet créé
*
* Description : Créé un projet vide de nbTachesMax tache(s).
*
*/
Projet creation(int nbTachesMax){
	int 	i;		/* Iterateur */
	Projet 	projet;	/* Pointeur sur la struct Projet */
	char 	x;		/* Reponse utilisateur */
	
	projet = (Projet) malloc(sizeof(TypProjet));
	projet->tacheProjet = malloc(sizeof(ListeTaches)*nbTachesMax);
	projet->estOriente = 0;
	
	printf("Le projet est-il oriente ? (y=yes ||n=no) ");
	scanf("%c", &x);
	if (x == 'y' ) {
		projet->estOriente=1;
	}
	else {
		projet->estOriente=0;
	}
	projet->nbMaxTaches = nbTachesMax;

	return projet;
}


/*
* Fonction : 	lecture
*
* Parametres : 	char *urlFichierSource (parametre char*)
*
* Retour : 		Le projet lu
*
* Description : Lis le projet contenu dans le fichier dont l'url est passé
* 				en paramètre et retourne le projet correspondant.
*
*/
Projet lecture(char *urlFichierSource){
	FILE	*fichier;			/* Fichier de lecture */
	Projet 	projet;				/* Projet correspondant au fichier lu */
	int 	i;					/* Iterateur */
	char 	line[128];			/* Ligne lu dans le fichier */
	int 	nbLine;				/* Nombre de ligne */
	int 	tmp;				/* Entier temporaire */
	int 	nbTachesMax;		/* Nombre de tache max du projet */
	int 	currentTache;		/* Tache courant */
	int 	currentTacheProjet;	/* TacheProjet courant */
	int 	currentDureeTache; 	/* Duree du tache courant */
	char 	*tok;				/* Tokenisation de la ligne lu */
	char 	*firstDelim;		/* Premier separateur */
	char 	*secDelim;			/* Seconds separateurs */
	
	tmp = 1;
	firstDelim=", \n -";
	secDelim = "'";
	tok = NULL;
	nbLine = 0;
	fichier = fopen(urlFichierSource, "r");
	projet = (Projet) malloc(sizeof(TypProjet));
	projet->estOriente = 1;

	if (fichier != NULL) {
	//compter le nbLine
		/*
		while (fgets(line, 128, fichier) != NULL) {
			nbLine++;
		}
		projet->nbMaxTaches=nbLine;
		//*/
		while (fgets(line, 128, fichier) != NULL) {
			if (nbLine > 1) {
				tok = NULL;
				tmp = 1;

				//creationTacheProjet(projet, currentTacheProjet);
				
				// nom
				tok = strtok(line, firstDelim);
				char x = tok[0];
				currentTacheProjet = (int) x-'A';
				fprintf(stdout,"\n%d", currentTacheProjet);
				//Creer une libListe par ligne
				
				// Intitule;
				tok = strtok(NULL, firstDelim);
				tok=del(tok, '\'');
				fprintf(stdout," %s", tok);

				//*
				while (tok != NULL) {
					tok = strtok(NULL, firstDelim);
					if(tok != NULL) {
						fprintf(stdout," %s", tok);
					}
				}
				//*/
			}
			nbLine++;
		}
	}
	projet->nbMaxTaches=nbLine;
	fclose(fichier);
	return projet;
}


/*
* Fonction : 	creationTache
*
* Parametres : 	Projet projet (parametre Projet)
* 				int tache (parametre entier)
*
* Retour : 		rien
*
* Description : Créé un tache sans tache dans le projet donné en paramètre
*				et ayant pour tache tache.
*
*/
void creationTacheProjet(Projet projet, int tache){
		projet->tacheProjet[tache] = (ListeTaches) malloc(sizeof(TypTache));
		projet->tacheProjet[tache]->tache = -1;
		projet->tacheProjet[tache]->dureeTache = 0;
}


/*
* Fonction : 	insertionTache
*
* Parametres : 	TypProjet *projet (parametre pointeur TypProjet)
* 				ListeTaches tache (parametre  liste chainee tache)
*
* Retour : 		rien
*
* Description : Insert un tache dans le projet passé en paramètre.
*
*/
void insertionTacheProjet(TypProjet *projet, ListeTaches tache){
	int i = 0;
	
	while (projet->tacheProjet[i]->tache != -1) {
		i++;
	}
	projet->tacheProjet[i] = tache;

}


/*
* Fonction : 	insertionArrete
*
* Parametres : 	Projet projet (parametre Projet)
* 				int tache1 (parametre  entier)
* 				int tache2 (parametre  entier)
* 				int dureeTache (parametre  entier)
*
* Retour : 		rien
*
* Description : Insert une arrete.
*
*/
void insertionArrete(Projet projet, int tache1, int tache2, int dureeTache){
	projet->tacheProjet[tache1] = ajouterTache(&projet->tacheProjet[tache1], tache2, 
												dureeTache);
	projet->tacheProjet[tache2] = ajouterTache(&projet->tacheProjet[tache2], tache1, 
												dureeTache);
}


/*
* Fonction : 	suppressionTache
*
* Parametres : 	Projet projet (parametre Projet)
* 				int tache (parametre  entier)
*
* Retour : 		rien
*
* Description : Supprime un tache.
*
*/
void suppressionTacheProjet(Projet projet, int tache){
    int i;	/* Iterateur */
    
    free(projet->tacheProjet[tache - 1]);
    projet->tacheProjet[tache - 1] = NULL;
    //Parcours le projet pour suppr le tache dans toute les liaison
    for (i = 0; i < projet->nbMaxTaches; ++i) {
        if (projet->tacheProjet[i] != NULL && projet->tacheProjet[i]->tache != -1) {
            projet->tacheProjet[i] = supprimerTache(projet->tacheProjet[i], tache);
        }
    }
}


/*
* Fonction : 	suppressionArrete
*
* Parametres : 	Projet projet (parametre Projet)
* 				int tache1 (parametre  entier)
* 				int tache2 (parametre  entier)
* 				int duree (parametre  entier)
*
* Retour : 		rien
*
* Description : Supprime une arrete avec le duree duree.
*
*/
void suppressionDependance(Projet projet, int tache1, int tache2, int duree){
    projet->tacheProjet[tache1] = supprimerDependance(projet->tacheProjet[tache1 - 1], 
    											tache2, duree);
}


/*
* Fonction : 	affichage
*
* Parametres : 	Projet projet (parametre Projet)
* 				FILE *fichier (parametre  pointeur FILE)
*
* Retour : 		rien
*
* Description : Ecrit la description du projet projet dans le fichier fichier.
*
*/
void affichage(Projet projet, FILE *fichier){
	int i;	/* Iterateur */
	
	fprintf(fichier, "# nombre maximum de taches\n");
	fprintf(fichier, "%i\n", projet->nbMaxTaches);
	fprintf(fichier, "# taches : taches\n");

	for (i = 0; i < projet->nbMaxTaches; ++i) {
		if (projet->tacheProjet[i] != NULL) {
			fprintf(fichier, "%i : ", i + 1);
			afficher(projet->tacheProjet[i], fichier);
		}
	}
}


/*
* Fonction : 	sauvegarde
*
* Parametres : 	Projet projet (parametre Projet)
* 				char *urlFichierDest (parametre  pointeur char)
*
* Retour : 		rien
*
* Description : Sauvegarde la description du projet dans le fichier passe en 
*				paramètre.
*
*/
void sauvegarde(Projet projet, char *urlFichierDest){
	FILE *fichier;	/* Fichier a ouvrir */
	fichier = fopen(urlFichierDest, "w");
	affichage(projet, fichier);
	fclose(fichier);
}

/*
* Fonction : 	
*
* Parametres : 	
*
* Retour : 		rien
*
* Description : 
*
*/
char* del(char str[], char ch){
	int i;
	int j=0;
	int size;
	char ch1;
	char str1[10];

	size=strlen(str);

	for(i=0;i<size;i++)
		{
		if(str[i] != ch)
		   {
		   ch1 = str[i];
		   str1[j] = ch1;
		   j++;
		   }
		}


	return str1;
}
