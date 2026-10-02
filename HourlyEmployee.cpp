#include "HourlyEmployee.h"
#include <iostream>
#include <iomanip>
using namespace std;

HourlyEmployee::HourlyEmployee(const string& id,
                               const string& name,
                               double hourlyRate,
                               int experienceYears,
                               double hoursWorked,
                               const string& maritalStatus,
                               int dependents,
                               const string& state,
                               const string& city,
                               const string& ssn,
                               const string& address,
                               int allowances,
                               bool additionalWithhold,
                               double additionalAmount)
    : Employee(id, name, hourlyRate, experienceYears, maritalStatus, 
               dependents, state, city, ssn, address, allowances,
               additionalWithhold, additionalAmount),
      hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}

double HourlyEmployee::calculateGrossPay() const {
    double regularHours = (hoursWorked > 40) ? 40 : hoursWorked;
    double overtimeHours = (hoursWorked > 40) ? (hoursWorked - 40) : 0;
    
    return (regularHours * hourlyRate) + (overtimeHours * hourlyRate * 1.5);
}

void HourlyEmployee::displayInfo() const {
    double gross = calculateGrossPay();
    double tax = calculateTax();
    double net = calculateNetPay();

    cout << "HOURLY - ID: " << id
         << ", Name: " << name
         << ", Rate: $" << fixed << setprecision(2) << hourlyRate
         << ", Hours: " << hoursWorked
         << ", Experience: " << experienceYears << " years"
         << ", Status: " << maritalStatus
         << ", Dependents: " << numDependents
         << ", Location: " << city << ", " << state
         << endl;

    cout << "         Gross: $" << gross
         << ", Tax: $" << tax
         << ", Net: $" << net
         << endl;
}
