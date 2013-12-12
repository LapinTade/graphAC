/*
**********************************************************
*
* Programme : 	libliste.c
*
* ecrit par : 	Mariaux Cédric et Roze Nicolas
*
* resume : 		Décrit les fontions de la structure TypTache
*
* date : 		02/10/13
*
***********************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include "libliste.h"


/*
* Fonction : 	ajouterTache
*
* Parametres : 	ListeTaches *liste (parametre pointeur ListeTaches)
* 				int tache (parametre  entier)
*				int duree 
*
* Retour : 		ListeTaches
*
* Description : ajoute un element dans la liste chainee liste.
*
*/
ListeTaches ajouterTache(ListeTaches *liste, int tache, int duree){
	ListeTaches element;	/* Maillon creer a ajouter */
	
	element = (ListeTaches) malloc(sizeof(TypTache));
	element->tache = tache;
	element->dureeTache = duree;
	element->tacheSuivant = *liste;
	
	 //return element;
	
}



/*
* Fonction : 	ajouterTacheAfter
*
* Parametres : 	ListeTaches *liste (parametre pointeur ListeTaches)
* 				int tache (parametre  entier)
*				int duree 
*
* Retour : 		ListeTaches
*
* Description : ajoute un element à la fin de la liste chainee liste.
*
*/
ListeTaches ajouterTacheAfter(ListeTaches *liste, int tache, int duree){
	ListeTaches element;	/* Maillon creer a ajouter */
	ListeTaches element2;
	element = (ListeTaches) malloc(sizeof(TypTache));
	element2 = (ListeTaches) malloc(sizeof(TypTache));
	
	element = *liste;
	if(element->tache!=-1){
		while(element->tacheSuivant->tache != -1) {
			element = element->tacheSuivant;
		}	
		element2->tacheSuivant = element->tacheSuivant;
		element->tacheSuivant=element2;
		element2->tache = tache;
		element2->dureeTache = duree;
	}

	//element->tacheSuivant = *liste;
	
	return element;
	
}


/*
* Fonction : 	supprimerTache
*
* Parametres : 	ListeTaches liste (parametre pointeur ListeTaches)
* 				int tache (parametre  entier)
*
* Retour : 		ListeTaches
*
* Description : Supprime l'element tache dans la liste liste.
*
*/
ListeTaches supprimerTache(ListeTaches liste, int tache){
	ListeTaches 	precedent;	/* Maillon precedent */
	ListeTaches	prem;		/* Premier maillon */
	ListeTaches 	todelete;	/* Maillon a supprimer */
	int 			flag;		/* Drapeau permetant de savoir si on est sur 
								*  la tête de liste */
	
	flag = 0;
	precedent = (ListeTaches) malloc(sizeof(TypTache));
	prem = (ListeTaches) malloc(sizeof(TypTache));
	prem = liste;
	
	while (liste->tache != -1) {
		if (liste->tache == tache) {
			todelete = liste;
			if (flag == 1) {			/* On est pas sur la tete de liste */
				precedent->tacheSuivant=liste->tacheSuivant;
			}
			else {
				prem = liste->tacheSuivant;
			}
			free(todelete);
		}
		else {
			precedent = liste;
			flag = 1;
		}
		if (liste->tache != -1) {
			liste = liste->tacheSuivant;
		}
	}
	
	return prem;
}


/*
* Fonction : 	supprimerDependance
*
* Parametres : 	ListeTaches liste (parametre pointeur ListeTaches)
* 				int tache (parametre  entier)
*				int duree (parametre entier)
*
* Retour : 		ListeTaches
*
* Description : Supprime l'arrete de la liste chainée liste ayant pour numero 
*				tache et duree duree.
*
*/
ListeTaches supprimerDependance(ListeTaches liste, int tache, int duree){
	ListeTaches 	precedent;	/* Maillon precedent */
	ListeTaches	prem;		/* Premier maillon */
	ListeTaches 	todelete;	/* Maillon a supprimer */
	int 			flag;		/* Drapeau permetant de savoir si on est sur 
								*  la tête de liste */
	
	flag = 0;
	precedent = (ListeTaches) malloc(sizeof(TypTache));
	prem = (ListeTaches) malloc(sizeof(TypTache));
	prem = liste;
	
	
	while (liste->tache != -1) {
		if (liste->tache == tache && liste->dureeTache == duree) {
			todelete = liste;
			if (flag == 1) {			/* On est pas sur la tete de liste */
				precedent->tacheSuivant = liste->tacheSuivant;
			}
			else {
				prem = liste->tacheSuivant;
			}
			free(todelete);
		}
		else {
			precedent = liste;
			flag = 1;
		}
		if (liste->tache != -1) {
			liste = liste->tacheSuivant;
		}
	}
	return prem;
}


/*
* Fonction : 	afficher
*
* Parametres : 	ListeTaches liste (parametre ListeTaches)
* 				FILE *fichier (parametre  pointeur FILE)
*
* Retour : 		rien
*
* Description : Ecrit la description de la liste chainée liste dans le fichier 
*				fichier.
*
*/
void afficher(ListeTaches liste, FILE *file){	
	while (liste->tache != -1) {
	
		fprintf(file, "(%d/%d)", liste->tache, liste->dureeTache);
		if (liste->tacheSuivant->tache != -1) {
			fprintf(file, ", ");
        }
		liste = liste->tacheSuivant;
	}
    fprintf(file, "\n");
}
