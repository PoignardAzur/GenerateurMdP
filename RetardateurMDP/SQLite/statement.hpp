

#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

#include "database.hpp"
#define SELECT_ALL_FROM(TABLE) "SELECT * FROM " TABLE

namespace sql3
{

	class Statement
	{
		public :

		Statement();
		Statement(Database& target, const char *query, int maxSize = -1);

		void prepareSelectAllIn(Database& target, const char *table, int sizeTableName = -1);		// each function is basically an indirect call of
		void prepareIn(Database& target, const char *query, int maxSize = -1);		// prepareStatementIn(target, query, maxSize, modifiedStatement)
		void prepareIn(sqlite3* target, const char *query, int maxSize = -1);

		bool step();													// selects the next column, returns false is there isn't any
		void makeAllSteps();
		void reset(bool doResetBindings = false);						// returns to the first line
		void resetBindings();											// deletes all bindings
		const char* getQuery();

		void bindInt(int i, int value);
		void bindDouble(int i, double value);							// binds the argument(s) n°[i] with [value]
		void bindNull(int i);
		void bindText(int i, const char* value, int size = -1);
//		void bindText16(int i, const char* value, int size = -1, void(*)(void*) = SQLITE_STATIC); // does what ??

		int columnByte(int i) const;											// give the value (if it's in the asked format)
		int columnByte16(int i) const;										// of the element n°[i] of the selected column
		int columnInt(int i) const;
		double columnDouble(int i) const;
		const unsigned char* columnText(int i) const;
		const char* columnStandardText(int i) const;
		//const unsigned char* columnText16(int i) const;

		void checkColumn(int i) const;										// throw an exception if (i > columnCount)
		int columnCount() const;
		void testCode(int sqlCode, char origin, const char* query) const;

		void erase();													// must be called after all statements are erased
		~Statement();


		private :

		sqlite3_stmt* p_stmt;
	};
}


#endif

/*

Essential :

sql3Statement
{
	public :

	void prepareIn(Database& target, const char *query, int maxSize = -1);
	bool step();
	void reset(bool doResetBindings = false);
	void erase();

	void bindInt(int i, int value);
	void bindDouble(int i, double value);
	void bindText(int i, const char* value, int size);
	void bindNull(int i);
};


const sql3Statement
{
	int             columnInt(int i);
	double          columnDouble(int i);
	char*           columnText(int i);
    unsigned char*  columnText(int i);
    char*           columnStandardText(int i);
	int             columnCount();
};


*/

/*

Binding system :
Each argument is numbered and replaced with a value (depending on the function).
The arguments are written with on of those formats :
? / ?n / :str / @str / $str ;
Where n is the number of the argument (must be between 1 and 999), and str its name.
Arguments (save for ?n) are indexed with their place in the string, the first from the left being n°1, the second from the left n°2...
Two arguments with the same name also have the same index.

*/
