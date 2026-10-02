#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "PayrollManager.h"
#include "FileHandler.h"

using namespace std;

class Menu {
private:
    PayrollManager manager;
    FileHandler fileHandler;

    void showMainMenu();
    void addEmployeeMenu();
    void removeEmployeeMenu();
    void searchEmployeeMenu();
    void processPayrollMenu();
    void loadDataMenu();
    void saveDataMenu();
    void w2Menu();

public:
    Menu();
    void run();
};

#endif
