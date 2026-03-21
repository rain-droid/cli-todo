#include "CLI11.hpp"
#include <sqlite3.h>
#include <stdio.h>
#include "cli-todo/sqlHandler.hpp"

int main(int argc, char** argv) {
    CLI::App app{"CLI ToDo Application"};
    argv = app.ensure_utf8(argv);

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");
    // app.add_option("-")
    CLI11_PARSE(app, argc, argv);
    printf("%s\n", filename.c_str());

    SqlHandler sqlHandler;
    sqlHandler.openDB(filename);
    sqlHandler.closeDB();

    return 0;
}
