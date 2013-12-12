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
	projet->tacheProjet = malloc(sizeof(ListeTaches)*(nbTachesMax+2));
	projet->estOriente = 0;
	
	/*printf("Le projet est-il oriente ? (y=yes ||n=no) ");
	scanf("%c", &x);
	if (x == 'y' ) {
		projet->estOriente=1;
	}
	else {
		projet->estOriente=0;
	}*/
	projet->estOriente=1;
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
	int 	currentTacheProjet=0;	/* TacheProjet courant */
	int 	currentDureeTache; 	/* Duree du tache courant */
	char 	*tok;				/* Tokenisation de la ligne lu */
	char 	*firstDelim;		/* Premier separateur */
	char 	*secDelim;			/* Seconds separateurs */
	int		firstLine;
	int duree;
	firstLine=1;
	tmp = 1;
	firstDelim=", \n -";
	secDelim = "'";
	tok = NULL;
	nbLine = 0;
	fichier = fopen(urlFichierSource, "r");
	projet = (Projet) malloc(sizeof(TypProjet));
	projet->estOriente = 1;
	ListeTaches element = (ListeTaches) malloc(sizeof(TypTache));  
	if (fichier != NULL) {
	//compter le nbLine
		while (fgets(line, 128, fichier) != NULL) {
			nbLine++;
		}
		close(fichier);
		fichier = fopen(urlFichierSource, "r");
		nbLine-=2;
		projet=creation(nbLine);
		printf("nbline : %d\n", nbLine);
		nbLine=0;
		printf("nbline : %d\n", nbLine);
		while (fgets(line, 128, fichier) != NULL) {
			if (nbLine > 1) {
				//fprintf(stdout,line);
				tok = NULL;
				tmp = 1;
				
				// nom
				tok = strtok(line, firstDelim);
				char x = tok[0];
				
				currentTacheProjet = (int) x-'A';
				creationTacheProjet(projet, currentTacheProjet);
				
				 fprintf(stdout,"\n%d", currentTacheProjet);
				//Creer une libListe par ligne
				
				int nom = currentTacheProjet; 
				// Intitule;
				tok = strtok(NULL, firstDelim);
				char intitule[40]; // = del(tok, '\'');
				strcpy(intitule, tok);
				printf(" %s", intitule);
				
				while (tok != NULL) {
					tok = strtok(NULL, firstDelim);

					if(tok != NULL) {
						if(firstLine){
							fprintf(stdout," >Duree: %s < ", tok);
							char x = tok[0];
							duree = (int) x-'0';
							printf("NOM: %d\n", nom);
							printf("DUREE: %c\n", tok[0]);
							printf("DUREE: %d\n", duree);
							firstLine = 0;
							//projet->tacheProjet[nom]=ajouterTacheAfter(&projet->tacheProjet[nom], nom, duree);
						}else{
							fprintf(stdout," >Tache: %s < ", tok);
							char x = tok[0];
							int tache = (int) x-'A';							
							projet->tacheProjet[nom]=ajouterTache(&projet->tacheProjet[nom], tache, 0);
						}
					}			
				}
				firstLine = 1;
				
				//printf("***********");
				//afficher(element, stdout);
				//printf("***********");
				//projet->tacheProjet[nom]=element;
				
			}
			projet->tacheProjet[currentTacheProjet]=ajouterTache(&projet->tacheProjet[currentTacheProjet], currentTacheProjet, duree);
			nbLine++;
		}
	}
	//projet->nbMaxTaches=nbLine;
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

/*
* Fonction : 	creationInitFin
*
* Parametres : 	TypProjet *projet
*
* Retour : 		rien
*
* Description : Creer l'etat initial et final pondere a 0.
*
*/
void creationInitFin(TypProjet *projet){
	int i=0;
	int tabOccur[projet->nbMaxTaches];
	printf("Tache : %d\n", projet->nbMaxTaches);
	creationTacheProjet(projet, projet->nbMaxTaches);
	int tacheInit = projet->nbMaxTaches;
	projet->nbMaxTaches++;
	printf("Tache : %d\n", projet->nbMaxTaches);
	creationTacheProjet(projet, projet->nbMaxTaches);
	int tacheFin = projet->nbMaxTaches;
	projet->nbMaxTaches++;
	ListeTaches element;
	element = (ListeTaches) malloc(sizeof(TypTache));
	
	//Creer tache pour init et fin avec intitule
	projet->tacheProjet[tacheInit]=ajouterTache(&projet->tacheProjet[tacheInit], tacheInit, 0);
	projet->tacheProjet[tacheFin]=ajouterTache(&projet->tacheProjet[tacheFin], tacheFin, 0);
	
	//Parcourir la liste d'adjacence et ajouter le noeud init en dependance au noeud qui n'ont pas de dependance
	
	for(i = 0; i < projet->nbMaxTaches-2; i++) {
		if(projet->tacheProjet[i]->tacheSuivant->tache == -1) {
			projet->tacheProjet[i]=ajouterTacheAfter(&projet->tacheProjet[i], tacheInit, 0);
		}
	}
	for(i = 0; i < projet->nbMaxTaches-2; i++){
		tabOccur[i]=0;
	}
	
	for(i = 0; i < projet->nbMaxTaches-2; i++){
		element = projet->tacheProjet[i];
		while(element->tache != -1){
			tabOccur[element->tache]++;
			element=element->tacheSuivant;
		}
	}
	for(i = 0; i < projet->nbMaxTaches-2; i++){
		if(tabOccur[i] == 1){
			projet->tacheProjet[tacheFin]=ajouterTacheAfter(&projet->tacheProjet[tacheFin], i, 0);
		}
	}
	
}

void recupDuree(TypProjet *projet){
	int i=0;
	int tabDuree[projet->nbMaxTaches];
	ListeTaches element;
	element = (ListeTaches) malloc(sizeof(TypTache));
	printf("YOYOYOOY");
	for(i = 0; i < projet->nbMaxTaches; i++){
		tabDuree[i]=0;
	}
	
	for(i = 0; i < projet->nbMaxTaches; i++){
		while(element->tache != -1){
			if(element->dureeTache > 0){
				tabDuree[element->tache]=element->dureeTache;
			}
		}
	}
	for(i = 0; i < projet->nbMaxTaches; i++){
		printf("[%d] => %d\n", i, tabDuree[i]);
	}

}
