// (89110, Spring 2023, Assignment #3, Nadav Rutman Moshe, 325387082, rutmann)
#include <stdio.h>
/*
 *
 *
 * a quote from the coding style guideline:
 *
 * 1. "... A rule of thumb is that a function should not exceed 40 lines of code. This is not
 * a hard limit, but rather a guideline to keep functions short and simple. Hence,
 * it will not be strictly enforced, but you should strive to keep functions short."
 *
 * my functions are short and simple , even though I have two around with 50 lines (including notes)
 *
 */
#include "string.h"


void cleanBuffer();

void printMenu();

void executeTask(char taskNumber);
#include "stdlib.h"


/*
* @brief main function that takes input from the user then executes the task of that input
 * until the user inputs 0
* @return 0 if the program runs successfully
*/
int main() {
    char ss[1000000];
    printf("%d\n",ss[100000]);
    printf("%u\n", atoi("-"));

    //shows which task the user chose
    char taskNumber = 'a';
    while (taskNumber != '0') {
        printMenu();
        scanf("%c" , &taskNumber);
        executeTask(taskNumber);
    }
    return 0;
}


/*
* @brief Prints the requested menu
* This function prints the options the user can use and asks from him to choose one
*/
void printMenu() {
    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Evaluator\n");
    printf("2. Binary strings\n");
    printf("3. Exciting number\n");
    printf("4. Cool number\n");
    printf("5. Count paths\n");
}

/*
* @brief Function to Clean the buffer
* This function scans characters until it reaches a new line
 * by that it erases the characters that stayed in the buffer after other scans
*/
void cleanBuffer() {
    char buffer;
    do {
        scanf("%c" , &buffer);
    } while (buffer != '\n');
}


#define OPEN_BRACKET '('
#define CLOSED_BRACKET ')'
#define PLUS '+'
#define MINUS '-'
#define DIVIDE '/'
#define MULTIPLY '*'
#define FLAG_NEW_LINE 4294967297
#define FLAG 4294967298
#define NEW_LINE '\n'
#define SPACE ' '


long long expression(char now);

/*
* @brief Function to ignore spaces
* This function scans characters until it's not a space
 * by that it erases the spaces that and returns the character which is not space
 *
 * @return the first char that is not space
*/
char spaceCase() {
    char now;
    scanf("%c" , &now);
    while (now == SPACE) {
        scanf("%c" , &now);
    }
    return now;
}

/*
* @brief this function does a mathematical operation between two numbers
 *
 * @param number1 the first number
 * @param operator indicates the mathematical operation
 * @param number2 the second number
 *
 * @return the result of the mathematical operation between two numbers if legal
*/
long long doMath(int number1 , char operator , int number2) {
    switch (operator) {
        case PLUS:
            return number1 + number2;
        case MULTIPLY:
            return number1 * number2;
        case MINUS:
            return number1 - number2;
        case DIVIDE:
            //can't divide by 0
            if (number2 == 0) {
                return FLAG;
            } else {
                return number1 / number2;
            }

    }
    // it will not reach here but just to make the error disappear
    return 0;
}

/*
* @brief this function checks the new character and acts accordingly
 * after there was a number and an operator it can be followed by:
 * a number or open bracket
 *
 * @param number the number (or sum) before the operator
 * @param operator indicates the mathematical operation
 * @param now indicates the current character (after the operator)
 *
 * @return the result of the mathematical operation between the number with either
 * a number or an expression for example: (9+8)
*/
long long doOperator(int number , char operator , char now) {
    switch (now) {
        case '0' ... '9':
            return doMath(number , operator , now - '0');
        case OPEN_BRACKET: {
            char current;
            scanf("%c" , &current);
            //needs to calculate the expression before adding to each other
            long long exp = expression(current);
            if (exp == FLAG || exp == FLAG_NEW_LINE) {
                return exp;
            } else {
                return doMath(number , operator , exp);
            }

        }
        case SPACE:
            now = spaceCase();
            return doOperator(number , operator , now);
        case NEW_LINE:
            return FLAG_NEW_LINE;
        default:
            return FLAG;

    }
}


