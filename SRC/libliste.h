/*
**********************************************************
*
* Programme : 	libliste.h
*
* ecrit par : 	Mariaux Cédric et Roze Nicolas
*
* resume : 		Décrit la structure TypTache
*
* date : 		20/11/13
*
***********************************************************
*/

//#ifndef TypTache

//#define TypTache

typedef struct TypTache TypTache;
struct TypTache{
	int tache;					/* Nom de la tache */
	int dureeTache;			/* Duree de la tache */
	char* intitule;				/* Intitule de la tache */
	TypTache* tacheSuivant;	/* Liste des taches dependante de cette tache */
};
	
typedef TypTache* ListeTaches;

ListeTaches 	ajouterTache(ListeTaches *tache, int sommet, int poid);
ListeTaches 	supprimerTache(ListeTaches tache, int sommet);
ListeTaches 	supprimerDependance(ListeTaches tache, int sommet, int poids);
void 			afficher(ListeTaches tache, FILE* file);



//#endif
