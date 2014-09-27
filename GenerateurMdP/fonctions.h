
#include "includes.h"

#define ADRESSE "Fichier.mdp"
#define TAILLE 12

#define DUREE_SECONDE 1
#define DUREE_MINUTE 60 * DUREE_SECONDE
#define TEMPS 30 * DUREE_MINUTE



bool appelerFonction(std::string& fichier1, std::string& fichier2);
bool donnerMotDePasse(std::string& fichier1, std::string& fichier2);
void creerNouveauMotDePasse(std::string& fichier1, std::string& fichier2);

std::string genererChaine();
std::string decalerChaine(const std::string& copie, char decalage);
char genererCaractere();

bool attendre(unsigned short temps);
std::string majChaine(const std::string&);
