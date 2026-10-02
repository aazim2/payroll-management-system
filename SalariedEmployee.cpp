#include "SalariedEmployee.h"
#include <iostream>
#include <iomanip>
using namespace std;

SalariedEmployee::SalariedEmployee(const string& id,
                                   const string& name,
                                   double salary,
                                   int experienceYears,
                                   double bonus,
                                   const string& maritalStatus,
                                   int dependents,
                                   const string& state,
                                   const string& city,
                                   const string& ssn,
                                   const string& address,
                                   int allowances,
                                   bool additionalWithhold,
                                   double additionalAmount)
    : Employee(id, name, salary, experienceYears, maritalStatus, 
               dependents, state, city, ssn, address, allowances,
               additionalWithhold, additionalAmount), bonus(bonus) {}

double SalariedEmployee::calculateGrossPay() const {
    double weeklySalary = basePay / 52.0;
    return weeklySalary + bonus;
}

void SalariedEmployee::displayInfo() const {
    double gross = calculateGrossPay();
    double tax = calculateTax();
    double net = calculateNetPay();

    cout << "SALARIED - ID: " << id
         << ", Name: " << name
         << ", Salary: $" << fixed << setprecision(2) << basePay << "/year"
         << ", Bonus: $" << bonus
         << ", Experience: " << experienceYears << " years"
         << ", Status: " << maritalStatus
         << ", Dependents: " << numDependents
         << ", Location: " << city << ", " << state
         << endl;

    cout << "           Gross: $" << gross
         << ", Tax: $" << tax
         << ", Net: $" << net
         << endl;
}
