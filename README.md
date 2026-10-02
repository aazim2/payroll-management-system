# Payroll Management System

A console payroll application in C++ that calculates pay and withholding for hourly
and salaried staff, persists records to CSV, and generates W-2 wage and tax statements.

Written for CSCI 272 (Object-Oriented Programming in C++) at New York City College
of Technology, CUNY.

## Build and run

```bash
make
./payroll
```

Requires a C++17 compiler. No external dependencies.

`employees.csv` holds a sample record, so the program has something to load on first
run. Menu option 6 reads it; option 7 writes back to it.

## What it does

```
1. Add Employee        5. Process Payroll
2. Remove Employee     6. Load From File
3. Search Employee     7. Save To File
4. List All Employees  8. Generate W-2
```

**Pay calculation.** Hourly staff are paid rate × hours; salaried staff receive a
period fraction of annual base plus any bonus. Both derive from a common `Employee`
base through a pure virtual `calculateGrossPay()`.

**Withholding.** Federal tax is computed from filing status, dependants and
withholding allowances. State, city, Social Security and Medicare are applied
separately, with year-to-date totals accumulated across pay periods.

**W-2 generation.** Option 8 writes `W2_<id>.txt` with YTD figures mapped to the
numbered boxes of the real form — Box 1 wages, Box 2 federal, Boxes 3–6 Social
Security and Medicare, Boxes 16–17 state.

## Design

```
Employee (abstract)
├── HourlyEmployee     rate × hours
└── SalariedEmployee   annual base ÷ periods + bonus

PayrollManager   owns the employee collection; processes a pay period
FileHandler      CSV read/write and W-2 output
Menu             console interface
```

The base class holds everything common to an employee — identity, address, filing
status, YTD accumulators — and declares `calculateGrossPay()` pure virtual. Each
subclass supplies only its own pay rule, so `PayrollManager` iterates a collection
of `Employee*` and never branches on type.

Separating `FileHandler` from `PayrollManager` keeps persistence away from payroll
logic: changing the storage format touches one file, and the calculation code has no
idea CSV exists.

## CSV format

One header row, then one row per employee. `Type` is `HOURLY` or `SALARIED`, which
decides which subclass `FileHandler` constructs.

```
Type,ID,Name,BasePay,ExperienceYears,MaritalStatus,Dependents,State,City,SSN,
Address,Allowances,AdditionalWithholding,AdditionalAmount,YTDGross,YTDFederal,
YTDState,YTDCity,YTDSocialSecurity,YTDMedicare,HourlyRate,HoursWorked,Bonus
```

## Notes

Sample data is fictional. The withholding calculations are a coursework
approximation of US payroll tax and are not suitable for real payroll.
