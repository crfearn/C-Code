/* Course: CSCI 450, Section 1
 Student Name: Charles Fearn
 Student ID: 10347804
 Homework #4
 Due Date: March 4, 2024

 In keeping with the Honor Code of UM, I have neither given nor received assistance
 from anyone other than the TA or the instructor.
 Program Description: This is a lexical analyzer that reads an input file (input.txt), 
 identifies tokens such as identifiers, literals, and operators, and outputs the 
 corresponding token codes along with the lexemes. It utilizes character classification 
 and a finite-state machine approach to analyze and categorize elements in the input source code
*/

/*****input.txt----- result = oldSum - value / 100; ******/


#include <stdio.h>
#include <ctype.h>

/* global declarations */

int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* function dexlarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token Coder */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEMICOL 27



/* main driver */
int main(){
	
	/* open input file */

	if ((in_fp = fopen("input.txt", "r")) == NULL){
		printf("ERROR - cannot open front.in \n");
		 }
	else {
		getChar();
		do {
			lex();
		}  
			while (nextToken != EOF);
	}

}


/* lookup function to lookup operators and parentheses */

int lookup(char ch) {
	switch	(ch) {
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;

		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;

		case '+':
			addChar();
			nextToken = ADD_OP;
			break;

		case '-':
			addChar();
			nextToken = SUB_OP;
			break;

		case '*':
			addChar();
			nextToken = MULT_OP;
			break;

		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		case '=':
			addChar();
			nextToken = ASSIGN_OP;
			break;
		case ';':
			addChar();
			nextToken = SEMICOL;
			break; 

		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

/*********************************************************/
/* addChar function to add nextChar to lexeme */

void addChar() {
	if (lexLen <= 98){
		lexeme [lexLen++] = nextChar;
		lexeme [lexLen] = 0;
	}
	else{
		printf("ERROR - lexeme is too long \n");
	}
}

/**********************************************************/
/* getChar function to get the next character of input and determine its character class */

void getChar() {
	if ((nextChar = getc(in_fp)) != EOF){
		if (isalpha(nextChar)) 
			charClass = LETTER;
	
		else if (isdigit(nextChar))
			charClass = DIGIT;
			else 
				charClass = UNKNOWN;
	}
	else {
		charClass = EOF;
	}
	
 }

 /********************************************/
 /* getNonBlank function to call getChar until it returns a non-whitespace character */

 void getNonBlank() {
 while	(isspace(nextChar))
 	getChar();
 }
 
 /**************************************************/
 /* lex- a simple lexical analyzer for arithmetic espressions */

 int lex() {
 	lexLen = 0;
 	getNonBlank();
 	switch	(charClass)	{

 	/* parse identifiers */

 		case LETTER:
 			addChar();
 			getChar();
 			while	(charClass == LETTER || charClass == DIGIT) {
 				addChar();
 				getChar();
 			}
 		  nextToken = IDENT;
 		  break;

/* parse integer literals */
 		case DIGIT:
 			addChar();
 			getChar();
 			while	(charClass == DIGIT) {
 				addChar();
 				getChar();
 			}
 			nextToken = INT_LIT;
 			break;

 /* parentheses and operators */

 		case UNKNOWN:
 			lookup(nextChar);
 			getChar();
 			break;

 /* EOF */

 		case EOF:
 			nextToken = EOF;
 			lexeme[0] = 'E';
 			lexeme[1] = 'O';
 			lexeme[2] = 'F';
 			lexeme[3] = 0;
 			break;
 	}

 	printf("Next token is: %d, Next lexeme is %s\n\n", nextToken, lexeme);

 	return nextToken;
 }