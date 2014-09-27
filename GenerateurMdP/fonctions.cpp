
#include "fonctions.h"


using namespace std;

bool appelerFonction(std::string& fichier1, std::string& fichier2)
{/*
	fichier1.seekg(0, ios::beg);
	fichier1.seekp(0, ios::beg);

	fichier2.seekg(0, ios::beg);
	fichier2.seekp(0, ios::beg);
*/
	string chaine;
	cin >> chaine;
	chaine = majChaine(chaine);
	cout << endl;

	if (chaine == "DONNERMOT")
	{
        if(!donnerMotDePasse(fichier1, fichier2))
        return false;
	}

	if (chaine == "RESETMOT")
	creerNouveauMotDePasse(fichier1, fichier2);

	if (chaine == "QUITTER")
	return false;

///	else
	return true;
}


bool donnerMotDePasse(std::string& fichier1, std::string& fichier2) //renvoie false si l'opération est avortée,
{                                                                     //donne le mot sinon
    std::ifstream fluxFichier1(fichier1.c_str());

	if (!attendre(TEMPS))
	return false;

/// else
	string chaine;
	fluxFichier1.seekg(0, std::ios::beg);
	getline(fluxFichier1, chaine);
	cout << endl << decalerChaine(chaine, -3);

	return true;
}


void creerNouveauMotDePasse(std::string& fichier1, std::string& fichier2)
{
    std::ofstream fluxFichier1(fichier1.c_str());
    std::ofstream fluxFichier2(fichier2.c_str());

	string chaine = genererChaine();
	fluxFichier1.seekp(0, std::ios::beg);
	fluxFichier1.write(decalerChaine(chaine, 3).c_str(), chaine.size());
	cout << chaine << endl;

	fluxFichier2.seekp(0, std::ios::beg);
    fluxFichier2.write(chaine.c_str(), chaine.size());
}


string genererChaine()
{
	string chaine(TAILLE, ' ');
	chaine[0] = '@';

	for(char i = 1; i < TAILLE; ++i)
	{
	    chaine[i] = genererCaractere();
	}

	return chaine;
}

char genererCaractere()
{
	char nombre = rand() % 36;

	if (nombre < 26)
	return nombre + 'a';

//	else
	return nombre - 26 + '0';
}


string majChaine(const string& copie)
{
    string chaineRetour = copie;
    for (unsigned short i = 0; i < chaineRetour.size(); ++i)
    {
        chaineRetour[i] = toupper(chaineRetour[i]);
    }

    return chaineRetour;
}


string decalerChaine(const string& copie, char decalage)
{
    string chaineRetour = copie;
    for (unsigned short i = 0; i < chaineRetour.size(); ++i)
    {
        chaineRetour[i] += decalage;
    }

    return chaineRetour;
}
