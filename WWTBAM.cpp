#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


void continueButton(){
	char start;
	printf("\nEnter any character to continue.\n");
	scanf(" %c", &start);
	clrscr();
}

void playGame();
void cashOut();
void fiftyFifty(char options[4][350], int questionIndex);
int askQuestion(char questions[], char options[4][350], int correctIndex);


//question, option, answers
void easy(char questions[10][350], char options[10][4][350], int answers[10]);
void medium (char questions[10][350], char options[10][4][350], int answers[10]);
void hard(char questions[10][350], char options[10][4][350], int answers[10]);


//global variable
int score = 0;
int chances = 4;
int finalscore = 0;
double placeholder[] = {0, 1000, 5000, 10000, 15000, 20000, 30000, 50000, 75000, 100000, 150000, 200000, 300000, 500000, 750000, 1000000 };
int level = 1;

void displayRewards() {
    for(int x = 15; x > 0; x--){
	printf("%d: Php %.0lf\n", x, placeholder[x]);
    }
}

void main(){
	clrscr();

	char choice;
	do {
		printf("=== Who Wants To Be a Millionaire ===\n");
		printf("1. Play\n");
		printf("2. Exit\n");
		printf("\nEnter your choice: ");
		scanf(" %c", &choice);
		switch (choice) {
			case '1':
				clrscr();
				playGame();
				break;
			case '2' :
				printf("\nThank you for playing!\n");
				getch();
				exit(0);
			default:
				printf("\nInvalid choice. Please try again.\n");
				continueButton();
		}
	} while (choice != '2');




	getch();
}


void playGame(){
	char questionsEasy[10][350], optionsEasy[10][4][350];
	int answersEasy[10];
	easy(questionsEasy, optionsEasy, answersEasy);


	char questionsMedium[10][350], optionsMedium[10][4][350];
	int answersMedium[10];
	medium(questionsMedium, optionsMedium, answersMedium);


	char questionsHard[10][350], optionsHard[10][4][350];
	int answersHard[10];
	hard(questionsHard, optionsHard, answersHard);

	int questionOrder[15];
	int askedQuestionsEasy[10] = {0};
	int askedQuestionsMedium[10] = {0};
	int askedQuestionsHard[10] = {0};

	srand(time(NULL));

	for (int x = 0; x < 15; x++){
		int questionIndex = questionOrder[x];
		int difficulty = x < 5 ? 1 : (x < 10 ? 2 : 3);
		int isCorrect = 0;

		do {
			questionIndex = rand () % 10;
		} while ((difficulty == 1 && askedQuestionsEasy[questionIndex]) || (difficulty == 2 && askedQuestionsMedium[questionIndex]) || (difficulty == 3 && askedQuestionsHard[questionIndex]));

		if (difficulty == 1) askedQuestionsEasy[questionIndex] = 1;
		else if(difficulty == 2) askedQuestionsMedium[questionIndex] = 1;
		else askedQuestionsHard[questionIndex] = 1;

		if (difficulty == 1) {
			isCorrect = askQuestion(questionsEasy[questionIndex % 10], optionsEasy[questionIndex % 10], answersEasy[questionIndex % 10]);
		} else if (difficulty == 2) {
			isCorrect = askQuestion(questionsMedium[questionIndex % 10], optionsMedium[questionIndex % 10], answersMedium[questionIndex % 10]);
		} else {
			isCorrect = askQuestion(questionsHard[questionIndex % 10], optionsHard[questionIndex % 10], answersHard[questionIndex % 10]);
		}
	if (!isCorrect) {
		if (finalscore > 5 && finalscore < 10){
			printf("Game Over!\n");
			printf("You won Php %.0lf, based on the last safety haven!\n", placeholder[5]);
			continueButton();
			exit(0);
		} else if (finalscore >= 10 && finalscore <= 15){
			printf("Game Over!\n");
			printf("You won Php %.0lf, based on the last safety haven!\n", placeholder[10]);
			continueButton();
			exit(0);
		} else if (finalscore >= 0) {
			printf("Game Over!\n");
			printf("You won nothing, better luck next time!\n");
			continueButton();
			exit(0);
		}
		}
	if (finalscore == 15){
		printf("Congratulation! You won the jackpot of %.0lf!\n", placeholder[15]);
		continueButton();
		exit(0);
	}
	}
}