/*
 *  @brief this function solves the current expression
 *  it uses do operator and recursion
 *  it gets the current char which can either be an operator or a closing bracket
 *  for example- (8+9) the char would be '+'
 *
 * @param number the first number of the expression or the sum of the expression until now
 * @param operator indicates the current character
 *
 * @return the result of the current expression
 */
long long solveExpression(int number , char operator) {
    switch (operator) {
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE: {
            char now;
            scanf("%c" , &now);
            // makes the current operator
            long long sum = doOperator(number , operator , now);
            if (sum == FLAG || sum == FLAG_NEW_LINE) {
                return sum;
            } else {
                //the result is valid so we continue
                char operator2;
                scanf("%c" , &operator2);
                //until we reach a closed bracket or an error
                return solveExpression(sum , operator2);
            }
        }
        case CLOSED_BRACKET:
            return number;
        case SPACE:
            operator = spaceCase();
            return solveExpression(number , operator);
        case NEW_LINE:
            return FLAG_NEW_LINE;
        default:
            return FLAG;
    }
}


/*
 * @brief this function solves the current expression
 *  it uses solve expression and recursion
 *  it gets the current char which can either be a digit or an open bracket
 * for example- (8+9) the char would be 8
 *
 *
 * @param now indicates the current char
 * @return the result of the current expression
 */
long long expression(char now) {
    switch (now) {
        case '0' ... '9': {
            //after a number in expression there should be an operator
            char operator;
            scanf("%c" , &operator);
            long long temp = solveExpression(now - '0' , operator);
            //we check that we managed to solve that
            if (temp == FLAG_NEW_LINE || temp == FLAG) {
                return temp;
            }
                //I could have written just return temp but it would have been harder to understand
            else {
                return temp;
            }
        }
        case OPEN_BRACKET: {
            char current;
            scanf("%c" , &current);
            //we have a bracket so we check the expression inside
            long long temp = expression(current);
            if (temp == FLAG_NEW_LINE || temp == FLAG) {
                return temp;
            } else {
                //the expression is valid so we expect an operator
                char operator;
                scanf("%c" , &operator);
                long long temp2 = solveExpression(temp , operator);
                if (temp2 == FLAG_NEW_LINE || temp2 == FLAG) {
                    return temp2;
                } else {
                    return temp2;
                }
            }
        }
        case SPACE:
            now = spaceCase();
            return expression(now);
        case NEW_LINE:
            return FLAG_NEW_LINE;
        default:
            return FLAG;

    }
}

/*
 * @brief this function checks the end of the first expression
 * after the first expression there must be a new line (or spaces before)
 *
 * @param now the current character which will be after the closing of the first expression
 * @param answer the answer of the first expression and therefore the final answer
 *
 * prints the result if there was a newline after the first expression
 */
void checkTheEnd(char now , long long answer) {
    //valid
    if (now == NEW_LINE) {
        printf("The value is %d" , (int) answer);

    } else if (now == SPACE) {
        now = spaceCase();
        checkTheEnd(now , answer);
    } else {
        printf("Invalid expression");
        cleanBuffer();
    }
}

/*
 * @brief this function represents the first expression
 *
 * it uses expression and checkTheEnd
 * and then prints according to the input (error or result)
 */
void firstExpression() {
    char current;
    scanf("%c" , &current);
    //solving it
    long long temp = expression(current);
    //need to clean the buffer
    if (temp == FLAG) {
        cleanBuffer();
        printf("Invalid expression");
    } else if (temp == FLAG_NEW_LINE) {
        printf("Invalid expression");
    } //I reached the end of the first expression (valid until now)
    else {
        char now;
        scanf("%c" , &now);
        //last check
        checkTheEnd(now , temp);
    }

}

#define NEW_ROW "\n"

/*
 * @brief the function solves task 1
 * checks the first character and acts accordingly
 * it uses firstExpression if the character is valid
 *
 * @param now the first character
 */
void task1(char now) {
    //valid start
    if (now == OPEN_BRACKET) {
        firstExpression();
        printf(NEW_ROW);
    } else if (now == SPACE) {
        now = spaceCase();
        task1(now);
    } else {
        //not valid - decide if I should clean the buffer
        if (now != NEW_LINE) {
            cleanBuffer();
        }
        printf("Invalid expression");
        printf(NEW_ROW);
    }

}

