
 /*****************************************************************************
 *                         T i c  -  R A C  -  T o e 
 ******************************************************************************
 *  Ficher source du programme Tic-RAC-Toe.
 *  Auteur : Julio Cesar Torres dos Santos 
 *  Enseignant: Walid Boulabiar
 *  Date : 03 mars 2017
 *  Instructions: 
 * 
 *  Dans le jeu il y a deux joueurs :  X et O. Le jeu demande aux joueurs  
 *  joueur d'indiquer la case qu'ils veulent jouer, de 0 à 8, en attribuant 
 *  les caractères X et O à chaque joueur. 
 * 
 *  Les joueurs jouent leurs coups sequentiellement; si le joueur indique une 
 *  case invalide, le jeu lui demande de reessayer; si le joueur indique une 
 *  case déjà prise, il perd son tour. 
 * 
 *  Gagne ce qui complète une ligne, colonne ou diagonale avec ses caractères. 
 * 
 *  Si on veut continuer un jeu enregistré préalablement, on doit fournir le 
 *  nom du fichier après la commande du jeu: 
 *      ./ticRACToe partie.txt
 * 
 *  Si on veut jouer un noveau jeu, on appele simplement le programme :
 *      ./ticRACToe
 ******************************************************************************
 * Compilation: 
 *   Sous Linux (Debian) ou Unix (BSD MacIntosh): 
 * 
 *      gcc ticRACToe.c ticRACToe_func.c -o ticRACToe -Wall 
 * 
 ******************************************************************************
 */ 

/**
 * Include des librairies utilisés par le programme. 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "ticRACtoe.h"

/**
 * Fonction principale du programme du jeu. 
 */ 
int main(int argc, char *argv[]){

	test_ticRACToe(); 

	exit(1);

	//Caractère de controle pour verifier la fin du jeu. 
	char fin = ' '; 

	// Vérifie si un fichier de jeu enregistré a été informé. 
	// Si c'est le cas, lire le contenu du fichier. 
	if(argc > 1){
		printf("%s\n", argv[1]);

		if(strcmp(argv[1],"t")){
			printf("Contition de test");
			// test_ticRACToe();
		}else {
			lire_jeu(argv[1]); 
		}
	}

	// Initialise le contenu de la matrice de jeu. 
	init_matrice(); 

	do{
		// Affiche la grille avec les valeurs correspondents à la matrice de jeu
		afficher_grille(); 

		// Demande à une jouer de donner son coup.
		jouer_tour(); 

		// Vérifie l'état du jeu
		fin = verifier_etat(); 

	}while(fin == ' '); 

}

/*
 * Affiche la grille selon ce qui est enregistré dans la matrice du jeu.
 * Fonction obligatoire.  
 */ 
void afficher_grille(){
		
	int i; 

	printf("\n\n\n");
	for(i =0; i < 3; i++){
		printf(" %c | %c | %c ", matrix[i][0], matrix[i][1], matrix[i][2]); 
		if(i != 2) 
			printf("\n---|---|---\n"); 
	}
	printf("\n\n\n\n"); 
}

/*
 * Initialise la matrice avec les valeurs correspondants. 
 * Si c'est un jeu enregistré et les donnés sont valides (19 caractères), 
 * on lit le contenu du fichier et l'attribue à la matrice de jeu; 
 * si c'est un nouveau jeu, on initialise la matrice de jeu à blanc. 
 */ 
void init_matrice(){
	
	if(strlen(jeu)== 19){

		//Jeu lu du fichier. Faire la copie des positions de données du fichier  
		matrix[0][0] = (jeu[0]  == 'B' ? '0' : jeu[0]); 
		matrix[0][1] = (jeu[2]  == 'B' ? '1' : jeu[2]); 
		matrix[0][2] = (jeu[4]  == 'B' ? '2' : jeu[4]); 
		matrix[1][0] = (jeu[6]  == 'B' ? '3' : jeu[6]); 
		matrix[1][1] = (jeu[8]  == 'B' ? '4' : jeu[8]); 
		matrix[1][2] = (jeu[10] == 'B' ? '5' : jeu[10]); 
		matrix[2][0] = (jeu[12] == 'B' ? '6' : jeu[12]); 
		matrix[2][1] = (jeu[14] == 'B' ? '7' : jeu[14]); 
		matrix[2][2] = (jeu[16] == 'B' ? '8' : jeu[16]);  

		//Qui est le joueur actuel 
		tour = jeu[18];
		printf("C'est le tour de  %c\n\n", tour); 
	}else{
		//Initialise les valeurs vides... 
		int i, j, cont = 0; 
		char pos[2];
		
		for(i=0; i < 3; i++){
			for(j=0; j < 3; j++){ 
				sprintf(pos, "%d", cont);
				matrix[i][j] = pos[0]; 
				cont++; 
			}
			printf("\n");
		} 
	}
}

/**
 * Fonction obligatoire. 
 * Jouer le tour. Demande au joueur du tour de jouer son coup. 
 * Si il joue une option invalide (une lettre, par example), 
 * le jeu lui de mande de jouer à nouveau. Par contre, si il joue 
 * une case qui est déjà prise, il perd son tour. 
 */
