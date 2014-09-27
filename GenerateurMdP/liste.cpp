
#include <fstream>
#include <string>

#define NOM_DU_FICHIER_A_RESET_1 "A faire chaque jour.txt"
#define NOM_DU_FICHIER_A_COPIER_1 "Fichiers\\Modele1.txt"
#define NOM_DU_FICHIER_A_RESET_2 "A faire chaque semaine.txt"
#define NOM_DU_FICHIER_A_COPIER_2 "Fichiers\\Modele2.txt"


std::string getAllLinesOf(const std::string& fileName)
{
    std::ifstream f(fileName.c_str());
    std::string str;
    std::string finalString;

    while(std::getline(f, str))
    {
        finalString += str + "\n";
    }

    return finalString;
}


void resetLists()
{
    std::ofstream f1(NOM_DU_FICHIER_A_RESET_1, std::ios_base::out | std::ios_base::trunc);
    std::ofstream f2(NOM_DU_FICHIER_A_RESET_2, std::ios_base::out | std::ios_base::trunc);

    f1 << getAllLinesOf(NOM_DU_FICHIER_A_COPIER_1);
    f2 << getAllLinesOf(NOM_DU_FICHIER_A_COPIER_2);
}

