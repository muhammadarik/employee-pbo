#pragma once
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>

using namespace std;

class Database {
protected:
    sql::Driver* driver;
    sql::Connection* con;

public:
    Database();
    ~Database();

    sql::Connection* getConnection();
};
