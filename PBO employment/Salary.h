#pragma once
#include "Database.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

class Salary : public Database {
public:
    // UPDATE Salary for existing emp_no
    void updateSalary(int emp_no, int new_salary, const std::string& from_date, const std::string& to_date) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "UPDATE salaries SET salary = ?, from_date = ?, to_date = ? WHERE emp_no = ?"
            );
            pstmt->setInt(1, new_salary);
            pstmt->setString(2, from_date);
            pstmt->setString(3, to_date);
            pstmt->setInt(4, emp_no);
            int affected = pstmt->executeUpdate();
            delete pstmt;

            if (affected > 0) {
                std::cout << "✅ Salary updated successfully." << std::endl;
            }
            else {
                std::cout << "⚠️  No salary record found for emp_no: " << emp_no << std::endl;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "❌ Update failed: " << e.what() << std::endl;
        }
    }

    // READ all salaries
    void readSalaries() {
        try {
            sql::Statement* stmt = getConnection()->createStatement();
            sql::ResultSet* res = stmt->executeQuery(
                "SELECT emp_no, salary, from_date, to_date FROM salaries"
            );
            std::cout << "\n=== Salaries List ===\n";
            while (res->next()) {
                std::cout << "Emp No: " << res->getInt("emp_no")
                    << ", Salary: " << res->getInt("salary")
                    << ", From: " << res->getString("from_date")
                    << ", To: " << res->getString("to_date")
                    << std::endl;
            }
            delete res;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "❌ Read failed: " << e.what() << std::endl;
        }
    }
};
