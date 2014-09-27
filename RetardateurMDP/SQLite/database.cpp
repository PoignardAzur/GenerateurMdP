

#include "statement.hpp"



sql3::Database::Database()
{}

sql3::Database::Database(const char* filename, int flags, const char *zVFS)
{
	open(filename, flags, zVFS);
}

void sql3::Database::open(const char* filename, int flags, const char *zVFS)
{
//	int errorCode = sqlite3_open_v2(filename, &p_database, flags, zVFS);
	testCode(sqlite3_open_v2(filename, &p_database, flags, zVFS), OPENING_DATABASE);
}

bool sql3::Database::isOpen() const
{
    return p_database != 0;
}


void sql3::Database::prepare(const char *query, int maxSize, Statement& modifiedStmt)
{
	modifiedStmt.prepareIn(p_database, query, maxSize);
}

void sql3::Database::prepare(const char *query, int maxSize, sqlite3_stmt*& modifiedStmt)
{
	prepareStatementIn(p_database, query, maxSize, modifiedStmt);
}

void sql3::Database::executeQuery(const char *query, int maxSize)
{
    Statement stmt(*this, query, maxSize);
    stmt.makeAllSteps();
}


void sql3::Database::close()
{
	sqlite3_close_v2(p_database);
	p_database = 0;
}

sql3::Database::~Database()
{
	close();
}


void sql3::Database::testCode(int sqlCode, char origin, const char* query)
{
	testErrorCode(sqlCode, origin, query);
}




namespace sql3
{

    void prepareStatementIn(sqlite3* target, const char *query, int maxSize, sqlite3_stmt*& modifiedStmt)
    {
    //	int errorCode = sqlite3_prepare_v2(&target, query, maxSize, &modifiedStmt, 0);
        testErrorCode(sqlite3_prepare_v2(target, query, maxSize, &modifiedStmt, 0), PREPARING_STATEMENT, query);
    }


    void testErrorCode(int sqlCode, char origin, const char* query)
    {
        if (sqlCode != SQLITE_OK)
        {
            sqlError errorMessages;

            if (origin == RUNNING_STATEMENT)
            errorMessages.origin = "Error encountered when running the statement";
            if (origin == PREPARING_STATEMENT)
            errorMessages.origin = "Error encountered when preparing the statement";
            if (origin == OPENING_DATABASE)
            errorMessages.origin = "Error encountered opening the database";
            if (origin == USING_INCORRECT_STATEMENT)
            errorMessages.origin = "Error encountered dealing with the corrupted statement";
            if (origin == BINDING_STATEMENT)
            errorMessages.origin = "Error encountered binding elements to the statement";

            errorMessages.errorCode = sqlite3_errstr(sqlCode);
            errorMessages.queryText = query;

            throw errorMessages;
        }
    }


    void execute(Statement* modifiedStmt)
    {
        try
        {
            modifiedStmt->makeAllSteps();
        }

        catch (sqlError errorMessages)
        {
            delete modifiedStmt;
            throw errorMessages;
        }

        delete modifiedStmt;
    }

    std::ostream& operator<<(std::ostream& os, sqlError errorMessages)
    {
        os << errorMessages.origin;

        if (errorMessages.queryText)
        os << " :" << std::endl << errorMessages.queryText;

        os << std::endl << "Reason given : " << errorMessages.errorCode;

        return os;
    }

}




