#include "Menu.h"
#include "HourlyEmployee.h"
#include "SalariedEmployee.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

Menu::Menu() : fileHandler("employees.csv") {}

void Menu::showMainMenu() {
    cout << "\n========== PAYROLL SYSTEM ==========\n";
    cout << "1. Add Employee\n";
    cout << "2. Remove Employee\n";
    cout << "3. Search Employee\n";
    cout << "4. List All Employees\n";
    cout << "5. Process Payroll\n";
    cout << "6. Load From File\n";
    cout << "7. Save To File\n";
    cout << "8. Generate W-2\n";
    cout << "0. Exit\n";
    cout << "====================================\n";
    cout << "Enter choice: ";
}

void Menu::addEmployeeMenu() {
    int type;
    cout << "\n1. Hourly Employee\n2. Salaried Employee\nEnter type: ";
    cin >> type;
    
    
    
      try {
        if (!(cin >> type)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input: Please enter a number (1 or 2)");
        }
        
        if (type != 1 && type != 2) {
            throw out_of_range("Invalid employee type. Enter 1 (Hourly) or 2 (Salaried).");
        }
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return;
    }
    
    

    string id, name, maritalStatus, state, city, ssn, address;
    int experience, dependents, allowances;
    bool addWh;
    double addAmount;

    cout << "Enter ID: ";
    cin >> id;
    
    try {
        if (manager.findEmployee(id) != nullptr) {
            throw runtime_error("Employee ID " + id + " already exists!");
        }
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return;
    }
    
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Experience Years: ";
    
    if (!(cin >> experience) || experience < 0) {
        cout << "Invalid experience. Setting to 0." << endl;
        experience = 0;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    
    cout << "Enter Marital Status (Single/Married): ";
    cin >> maritalStatus;
    cout << "Enter Dependents: ";
    cin >> dependents;
    cout << "Enter State: ";
    cin >> state;
    cout << "Enter City: ";
    cin >> city;
    cout << "Enter SSN (xxx-xx-xxxx): ";
    cin >> ssn;
    cout << "Enter Address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter Allowances: ";
    cin >> allowances;



    cout << "Additional Withholding? (1=yes, 0=no): ";
    cin >> addWh;
    if (addWh) {
        cout << "Enter Additional Amount: ";
        cin >> addAmount;
    } else {
        addAmount = 0.0;
    }

    try {
        if (type == 1) {
            double rate, hours;
            cout << "Enter Hourly Rate: ";
            cin >> rate;
            cout << "Enter Hours Worked: ";
            cin >> hours;

            Employee* emp = new HourlyEmployee(
                id, name, rate, experience, hours,
                maritalStatus, dependents, state, city,
                ssn, address, allowances, addWh, addAmount
            );
            manager.addEmployee(emp);
        }
        else if (type == 2) {
            double salary, bonus;
            cout << "Enter Annual Salary: ";
            cin >> salary;
            cout << "Enter Weekly Bonus: ";
            cin >> bonus;

            Employee* emp = new SalariedEmployee(
                id, name, salary, experience, bonus,
                maritalStatus, dependents, state, city,
                ssn, address, allowances, addWh, addAmount
            );
            manager.addEmployee(emp);
        }
        else {
            throw invalid_argument("Invalid employee type");
        }

        cout << "Employee added successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::removeEmployeeMenu() {
    string id;
    cout << "Enter Employee ID to remove: ";
    cin >> id;

    if (manager.removeEmployee(id))
        cout << "Employee removed.\n";
    else
        cout << "Employee not found.\n";
}

void Menu::searchEmployeeMenu() {
    string id;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    manager.showEmployeeDetails(id);
}

void Menu::processPayrollMenu() {
    string period;
    cout << "Enter Pay Period (e.g., 01/15/2025): ";
    cin >> period;

    manager.processPayroll(period);
}

void Menu::loadDataMenu() {
    cout << "Loading employees from file...\n";
    try {
        manager.clearAll();
        fileHandler.loadFromFile(manager);
    }
    catch (const exception& e) {
        cout << "Error loading file: " << e.what() << endl;
    }
}

void Menu::saveDataMenu() {
    cout << "Saving employees...\n";
    try {
        fileHandler.saveToFile(manager);
    }
    catch (const exception& e) {
        cout << "Error saving file: " << e.what() << endl;
    }
}

void Menu::w2Menu() {
    string id;
    cout << "Enter Employee ID for W-2: ";
    cin >> id;
    manager.generateW2(id);
}

void Menu::run() {
    int choice;
    
    // Load data automatically on startup
    try {
        loadDataMenu();
    } 
    catch (...) {
        cout << "Starting with empty employee database.\n";
    }

    while (true) {
        try {
            showMainMenu();
            cin >> choice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input. Please enter a number.");
            }
            
            switch (choice) {
                case 1: addEmployeeMenu(); break;
                case 2: removeEmployeeMenu(); break;
                case 3: searchEmployeeMenu(); break;
                case 4: manager.listAllEmployees(); break;
                case 5: processPayrollMenu(); break;
                case 6: loadDataMenu(); break;
                case 7: saveDataMenu(); break;
                case 8: w2Menu(); break;
                case 0:
                    cout << "\nSaving data before exit...\n";
                    saveDataMenu();
                    cout << "Exiting program. Goodbye!\n";
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } 
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        } 
        catch (...) {
            cout << "Unknown error occurred.\n";
        }
    }
}