int askQuestion(char questions[], char options[4][350], int correctIndex){
	displayRewards();
	printf("\nLevel %d - Prize: %.0lf\n", level, placeholder[level]);
	printf("%s\n", questions);

	for (int i = 0; i < 4; i++){
		printf("%c. %s\n", 'A' + i, options[i]);
	}
	char useFF;
	printf("\nDo you want to use 50/50 lifeline? (%d remaining) (Y/N): ", chances);
	scanf(" %c", &useFF);
	if (useFF == 'Y' || useFF == 'y'){
		fiftyFifty(options, correctIndex);
	}
	char answer;
		printf("\nEnter your answer: ");
		scanf(" %c", &answer);
		answer = toupper(answer);
	if (answer - 'A' == correctIndex) {
		printf("Correct!");
		finalscore += 1;
		level += 1;
		cashOut();
		continueButton();
		return 1;
	} else {
		printf("Wrong!, The correct answer is %c\n", 'A' + correctIndex);
		continueButton();
		return 0;
	}

}
void cashOut(){
	char isCashOut;
	printf("\n\nDo you want to cash out? (Y/N): ");
	scanf(" %c", &isCashOut);
	if (isCashOut == 'Y' || isCashOut == 'y') {
		if(level > 0 && level < 5){
			printf("You cashed out with a prize of Php %.0lf\n", placeholder[level - 1]);
			getch();
			exit(0);
		} else if (level >= 5 && level < 10) {
			printf("You cashed out with a prize of Php %.lf\n", placeholder[level - 1]);
			getch();
			exit(0);
		} else if (level >= 10 && level < 15) {
			printf("You cashed out with a prize of Php %.0lf\n", placeholder[level - 1]);
			getch();
			exit(0);
		}
	}
}
void fiftyFifty(char options[4][350], int correctIndex) {
	if (chances > 0) {
		char tempOptions[4][350]; //0 value
		int removed = 0;


		for (int x = 0; x < 4; x++) {
			strcpy(tempOptions[x], options[x]);
		}


		for (int y = 0; y < 4 && removed < 2; y++) {
			if (y != correctIndex && strlen(tempOptions[y]) > 0){
			strcpy(tempOptions[y], "");
			removed++;
		}
	}
	chances--;


	printf("50/50 used up!\n");
	for(int z = 0; z < 4; z++){
		if(strlen(tempOptions[z]) > 0) {
			printf("%c. %s\n", 'A' + z, tempOptions[z]);
		}
	}
	} else {
		printf("\n50/50 used up!");
	}
}


void easy(char questions[10][350], char options[10][4][350], int answers[10]){
	strcpy(questions[0], "What does IT stand for?\n");
	strcpy(options[0][0], "Information Technology"); strcpy(options[0][1], "Information Theory"); strcpy(options[0][2], "Internet Technology"); strcpy(options[0][3], "Intelligent Technology");
	answers[0] = 0;
	strcpy(questions[1], "A pictorial representation of the logical steps it takes to solve a problem.\n");
	strcpy(options[1][0], "Flowchart"); strcpy(options[1][1], "Algorithm"); strcpy(options[1][2], "Program"); strcpy(options[1][3], "function");
	answers[1] = 0;
	strcpy(questions[2], "It is a set of instructions or a recipe\n");
	strcpy(options[2][0], "Flowchart"); strcpy(options[2][1], "Algorithm"); strcpy(options[2][2], "Program"); strcpy(options[2][3], "Function");
	answers[2] = 1;
	strcpy(questions[3], "Expressions or values on which an operator acts or works.\n");
	strcpy(options[3][0], "Operands");
	strcpy(options[3][1], "Arguments");
	strcpy(options[3][2], "Parameters");
	strcpy(options[3][3], "Values");
	answers[3] = 0;
	strcpy(questions[4], "It connects and show the appropriate sequence of steps\n");
	strcpy(options[4][0], "Arrows");
	strcpy(options[4][1], "Links");
	strcpy(options[4][2], "Line");
	strcpy(options[4][3], "Flowlines");
	answers[4] = 3;
	strcpy(questions[5], "A text-based representation of the logical steps it takes to solve a problem\n");
	strcpy(options[5][0], "Pseudocode");
	strcpy(options[5][1], "Code");
	strcpy(options[5][2], "Script");
	strcpy(options[5][3], "Markup");
	answers[5] = 0;
	strcpy(questions[6], "What function is defined in the stdio.h header file\n");
	strcpy(options[6][0], "printf();");
	strcpy(options[6][1], "sqrt();");
	strcpy(options[6][2], "getch();");
	strcpy(options[6][3], "clrscr();");
	answers[6] = 0;
	strcpy(questions[7], "It is a collection of useful functions and symbols that may be accessed by a program\n");
	strcpy(options[7][0], "Module");
	strcpy(options[7][1], "Framework");
	strcpy(options[7][2], "Library");
	strcpy(options[7][3], "API");
	answers[7] = 2;
	strcpy(questions[8], "Used to give identity for a variable, function, data definition, or labels\n");
	strcpy(options[8][0], "Keywords");
	strcpy(options[8][1], "Identifiers");
	strcpy(options[8][2], "Constants");
	strcpy(options[8][3], "Tags");
	answers[8] = 1;
	strcpy(questions[9], "These are the data used to represent fixed values.\n");
	strcpy(options[9][0], "Variables");
	strcpy(options[9][1], "Expressions");
	strcpy(options[9][2], "Constants");
	strcpy(options[9][3], "Literals");
	answers[9] = 3;
}


