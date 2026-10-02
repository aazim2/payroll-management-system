#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H

#include "Employee.h"

class HourlyEmployee : public Employee {
private:
    double hourlyRate;
    double hoursWorked;

public:
    HourlyEmployee(const string& id,
                   const string& name,
                   double hourlyRate,
                   int experienceYears = 0,
                   double hoursWorked = 40.0,
                   const string& maritalStatus = "single",
                   int dependents = 0,
                   const string& state = "NY",
                   const string& city = "NYC",
                   const string& ssn = "",
                   const string& address = "",
                   int allowances = 1,
                   bool additionalWithhold = false,
                   double additionalAmount = 0.0);

    double calculateGrossPay() const;
    void displayInfo() const;

    double getHourlyRate() const { return hourlyRate; }
    double getHoursWorked() const { return hoursWorked; }
    void setHourlyRate(double rate) { hourlyRate = rate; basePay = rate; }
    void setHoursWorked(double hours) { hoursWorked = hours; }
};

#endif
