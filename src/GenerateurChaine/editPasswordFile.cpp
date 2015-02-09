

#include <cstdlib>
#include <string>


char generateLetter()
{
    char nombre = rand() % 36;

    if (nombre < 26)
    return nombre + 'a';

//	else
    return nombre - 26 + '0';
}


std::string generateStr(int size)
{
    std::string str(size, ' ');
    str[0] = '@';

    for(char i = 1; i < size; ++i)
    {
        str[i] = generateLetter();
    }

    return str;
}


