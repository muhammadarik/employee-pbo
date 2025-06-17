#include <iostream>
#include "Employee.h"
#include "Department.h"
#include "DeptEmp.h"
#include "DeptManager.h"
#include "Title.h"
#include "Salary.h"
#include "Benefit.h"


using namespace std;

void showMenu() {
    cout << "\n====== MENU CRUD ======" << endl;
    cout << "1. Create Employee" << endl;
    cout << "2. Read Employees" << endl;
    cout << "3. Update Employee" << endl;
    cout << "4. Delete Employee" << endl;
    cout << "5. Create Department" << endl;
    cout << "6. Create DeptEmp" << endl;
    cout << "7. Create DeptManager" << endl;
    cout << "8. Update Salary" << endl;
    cout << "9. Update Title" << endl;
    cout << "10. Read Salaries" << endl;
    cout << "11. Read Titles" << endl;
    cout << "12. Update Benefit" << endl;
    cout << "13. Read Benefits" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose: ";
}

int main() {
    Employee emp;
    Department dep;
    DeptEmp depEmp;
    DeptManager depMgr;
    Salary sal;
    Title titl;
    Benefit ben;

    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int emp_no;
            string full_name, gender, birth, hire;
            cout << "Enter Emp No: ";
            cin >> emp_no;
            cin.ignore();
            cout << "Enter Full Name: ";
            getline(cin, full_name);
            cout << "Enter Gender: ";
            cin >> gender;
            cout << "Enter Birth Date (YYYY-MM-DD): ";
            cin >> birth;
            cout << "Enter Hire Date (YYYY-MM-DD): ";
            cin >> hire;
            emp.createEmployee(emp_no, full_name, gender, birth, hire);
            break;
        }
        case 2:
            emp.readEmployees();
            break;
        case 3: {
            int emp_no;
            string full_name, gender, birth, hire;
            string employee_type, email, phone;

            cout << "Enter Emp No to Update: ";
            cin >> emp_no;
            cin.ignore();
            cout << "Enter New Full Name: ";
            getline(cin, full_name);
            cout << "Enter Gender: ";
            cin >> gender;
            cout << "Enter Birth Date (YYYY-MM-DD): ";
            cin >> birth;
            cout << "Enter Hire Date (YYYY-MM-DD): ";
            cin >> hire;
            cin.ignore();
            cout << "Enter Employee Type (e.g., Staff, Manager): ";
            getline(cin, employee_type);
            cout << "Enter Email: ";
            getline(cin, email);
            cout << "Enter Phone: ";
            getline(cin, phone);

            emp.updateEmployee(emp_no, full_name, gender, birth, hire,
                employee_type, email, phone);
            break;
        }
        case 4: {
            int emp_no;
            cout << "Enter Emp No to Delete: ";
            cin >> emp_no;
            emp.deleteEmployee(emp_no);
            break;
        }
        case 5: {
            int dept_no;
            string dept_name;
            cout << "Enter Department No (int): ";
            cin >> dept_no;
            cin.ignore();
            cout << "Enter Department Name: ";
            getline(cin, dept_name);
            dep.createDepartment(dept_no, dept_name);
            break;
        }
        case 6: {
            int emp_no, dept_no;
            string from_date, to_date;
            cout << "Enter Emp No: ";
            cin >> emp_no;
            cout << "Enter Dept No (int): ";
            cin >> dept_no;
            cout << "Enter From Date (YYYY-MM-DD): ";
            cin >> from_date;
            cout << "Enter To Date (YYYY-MM-DD): ";
            cin >> to_date;
            depEmp.createDeptEmp(emp_no, dept_no, from_date, to_date);
            break;
        }
        case 7: {
            string dept_no;
            int emp_no;
            string from_date, to_date;
            cin.ignore();
            cout << "Enter Dept No (string): ";
            getline(cin, dept_no);
            cout << "Enter Emp No: ";
            cin >> emp_no;
            cout << "Enter From Date (YYYY-MM-DD): ";
            cin >> from_date;
            cout << "Enter To Date (YYYY-MM-DD): ";
            cin >> to_date;
            depMgr.createDeptManager(dept_no, emp_no, from_date, to_date);
            break;
        }
        case 8: {
            int emp_no, new_salary;
            string from_date, to_date;
            cout << "Enter Emp No: ";
            cin >> emp_no;
            cout << "Enter New Salary: ";
            cin >> new_salary;
            cout << "Enter From Date (YYYY-MM-DD): ";
            cin >> from_date;
            cout << "Enter To Date (YYYY-MM-DD): ";
            cin >> to_date;
            sal.updateSalary(emp_no, new_salary, from_date, to_date);
            break;
        }
        case 9: {
            int emp_no;
            string new_title, from_date, to_date;
            cout << "Enter Emp No: ";
            cin >> emp_no;
            cin.ignore();
            cout << "Enter New Title: ";
            getline(cin, new_title);
            cout << "Enter From Date (YYYY-MM-DD): ";
            cin >> from_date;
            cout << "Enter To Date (YYYY-MM-DD): ";
            cin >> to_date;
            titl.updateTitle(emp_no, new_title, from_date, to_date);
            break;
        }
        case 10:
            sal.readSalaries();
            break;
        case 11:
            titl.readTitles();
            break;
        case 12: {
            int emp_no, health, retire, life;
            string add_benefit;
            double add_value;

            cout << "Enter Emp No: ";
            cin >> emp_no;

            cout << "Health Insurance (1/0): ";
            cin >> health;

            cout << "Retirement Plan (1/0): ";
            cin >> retire;

            cout << "Life Insurance (1/0): ";
            cin >> life;

            cin.ignore();
            cout << "Additional Benefits: ";
            getline(cin, add_benefit);

            cout << "Additional Benefit Values: ";
            cin >> add_value;

            ben.updateBenefit(emp_no, health, retire, life, add_benefit, add_value);
            break;
        }
        case 13:
            ben.readBenefits();
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option." << endl;
        }
    } while (choice != 0);

    return 0;
}