/*
 * @brief the function prints a number in his binary form
 * the function uses recursion
 *
 * @param number the decimal number
 * @param length the required length by the user
 */
void printDecimalInBinary(unsigned int number , int length) {
    //1, "1","0" are not hard coded or magic numbers because this number is part of the algorithm’s
    // logic (shall never be changed).
    // reaches the last bit
    if (length == 0) {
        int bit = 1;
        if (number & bit) {
            printf("1");
        } else {
            printf("0");
        }
        printf(NEW_ROW);
    } else {
        int bit = 1;
        bit <<= length;
        //checked the bit in length place
        if (number & bit) {
            printf("1");
        } else {
            printf("0");
        }
        //moves the index
        printDecimalInBinary(number , length - 1);
    }
}

/*
 * @brief the function gets a number and checks if he is valid
 * valid - doesn't have 2 bits of 1 in a row
 * the function uses recursion
 *
 * @param number the number
 * @return is the number valid ? 1 : 0
 */
int isValid(unsigned int number , int base) {
    // the end
    if (number == 0) {
        return 1;
    }
    //checks for two 1s in a row
    //in this example 2 is a hard coded number
    if (number % base && (number / base) % base) {
        return 0;
    } else {
        //getting the next bit
        return isValid(number / base , base);
    }
}

/*
 * @brief the function returns the biggest number with length bits
 * the function uses recursion
 *
 * @param length the length which was inserted by the user
 * @param number starts with a 0 and then gets added bit by bit
 * @return the biggest number represented by length bits
 */
unsigned int maximumNum(int length , unsigned int number) {
    //the end
    if (length == 0) {
        // the first bit is set to 1
        number |= 1;
        return number;
    } else {
        int bit = 1;
        bit <<= length;
        // the length bit is set to 1
        number |= bit;
        //moves length
        return maximumNum(length - 1 , number);
    }
}

/*
 * @brief prints all the numbers between 0 to maximum that are valid by order
 * the function uses isValid, printDecimalInBinary
 * the function uses recursion
 *
 * @param current the current number to print or not
 * @param maximum the biggest number with length bits
 * @param length the length which was inserted by the user
 */
void allNumbers(unsigned int current , unsigned int maximum , int length) {
    //ends when it reaches the maximum
    if (current < maximum) {
        //if the number is valid it prints it in binary
        if (isValid(current , 2)) {
            printDecimalInBinary(current , length - 1);
        }
        //moves to the next number
        allNumbers(current + 1 , maximum , length);
    }
}

/*
 * @brief the function solves task 2
 * it uses maximumNum and allNumbers
 *
 * @param length the length which was inserted by the user
 */
void task2(int length) {
    unsigned int maximum = maximumNum(length - 1 , 0);
    //uses this function to print those numbers
    allNumbers(0 , maximum , length);
}

/*
 * @brief the function gets a number and returns the number of digits of that number
 * the function uses recursion
 *
 * @param natural a natural number
 * @return the number of digits of that number
 */
int numOfDigits(unsigned int natural) {
    //the end
    if (natural == 0) {
        return 0;
    }
    //counts 1 and moves to the next digit
    return 1 + numOfDigits(natural / 10);
}

/*
 * @brief the function gets a number and an exponent and returns
 * the number to the power of the exponent
 *the function uses recursion
 *
 * @param number the selected number
 * @param exponent the selected exponent
 * @return the number to the power of the exponent
 */
unsigned long long power(int number , int exponent) {
    //the end
    if (exponent == 0) {
        return 1;
    }
    //makes one more multiplication
    return (number * power(number , exponent - 1));
}

/*
 * @brief the function returns the sum of:
 * every digit of the number to the power of (the number of the digits of that number)
 * the function uses power and recursion
 *
 * @param length the number of digits of that number
 * @param natural the number inserted by the user
 * @return the sum of the digits to the power of length
 */
unsigned long long sumNatural(int length , unsigned int natural) {
    //the end
    if (natural == 0) {
        return 0;
    }
    //sums all: the digits in the power of length
    return power(natural % 10 , length) + sumNatural(length , natural / 10);
}

