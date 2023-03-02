#include <stdio.h>
#include <stdlib.h>

void UserInput(FILE *fp, int sudoku[9][9]);
void SudokuCheck(int sudoku[][9], int *checker, int *userChoice);
void CountReset(int *checker);
void CountCheck(int *checker);
void rCCheck(int sudoku[][9], int *checker, int i, int *userChoice);
void BoxCheck(int sudoku[][9], int *checker, int i, int *userChoice);
void PosCheck(int sudoku[][9], int *checker);
void PosRow(int sudoku[][9], int *checker, int i, int j);
void PosCol(int sudoku[][9], int *checker, int i, int j);
void PosBox(int sudoku[][9], int *checker, int i, int j);

void main(int argc, char *argv[]){ // Main Function
	int isValid = 0, userChoice, *pUserChoice; //Initialise needed variables
    int sudoku[9][9]; //Initialize Sudoku array
    int checker[10]; //Initialize Checker Array
    pUserChoice = &userChoice; //Pointer to choice selection

    
    FILE *fp = NULL; //Initialize and open a file from command line
    fp = fopen(argv[1], "r");
    
    if(fp == NULL){ //File Command Line error
        printf("\nPlease include a file name command line argument\nExample: ./hw01 PuzzleTest.txt\n\n");
        exit(0);
    }
        
	while (isValid == 0){ //Loop for checking for valid options
		printf("\nEnter an option: End Program - 0, Check Possible Solutions - 1, Verify Puzzle - 2\n");
		fscanf(fp, "%d", &userChoice); //Takes in the user choice
        		printf("Option Selected: %d", *pUserChoice); //Prints user choice for user
		switch(userChoice) {
			case 0 : // Ends Program
				printf("\nProgram Complete!\n");
				exit(0);
				break;
			case 1 : // Checks Possible Values
                isValid = 1;
                UserInput(fp, sudoku);
                PosCheck(sudoku, checker);
				break;
			case 2 : // Checks if sudoku is correct or incorrect
                isValid = 1;
                UserInput(fp, sudoku);
                SudokuCheck(sudoku, checker, pUserChoice);
                printf("\nPuzzle Correct! Ending Program\n\n");
				break;
			default : // Error message for invalid entry
				printf("Error: Invalid Entry! Please enter 0, 1, or 2.\n");
		}
	}
}

void UserInput(FILE *fp, int sudoku[9][9]){ // Takes in Sudoku from file and prints for user to see
	int i, j;

	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			fscanf(fp, "%d", &sudoku[i][j]);
		}
	}
	printf("\nYour Entry is:\n");
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
}

void SudokuCheck(int sudoku[][9], int *checker, int *userChoice){ // Calls functions to check Columns, Rows and Boxes
    int i, j;
    CountReset(checker);
    for(i = 0; i < 9; i++){
        rCCheck(sudoku, checker, i, userChoice);
        if(i < 3)
            BoxCheck(sudoku, checker, i, userChoice);  
    }
}

void CountReset(int *checker){ // Function to reinitialize checker as 0 when needed 
    int i;
    for(i = 0; i <= 9; i++){
        checker[i] = 0;
    }
}

void CountCheck(int *checker){ // Checks the values on the checker to search for unused or duplicate values
    int i;
    for(i = 1; i <= 9; i++){
        if(checker[i] != 1){
            printf("\nPuzzle is incorrect. Ending Program\n\n");
            exit(0);
        }
    }
}

void rCCheck(int sudoku[][9], int *checker, int i,  int *userChoice){ // Function sends values from Columns and Rows to the Checker and Calls for the Checker to be validated and reset
    int j, k;
    for(j = 0; j < 2; j++){
        for(k = 0; k < 9; k++){
            if(j == 0){
                checker[sudoku[i][k]]++;
            }
            if(j == 1){
                checker[sudoku[k][i]]++;
            }
        }
        CountCheck(checker);
        CountReset(checker);
    }
}

void BoxCheck(int sudoku[9][9], int *checker, int i, int *userChoice){ // Function sends values from boxes to the Checker and Calls for the Checker to be validated and reset
    int j, k, l;
    for(j = 0; j < 3; j++){
        for(k = 0; k < 3; k++){
            for(l = 0; l < 3; l++){
                checker[sudoku[3 * i + k][3 * j + l]]++;
            }
        } 
        CountCheck(checker);
        CountReset(checker);
    }
}

void PosCheck(int sudoku[][9], int *checker){ // Calls functions to add values to checker and print what is available
    int i, j, k, first = 0;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(sudoku[i][j]==0){
                CountReset(checker);
                PosRow(sudoku, checker, i, j);
                PosCol(sudoku, checker, i, j);
                PosBox(sudoku, checker, i, j);
                for(k = 1; k <= 9; k++){
                    if(checker[k]==0){
                        if(first == 0){
                            printf("\nSudoku [%d][%d] = %d", i, j, k);
                            first++;
                        }else{
                            printf(", %d", k);
                        }
                    }
                }
                first = 0;
            }
        }
    }
    printf("\nProgram Complete!");
}

void PosRow(int sudoku[][9], int *checker, int i, int j){ //Fills checker with values for row
    int k;
    for(k = 0; k < 9; k++){
        if(sudoku[i][k] != 0){
            checker[sudoku[i][k]] = 1;
        }
    }
}

void PosCol(int sudoku[][9], int *checker, int i, int j){ //Fills checker with values for columns
    int k;
    for(k = 0; k < 9; k++){
        if(sudoku[k][j] != 0){
            checker[sudoku[k][j]] = 1;
        }
    }  
}

void PosBox(int sudoku[][9], int *checker, int i, int j){ ////Fills checker with values for boxes
    int ii, jj, k, l;
    ii = i / 3;
    jj = j / 3;
    for(k = 0; k < 3; k++){
        for(l = 0; l < 3; l++){
            if(sudoku[3 * ii + k][3 * jj + l] != 0){
                checker[sudoku[3 * ii + k][3 * jj + l]] = 1;
            }
        }
    }
}
