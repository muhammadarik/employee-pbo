#pragma once
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

class Title : public Database {
public:
    // UPDATE Title for existing emp_no
    void updateTitle(int emp_no, const std::string& new_title, const std::string& from_date, const std::string& to_date) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "UPDATE titles SET title = ?, from_date = ?, to_date = ? WHERE emp_no = ?"
            );
            pstmt->setString(1, new_title);
            pstmt->setString(2, from_date);
            pstmt->setString(3, to_date);
            pstmt->setInt(4, emp_no);
            int affected = pstmt->executeUpdate();
            delete pstmt;

            if (affected > 0) {
                std::cout << "✅ Title updated successfully." << std::endl;
            }
            else {
                std::cout << "⚠️  No title record found for emp_no: " << emp_no << std::endl;
            }
        }
        catch (const sql::SQLException& e) {
            std::cerr << "❌ Update failed: " << e.what() << std::endl;
        }
    }

    // READ all Titles
    void readTitles() {
        try {
            sql::Statement* stmt = getConnection()->createStatement();
            sql::ResultSet* res = stmt->executeQuery(
                "SELECT emp_no, title, from_date, to_date FROM titles"
            );
            std::cout << "\n=== Titles List ===\n";
            while (res->next()) {
                std::cout << "Emp No: " << res->getInt("emp_no")
                    << ", Title: " << res->getString("title")
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
