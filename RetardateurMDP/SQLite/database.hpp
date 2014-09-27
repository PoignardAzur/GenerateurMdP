
#ifndef DATABASE_HEADER
#define DATABASE_HEADER

#include "sqlite3.h"
#include <ostream>

#define RUNNING_STATEMENT 0
#define PREPARING_STATEMENT 1
#define OPENING_DATABASE 2
#define USING_INCORRECT_STATEMENT 3
#define BINDING_STATEMENT 4
#define OTHER_SQL3_ERROR 10


namespace sql3
{
    struct sqlError
    {
        const char* origin;
        const char* queryText;
        const char* errorCode;
    };


	class Statement;

	class Database
	{
		public :

		Database();
		Database(const char* filename, int flags = SQLITE_OPEN_READWRITE, const char *zVFS = 0);		// simply calls open(filename, flags, zVFS)
//		Database(const char* filename, bool utf16);

		void open(const char* filename, int flags = SQLITE_OPEN_READWRITE, const char *zVFS = 0);		// don't touch zVFS, that's pointless
//		void open(const char* filename, bool utf16);
//		void open16(const char* filename);
        bool isOpen() const;

		void prepare(const char *query, int maxSize, Statement& modifiedStmt);                          // simply calls
		void prepare(const char *query, int maxSize, sqlite3_stmt*& modifiedStmt);                      // prepareStatementIn(target, query, maxSize, modifiedStatement)
		void executeQuery(const char *query, int maxSize = -1);                                         // executes the query without using a statement
//		void prepare16

		void testCode(int sqlCode, char origin, const char* query = 0);
		void close();
		~Database();

		private :

		sqlite3* p_database;
	};

    std::ostream& operator<<(std::ostream& os, sqlError errorMessage);

    void createDatabaseFromFile(Database& db, std::istream &commandFile, const char* dbName = 0);

    void execute(Statement* modifiedStmt);      // makes all steps of the statement, then deletes it, even if there is an error.
	void prepareStatementIn(sqlite3* target, const char *query, int maxSize, sqlite3_stmt*& modifiedStmt); 	// maxSize will be automatically calculated if -1 is
	void testErrorCode(int sqlCode, char origin, const char* query);                                        // entered, but should still be provided if possible
}                                                                                                           // to slightly improve performances


/*

class sql3::Database
{
	public :

	Database();
	void open(const char* filename, int flags = SQLITE_OPEN_READWRITE, const char *zVFS = 0);
	void close();

	void prepare(const char *query, int maxSize, Statement& modifiedStmt);
	void prepareSelectAll(const char *table, int maxSize, Statement& modifiedStmt);
};


*/


#endif

