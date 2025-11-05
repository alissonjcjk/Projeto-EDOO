#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class Database {
private:
    sqlite3* db;
    std::string dbName;

public:
    Database(const std::string& name);
    ~Database();

    bool open();
    void close();
    bool execute(const std::string& sql);
    bool query(const std::string& sql, int (*callback)(void*, int, char**, char**), void* data = nullptr);
};

#endif
