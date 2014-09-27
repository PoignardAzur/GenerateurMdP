
#include "fonctions.h"

using namespace std;


bool attendre(unsigned short dureePause) //renvoie true si le mot a été donné à la fin du temps imparti, false si le timer a été coupé
{
    time_t temps0 = time(0);
    int tempsEcoule;
    int tempsRestant;
    char C = ' ';

    cout << "Tapez \"T\" pour connaitre le temps restant avant la fin du mot de pase, \"M\" pour eventuellement obtenir"
            " le mot de passe, et \"Q\" pour quitter. La casse ne compte pas." << endl;

    while (true)
    {
        cout << endl;
        cin >> C;

        tempsEcoule = difftime(time(0), temps0);
        tempsRestant = dureePause - tempsEcoule;
        if (tempsRestant < 0)
        tempsRestant = 0;

        switch (toupper(C))
        {
            case 'T' :
            if (tempsRestant == 1)
            cout << endl << "Il reste une seconde. Oui oui, pile une seconde." << endl;
            else if (tempsRestant <= 60)
            cout << endl << "Il reste " << tempsRestant << " secondes." << endl;
            else if (tempsRestant < 120)
            cout << endl << "Il reste une minute et " << tempsRestant % 60 << " secondes." << endl;

            else if (tempsRestant % 60 == 0)
            cout << endl << "Il reste " << tempsRestant / 60 << " minutes." << endl;
            else if (tempsRestant % 60 == 1)
            cout << endl << "Il reste " << tempsRestant / 60 << " minutes et une seconde. Tout pile." << endl;
            else
            cout << endl << "Il reste " << tempsRestant / 60 << " minutes et " << tempsRestant % 60 << " secondes." << endl;
            break;

            case 'M' :
            if (tempsEcoule > dureePause)
            return true;

///         else
            cout << endl << "Pas encore." << endl;
            break;

            case 'Q' :
            return false;

            default :
            cout << endl << "Entree invalide." << endl;

        }
    }
}

