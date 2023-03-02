#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"
#include "stack.h"

void main(int argc, char *argv[]){
    FILE *inFile;
    int isCorrect, *tagType;
    char *tag, *popTag;
    stackADT tagStack;
    
    if(argc != 2){ //Checks entry arguments
        printf("Error: Incompatible commandline arguement.\nPlease execute in the following format: htmlchecker filename.txt\n");
        exit(0);
    }
    inFile = fopen(argv[1], "r");//Open Files
    if(inFile == NULL){
        printf("No File.\n");
        exit(0);
    }
    
    tagStack = NewStack();
    
    while(tag != NULL){
        tag = getTag(inFile, tagType);
        
        switch(*tagType){
                case(1):
                    Push(tagStack, tag);
                    break;
                
                case(2):
                    free(tag);
                    break;
                
                case(3):
                    popTag = Pop(tagStack);
                    isCorrect = isEqual(tag, popTag);
                    
                    if (isCorrect == 0){
                        printf("Code is incorrect\n");
                        printf("Incorrect Nesting %s\n", tag);
                        free(tag);
                        free(popTag);
                        FreeStack(tagStack);
                        exit(0);
                    }
                    else{
                        free(tag);
                        free(popTag);
                    }
                    break;
                
                case(4):
                    free(tag);
                    break;
        } 
    }
    
    if(isCorrect != 0){
        if(StackIsEmpty(tagStack) != 0)
            printf("Code is correct\n")
    }
    
    free(tag);
    FreeStack(tagStack);
    fclose(inFile);
}

static char *getTag(FILE *inFile, int *tagType) // Takes in array and checks tags
{
	char buff[255];
	int ch, i, length;
	char *tag;
	*tagType = 0;

	ch = getc(inFile);

	while (ch != EOF){
		if (ch == '<'){
			*tagType = 1;
			buff[0] = '<';
			i = 1;
			while (ch != '>'){
				ch = getc(inFile);
				if (ch == EOF)
					return NULL;
				buff[i] = ch;
				if (buff[1] == '/')
					*tagType = 3;
				if (buff[1] == '!' && buff[2] == '-' && buff[3] == '-'){
					while (buff[i-1] != '-' && buff[i-2] != '-'){
						ch = getc(inFile);
						if (ch == EOF)
							return NULL;
						buff[i] = ch;
						if (buff[i] == '>'){
							if (buff[i-1] != '-' && buff[i-2] != '-')
								buff[i] = ' ';
						}
						i++;
					}
					*tagType = 4;
				}
				i++;
			}
			
			buff[i] = '\0';
			length = strlen(buff);
			tag = malloc(length + 1);
			if (tag == NULL){
			    	printf("Error: Insufficient Memory.\n");
			    	free(tag);
			    	exit(-1);
			    }
			strncpy(tag, buff, length);
			if ((buff[i - 2]) == '/')
				*tagType = 2;
			return tag;
		}
		ch = getc(inFile);
	}
	return NULL;
}

static bool isEqual(char *tag, char *popTag) // Checks if tags are matching 
{
	int i = 1, j = 2;
	
	while (tag[j] != '>'){
		if (popTag[i] != tag[j] && (popTag[i] != ' ' && tag[j] != '>'))
			return 0;
		i++;
		j++;
	}
	return 1;
}