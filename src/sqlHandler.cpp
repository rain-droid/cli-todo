#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>
#include <cli-todo/sqlHandler.hpp>




SqlHandler::SqlHandler(): db(nullptr) {}
SqlHandler::~SqlHandler()
{
    closeDB();
}

int SqlHandler::openDB(const char* filename){
    int rc = sqlite3_open(filename, &db);
    if (rc)
    {
        printf("Database could not be opened: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    else
    {
        printf("Opened database successfully\n");
        return 0;
    }
}


int SqlHandler::closeDB()
{
    if(db)
    {
        sqlite3_close(db);
        printf("Database closed successfully\n");
        db = nullptr;
        return 0;
    }
    return 1;
}
