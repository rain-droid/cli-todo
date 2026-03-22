#ifndef SQL_HANDLER_H
#define SQL_HANDLER_H

#include <sqlite3.h>

class SqlHandler
{
    private:
    sqlite3* db;
    int createListTable();
    int createItemTable();
    public:
    SqlHandler();
    ~SqlHandler();

    int openDB(const std::string& filename);
    int closeDB();
    int initDB();
    int createNewList(const std::string& listname,
        const std::string& description = "",
        const std::string& password = "");
    int createNewItem(const std::string& header, const int& list_id, const std::string&, )
};

#endif // SQL_HANDLER_H