void medium(char questions[10][350], char options[10][4][350], int answers[10]) {
    strcpy(questions[0], "What does ASCII stands for?");
    strcpy(options[0][0], "American Standard Code for Information Interchange");
    strcpy(options[0][1], "American Standard Code for Internet Communication");
    strcpy(options[0][2], "American Standard Code for Intelligent Computers");
    strcpy(options[0][3], "Advanced Standard Code for Information Interchange");
    answers[0] = 0;

    strcpy(questions[1], "What is the decimal value of the character 'A' in the ASCII table");
    strcpy(options[1][0], "66");
    strcpy(options[1][1], "64");
    strcpy(options[1][2], "65");
    strcpy(options[1][3], "67");
    answers[1] = 2;

    strcpy(questions[2], "If an array uses an expression as a subscript, the value of the expression is evaluated last to determine the subscript");
    strcpy(options[2][0], "False");
    strcpy(options[2][1], "Neither True or False");
    strcpy(options[2][2], "True");
    strcpy(options[2][3], "Both True and False");
    answers[2] = 0;

    strcpy(questions[3], "The sqrt() function is defined in what header file?");
    strcpy(options[3][0], "stdio.h");
    strcpy(options[3][1], "math.h");
    strcpy(options[3][2], "string.h");
    strcpy(options[3][3], "stdlib.h");
    answers[3] = 1;

    strcpy(questions[4], "In functions, if the data type is omitted, it defaults to what data type");
    strcpy(options[4][0], "char");
    strcpy(options[4][1], "float");
    strcpy(options[4][2], "int");
    strcpy(options[4][3], "double");
    answers[4] = 2;

    strcpy(questions[5], "In the ASCII table, the character 'm' represents what hexadecimal value?");
    strcpy(options[5][0], "6A");
    strcpy(options[5][1], "6D");
    strcpy(options[5][2], "6F");
    strcpy(options[5][3], "6C");
    answers[5] = 1;

    strcpy(questions[6], "How many unary arithmetic operators and binary operators are there");
    strcpy(options[6][0], "1 and 3");
    strcpy(options[6][1], "1 and 4");
    strcpy(options[6][2], "1 and 5");
    strcpy(options[6][3], "2 and 5");
    answers[6] = 2;

    strcpy(questions[7], "This system records data collected at the boundaries of organizations, in other words, at the point where the organization transacts business with other parties");
    strcpy(options[7][0], "Decision Support System");
    strcpy(options[7][1], "Enterprise Resource Planning");
    strcpy(options[7][2], "Customer Relationship Management");
    strcpy(options[7][3], "Transaction Processing System");
    answers[7] = 3;

    strcpy(questions[8], "It is a wireless networking technology that uses radio waves to provide wireless high-speed Internet access");
    strcpy(options[8][0], "Bluetooth");
    strcpy(options[8][1], "Wireless Fidelity");
    strcpy(options[8][2], "Near Field Communication");
    strcpy(options[8][3], "4G LTE");
    answers[8] = 1;

    strcpy(questions[9], "It is a number system that uses basic numerals to represent any possible number: dot for 1, horizontal bar for 5, and ovular shell for 0");
    strcpy(options[9][0], "Binary");
    strcpy(options[9][1], "Decimal");
    strcpy(options[9][2], "Mayan");
    strcpy(options[9][3], "Roman");
    answers[9] = 2;
}

