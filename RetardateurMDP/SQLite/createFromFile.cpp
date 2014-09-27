

#include "statement.hpp"
#include <sstream>


namespace sql3
{

    void createDatabaseFromFile(Database& db, std::istream &commandFile, const char* dbName)
    {
        Statement stmt;
        std::string str;
        std::string str02;
        int line = 0;
        bool end = false;

        if (dbName == 0)
        {
            std::getline(commandFile, str);
            dbName = str.c_str();
        }

        db.open(dbName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

        try
        {

            while (std::getline(commandFile, str) && (!end) )
            {
                if (str.size() > 1)
                {
                    if (str.substr(0,3) == "END")
                    end = true;

                    else if (str.substr(0,2) != "//")
                    {
                        db.prepare(str.c_str(), str.size(), stmt);
                        stmt.makeAllSteps();
                    }
                }

                line ++;

            }
        }

        catch (sqlError error)
        {
            std::string errorText;
            std::stringstream(errorText) << "Error encountered creating the database " << dbName << " while reading line " << line
            << " : " << std::endl << error;
            throw errorText.c_str();
        }
    }
}


