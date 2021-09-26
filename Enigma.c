#include <stdio.h>
#include <stdlib.h>

char tableauAlphabet[26];
char tableauR1[26];
char tableauR2[26];
char tableauR3[26];
char tableauPerm[26];

char tradLettres ( char lettre){
    // Detecte les lettres maj et miniscules et transforme le tout en Maj. Detecte si y'a un caractere special utilisant le code ASCII
    int ascii;
    ascii = lettre;
    if ( ascii >= 65 && ascii <=90) return lettre;
    else if ( ascii >= 97 && ascii <=122){
        ascii = ascii -32;
        lettre = ascii;
        return lettre;
    }
    else return lettre;

}

int detecteurLettres ( char lettre){
    // renvoie une valeur special dependante si le caractere est une lettre maj, ou miniscules ou pas une lettre utlisant le code ASCII
    int ascii;
    ascii = lettre;
    if ( ascii >= 65 && ascii <=90) return 0;
    else if ( ascii >= 97 && ascii <=122) return 1;
    else return -1;

}

void intialiseurAlphabet(){
    // Fonction qui initialise le tableau globale d'alphabet à l'aide du code ASCII
	int ascii = 65;
	int i;
	for (i=0 ; i<26 ; i++){
		tableauAlphabet[i] = ascii;
		ascii++;
	}
}

void intialiseurR1(){
    // Fonction qui initialise le tableau globale du 1er Rotor depuis un fichier .txt
    int i;
    FILE* fichierR1 = NULL;
    fichierR1 = fopen("Rotor1.txt","rw");
    if (fichierR1 != NULL){
    for (i=0; i<26 ; i++)
    tableauR1[i]=fgetc(fichierR1);
    }
    fclose(fichierR1);
}

void intialiseurR2(){
    // Fonction qui initialise le tableau globale du 2eme Rotor depuis un fichier .txt
    int i;
    FILE* fichierR2 = NULL;
    fichierR2 = fopen("Rotor2.txt","rw");
    if (fichierR2 != NULL){
    for (i=0; i<26 ; i++)
    tableauR2[i]=fgetc(fichierR2);
    }
    fclose(fichierR2);
}

void intialiseurR3(){
    // Fonction qui initialise le tableau globale du 3eme Rotor depuis un fichier .txt
    int i;
    FILE* fichierR3 = NULL;
    fichierR3 = fopen("Rotor3.txt","r");
    if (fichierR3 != NULL){
    for (i=0; i<26 ; i++)
    tableauR3[i]=fgetc(fichierR3);
    }
    fclose(fichierR3);
}

void initialiseurPermutor(){
    // Fonction qui initialise le tableau globale du Permuteur depuis un fichier .txt
    int i;
    FILE* fichierPerm = NULL;
    fichierPerm = fopen("Permutor.txt","r");
    if (fichierPerm !=NULL){
        for( i =0; i<26; i++){
            tableauPerm[i]=fgetc(fichierPerm);

        }

    }
fclose(fichierPerm);

}


char rotorR1 ( char lettre, int nbLettres, int type){
    // La fonction du 1er Rotor, si type == 1 on utilise R, si type == -1 , on utilise R-1
    int letAscii;
    int i;
    int r1=0;
    r1 = nbLettres %26;
    if (type ==1){
        letAscii = lettre-65; // initalisateurAlphabet
        return tableauR1[letAscii + r1];
        }
    else if ( type == -1){
        for (i=0; i<26; i++){
            if (lettre == tableauR1[i]){
                return tableauAlphabet[i+r1];
            }
        }
    }
}


char rotorR2 (char lettre, int nblettres, int type){
    // La fonction du 2eme Rotor, si type == 1 on utilise R, si type == -1 , on utilise R-1
    int i;
    int letAscii;
    int r2=0;
    r2 = nblettres / 26;
    r2 = r2 %26;

    if (type ==1){
        letAscii = lettre-65; // initalisateurAlphabet
        return tableauR2[letAscii + r2];}
    else if ( type == -1){
        for (i=0; i<26; i++){
            if (lettre == tableauR2[i]){
                return tableauAlphabet[i+r2];
            }
        }
    }


}

