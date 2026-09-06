#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TAILLE 100
#define FICHIER_HISTORIQUE "historique_mots_de_passe.txt"

const char MINUSCULES[] = "abcdefghijklmnopqrstuvwxyz";
const char MAJUSCULES[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char CHIFFRES[]   = "0123456789";
const char SYMBOLES[]   = "!@#$%^&*()_+-=[]{}|;:,.<>?";

// Mélange aléatoire des caractères
void melanger(char *str, int taille) {
    for (int i = taille - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}