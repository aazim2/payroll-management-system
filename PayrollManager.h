#ifndef PAYROLLMANAGER_H
#define PAYROLLMANAGER_H

#include <vector>
#include <string>
#include <functional>
#include "Employee.h"

using namespace std;

class PayrollManager {
private:
    vector<Employee*> employees;

public:
    PayrollManager();
    ~PayrollManager();
    
    const vector<Employee*>& getEmployees() const { return employees; }
    
    void addEmployee(Employee* emp);
    bool removeEmployee(const string& id);
    Employee* findEmployee(const string& id) const;
    
    // Template function - project requirement
    template<typename T>
    Employee* findEmployeeByAttribute(T value, function<T(Employee*)> getter) const;
    
    void processPayroll(const string& payPeriod);
    void listAllEmployees() const;
    void showEmployeeDetails(const string& id) const;
    
    void clearAll();
    void generateW2(const string& id) const;
};

#endif
