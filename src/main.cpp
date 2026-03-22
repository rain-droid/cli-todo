#include "CLI11.hpp"
#include "cli-todo/sqlHandler.hpp"
#include <iostream>

int main(int argc, char** argv) {
    CLI::App app{"CLI ToDo Application"};
    argv = app.ensure_utf8(argv);

    std::string dbFilename = "../clido.db";
    app.add_option("-f,--file", dbFilename, "Path to the database file. Default is clido.db");
    // app.add_option("-")
    CLI11_PARSE(app, argc, argv);

    SqlHandler sqlHandler;

    std::cout << "Database File: " << dbFilename << std::endl;

    if (sqlHandler.openDB(dbFilename)==0)
    {
        std::cout << "Database opened successfully " << dbFilename << std::endl;
    }
    else
    {
        std::cerr << "Failed to open database " << dbFilename << std::endl;
    }
    sqlHandler.initDB();
    int id = sqlHandler.createNewList("test-list","test-description");
    if (id == -1)
    {
        std::cout << "Error creating new List!" << std::endl;
    }
    else
    {
        std::cout << "Created new List " << id << std::endl;
    }
    sqlHandler.closeDB();
    return 0;
}
