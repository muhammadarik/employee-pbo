#pragma once
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

class Department : public Database {
public:
    void createDepartment(int dept_no, std::string dept_name) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "INSERT INTO departments (dept_no, dept_name) VALUES (?, ?)"
            );
            pstmt->setInt(1, dept_no);  // ✅ betul
            pstmt->setString(2, dept_name);
            pstmt->execute();
            delete pstmt;
            std::cout << "Department added successfully." << std::endl;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Create failed: " << e.what() << std::endl;
        }
    }

    void readDepartments() {
        try {
            sql::Statement* stmt = getConnection()->createStatement();
            sql::ResultSet* res = stmt->executeQuery("SELECT * FROM departments");
            while (res->next()) {
                std::cout << res->getInt("dept_no") << ", "   // ✅ getInt karena dept_no adalah int
                    << res->getString("dept_name") << std::endl;
            }
            delete res;
            delete stmt;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Read failed: " << e.what() << std::endl;
        }
    }

    void updateDepartment(int dept_no, std::string newName) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "UPDATE departments SET dept_name = ? WHERE dept_no = ?"
            );
            pstmt->setString(1, newName);
            pstmt->setInt(2, dept_no);   // ✅ pakai int langsung
            pstmt->execute();
            delete pstmt;
            std::cout << "Updated successfully." << std::endl;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Update failed: " << e.what() << std::endl;
        }
    }

    void deleteDepartment(int dept_no) {   // ✅ signature pakai int
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "DELETE FROM departments WHERE dept_no = ?"
            );
            pstmt->setInt(1, dept_no);    // ✅ pakai int langsung
            pstmt->execute();
            delete pstmt;
            std::cout << "Deleted successfully." << std::endl;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Delete failed: " << e.what() << std::endl;
        }
    }
};
