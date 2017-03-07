/**
 *  Ficher d'entete du programme Tic-RAC-Toe.
 *  Auteur : Julio Cesar Torres dos Santos 
 *  Enseignant: Walid Boulabiar 
 *  Date : 03 mars 2017
 *  Fournir les interfaces et les initialisations de variables pour les 
 *  programmes Tic-RAC-Toe.c et Test-RAC-Toe. 
 */ 

#define TAILLE_MAX_FICH 21
#define JOUEUR1 'X'
#define JOUEUR2 'O'

/**
* Declaration des variables globales 
*/ 
	//Matrice de jeu
	char matrix[3][3];

	//Variable auxiliaire d'écriture du jeu
	char jeu[TAILLE_MAX_FICH]; 

	//Le joueur qui detient le tour de jouer à ce moment. 
	char tour = 'X';

	// Quantité de coups joués 
	int cont_coup = 0; 


/** 
* Declaration des fonctions du programme 
*/

//Fonction obligatoire - affiche la grille sur l'ecran 
void afficher_grille(); 

//Fonction obligatoire - demande aux joueurs de faire leur choix
void jouer_tour(); 

//Fonction obligatoire. Vérifie l'état du jeu. 
char verifier_etat(); 

/**
* Autres fonctions 
*/ 

//Fonction qui initialise les valeurs de la matrice
void init_matrice(); 

//Fonctions de lecture de fichier
FILE* ouvre_fich(char*, int); 
void lire_jeu(char*); 
char* traduire(int); 
void sortir();

void test_ticRACToe(); 
void test_routine();