/*
 *@brief the function solves task 3,
 * it uses numOfDigits, sumNatural to help solve the task
 * if the number is equal to his sumNatural then he is exciting
 *
 * @param natural the number inserted by the user
 */
void task3(unsigned int natural) {
    // edge case
    if (natural == 0) {
        printf("The number is exciting");
    } else {
        int length = numOfDigits(natural);
        //checks for equality
        if (sumNatural(length , natural) == natural) {
            printf("The number is exciting");
        } else {
            printf("The number is not exciting");
        }
    }
    cleanBuffer();
    printf(NEW_ROW);
}


// the biggest number in unsigned int has 10 digits

#define ARRAY_SIZE 10

/*
 * @brief the function initializes the array with all the number's digits
 * for the number 153
 * it will be {1,5,3 ...}
 *
 *
 * @param array the array we want to initialize
 * @param length the length of the inserted number
 * @param number the inserted number by the user
 */
void initialization(unsigned int array[] , int length , unsigned int number) {
    //we need the reversed number in order to get into the array easily he might be bigger than
    //unsigned int
    unsigned long  reversedNumber;
    //hard coded number
    const int BASE = 10;
    while (number != 0) {
        int digit;
        //checks the right digit
        digit = number % BASE;
        //makes spaces for that digit
        reversedNumber *= BASE;
        //adds the current digit
        reversedNumber += digit;
        number /= BASE;
    }
    //also works for 200:
    //2 , 0 , 0
    for (int i = 0; i < length; ++i) {
        //the current digit
        array[i] = reversedNumber % BASE;
        reversedNumber /= BASE;
    }

}

/*
 * @brief the function gets an array and returns the sum of the array
 * for every array[i]: 0 <= i < length
 *
 * @param array the received array
 * @param length indicates the real size of the array
 * @return the sum of length first members of array
 */
unsigned int arraySum(unsigned int array[] , int length) {
    unsigned int sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += array[i];
    }
    return sum;
}

/*
 * @brief the function "shifts right" once the array
 * the function moves every element once to the right
 * it keeps the 0 element the same as it was
 *
 * @param array the array
 * @param length indicates the real size of the array
 */
void shiftLeft(unsigned int array[] , int length) {
    //minus 1 because it uses i+1
    for (int i = 0; i < length-1; ++i) {
        //makes the i+1 element be the i element
        array[i] = array[i + 1];
    }
}

/*
 * @brief the function solves task 4
 * checks if the received the number is considered cool
 * it uses initialization, arraySum and shiftRight
 *
 * @param natural the number the user inputs
 */
void task4(unsigned int natural) {
    //one digit is always cool
    if (natural / 10 == 0) {
        printf("The number is cool");
    } else {
        //builds an array size 10
        unsigned int sumArray[ARRAY_SIZE];
        int length = numOfDigits(natural);
        //sets the array to have the digits of the number
        initialization(sumArray , length , natural);
        //the sum of the array
        unsigned int currentSum = arraySum(sumArray , length);
        const int LAST_PLACE = length - 1;
        //if it is bigger or equal to natural it should stop and compare
        //the sum should grow bigger but there are 32 bits in unsigned int so it might "jump" to
        //a smaller number because of overflow so I stopped it there too
        while (currentSum < natural && currentSum >= sumArray[LAST_PLACE]) {
            shiftLeft(sumArray , length);
            //updates the array
            sumArray[LAST_PLACE] = currentSum;
            currentSum = arraySum(sumArray , length);
        }
        if (currentSum == natural) {
            printf("The number is cool");
        } else {
            printf("The number is not cool");
        }

    }
    cleanBuffer();
    printf(NEW_ROW);
}

#define MAX_STEPS 3
#define RESET 0
#define STEP 1

