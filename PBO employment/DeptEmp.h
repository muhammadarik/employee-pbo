#pragma once
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>



class DeptEmp : public Database {
public:
    void createDeptEmp(int emp_no, int dept_no, std::string from_date, std::string to_date) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "INSERT INTO dept_emp (emp_no, dept_no, from_date, to_date) VALUES (?, ?, ?, ?)"
            );
            pstmt->setInt(1, emp_no);
            pstmt->setInt(2, dept_no);  // ✅ int sesuai kolom numeric
            pstmt->setString(3, from_date);
            pstmt->setString(4, to_date);
            pstmt->execute();
            delete pstmt;
            std::cout << "DeptEmp added successfully." << std::endl;
        }
        catch (sql::SQLException& e) {
            std::cerr << "Create failed: " << e.what() << std::endl;
        }
    }
};
