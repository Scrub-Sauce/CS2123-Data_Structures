/*
 * File: employee.c
 * ----------------
 * This program tests the functions defined for records of type
 * employeeRecordT and employeeT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Type: string
 * ------------
 * The type string is identical to the type char *, which is
 * traditionally used in C programs.  The main point of defining a
 * new type is to improve program readability.   At the abstraction
 * levels at which the type string is used, it is usually not
 * important to take the string apart into its component characters.
 * Declaring it as a string emphasizes this atomicity.
 */

typedef char *string;



/*
 * Constants
 * ---------
 * MaxEmployees -- Maximum number of employees
 */

#define MaxEmployees 100

/*
 * Type: employeeRecordT
 * ---------------------
 * This structure defines a type for an employee record.
 */

typedef struct {
    string name;
    string title;
    string ssnum;
    double salary;
    int withholding;
} employeeRecordT;

/*
 * Type: employeeT
 * ---------------
 * This type definition introduces an employeeT as a
 * pointer to the same record type as before.
 */

typedef struct {
    string name;
    string title;
    string ssnum;
    double salary;
    int withholding;
} *employeeT;

/*
 * Type: payrollT
 * --------------
 * This type represents an entire collection of employees.  The
 * type definition uses a dynamic array of employeeT values to
 * ensure that there is no maximum bound imposed by the type.
 * The cost of this design is that the programmer must explicitly
 * allocate the storage for the array using NewArray.
 */

typedef struct { 
    int nEmployees;
    employeeT *employees;
} *payrollT;

/*
 * Global variables
 * ----------------
 * staff       -- Array of employees
 * nEmployees  -- Number of employees
 * manager     -- Used to produce a figure for the code
 */

static employeeRecordT staff[MaxEmployees];
static int nEmployees;

static employeeRecordT manager = {
    "Ebenezer Scrooge", "Partner", "271-82-8183", 250.00, 1
};

/* Private function declarations */

static void InitEmployeeTable(void);
static payrollT CreatePayroll();
static void ListEmployees(payrollT payroll);
static double AverageSalary(payrollT payroll);

/* helper functions from the textbook lib */
string GetLine(void);
string ReadLine(FILE *infile);
payrollT GetPayroll();
void FreePayroll(payrollT payroll);
void CalcPayroll(payrollT payroll);
double CalcTax(payrollT payroll, int i);
double CalcNet(payrollT payroll, double tax, int i);

/* Main program */

main()
{
    payrollT payroll;

    //InitEmployeeTable();
    payroll = GetPayroll();
    //ListEmployees(payroll);
    CalcPayroll(payroll);
    FreePayroll(payroll);
}

//static void InitEmployeeTable(void)
//{
//    employeeRecordT empRec;
//
//    empRec.name = "Ebenezer Scrooge";
//    empRec.title = "Partner";
//    empRec.ssnum = "271-82-8183";
//    empRec.salary = 250.00;
//    empRec.withholding = 1;
//    staff[0] = empRec;
//    empRec.name = "Bob Cratchit";
//    empRec.title = "Clerk";
//    empRec.ssnum = "314-15-9265";
//    empRec.salary = 15.00;
//    empRec.withholding = 7;
//    staff[1] = empRec;
//    nEmployees = 2;
//}

//static payrollT CreatePayroll(employeeRecordT staff[], int nEmployees)
//{
//    payrollT payroll;
//    int i;
//
//    payroll = (payrollT) malloc(sizeof *payroll); // New(payrollT);
//    payroll->employees = (employeeT *) malloc(nEmployees*sizeof(employeeT)); // NewArray(nEmployees, employeeT);
//    payroll->nEmployees = nEmployees;
//    for (i = 0; i < nEmployees; i++) {
//        payroll->employees[i] = (employeeT)malloc(sizeof *((employeeT) NULL));   // (New(employeeT);
//        payroll->employees[i]->name = staff[i].name;
//        payroll->employees[i]->title = staff[i].title;
//        payroll->employees[i]->ssnum = staff[i].ssnum;
//        payroll->employees[i]->salary = staff[i].salary;
//        payroll->employees[i]->withholding = staff[i].withholding;
//    }
//    return (payroll);
//}

