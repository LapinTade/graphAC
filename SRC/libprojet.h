/*
**********************************************************
*
* Programme : 	TypProjet.h
*
* ecrit par : 	Mariaux Cédric et Roze Nicolas
*
* resume : 		Décrit la structure TypProjet
*
* date : 		02/10/13
*
***********************************************************
*/
//#ifndef TypProjet

//#define TypProjet
#include <stdio.h>
#include <stdlib.h>
#include "libliste.h"


typedef struct TypProjet TypProjet;
struct TypProjet {
	int nbMaxTaches;		/* Nombre de tacheProjet maximum */
	int estOriente;			/* 0 si le projet est pas oriente, 1 si oui*/
	ListeTaches *tacheProjet;	/* Liste des tacheProjets taches */
};

typedef TypProjet *Projet;

Projet 	creation(int nbTachesMax);
Projet 	lecture(char *urlFichierSource);
void 	creationTacheProjet(Projet projet, int tacheProjet);
void 	insertionTacheProjet(TypProjet *projet, ListeTaches tache);
void 	insertionDependance(Projet projet, int tache1, int tache2, int dureeTache);
void 	suppressionTacheProjet(Projet projet, int tacheProjet);
void 	suppressionDependance(Projet projet, int tache1, int tache2, int duree);
void 	affichage(Projet projet, FILE *file);
void 	sauvegarde(Projet projet, char* urlFichierDest);
char* 	del(char str[], char ch);
void 	creationInitFin(TypProjet *projet);
void 	recupDuree(Projet projet);
int 	dureePlusCourte(Projet projet, int debut, int fin);
int 	dureePlusGrande(Projet projet, int debut, int fin);
int sommeDuree(Projet projet);

//#endif
