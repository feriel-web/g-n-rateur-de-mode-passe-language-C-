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