void jouer_tour(){

	char carre;
	int icarre;
	char coord[3];  

	// Donne des instructions au joueur; demande l'entrée de son choix. 
	printf("C'est le tour du joueur %c\n", tour); 
	printf("Saisissez votre choix de carré entre <0> et <8>. \nPour quitter le jeu, faites <9>. \nCHOIX:"); 
	
	scanf("%s", &carre); 	
	icarre = carre -48; 

	// Si le valeur rentré est invalide, informe le joueur et fait escape 
	// pour lui permettre de jouer à nouveau. 
	if(icarre < 0 || icarre > 9){
		printf("\n\n *** ATTENTION *** ");
		printf("Option invalide. Saisissez à nouveau, svp");
		printf("*****");
		return; 
	}
		
	printf("Choix faite : %d\n", icarre);

	// Tester la condition de sortie du jeu (9); si carré valide, 
	// traduire le numéro en coordonés de la matrice de jeu. 
	if(icarre == 9){
		sortir(); 
	}else{
		strcpy(coord,traduire(icarre)); 	
	}
	
	// Convert les valeurs  ASCII reçus en integers 
	int x, y; 
	x = (coord[0]-48); 
	y = (coord[1]-48); 

	// Si la position est déjà occupé, informer au joueur qu'il a perdu son tour; 
	if(matrix[x][y] == 'X' || matrix[x][y] == 'O'){
		printf("Position occupé. Tu as perdu ton tour! \n\n"); 
	}else {
		// Enregistre le coup joué dans la matrice de jeu
		matrix[x][y] = tour; 
		printf("Tour du joueur %c\n", tour);
		cont_coup++; 
	}
	// Change le joueur qui a le tour courant. 
	tour = (tour == 'X' ? 'O' : 'X'); 
}

/**
 *  Vérifie l'état du jeu: si partie courant, ou gagné. 
 */ 
char verifier_etat(){
	int i; 

	// Vérification des coups joués 
	if(cont_coup >= 9){
		printf("===== La partie est nulle! =====");
		afficher_grille(); 
		return 'N';
	}

	// Vérification des lignes  
	for(i=0; i < 3; i++) { 
		if((matrix[i][0] == matrix[i][1]) && (matrix[i][0] == matrix[i][2])){
			printf("===== Le joueur %c est gagnant par la ligne.===== \n", matrix[i][0]);
			afficher_grille();
			return matrix[i][0]; 
		}
	}

	// Vérification des colonnes 
	for(i=0; i < 3; i++){
		if((matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i])){
			printf("===== Le joueur %c est gagnant par la colonne.===== \n", matrix[0][i]);
			afficher_grille();
			return matrix[0][i]; 
		}
	}

	// Vérification de la diagonale principale 
	if((matrix[0][0] == matrix[1][1]) && (matrix[0][0] == matrix[2][2])){
		printf("===== Le joueur %c est gagnant par la diagonale principale.===== \n", matrix[0][0]);
		afficher_grille();
		return matrix[0][0]; 
	}

	// Vérfication de la diagonale inverse 
	if((matrix[0][2] == matrix[1][1]) && (matrix[0][2] == matrix[2][0])){
		printf("===== Le joureur %c est gagnant par la diagonale inverse.===== \n", matrix[0][2]);
		afficher_grille();
		return matrix[0][2]; 
	}

	return ' '; 
}


/*
 * Ouvre le fichier de jeu, en mode de lecture ou d'écriture, selon le paramètre opt. 
 * L'opt 1 ouvre le fichier en mode de lecture; le mode 2 ouvre le fichier en mode 
 * d'écriture, qui écrase les valeurs qui existaient dans le fichier auparavant. 
 * 
 * Paramètres: 
 * char* fich : nom du fichier à ouvrir
 * int   opt  : mode d'ouverture du fichier
 * FILE* fp   : pointeur au fichier ouvert
 */ 
FILE* ouvre_fich(char* fich, int opt){

	FILE *fp; 

	char mode; 
	if(opt == 1){
		mode = 'r'; // Mode d'ouverture: ouvre en lecture
	}else{
		mode = 'w'; // Mode d'ouverture: ouvre en création/écriture 
	}

	// Problème avec la lecture du fichier. Informe les joueurs et quitte le jeu. 
	if((fp = fopen(fich, &mode))== NULL){
		printf("Impossible ouvrir le fichier. La commande a échoué...\n"); 
		exit(1); 
	}
	// Retourne le pointeur du fichier
	return fp;
}

/** 
 * Lire le jeu à partir d'un fichier enregistré en disque. 
 * 
 * Paramètre : 
 * char* fich : nom du fichier à lire
 */ 
void lire_jeu(char* fich){

	// Pointeur de fichier. Utilise le mode d'ouveture 1 - lecture. 
	FILE *fp = ouvre_fich(fich, 1); 

	fgets(jeu, TAILLE_MAX_FICH, fp); 
	printf("Contenu du fichier '%s' :\n%s\n", fich, jeu); 

	fclose(fp);
}

