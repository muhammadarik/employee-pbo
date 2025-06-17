#pragma once
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

class DeptManager : public Database {
public:
    void createDeptManager(std::string dept_no, int emp_no, std::string from_date, std::string to_date) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "INSERT INTO dept_manager (dept_no, emp_no, from_date, to_date) VALUES (?, ?, ?, ?)"
            );
            pstmt->setString(1, dept_no);
            pstmt->setInt(2, emp_no);
            pstmt->setString(3, from_date);
            pstmt->setString(4, to_date);
            pstmt->execute();
            delete pstmt;
            std::cout << "DeptManager added successfully." << std::endl;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Create failed: " << e.what() << std::endl;
        }
    }
};
