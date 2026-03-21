#ifndef SQL_HANDLER_H
#define SQL_HANDLER_H

#include <sqlite3.h>

class SqlHandler
{
    private:
    sqlite3* db;
    public:
    SqlHandler();
    ~SqlHandler();

    int openDB(std::string filename);
    int closeDB();
};

#endif // SQL_HANDLER_H