void FreePayroll(payrollT payroll){ //Frees Payroll Structures
    int i;
    
    for(i = 0; i < nEmployees; i++){
        free(payroll->employees[i]->name);
        free(payroll->employees[i]->title);
        free(payroll->employees[i]->ssnum);
        free(payroll->employees[i]);
    }
    free(payroll->employees);
    free(payroll);
}

static void ListEmployees(payrollT payroll)
{
    int i;

    for (i = 0; i < payroll->nEmployees; i++) {
        printf("%s (%s)\n", payroll->employees[i]->name, payroll->employees[i]->title);
    }
}

static double AverageSalary(payrollT payroll)
{
    double total;
    int i;

    total = 0;
    for (i = 0; i < payroll->nEmployees; i++) {
        total += payroll->employees[i]->salary;
    }
    return (total / nEmployees);
}

/*
 * to read strings from user and dynamically allocate memory,
 * it might be good idea to use the following helper functions  
 * from the book lib 
 * 
 */
string ReadLine(FILE *infile)
{
    string line, nline;
    int n, ch, size;

    n = 0;
    size = 120;
    line = (string) malloc(size + 1);
    if(line==NULL) return NULL;
    while ((ch = getc(infile)) != '\n' && ch != EOF) {
        if (n == size) {
            size *= 2;
            nline = (string) malloc(size + 1);
            if(nline==NULL) {free(line); return NULL; }
            strncpy(nline, line, n);
            free(line);
            line = nline;
        }
        line[n++] = ch;
    }
    if (n == 0 && ch == EOF) {
        free(line);
        return (NULL);
    }
    line[n] = '\0';
    nline = (string) malloc(n + 1);
    if(nline==NULL) {free(line); return NULL; }
    strcpy(nline, line);
    free(line);
    return (nline);
}

string GetLine(void)
{
    return (ReadLine(stdin));
}

payrollT GetPayroll(){ // Mallocs data structure for payroll and asks for user input to assign values
    payrollT payroll;
    employeeRecordT employeeRecord;
    int i;
    char *tmp;
    
    printf("\nHow many employees: ");
    tmp = GetLine();
    nEmployees = atoi(tmp);
    free(tmp);
        
    payroll = (payrollT)malloc(sizeof *payroll);
    if(payroll == NULL){
        printf("Error: Insufficient Memory");
        exit(0);
    }
    payroll->employees = (employeeT *) malloc(nEmployees*sizeof(employeeT));
    if(payroll->employees == NULL){
        printf("Error: Insufficient Memory");
        exit(0);
    }
    
    for(i = 0; i < nEmployees; i++){
        payroll->employees[i] = (employeeT)malloc(sizeof *((employeeT) NULL));
        if(payroll->employees[i] == NULL){
            printf("Error: Insufficient Memory");
            exit(0);
        }
        printf("\nEmployee #%d\n", i+1);
        printf("\tName: ");
        payroll->employees[i]->name = GetLine();
        printf("\tTitle: ");
        payroll->employees[i]->title = GetLine();
        printf("\tSSNum: ");
        payroll->employees[i]->ssnum = GetLine();
        printf("\tSalary: ");
        tmp = GetLine();
        payroll->employees[i]->salary = atof(tmp);
        free(tmp);
        printf("\tWithholding exemptions: ");
        tmp = GetLine();
        payroll->employees[i]->withholding = atoi(tmp);
        free(tmp);
    }
    return (payroll);
}

void CalcPayroll(payrollT payroll){ //calls functions and prints income information
    int i;
    double tax, net;
    
    printf("\n\nName                           Gross\t Tax\tNet\n");
    printf("------------------------------------------------------------\n");
    for(i = 0; i < nEmployees; i++){
        tax = CalcTax(payroll, i);
        net = CalcNet(payroll, tax, i);
         
        printf("%-30s %6.2lf - %5.2lf = %6.2lf \n", payroll->employees[i]->name, payroll->employees[i]->salary, tax, net);
    }
}

double CalcTax(payrollT payroll, int i){ //Calculates Tax for on employee gross wage and returns to CalcPayroll
    double tax;
    
    tax = payroll->employees[i]->salary - payroll->employees[i]->withholding;
    tax = tax * 0.25;
        
    return (tax);
}

double CalcNet(payrollT payroll, double tax, int i){ //Calculates Net income and returns to CalcPayroll
    double net;
    
    net = payroll->employees[i]->salary - tax;
    
    return (net);
}

