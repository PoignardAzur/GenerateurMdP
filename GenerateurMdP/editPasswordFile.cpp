

#include "generateurmdp.h"
#include <fstream>
#include <ctime>

#define FILE_NAME "FichiersGenerateur\\Fichier.mdp"
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


std::string createNewPassword()
{
    std::ofstream f(FILE_NAME);

    std::string str = generateStr();
    f.seekp(0, std::ios::beg);
    f.write(shiftString(str, 3).c_str(), str.size());
    return str;
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

char generateLetter()
{
    char nombre = rand() % 36;

    if (nombre < 26)
    return nombre + 'a';

//	else
    return nombre - 26 + '0';
}


std::string generateStr()
{
	srand(time(0));
    std::string str(STR_SIZE, ' ');
    str[0] = '@';

    for(char i = 1; i < STR_SIZE; ++i)
    {
        str[i] = generateLetter();
    }

    return str;
}


