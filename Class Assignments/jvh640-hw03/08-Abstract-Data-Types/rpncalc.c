/*
 * File: rpncalc.c
 * ---------------
 * This program simulates an electronic calculator that uses
 * reverse Polish notation, in which the operators come after
 * the operands to which they apply.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"
#include "stack.h"

/* Private function prototypes */

static void ApplyOperator(char op, stackADT operandStack);
static void HelpCommand(void);
static void ClearStack(stackADT operandStack);
static void DisplayStack(stackADT operandStack);

/* Main program */

main()
{
    stackADT operandStack;
    string line;
    char ch;
    double *tmp;

    printf("RPN Calculator Simulation (type H for help)\n");
    operandStack = NewStack();
    while (TRUE) {
        printf("> ");
        line = GetLine();
        ch = toupper(line[0]);
        switch (ch) {
          case 'Q': 
                {
                ClearStack(operandStack);
                FreeStack(operandStack);
                exit(0);
                }
          case 'H': HelpCommand(); break;
          case 'C': ClearStack(operandStack); break;
          case 'S': DisplayStack(operandStack); break;
          default:
            if (isdigit(ch)) {
                tmp = (double *)malloc(sizeof(double));
                *tmp = atof(line);
                Push(operandStack, tmp);
            } else {
                ApplyOperator(ch, operandStack);
            }
            break;
        }
    }
    ClearStack(operandStack);
    FreeStack(operandStack);
}

/* Private functions */

/*
 * Function: ApplyOperator
 * Usage: ApplyOperator(op, operandStack);
 * ---------------------------------------
 * This function applies the operator to the top two elements on
 * the operand stack.  Because the elements on the stack are
 * popped in reverse order, the right operand is popped before
 * the left operand.
 */

static void ApplyOperator(char op, stackADT operandStack)
{
    double *lhs, *rhs, *result;
    
    result = (double *)malloc(sizeof(double));

    rhs = Pop(operandStack);
    lhs = Pop(operandStack);
    
    printf("%g %c %g\n", *lhs, op, *rhs);
    switch (op) {
      case '+': *result = *lhs + *rhs; break;
      case '-': *result = *lhs - *rhs; break;
      case '*': *result = *lhs * *rhs; break;
      case '/': *result = *lhs / *rhs; break;
      default:  Error("Illegal operator %c", op);
    }
    free(rhs);
    free(lhs);
    printf("Result: %g\n", *result);
    Push(operandStack, result);
}

/*
 * Function: HelpCommand
 * Usage: HelpCommand();
 * ---------------------
 * This function generates a help message for the user.
 */

static void HelpCommand(void)
{
    printf("Enter expressions in Reverse Polish Notation,\n");
    printf("in which operators follow the operands to which\n");
    printf("they apply.  Each line consists of a number, an\n");
    printf("operator, or one of the following commands:\n");
    printf("  Q -- Quit the program\n");
    printf("  H -- Display this help message\n");
    printf("  C -- Clear the calculator stack\n");
    printf("  S -- Display all values in the stack\n");
}

/*
 * Function: ClearStack
 * Usage: ClearStack(stack);
 * -------------------------
 * This function clears the stack by popping elements until it is
 * empty.
 */

static void ClearStack(stackADT stack)
{
    double *tmp;
    while (!StackIsEmpty(stack)) {
        tmp = Pop(stack);
        free(tmp);
    }
}

/*
 * Function: DisplayStack
 * Usage: DisplayStack(stack);
 * ---------------------------
 * This function displays the contents of a stack.
 */

static void DisplayStack(stackADT stack)
{
    int i, depth;

    printf("Stack: ");
    if (depth == 0) {
        printf("empty\n");
    } else {
        for (i = depth - 1; i >= 0; i--) {
            if (i < depth - 1) printf(", ");
            printf("%g", *(double *)GetStackElement(stack, i));
        }
        printf("\n");
    }
}



