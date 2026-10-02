#include "PayrollManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

PayrollManager::PayrollManager() {}

PayrollManager::~PayrollManager() {
    clearAll();
}

void PayrollManager::addEmployee(Employee* emp) {
    if (emp != NULL) {
        employees.push_back(emp);
    }
}

bool PayrollManager::removeEmployee(const string& id) {
    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i]->getId() == id) {
            delete employees[i];
            employees.erase(employees.begin() + i);
            return true;
        }
    }
    return false;
}

Employee* PayrollManager::findEmployee(const string& id) const {
    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i]->getId() == id) {
            return employees[i];
        }
    }
    return NULL;
}

// Template function implementation
template<typename T>
Employee* PayrollManager::findEmployeeByAttribute(T value, function<T(Employee*)> getter) const {
    for (size_t i = 0; i < employees.size(); ++i) {
        if (getter(employees[i]) == value) {
            return employees[i];
        }
    }
    return NULL;
}

// Explicit instantiation
template Employee* PayrollManager::findEmployeeByAttribute<string>(string, function<string(Employee*)>) const;

void PayrollManager::processPayroll(const string& payPeriod) {
    if (employees.empty()) {
        cout << "No employees to process payroll for." << endl;
        return;
    }

    cout << "\nProcessing payroll for: " << payPeriod << endl;

    for (size_t i = 0; i < employees.size(); ++i) {
        employees[i]->recordPaystub(payPeriod);
        cout << "Processed: " << employees[i]->getName() 
             << " - Gross: $" << fixed << setprecision(2) << employees[i]->calculateGrossPay()
             << ", Net: $" << employees[i]->calculateNetPay() << endl;
    }

    cout << "Payroll processing completed.\n" << endl;
}

void PayrollManager::listAllEmployees() const {
    if (employees.empty()) {
        cout << "No employees found." << endl;
        return;
    }

    cout << "\n=== Employee List ===" << endl;

    for (size_t i = 0; i < employees.size(); ++i) {
        cout << (i + 1) << ". "
             << employees[i]->getId()
             << " - " << employees[i]->getName()
             << " (" << employees[i]->getCity()
             << ", " << employees[i]->getState() << ")"
             << endl;
    }

    cout << endl;
}

void PayrollManager::showEmployeeDetails(const string& id) const {
    Employee* emp = findEmployee(id);

    if (emp == NULL) {
        cout << "Employee not found." << endl;
        return;
    }

    cout << "\n=== Employee Details ===" << endl;
    emp->displayInfo();

    cout << "\n=== Pay History ===" << endl;
    const vector<Paystub>& history = emp->getPayHistory();

    if (history.empty()) {
        cout << "No pay history available." << endl;
    } else {
        for (size_t i = 0; i < history.size(); ++i) {
            cout << "[" << history[i].payPeriod << "] "
                 << "Gross: $" << fixed << setprecision(2) << history[i].grossPay
                 << ", Net: $" << history[i].netPay
                 << endl;
        }
    }

    cout << endl;
}

void PayrollManager::clearAll() {
    for (size_t i = 0; i < employees.size(); ++i) {
        delete employees[i];
    }
    employees.clear();
}

void PayrollManager::generateW2(const string& id) const {
    Employee* emp = findEmployee(id);

    if (emp == NULL) {
        cout << "Employee not found.\n";
        return;
    }

    string filename = "W2_" + emp->getId() + ".txt";
    ofstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "Error: Cannot create W-2 file.\n";
        return;
    }

    file << "================== W-2 Wage and Tax Statement ==================\n\n";
    file << "Employee Name : " << emp->getName() << "\n";
    file << "SSN           : " << emp->getSSN() << "\n";
    file << "Address       : " << emp->getAddress() << "\n";
    file << "City          : " << emp->getCity() << "\n";
    file << "State         : " << emp->getState() << "\n\n";

    file << "---------------------------- INCOME -----------------------------\n";
    file << "Box 1 – Wages, Tips:               $" << emp->getYTDGross() << "\n\n";

    file << "----------------------- FEDERAL TAX -----------------------------\n";
    file << "Box 2 – Federal Income Tax:        $" << emp->getYTDFederalTax() << "\n\n";

    file << "---------------- SOCIAL SECURITY & MEDICARE ---------------------\n";
    file << "Box 3 – Social Security Wages:     $" << emp->getYTDGross() << "\n";
    file << "Box 4 – Social Security Tax:       $" << emp->getYTDSocialSecurityTax() << "\n";
    file << "Box 5 – Medicare Wages:            $" << emp->getYTDGross() << "\n";
    file << "Box 6 – Medicare Tax:              $" << emp->getYTDMedicareTax() << "\n\n";

    file << "----------------------------- STATE ------------------------------\n";
    file << "Box 16 – State Wages:              $" << emp->getYTDGross() << "\n";
    file << "Box 17 – State Tax Withheld:       $" << emp->getYTDStateTax() << "\n";

    file << "\n=================================================================\n";

    file.close();
    cout << "W-2 generated successfully: " << filename << endl;
}