/**
 * Écrire l'état courant de la matrice de jeu dans le fichier de sortie standard 
 * 'partie.txt'. 
 * Le format du fichier est: 
 *     P;P;P;P;P;P;P;P;P/T
 *        où P est un des caractères de joueur (X ou O) ou le caractère B pour une case blanche; et 
 *           T est le joueur qui a le tour courant. 
 */ 
void ecrire_jeu(){

	FILE *fp = ouvre_fich("partie.txt", 2); 

	// Teste si la coordoné a un char de joueur valide; sinon, attribue un 'B'. 
	char grava[TAILLE_MAX_FICH] = { 
		((matrix[0][0] == 'X' || matrix[0][0] == 'O') ? matrix[0][0] : 'B'), ';', 
		((matrix[0][1] == 'X' || matrix[0][1] == 'O') ? matrix[0][1] : 'B'), ';', 
		((matrix[0][2] == 'X' || matrix[0][2] == 'O') ? matrix[0][2] : 'B'), ';', 
		((matrix[1][0] == 'X' || matrix[1][0] == 'O') ? matrix[1][0] : 'B'), ';', 
		((matrix[1][1] == 'X' || matrix[1][1] == 'O') ? matrix[1][1] : 'B'), ';', 
		((matrix[1][2] == 'X' || matrix[1][2] == 'O') ? matrix[1][2] : 'B'), ';', 
		((matrix[2][0] == 'X' || matrix[2][0] == 'O') ? matrix[2][0] : 'B'), ';', 
		((matrix[2][1] == 'X' || matrix[2][1] == 'O') ? matrix[2][1] : 'B'), ';', 
		((matrix[2][2] == 'X' || matrix[2][2] == 'O') ? matrix[2][2] : 'B'),  
		'/', tour
	};

	fputs(grava, fp);
	fclose(fp); 

}

/**
 * Traduit l'input d'usager dans une coordoné pour la matrice du jeu. 
 * Selon la matrice montré à l'usager, il peut jouer les numéros entre 0 et 8, 
 * pour les cases valides. Le numéro doit être traduit à la bonne coordonné de 
 * la matrice de jeu bidimentionnelle.
 * Paramètre : 
 * int carre : le numéro de carré informé par l'usager, selon l'interface. 
 * char*     : la coordonné de la position dans la matrice de jeu.  
 */ 
 char* traduire(int carre){
 	char coord[3]; 

 	switch(carre){
 		case 0: 
 			return "00"; 
 			break; 
 		case 1: 
 			return "01"; 
 			break; 
 		case 2: 
 			return "02"; 
 			break; 
 		case 3: 
 			return "10"; 
 			break; 
 		case 4: 
 			return "11"; 
 			break; 
 		case 5: 
 			return "12"; 
 			break; 
 		case 6: 
 			return "20"; 
 			break; 
 		case 7: 
 			return "21"; 
 			break; 
 		case 8: 
 			return "22"; 
 			break; 
 	}

 	// Valeur invalide, retourne un erreur
 	return "E"; 
 }

/**
 * Sortie du jeu. Faire l'enregistrement des donnés de la matrice de jeu dans le fichier 
 * et sortir avec le code signal 2. 
 */ 
 void sortir(){
 	printf("Partie abandonnée et enregistrée. Elle sera enregistré dans le fichier 'partie.txt'. \n\n\n\n");
 	ecrire_jeu();
 	exit(2);
 }

void test_ticRACToe(){

	char test_recs[22][22] = {
		"B;B;B;B;B;B;B;B;B/X",
		"X;X;O;O;O;X;X;M;X/O",
		"X;X;X;O;B;B;B;B;O/X",
		"O;B;O;X;X;X;B;B;B/X",
		"B;B;B;O;B;O;X;X;X/X",
		"X;B;O;B;X;B;O;B;X/X",
		"O;B;X;O;X;B;X;B;O/X",
		"X;O;B;X;B;B;X;B;O/X",
		"O;X;B;B;X;B;B;X;O/X",
		"B;O;X;B;O;X;B;B;X/X",
		"O;O;O;B;X;B;X;B;B/O",
		"B;X;B;O;O;O;B;X;B/O",
		"B;B;X;B;B;X;O;O;O/O",
		"O;B;B;B;O;B;X;X;O/O",
		"X;B;O;X;O;B;O;B;B/O",
		"O;X;B;O;B;X;O;B;B/O",
		"B;O;B;X;O;B;B;O;X/O",
		"B;B;O;B;X;O;B;X;O/O",
		"O;X;B;X;O;X;B;B;B/O"
	};

	for(int i = 0; i < 20; i++){
		// printf("%s\n", test_recs[i]); 
		strcpy(jeu, test_recs[i]); 
		test_routine(); 
	}
}

void test_routine(){

	printf("=========================================\n");

	printf("%s\n", jeu);

	init_matrice(); 

	afficher_grille(); 

	char etat = verifier_etat(); 

	if(etat == ' '){
		printf("=====Partie n'est pas finie=====.\n");
	}else if(etat == 'N'){
		printf("===== La partie est nulle! =====");
	}
}
 /*****************************************************************************
  *                     F i n   d e   p r o g r a m m e   
  *****************************************************************************/