/*
 * @brief the function returns the number of paths of a rows by columns inserted by the user
 * so the idea of the function:
 * it starts at (0,0) and then it has two options:
 *
 * going down- it will call the function again with the changes:
 * it will call the function again with the changes:
 *
 * going right- it will call the function again with the changes:
 * j+1,  reset count down steps , add one to right count
 *
 * it adds the number of paths of both options
 *
 * if it gets out of bound or does 3 down/right steps in a row it will return 0
 * if it reaches the final square it will return 1
 *
 * then all the solutions will add on the way back
 *
 * @param i the current row
 * @param j the current column
 * @param rows the number of rows
 * @param columns the number of columns
 * @param countRight number of currently going right in a row
 * @param countDown number of currently going down in a row
 * @return number of paths from i,j to rows-1,columns-1
 */
int numOfPaths(unsigned int i , unsigned int j ,
               unsigned int rows , unsigned int columns ,
               int countRight , int countDown) {
    const unsigned int ENDING_ROW = rows - 1;
    const unsigned int ENDING_COLUMN = columns - 1;
    // stops when it reaches the dimensions
    if (i == rows || j == columns) {
        return 0;
    }
    // stops when it does max right or max down
    if (countRight == MAX_STEPS || countDown == MAX_STEPS) {
        return 0;
    }
    //returns 1 when it reached the final square
    if (i == ENDING_ROW && j ==  ENDING_COLUMN) {
        return 1;
    }
    //returns the sum of number of paths to the one right and number of paths one down
    int down = numOfPaths(i + STEP , j , rows , columns , RESET , countDown + STEP);
    int right = numOfPaths(i , j + STEP , rows , columns , countRight + STEP , RESET);
    return down + right;
}

#define ZERO_CASE "The number of paths is 0"
#define ONE_CASE "The number of paths is 1"
#define STARTING_ROW 0
#define STARTING_COLUMN 0

/*
 * @brief the function solves task 5
 * the function checks for edge cases and if it's not one then it calculates the number of paths
 * using the function numOfPaths then prints it
 *
 * @param width the width inserted by the user
 * @param height the height inserted by the user
 */
void task5(unsigned int width , unsigned int height) {
    //edge cases
    if (width == 0 || height == 0) {
        printf(ZERO_CASE);
    } else if (width == 1) {
        if (height > MAX_STEPS) {
            printf(ZERO_CASE);
        } else {
            printf(ONE_CASE);
        }
    } else if (height == 1) {
        if (width > MAX_STEPS) {
            printf(ZERO_CASE);
        } else {
            printf(ONE_CASE);
        }
    } else {
        int answer;
        //calculates the num of paths
        answer = numOfPaths(STARTING_ROW , STARTING_COLUMN ,
                            height , width ,
                            RESET , RESET);
        printf("The number of paths is %d" , answer);
    }
    cleanBuffer();
    printf(NEW_ROW);
}

/*
* @brief this function gets a task number and executes the task accordingly
 *the function identifies the task number with a switch loop and acts accordingly
 *
 * @param taskNumber The number of the task inserted by the user.
 *
 *
*/
void executeTask(char taskNumber) {
    switch (taskNumber) {
        case '0':
            break;
        case '1':
            printf("Enter an expression:");
            printf(NEW_ROW);
            //in order to scan the input we must clean the buffer
            cleanBuffer();
            char now;
            scanf("%c" , &now);
            task1(now);
            break;
        case '2':
            printf("Enter length:");
            printf(NEW_ROW);
            int length;
            scanf("%d" , &length);
            int const BIT_MAX = sizeof(int)*8 , BIT_MIN = 1;
            //invalid input
            if (length < BIT_MIN || length > BIT_MAX) {
                printf("Invalid length");
                printf(NEW_ROW);
            } else {
                task2(length);
            }
            //either way the buffer is not clean
            cleanBuffer();
            break;
        case '3':
            printf("Enter a natural number:");
            printf(NEW_ROW);
            unsigned int natural1;
            scanf("%u" , &natural1);
            //executes task3
            task3(natural1);
            break;
        case '4':
            printf("Enter a natural number:");
            printf(NEW_ROW);
            unsigned int natural2;
            scanf("%u" , &natural2);
            //executes task4
            task4(natural2);
            break;
        case '5':
            printf("Enter width and height:");
            printf(NEW_ROW);
            unsigned int width , height;
            scanf("%u %u" , &width , &height);
            //executes task5
            task5(width , height);
            break;
        default:
            cleanBuffer();
            printf("Invalid option\n");

    }
}

