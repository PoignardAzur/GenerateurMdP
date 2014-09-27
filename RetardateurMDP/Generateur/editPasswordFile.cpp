

#include "editPasswordFile.hpp"
#include <fstream>
#include <ctime>


//#define FILE_NAME "Fichiers\\FichierRetardeur\\Fichier.mdp"
#define FILE_NAME "FichierRetardeur\\Fichier.mdp"
#define STR_SIZE 12


std::string shiftString(const std::string& copie, signed char decalage)
{
    std::string chaineRetour = copie;
    for (unsigned short i = 0; i < chaineRetour.size(); ++i)
    {
        chaineRetour[i] += decalage;
    }

    return chaineRetour;
}


void createNewPassword(const std::string& str)
{
    std::ofstream f(FILE_NAME, std::ios::out | std::ios::trunc);
    f.seekp(0, std::ios::beg);
    f.write(shiftString(str, 3).c_str(), str.size());
}


const std::string& getPassword()
{
//    std::ofstream fluxFichier1("FILE_NAME");
    std::ifstream f(FILE_NAME);

    std::string str;
    f.seekg(0, std::ios::beg);
    getline(f, str);
    return shiftString(str, -3);
}

