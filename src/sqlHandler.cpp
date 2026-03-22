#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <cli-todo/sqlHandler.hpp>
#include <string_view>




SqlHandler::SqlHandler(): db(nullptr) {}
SqlHandler::~SqlHandler()
{
    closeDB();
}

int SqlHandler::openDB(const std::string& filename ){
    const char* file = filename.c_str();
    int rc = sqlite3_open(file, &db);
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


int SqlHandler::createListTable()
{
    const std::string sql_query = "Create TABLE list ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL UNIQUE,"
        "description TEXT NULL,"
        "password TEXT NULL,"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ");";

    if (!db){
        std::cerr << "Database is not open" << std::endl;
        return -1;
    }
    char* message_err = nullptr;
    int rc =  sqlite3_exec(db,sql_query.c_str(), NULL, 0,&message_err);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Error Creating List Table" << std::endl;
        sqlite3_free(message_err);
    }
    else
    {
        std::cout << "List Table Created successfully" << std::endl;
    }
    return rc;
}

int SqlHandler::createItemTable()
{
    const std::string sql_query = "Create TABLE item ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "list_id INTEGER NOT NULL,"
        "header TEXT NOT NULL,"
        "description TEXT NULL,"
        "status TEXT NOT NULL DEFAULT 'pending',"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "FOREIGN KEY (list_id) REFERENCES list(id) on DELETE CASCADE"
        ");";

    if (!db){
        return -1;
        std::cerr << "Database is not open" << std::endl;
    }
    char* message_err = nullptr;
    int rc =  sqlite3_exec(db,sql_query.c_str(), NULL, 0,&message_err);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Error Creating List Table" << std::endl;
        sqlite3_free(message_err);
    }
    else
    {
        std::cout << "List Table Created successfully" << std::endl;
    }
    return rc;
}
int SqlHandler::initDB()
{
    int rc = createListTable();
    if (rc != SQLITE_OK){
        return rc;
    }
    return createItemTable();
}

int SqlHandler::createNewList(const std::string& listname,
    const std::string& description,
    const std::string& password
)
{
    const std::string sql_query = "INSERT INTO list(name,description,password) VALUES (?,?,?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql_query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Error preparing " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    sqlite3_bind_text(stmt,1,listname.c_str(),-1,SQLITE_TRANSIENT);

    if (description.empty())
    {
        sqlite3_bind_null(stmt, 2);
    }
    else
    {
        sqlite3_bind_text(stmt, 2, description.c_str(), -1 , SQLITE_TRANSIENT);
    }

    if (password.empty())
    {
        sqlite3_bind_null(stmt,3);
    }
    else
    {
        sqlite3_bind_text(stmt, 3, password.c_str(),-1, SQLITE_TRANSIENT);
    }

    int result = -1;
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to create new list " << sqlite3_errmsg(db) << std::endl;
        result = -1;
    }
    else
    {
        std::cout << "New List created successfully" << std::endl;
        result = static_cast<int>(sqlite3_last_insert_rowid(db));
    }

    sqlite3_finalize(stmt);
    return result;
}

int SqlHandler::createNewItem()
