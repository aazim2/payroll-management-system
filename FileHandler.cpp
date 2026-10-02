#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "HourlyEmployee.h"
#include "SalariedEmployee.h"
using namespace std;

FileHandler::FileHandler(const string& filename) : filename(filename) {}

// Helper function to split CSV line
static vector<string> splitCSVLine(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void FileHandler::saveToFile(const PayrollManager& manager) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Cannot open file for writing: " << filename << endl;
        return;
    }

    // Write CSV header
    file << "Type,ID,Name,BasePay,ExperienceYears,MaritalStatus,Dependents,"
         << "State,City,SSN,Address,Allowances,AdditionalWithholding,AdditionalAmount,"
         << "YTDGross,YTDFederal,YTDState,YTDCity,YTDSocialSecurity,YTDMedicare,"
         << "HourlyRate,HoursWorked,Bonus\n";

    const vector<Employee*>& list = manager.getEmployees();

    for (size_t i = 0; i < list.size(); ++i) {
        Employee* emp = list[i];

        // Write common fields
        file << (dynamic_cast<HourlyEmployee*>(emp) ? "HOURLY" : "SALARIED") << ",";
        file << emp->getId() << ",";
        file << emp->getName() << ",";
        file << emp->getBasePay() << ",";
        file << emp->getExperienceYears() << ",";
        file << emp->getMaritalStatus() << ",";
        file << emp->getNumDependents() << ",";
        file << emp->getState() << ",";
        file << emp->getCity() << ",";
        file << emp->getSSN() << ",";
        file << emp->getAddress() << ",";
        file << emp->getWithholdingAllowances() << ",";
        file << (emp->getAdditionalWithholdingFlag() ? "1" : "0") << ",";
        file << emp->getAdditionalWithholdingAmount() << ",";
        file << emp->getYTDGross() << ",";
        file << emp->getYTDFederalTax() << ",";
        file << emp->getYTDStateTax() << ",";
        file << emp->getYTDCityTax() << ",";
        file << emp->getYTDSocialSecurityTax() << ",";
        file << emp->getYTDMedicareTax() << ",";

        // Write type-specific fields
        HourlyEmployee* h = dynamic_cast<HourlyEmployee*>(emp);
        SalariedEmployee* s = dynamic_cast<SalariedEmployee*>(emp);
        
        if (h != NULL) {
            file << h->getHourlyRate() << ",";
            file << h->getHoursWorked() << ",";
            file << "0";  // Bonus field for hourly employees
        } else if (s != NULL) {
            file << "0,";  // HourlyRate
            file << "0,";  // HoursWorked
            file << s->getBonus();  // Bonus for salaried
        }
        
        file << "\n";
    }

    file.close();
    cout << "Data saved to CSV file: " << filename << endl;
}

void FileHandler::loadFromFile(PayrollManager& manager) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Cannot open file for reading: " << filename << endl;
        return;
    }

    string line;
    
    // Skip header row
    getline(file, line);
    
    int lineNum = 1;
    while (getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;
        
        try {
            vector<string> tokens = splitCSVLine(line);
            
            if (tokens.size() < 23) {
                cout << "Warning: Line " << lineNum << " has incorrect format. Skipping." << endl;
                continue;
            }
            
            string type = tokens[0];
            string id = tokens[1];
            string name = tokens[2];
            double basePay = stod(tokens[3]);
            int exp = stoi(tokens[4]);
            string maritalStatus = tokens[5];
            int dependents = stoi(tokens[6]);
            string state = tokens[7];
            string city = tokens[8];
            string ssn = tokens[9];
            string address = tokens[10];
            int allowances = stoi(tokens[11]);
            bool addWh = (tokens[12] == "1");
            double addAmount = stod(tokens[13]);
            
            double ytdGross = stod(tokens[14]);
            double ytdFed = stod(tokens[15]);
            double ytdState = stod(tokens[16]);
            double ytdCity = stod(tokens[17]);
            double ytdSS = stod(tokens[18]);
            double ytdMed = stod(tokens[19]);
            
            // tokens[20] is the CSV's HourlyRate column. It is not read here:
            // HourlyEmployee derives the rate from basePay, so reading it would
            // give two sources of truth for the same figure.
            double hoursWorked = stod(tokens[21]);
            double bonus = stod(tokens[22]);
            
            Employee* emp = NULL;
            
            if (type == "HOURLY") {
                emp = new HourlyEmployee(
                    id, name, basePay, exp, hoursWorked,
                    maritalStatus, dependents, state, city,
                    ssn, address, allowances, addWh, addAmount
                );
            }
            else if (type == "SALARIED") {
                emp = new SalariedEmployee(
                    id, name, basePay, exp, bonus,
                    maritalStatus, dependents, state, city,
                    ssn, address, allowances, addWh, addAmount
                );
            }
            
            if (emp != NULL) {
                emp->setYTDGross(ytdGross);
                emp->setYTDFederalTax(ytdFed);
                emp->setYTDStateTax(ytdState);
                emp->setYTDCityTax(ytdCity);
                emp->setYTDSocialSecurityTax(ytdSS);
                emp->setYTDMedicareTax(ytdMed);
                
                manager.addEmployee(emp);
            }
        }
        catch (const exception& e) {
            cout << "Error parsing line " << lineNum << ": " << e.what() << endl;
            continue;
        }
    }

    file.close();
    cout << "Data loaded from CSV file: " << filename << endl;
}