char rotorR3 (char lettre, int nblettres, int type){
    // La fonction du 3eme Rotor , si type == 1 on utilise R, si type == -1 , on utilise R-1
    int i;
    int letAscii;
    int r3=0;
    r3 = nblettres / (26*26);
    r3 = r3%26;
    if (type ==1){
        letAscii = lettre-65;
        return tableauR3[letAscii + r3];}
    else if ( type == -1){
        for (i=0; i<26; i++){
            if (lettre == tableauR3[i]){
                return tableauAlphabet[i+r3];
            }
        }
    }

}

char permutor (char lettre){
    // la fonction du permuteur
    int letAscii;
    letAscii = lettre-65;
    return tableauPerm[letAscii];


}


int main (){
    // Ces 5 premieres lignes permettent d'initialiser les 5 tableaux globeaux
    intialiseurAlphabet();
    intialiseurR1();
    intialiseurR2();
    intialiseurR3();
    initialiseurPermutor();



    int nbLettres =0;
    int ascii=0;
    int det;
    int i;

    char lettre;
    char let1,let2;
    char tableauS1[26];       // le tableau d'alphabet + 6 paires de permutations que va rentrer l'utlisateur
    char tableauChoisies[13];  // Chaine de caracteres qui contient les paires rentré par l'utilisateur

    for (i=0; i<26; i++){
    tableauS1[i]= tableauAlphabet[i];  // Initialise le tableau S1 avec l'alphabet
    }
    printf("\n Vous devez rentrer les premiers 6 paires de substitutions! \n");
    // Receptions des 6 paires de permutations choisies
    printf("\n Rentrez les 12 lettres de façon suivie, exemple : (azertyuiopqs) \n");
    printf(" \n ");
    fgets(tableauChoisies, 13, stdin);
        for(i=0; i <12; i=i+2){ // Une boucle for 2 par 2 pour prelever les paires et les mettre dans le tableau S1

        let1 = tradLettres(tableauChoisies[i]);     // on fait passer les lettres rentrés dans le traducteur au cas ou l'utilisateur utilise le miniscule
        let2 = tradLettres(tableauChoisies[i+1]);
        tableauS1[let1-65]= let2;
        tableauS1[let2-65]= let1;

        }



    nbLettres =0;

    printf("\n\n Texte Chiffre: \n\n ");
                            // Ouverture du fichier contenant le texte crypté //
    FILE* texteNew = NULL;
    texteNew = fopen("texteNew.txt","r");
    rewind(texteNew);  // Pour s'assurer que le curseur est au debut du texte

    if (texteNew != NULL){  // On teste la bonne reception du fichier texte
        while( (lettre=getc(texteNew)) != EOF){    // Pour lire tout le texte crypté
        det = detecteurLettres(lettre);         // Valeur à enregistré pour savoir si c'est une lettre min, maj ou un caractere special
        lettre = tradLettres(lettre);           // On transforme la lettre en majuscule
        if (det == -1){
                nbLettres ++;
                printf("%c",lettre);        // Dans le cas d'un caractere different de l'alphabet

                }
        else {
            ascii = lettre;
            lettre = tableauS1[ascii-65];
            lettre = rotorR1(lettre, nbLettres, 1);
            lettre = rotorR2(lettre, nbLettres, 1);
            lettre = rotorR3(lettre, nbLettres, 1);
            lettre = permutor(lettre);
            lettre = rotorR3(lettre, nbLettres, -1);
            lettre = rotorR2(lettre, nbLettres, -1);
            lettre = rotorR1(lettre, nbLettres, -1);
            for (i=0; i <26 ; i++){
                if (lettre == tableauS1[i]) lettre = tableauAlphabet[i];

            }

            if (det == 0) printf("%c", lettre);         // selon la lettre du texte original, on teste si la lettre était miniscule pour la rendre miniscule sinon on la laisse majuscule
            else if (det == 1) {
                ascii = lettre;
                ascii = ascii + 32;
                lettre = ascii;
                printf("%c", lettre);

            }
        nbLettres ++;
        }

    }

    }
    else printf(" \n Erreur a trouver le texte a crypter");
printf("\n");


fclose(texteNew);
}
