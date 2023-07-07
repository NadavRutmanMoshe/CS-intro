// (89110, Spring 2023, Assignment #2, Nadav Rutman Moshe, 325387082, rutmann)
#include <stdio.h>


#define SPACE " "
#define DOT "."
#define RIGHT_SLASH "\\"
#define LEFT_SLASH "/"
#define NEW_ROW "\n"
#define LINE "-"
#define MIDDLE_SIGN "X"

/*
* @brief Prints a sand clock
*
* @param size the size of the width of the clock.
* @param flag which side is the sand.
*
* @prints the sand clock.
*/


void task1(int size, int flag) {
    for (int i = 0; i < size; ++i)
        printf(LINE);
    printf(NEW_ROW);
    // numbers of half the rows because it's int it will round down a number that is not even
    const int ROWS = size / 2;
    //where do I need to write '/'  or   '\'
    int index1 = 0, index2 = size - 1;
    //where do I need to stop writing
    int stop = size;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < size; ++j) {
            //stop writing spaces
            if (j >= stop) {
                break;
            }
            //index1- right slash index2- left slash in between dots and before spaces
            if (j == index1) {
                printf(RIGHT_SLASH);
            }else if (j == index2) {
                printf(LEFT_SLASH);
            } else if (flag == 1 && j > index1 && j < index2) {
                printf(DOT);
            } else {
                printf(SPACE);
            }

        }
        //makes the transition for the indexes for the next line
        stop--;
        index1++;
        index2--;
        printf(NEW_ROW);
    }
    //when the size is not even we need to add an X in the middle
    if (size % 2 == 1) {
        //declares the next usage of stop for odd size
        stop = ROWS + 2;
        for (int i = 0; i < size; ++i) {
            //stops the spaces after the X
            if (i > index1) {
                break;
            }
            if (i != index1) {
                printf(SPACE);
            } else {
                printf(MIDDLE_SIGN);
            }
        }
        printf(NEW_ROW);
        //when the size is even the indexes get their next place
        //when the size is odd it's exactly in the middle so we move them once
        index1++;
        index2--;
    } else {
        stop = ROWS + 1;
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < size; ++j) {
            //stops writing spaces
            if (j >= stop) {
                break;
            }
            //index1- right slash index2- left slash in between dots and before spaces
            if (j == index1) {
                printf(RIGHT_SLASH);
            }else if (j == index2) {
                printf(LEFT_SLASH);
            } else if (flag == 0 && j < index1 && j > index2) {
                printf(DOT);
            } else {
                printf(SPACE);
            }

        }
        //makes the transition for the indexes for the next line
        stop++;
        index1++;
        index2--;
        printf(NEW_ROW);
    }
    for (int i = 0; i < size; ++i)
        printf(LINE);
    printf(NEW_ROW);
}

/*
* @brief Reverses the bits of a number
*
* @param num the number before the reverse.
*
* @prints the number with reversed bits.
*/

void task2(int num) {
    int reversedNumber = 0;
    int const NUMBER_OF_BITS = 32;
    //goes over all the bits
    for (int i = 0; i < NUMBER_OF_BITS; ++i) {
        int reversedBit = 1;
        //the reversed place
        reversedBit <<= (NUMBER_OF_BITS - 1 - i);
        int bit = 1;
        //makes the ith bit 1
        bit <<= i;
        //checks if there is a 1 in the ith bit in the number
        bit &= num;
        //if it's one it will be added to the result in the reversed place
        if (bit != 0) {
            reversedNumber |= reversedBit;
        }
    }
    printf("The reversed number is %d", reversedNumber);
    printf(NEW_ROW);
}

/*
* @brief Reverses the digits of the number
*
* @param num the number before the reverse.
*
* @prints the reversed number.
*/

void task3(int num) {
    //unsigned long long for cases where the reversed number is bigger than 32 bits
    unsigned long long reversedNumber = 0;
    int copy = num;
    while (copy != 0) {
        int digit;
        //checks the right digit
        digit = copy % 10;
        //shift left once in base 10
        reversedNumber *= 10;
        //adds the current digit
        reversedNumber += digit;
        //shift right once in base 10
        copy /= 10;
    }
    printf("The reversed number is %llu", reversedNumber);
    printf(NEW_ROW);
}

