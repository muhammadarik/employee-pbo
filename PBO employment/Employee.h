#pragma once
#include "Database.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

class Employee : public Database {
public:
    // CREATE Employee + Auto Create Empty Salary & Title row
    void createEmployee(int emp_no, const std::string& full_name, const std::string& gender,
        const std::string& birth, const std::string& hire) {
        try {
            // Insert Employee (basic fields only)
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "INSERT INTO employees (emp_no, full_name, gender, birth_date, hire_date) "
                "VALUES (?, ?, ?, ?, ?)"
            );
            pstmt->setInt(1, emp_no);
            pstmt->setString(2, full_name);
            pstmt->setString(3, gender);
            pstmt->setString(4, birth);
            pstmt->setString(5, hire);
            pstmt->execute();
            delete pstmt;
            std::cout << "Employee added successfully." << std::endl;

            // Insert empty salary row
            pstmt = getConnection()->prepareStatement(
                "INSERT INTO salaries (emp_no, salary, from_date, to_date) VALUES (?, 0, ?, ?)"
            );
            pstmt->setInt(1, emp_no);
            pstmt->setString(2, hire);
            pstmt->setString(3, "9999-12-31");
            pstmt->execute();
            delete pstmt;
            std::cout << "Empty salary row created." << std::endl;

            // Insert empty title row
            pstmt = getConnection()->prepareStatement(
                "INSERT INTO titles (emp_no, title, from_date, to_date) VALUES (?, '', ?, ?)"
            );
            pstmt->setInt(1, emp_no);
            pstmt->setString(2, hire);
            pstmt->setString(3, "9999-12-31");
            pstmt->execute();
            delete pstmt;
            std::cout << "Empty title row created." << std::endl;

            // Setelah insert empty title row
            // Tambah insert benefit row
            pstmt = getConnection()->prepareStatement(
                "INSERT INTO benefits (emp_no, health_insurance, retirement_plan, life_insurance, additional_benefits, additional_benefit_values) "
                "VALUES (?, 0, 0, 0, '', 0)"
            );
            pstmt->setInt(1, emp_no);
            pstmt->execute();
            delete pstmt;
            std::cout << "Empty benefit row created." << std::endl;


        }
        catch (const sql::SQLException& e) {
            std::cerr << "Create Employee failed: " << e.what() << std::endl;
        }
    }

    // READ Employees - output as table
    void readEmployees() {
        try {
            sql::Statement* stmt = getConnection()->createStatement();
            sql::ResultSet* res = stmt->executeQuery(
                "SELECT emp_no, full_name, gender, birth_date, hire_date, "
                "employee_type, email, phone "
                "FROM employees"
            );

            // Header
            std::cout << "\n=== Employee List ===\n";
            std::cout << std::left
                << std::setw(8) << "EmpNo"
                << std::setw(20) << "Full Name"
                << std::setw(8) << "Gender"
                << std::setw(12) << "Birth Date"
                << std::setw(12) << "Hire Date"
                << std::setw(15) << "Type"
                << std::setw(25) << "Email"
                << std::setw(15) << "Phone"
                << std::endl;

            std::cout << std::string(115, '-') << std::endl;

            // Rows
            while (res->next()) {
                std::cout << std::left
                    << std::setw(8) << res->getInt("emp_no")
                    << std::setw(20) << res->getString("full_name")
                    << std::setw(8) << res->getString("gender")
                    << std::setw(12) << res->getString("birth_date")
                    << std::setw(12) << res->getString("hire_date")
                    << std::setw(15) << res->getString("employee_type")
                    << std::setw(25) << res->getString("email")
                    << std::setw(15) << res->getString("phone")
                    << std::endl;
            }

            delete res;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Read failed: " << e.what() << std::endl;
        }
    }


    // UPDATE Employee (without performance_rating)
    void updateEmployee(int emp_no,
        const std::string& full_name,
        const std::string& gender,
        const std::string& birth,
        const std::string& hire,
        const std::string& employee_type,
        const std::string& email,
        const std::string& phone) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "UPDATE employees SET "
                "full_name = ?, gender = ?, birth_date = ?, hire_date = ?, "
                "employee_type = ?, email = ?, phone = ? "
                "WHERE emp_no = ?"
            );
            pstmt->setString(1, full_name);
            pstmt->setString(2, gender);
            pstmt->setString(3, birth);
            pstmt->setString(4, hire);
            pstmt->setString(5, employee_type);
            pstmt->setString(6, email);
            pstmt->setString(7, phone);
            pstmt->setInt(8, emp_no);
            pstmt->execute();
            delete pstmt;
            std::cout << "Employee updated successfully." << std::endl;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Update failed: " << e.what() << std::endl;
        }
    }

    // DELETE Employee
    void deleteEmployee(int emp_no) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "DELETE FROM employees WHERE emp_no = ?"
            );
            pstmt->setInt(1, emp_no);
            pstmt->execute();
            delete pstmt;
            std::cout << "Employee deleted successfully." << std::endl;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Delete failed: " << e.what() << std::endl;
        }
    }
};
