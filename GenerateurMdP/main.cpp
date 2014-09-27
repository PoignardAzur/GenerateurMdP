
#include "fonctions.h"


using namespace std;


int main()
{
	srand(time(0));
	std::string fichier(ADRESSE);

	std::string fichier2("C:\\Users\\Travail\\Desktop\\MotDePasse.txt");

	std::cout << "Taper \"DonnerMot\" pour recuperer le mot de passe a la fin du timer,"
	<< endl << "Taper \"ResetMot\" pour enregistrer un nouveau mot de passe aleatoire,"
	<< endl << "Taper \"ResetListe\" pour remettre la liste a zero,"
	<< endl << "Taper \"Quitter\" pour finir." << endl << endl << endl;

	while( appelerFonction(fichier, fichier2) );
	return EXIT_SUCCESS;
}