/*
* @brief Switches two bits in a number
 * the function identifies between two cases:
 * 1. the bits are the same: 1, 1 / 0, 0
 * 2. the bits are not the same: 1, 0 / 0, 1
 * in the first one the number stays the same
 * in the second one you need to turn 0 to 1 and
 * 1 to 0
*
* @param num the number before the switch of the bits.
 * @param index1 the place of the first bit.
 * @param index1 the place of the second bit.
*
* @prints the number with switched bits.
*/

void task6(unsigned int num, int index1, int index2) {
    //correlates for the bit in index1
    unsigned int bit1 = 1;
    bit1 <<= index1;
    //correlates for the bit in index2
    unsigned int bit2 = 1;
    bit2 <<= index2;
    //makes the changes on copy1
    unsigned int copy1 = num;
    bit1 &= copy1;
    bit2 &= copy1;
    //makes them one and zero for comparison
    bit1 >>= index1;
    bit2 >>= index2;
    unsigned int switchedNumber = num;
    //when one of them is 0 and the other is 1
    if (bit1 != bit2) {
        //this if, makes both cases of 0 1 the same:
        //index1- will have the task 0 to 1
        //index2- will have the task 1 to 0
        if (bit1) {
            bit2 = 1;
            int temp;
            temp = index1;
            index1 = index2;
            index2 = temp;
        }
        //now we want to turn index2 to 0 and index1 to 1

        //the bit that we will insert
        bit1 = 1;
        bit1 <<= index2;
        copy1 = ~num;
        copy1 |= bit1;
        //we made the bit in index2- 1
        copy1 = ~copy1;
        //we copied that number into the result (the original number with 1 instead of 0 in index2)
        switchedNumber = copy1;
        bit2 <<= index1;
        //we made the bit in index1- 1
        switchedNumber |= bit2;
    }
    //when the bits are the same result= original number
    //when the bits are the different result= switched bits
    printf("The result is %u\n", switchedNumber);
}

/*
* @brief Function to Clean the buffer
* This function scans characters until it reaches a new line
 * by that it erases the characters that stayed in the buffer after other scans
*/

void cleanBuffer(char buffer) {
    do {
        scanf("%c", &buffer);
    } while (buffer != '\n');
}

#define NEWLINE '\n'
#define NUM_TO64 52
#define LOWER_CASE_TO64 26
#define UPPER_CASE_TO64 0
#define PLUS_TO64 62
#define SLASH_TO64 63
#include "stdlib.h"

int* fun(int a)
{
    int* p = malloc(sizeof (int));
    p=&a;
    return p;
}

