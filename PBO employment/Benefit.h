#pragma once
#include "Database.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

class Benefit : public Database {
public:
    // CREATE Benefit (insert empty row)
    void createBenefit(int emp_no) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "INSERT INTO benefits (emp_no, health_insurance, retirement_plan, life_insurance, "
                "additional_benefits, additional_benefit_values) "
                "VALUES (?, 0, 0, 0, '', 0)"
            );
            pstmt->setInt(1, emp_no);
            pstmt->execute();
            delete pstmt;
            std::cout << "Empty benefit row created." << std::endl;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Create Benefit failed: " << e.what() << std::endl;
        }
    }

    // READ Benefits - output as table
    void readBenefits() {
        try {
            sql::Statement* stmt = getConnection()->createStatement();
            sql::ResultSet* res = stmt->executeQuery(
                "SELECT benefit_id, emp_no, health_insurance, retirement_plan, life_insurance, "
                "additional_benefits, additional_benefit_values "
                "FROM benefits"
            );

            std::cout << "\n=== Benefit List ===\n";
            std::cout << std::left
                << std::setw(10) << "BenefitID"
                << std::setw(8) << "EmpNo"
                << std::setw(18) << "Health Insurance"
                << std::setw(18) << "Retirement Plan"
                << std::setw(16) << "Life Insurance"
                << std::setw(30) << "Additional Benefits"
                << std::setw(20) << "Add Benefit Values"
                << std::endl;

            std::cout << std::string(120, '-') << std::endl;

            while (res->next()) {
                std::cout << std::left
                    << std::setw(10) << res->getInt("benefit_id")
                    << std::setw(8) << res->getInt("emp_no")
                    << std::setw(18) << res->getInt("health_insurance")
                    << std::setw(18) << res->getInt("retirement_plan")
                    << std::setw(16) << res->getInt("life_insurance")
                    << std::setw(30) << res->getString("additional_benefits")
                    << std::setw(20) << res->getDouble("additional_benefit_values")
                    << std::endl;
            }

            delete res;
            delete stmt;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Read Benefits failed: " << e.what() << std::endl;
        }
    }

    // UPDATE Benefit
    void updateBenefit(int emp_no,
        int health_insurance,
        int retirement_plan,
        int life_insurance,
        const std::string& additional_benefits,
        double additional_benefit_values) {
        try {
            sql::PreparedStatement* pstmt = getConnection()->prepareStatement(
                "UPDATE benefits SET "
                "health_insurance = ?, "
                "retirement_plan = ?, "
                "life_insurance = ?, "
                "additional_benefits = ?, "
                "additional_benefit_values = ? "
                "WHERE emp_no = ?"
            );
            pstmt->setInt(1, health_insurance);
            pstmt->setInt(2, retirement_plan);
            pstmt->setInt(3, life_insurance);
            pstmt->setString(4, additional_benefits);
            pstmt->setDouble(5, additional_benefit_values);
            pstmt->setInt(6, emp_no);
            pstmt->execute();
            delete pstmt;
            std::cout << "Benefit updated successfully." << std::endl;
        }
        catch (const sql::SQLException& e) {
            std::cerr << "Update Benefit failed: " << e.what() << std::endl;
        }
    }
};
