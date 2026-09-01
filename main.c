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

// Mélange aléatoire des caractères (Fisher-Yates)
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

int main() {
    int longueur;
    int inclure_maj, inclure_chiffres, inclure_symboles;
    char jeu_complet[300] = "";
    char mot_de_passe[MAX_TAILLE];
    int pos = 0;

    srand((unsigned int)time(NULL));

    printf("=== GENERATEUR DE MOTS DE PASSE SECURISE ===\n\n");

    do {
        printf("Choisissez la longueur du mot de passe (min 4, max 99) : ");
        if (scanf("%d", &longueur) != 1) {
            while (getchar() != '\n');
        }
    } while (longueur < 4 || longueur >= MAX_TAILLE);

    printf("Inclure des lettres majuscules ? (1: Oui, 0: Non) : ");
    scanf("%d", &inclure_maj);
    printf("Inclure des chiffres ? (1: Oui, 0: Non) : ");
    scanf("%d", &inclure_chiffres);
    printf("Inclure des symboles ? (1: Oui, 0: Non) : ");
    scanf("%d", &inclure_symboles);

    // 1. Forcer au moins 1 caractère de chaque type sélectionné
    mot_de_passe[pos++] = MINUSCULES[rand() % strlen(MINUSCULES)];
    strcat(jeu_complet, MINUSCULES);

    if (inclure_maj) {
        mot_de_passe[pos++] = MAJUSCULES[rand() % strlen(MAJUSCULES)];
        strcat(jeu_complet, MAJUSCULES);
    }
    if (inclure_chiffres) {
        mot_de_passe[pos++] = CHIFFRES[rand() % strlen(CHIFFRES)];
        strcat(jeu_complet, CHIFFRES);
    }
    if (inclure_symboles) {
        mot_de_passe[pos++] = SYMBOLES[rand() % strlen(SYMBOLES)];
        strcat(jeu_complet, SYMBOLES);
    }

    // 2. Remplir le reste de la longueur voulue
    int taille_jeu = strlen(jeu_complet);
    for (; pos < longueur; pos++) {
        mot_de_passe[pos] = jeu_complet[rand() % taille_jeu];
    }
    mot_de_passe[longueur] = '\0';

    // 3. Mélanger pour ne pas avoir les types forcés toujours au début
    melanger(mot_de_passe, longueur);

    // Affichage
    printf("\n==========================================");
    printf("\nMot de passe genere : %s\n", mot_de_passe);
    evaluer_robustesse(mot_de_passe);
    sauvegarder_historique(mot_de_passe);
    printf("==========================================\n");

    return 0;
}
