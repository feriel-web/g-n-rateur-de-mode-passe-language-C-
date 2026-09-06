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
void evaluer_robustesse(const char *mdp) {
    int longueur = strlen(mdp);
    int a_min = 0, a_maj = 0, a_chiffre = 0, a_symbole = 0;

    for (int i = 0; i < longueur; i++) {
        if (islower((unsigned char)mdp[i])) a_min = 1;
        else if (isupper((unsigned char)mdp[i])) a_maj = 1;
        else if (isdigit((unsigned char)mdp[i])) a_chiffre = 1;
        else a_symbole = 1;
    }

int score = a_min + a_maj + a_chiffre + a_symbole;

    printf("\n--- Indice de robustesse ---\n");
    if (longueur >= 12 && score == 4) {
        printf("Niveau : TRES FORT (Excellente securite)\n");
    } else if (longueur >= 8 && score >= 3) {
        printf("Niveau : MOYEN (Accepte pour un usage standard)\n");
    } else {
        printf("Niveau : FAIBLE (Ajoutez de la longueur et des symboles)\n");
    }
}

void sauvegarder_historique(const char *mdp) {
    FILE *fichier = fopen(FICHIER_HISTORIQUE, "a");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    fprintf(fichier, "%s\n", mdp);
    fclose(fichier);
    printf("Mot de passe enregistre dans '%s'.\n", FICHIER_HISTORIQUE);
}

