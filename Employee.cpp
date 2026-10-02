#include "Employee.h"
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <cmath>
using namespace std;

Employee::Employee(const string& id,
                   const string& name,
                   double basePay,
                   int experienceYears,
                   const string& maritalStatus,
                   int numDependents,
                   const string& state,
                   const string& city,
                   const string& ssn,
                   const string& address,
                   int withholdingAllowances,
                   bool additionalWithholding,
                   double additionalWithholdingAmount)
    // Initialiser order follows the declaration order in Employee.h. Members are
    // always constructed in declaration order regardless of what is written here,
    // so listing them out of order is misleading and raises -Wreorder.
    : id(id), name(name), socialSecurityNumber(ssn), address(address),
      basePay(basePay), experienceYears(experienceYears),
      maritalStatus(maritalStatus), numDependents(numDependents),
      state(state), city(city),
      withholdingAllowances(withholdingAllowances), additionalWithholding(additionalWithholding),
      additionalWithholdingAmount(additionalWithholdingAmount),
      ytdGrossIncome(0.0), ytdFederalTax(0.0), ytdStateTax(0.0),
      ytdCityTax(0.0), ytdSocialSecurityTax(0.0), ytdMedicareTax(0.0) {}

double Employee::calculateTax() const {
    double gross = calculateGrossPay();
    double f = calculateFederalWithholding(gross);
    double s = calculateStateTax(gross);
    double c = calculateCityTax(gross);
    double ss = calculateSocialSecurityTax(gross);
    double m = calculateMedicareTax(gross);
    
    if (additionalWithholding)
        f += additionalWithholdingAmount;
    
    return f + s + c + ss + m;
}

double Employee::calculateNetPay() const {
    return calculateGrossPay() - calculateTax();
}

void Employee::recordPaystub(const string& payPeriod) {
    double gross = calculateGrossPay();
    double f = calculateFederalWithholding(gross);
    double s = calculateStateTax(gross);
    double c = calculateCityTax(gross);
    double ss = calculateSocialSecurityTax(gross);
    double m = calculateMedicareTax(gross);
    
    if (additionalWithholding)
        f += additionalWithholdingAmount;
    
    double net = gross - (f + s + c + ss + m);
    
    // Update YTD
    ytdGrossIncome += gross;
    ytdFederalTax += f;
    ytdStateTax += s;
    ytdCityTax += c;
    ytdSocialSecurityTax += ss;
    ytdMedicareTax += m;
    
    // Save paystub
    Paystub stub;
    stub.payPeriod = payPeriod;
    stub.grossPay = gross;
    stub.federalTax = f;
    stub.stateTax = s;
    stub.cityTax = c;
    stub.socialSecurityTax = ss;
    stub.medicareTax = m;
    stub.netPay = net;
    
    payHistory.push_back(stub);
}

double Employee::calculateFederalWithholding(double grossIncome) const {
    // Simple progressive tax for demonstration
    double tax = 0.0;
    
    if (grossIncome <= 500)
        tax = grossIncome * 0.10;
    else if (grossIncome <= 1500)
        tax = 500 * 0.10 + (grossIncome - 500) * 0.12;
    else
        tax = 500 * 0.10 + 1000 * 0.12 + (grossIncome - 1500) * 0.22;
    
    // Subtract allowance credit
    tax -= withholdingAllowances * 5.0;
    
    if (tax < 0)
        tax = 0;
    
    return tax;
}

double Employee::calculateStateTax(double grossIncome) const {
    return grossIncome * 0.05;  // 5% state tax
}

double Employee::calculateCityTax(double grossIncome) const {
    return grossIncome * 0.01;  // 1% city tax
}

double Employee::calculateSocialSecurityTax(double grossIncome) const {
    return grossIncome * 0.062; // 6.2% Social Security
}

double Employee::calculateMedicareTax(double grossIncome) const {
    return grossIncome * 0.0145; // 1.45% Medicare
}

void Employee::displayInfo() const {
    cout << "ID: " << id << ", Name: " << name 
         << ", Experience: " << experienceYears << " years"
         << ", Status: " << maritalStatus << ", Dependents: " << numDependents
         << ", Location: " << city << ", " << state;
}

bool Employee::operator==(const Employee& other) const {
    return this->id == other.id;
}

ostream& operator<<(ostream& os, const Employee& emp) {
    emp.displayInfo();
    return os;
}
