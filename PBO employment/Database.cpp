#include "Database.h"

Database::Database() {
    try {
        driver = sql::mysql::get_driver_instance();
        con = driver->connect("tcp://localhost:3306", "root", "");
        con->setSchema("pbo_employment");
        cout << "Connected to database." << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

Database::~Database() {
    delete con;
}

sql::Connection* Database::getConnection() {
    return con;
}
