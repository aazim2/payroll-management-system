#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Paystub {
    string payPeriod;
    double grossPay;
    double federalTax;
    double stateTax;
    double cityTax;
    double socialSecurityTax;
    double medicareTax;
    double netPay;
};

class Employee {
protected:
    string id;
    string name;
    string socialSecurityNumber;
    string address;
    double basePay;
    int experienceYears;
    string maritalStatus;
    int numDependents;
    string state;
    string city;
    
    int withholdingAllowances;
    bool additionalWithholding;
    double additionalWithholdingAmount;
    
    double ytdGrossIncome;
    double ytdFederalTax;
    double ytdStateTax;
    double ytdCityTax;
    double ytdSocialSecurityTax;
    double ytdMedicareTax;
    
    vector<Paystub> payHistory;

public:
    Employee(const string& id,
             const string& name,
             double basePay,
             int experienceYears,
             const string& maritalStatus = "single",
             int numDependents = 0,
             const string& state = "NY",
             const string& city = "NYC",
             const string& ssn = "",
             const string& address = "",
             int withholdingAllowances = 1,
             bool additionalWithholding = false,
             double additionalWithholdingAmount = 0.0);
    
    virtual ~Employee() {}

    virtual double calculateGrossPay() const = 0;
    virtual void displayInfo() const;
    
    double calculateTax() const;
    double calculateNetPay() const;
    void recordPaystub(const string& payPeriod);
    
    double calculateFederalWithholding(double grossIncome) const;
    double calculateStateTax(double grossIncome) const;
    double calculateCityTax(double grossIncome) const;
    double calculateSocialSecurityTax(double grossIncome) const;
    double calculateMedicareTax(double grossIncome) const;
    
    bool operator==(const Employee& other) const;
    friend ostream& operator<<(ostream& os, const Employee& emp);

    // Getters
    const string& getId() const { return id; }
    const string& getName() const { return name; }
    const string& getSSN() const { return socialSecurityNumber; }
    const string& getAddress() const { return address; }
    double getBasePay() const { return basePay; }
    int getExperienceYears() const { return experienceYears; }
    const string& getMaritalStatus() const { return maritalStatus; }
    int getNumDependents() const { return numDependents; }
    const string& getState() const { return state; }
    const string& getCity() const { return city; }
    int getWithholdingAllowances() const { return withholdingAllowances; }
    bool getAdditionalWithholdingFlag() const { return additionalWithholding; }
    double getAdditionalWithholdingAmount() const { return additionalWithholdingAmount; }
    double getYTDGross() const { return ytdGrossIncome; }
    double getYTDFederalTax() const { return ytdFederalTax; }
    double getYTDStateTax() const { return ytdStateTax; }
    double getYTDCityTax() const { return ytdCityTax; }
    double getYTDSocialSecurityTax() const { return ytdSocialSecurityTax; }
    double getYTDMedicareTax() const { return ytdMedicareTax; }
    const vector<Paystub>& getPayHistory() const { return payHistory; }

    // Setters
    void setYTDGross(double amount) { ytdGrossIncome = amount; }
    void setYTDFederalTax(double amount) { ytdFederalTax = amount; }
    void setYTDStateTax(double amount) { ytdStateTax = amount; }
    void setYTDCityTax(double amount) { ytdCityTax = amount; }
    void setYTDSocialSecurityTax(double amount) { ytdSocialSecurityTax = amount; }
    void setYTDMedicareTax(double amount) { ytdMedicareTax = amount; }
};

#endif
