#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "PayrollManager.h"

using namespace std;

class FileHandler {
private:
    string filename;

public:
    FileHandler(const string& filename = "employees.csv");
    
    void saveToFile(const PayrollManager& manager);
    void loadFromFile(PayrollManager& manager);
    
    void setFilename(const string& fname) { filename = fname; }
    string getFilename() const { return filename; }
};

#endif