int main() {
    int* a;
    int c = 2;
    a = fun(c);
    printf("a: %d \n",*a);
    int* b;
    int y = 5;
    int x =4;
    a= &y;
    b = a;
    printf("a: %d b: %d \n",*a,*b);
    b = &x;
    printf("a: %d b: %d \n",*a,*b);

    //will help cleaning the buffer
    char buffer = 'a';
    //shows which task the user chose
    char taskNumber = '1';
    //those 3 variables help us to know if the buffer is empty
    int firstInput = 0, valid4 = 0, valid5 = 0;
    while (taskNumber != '0') {
        printf("Choose an option:\n");
        printf("0. Exit\n");
        printf("1. Hourglass\n");
        printf("2. Reverse bits\n");
        printf("3. Reverse digits\n");
        printf("4. Convert to Decimal\n");
        printf("5. Base64 to Decimal\n");
        printf("6. Swap bits\n");
        //by negating the cases where the buffer is empty:
        //1. the first time I get an input
        //2. task 4 was done and successfully
        //3. task 5 was done and successfully
        //4. the user used '\n' (enter) as his char
        // negating (1 or 2 or 3 or 4) = not(1) and not(2) and not(3) and not(4)
        if (firstInput == 1 && (taskNumber != '4' || valid4 == 0) && (taskNumber != '5' || valid5 == 0) && taskNumber != '\n') {
            cleanBuffer(buffer);
        }
        //scans the task number
        scanf("%c", &taskNumber);
        //shows that it's not the first time
        firstInput = 1;
        //for every case it does the case's task
        switch (taskNumber) {
            case '0':
                break;
            case '1':
                printf("Enter size:\n");
                int size;
                scanf("%d", &size);
                printf("Enter flag:\n");
                int flag;
                scanf("%d", &flag);
                const int SIZE_MIN = 3;
                //checks for invalid input
                if (size < SIZE_MIN || (flag != 0 && flag != 1)) {
                    printf("Invalid Parameters\n");
                } else {
                    //calls for the task to be done
                    task1(size, flag);
                }
                break;
            case '2':
                printf("Enter a number:\n");
                //inserting the input to num1
                int num1;
                scanf("%d", &num1);
                //calls for the task to be done
                task2(num1);
                break;
            case '3':
                printf("Enter a number:\n");
                //inserting the input to num2
                int num2;
                scanf("%d", &num2);
                //calls for the task to be done
                task3(num2);
                break;
            case '4':
                //resets the validity of 4
                valid4 = 0;
                printf("Enter base:\n");
                int base;
                scanf("%d", &base);
                const int BASE_MIN = 2, BASE_MAX = 9;
                //checks for invalid base
                if (base > BASE_MAX || base < BASE_MIN) {
                    printf("Invalid Base\n");
                    break;
                } else {
                    int res = 0;
                    //the current character we check
                    char now = '0';
                    printf("Enter a number:\n");
                    cleanBuffer(buffer);
                    while (now != NEWLINE) {
                        scanf("%c", &now);
                        //checks if the number is not between 0 to base-1
                        if (now < '0' || (now - '0') >= base) {
                            break;
                        } else {
                            //makes everyone until now bigger by base (shift left)
                            res *= base;
                            //adds the new number
                            res += (now - '0');
                        }
                    }
                    if (now == NEWLINE) {
                        valid4 = 1;
                        printf("The converted number is %d\n", res);
                    } else {
                        printf("Invalid character %c in base %d\n", now, base);
                    }
                }
                break;
            case '5':
                //resets the validity of 5
                valid5 = 0;
                printf("Enter a number:\n");
                //the current character to convert to 64
                char now = '0';
                //will help identify if there was a character that is not in base 64
                int notIn64 = 0;
                unsigned long long int res = 0;
                cleanBuffer(buffer);
                const int BASE = 64;
                while (now != NEWLINE && notIn64 == 0) {
                    //makes everyone until now bigger by base (shift left)
                    res *= BASE;
                    scanf("%c", &now);
                    //for each group it adds the new character in base 64
                    switch (now) {
                        case '0' ... '9':
                            res += (now - '0' + NUM_TO64);
                            break;
                        case 'a' ... 'z':
                            res += (now - 'a' + LOWER_CASE_TO64);
                            break;
                        case 'A' ... 'Z':
                            res += (now - 'A' + UPPER_CASE_TO64);
                            break;
                        case '+':
                            res += PLUS_TO64;
                            break;
                        case '/':
                            res += SLASH_TO64;
                            break;
                        case NEWLINE:
                            break;
                        default:
                            notIn64 = 1;
                            break;
                    }
                }
                //in a case of a new line the program will multiply the result one more time
                res /= BASE;
                if (notIn64) {
                    printf("Invalid character %c in base 64\n", now);
                } else {
                    valid5 = 1;
                    printf("The converted number is %llu\n", res);
                }
                break;
            case '6':
                printf("Enter a number:\n");
                //inserting the input to num3
                unsigned int num3;
                scanf("%u", &num3);
                printf("Enter indexes:\n");
                int index1, index2;
                scanf("%d %d", &index1, &index2);
                int const BIT_MAX = 31, BIT_MIN = 0;
                //checks if the indexes are valid
                if (index1 > BIT_MAX || index1 < BIT_MIN || index2 > BIT_MAX || index2 < BIT_MIN) {
                    printf("Invalid indexes\n");
                } else {
                    //calls for the task to be done
                    task6(num3, index1, index2);
                }
                break;
            case '\n':
                //edge case
                scanf("%c", &taskNumber);
                printf("Invalid option\n");
                break;
            default:
                printf("Invalid option\n");

        }
    }
    return 0;
}
