#include "Database.h"

Database::Database(const std::string& name)
    : db(nullptr), dbName(name) {}

Database::~Database() {
    close();
}

bool Database::open() {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Erro ao abrir o banco: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "Banco conectado com sucesso.\n";
    return true;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        std::cout << "Conexão com o banco encerrada.\n";
    }
}

bool Database::execute(const std::string& sql) {
    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao executar SQL: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

bool Database::query(const std::string& sql, int (*callback)(void*, int, char**, char**), void* data) {
    char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), callback, data, &errorMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao consultar: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}