void hard(char questions[10][350], char options[10][4][350], int answers[10]) {
    strcpy(questions[0], "Who was the founder of C programming language");
    strcpy(options[0][0], "Dennis Ritchie");
    strcpy(options[0][1], "Sigmund Freud");
    strcpy(options[0][2], "Bjarne Stroustrup");
    strcpy(options[0][3], "Marcian Hoff");
    answers[0] = 0;

    strcpy(questions[1], "The following are examples of programming language except");
    strcpy(options[1][0], "Java");
    strcpy(options[1][1], "Julia");
    strcpy(options[1][2], "Rus");
    strcpy(options[1][3], "C++");
    answers[1] = 2;

    strcpy(questions[2], "When was the first computer that resembles modern machines today and was constructed by Charles Babbage created?");
    strcpy(options[2][0], "1833-1871");
    strcpy(options[2][1], "1833-1872");
    strcpy(options[2][2], "1833-1873");
    strcpy(options[2][3], "1833-1874");
    answers[2] = 0;

    strcpy(questions[3], "The World Wide Web(WWW) was invented in?");
    strcpy(options[3][0], "1988");
    strcpy(options[3][1], "1989");
    strcpy(options[3][2], "1990");
    strcpy(options[3][3], "1991");
    answers[3] = 1;

    strcpy(questions[4], "Who is considered as 'The father of computer");
    strcpy(options[4][0], "Rene Descartes");
    strcpy(options[4][1], "Federico Faggin");
    strcpy(options[4][2], "Ada Lovelace");
    strcpy(options[4][3], "Charles Babbage");
    answers[4] = 3;

    strcpy(questions[5], "It refers to those applications or services that are resident on a server that is accessible using a Web browser. The only client-side software needed to access and execute these applications is a Web browser environment.");
    strcpy(options[5][0], "Remote Desktop Applications");
    strcpy(options[5][1], "Internet-Dependent Software Solutions");
    strcpy(options[5][2], "Web-based IT Architectures");
    strcpy(options[5][3], "Cloud-Integrated Data Systems");
    answers[5] = 2;

    strcpy(questions[6], "Who is considered the world's first computer programmer?");
    strcpy(options[6][0], "Ada Lovilace(1841)");
    strcpy(options[6][1], "Ada Lovelace(1840)");
    strcpy(options[6][2], "Ada Lovelaice(1840)");
    strcpy(options[6][3], "Ade Lovelace(1841)");
    answers[6] = 1;

    strcpy(questions[7], "It is the part of a central processing unit that carries out arithmetic and logic operations on the operands in computer instruction words.");
    strcpy(options[7][0], "Arithmetic Unit Logic");
    strcpy(options[7][1], "Arithmetic Logical Unit");
    strcpy(options[7][2], "Arithmetic Logic Unit");
    strcpy(options[7][3], "Logical Control Processor");
    answers[7] = 2;

    strcpy(questions[8], "It takes the optimal course of actions, gathers detailed data, and helps middle/senior managers make decisions");
    strcpy(options[8][0], "Group Decision Support Systems (GDSS/DSS)");
    strcpy(options[8][1], "Executive Information Systems(EIS");
    strcpy(options[8][2], "Management Information Systems(MIS)");
    strcpy(options[8][3], "Transaction Processing Systems");
    answers[8] = 0;

    strcpy(questions[9], "It is a unique identifier used to locate a resource on the internet");
    strcpy(options[9][0], "Uniform Resource Locator");
    strcpy(options[9][1], "Universal Resource Locator");
    strcpy(options[9][2], "Uniform Resource Link");
    strcpy(options[9][3], "Universal Resource Link");
    answers[9] = 0;
}
