#ifndef SALARIEDEMPLOYEE_H
#define SALARIEDEMPLOYEE_H

#include "Employee.h"

class SalariedEmployee : public Employee {
private:
    double bonus;

public:
    SalariedEmployee(const string& id,
                     const string& name,
                     double salary,
                     int experienceYears = 0,
                     double bonus = 0.0,
                     const string& maritalStatus = "single",
                     int dependents = 0,
                     const string& state = "CA",
                     const string& city = "Los Angeles",
                     const string& ssn = "",
                     const string& address = "",
                     int allowances = 1,
                     bool additionalWithhold = false,
                     double additionalAmount = 0.0);

    double calculateGrossPay() const;
    void displayInfo() const;

    double getBonus() const { return bonus; }
    void setBonus(double b) { bonus = b; }
};

#endif
