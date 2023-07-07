// (89110, Spring 2023, Assignment #4, Nadav Rutman Moshe, 325387082, rutmann)

#include "ex_4.h"

#define SYMBOL "~"
#define SPACE ' '

/*
 * @brief the function prints a line of ~
 *
 * @param columns the length of the line
 */
void printLine(int columns) {
    for (int i = 0; i < columns; ++i) {
        printf(SYMBOL);
    }
    printf("\n");
}

/*
 * @brief the function gets a board and resets it
 * the function sets every char in the board to be space
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 */
void initBoard(char board[ROWS][COLS], int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = SPACE;
        }
    }
}

/*
 * @brief the function prints the current board
 * the function prints the board in the format of two lines of '~' as a frame
 * and between each "play" there are two lines | | (has not been played) |A| (has been played)
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 */
void printBoard(char board[ROWS][COLS], int rows, int columns) {
    const int REAL_COLUMNS = (2 * columns) + 1;
    //first "~" line
    printLine(REAL_COLUMNS);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < REAL_COLUMNS - 1; ++j) {
            //every second char is a |
            if (j % 2 == 0) {
                printf("|");
            } else {
                //the difference between j to the board is j/2
                printf("%c", board[i][j / 2]);
            }
        }
        printf("|\n");
    }
    //last "~" line
    printLine(REAL_COLUMNS);
}

/*
 * @brief the function gets a player and a column and makes the move of the player
 * the function checks if the parameters are valid and also if the column is full (can't make move)
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @param player character representing the player currently playing
 * @param column the chosen column of that player
 * @return if the move is executed 1 else 0
 */
int makeMove(char board[ROWS][COLS], int rows, int columns, int players, char player, int column) {
    //invalid player or invalid column
    if (player < 'A' || player >= 'A' + players || column >= columns || column < 0) {
        return 0;
    }
    //full column
    if (board[0][column] != SPACE) {
        return 0;
    }
    int place = rows - 1;
    for (int i = 0; i < rows; ++i) {
        if (board[i][column] != SPACE) {
            //finds the place
            place = i - 1;
            break;
        }

    }
    board[place][column] = player;
    return 1;
}

/*
 * @brief the function gets a column and removes the last play in that column
 * the function checks if the column is valid and if there is something in that column to remove
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param column the chosen colum to undo the move
 * @return if the move is executed 1 else 0
 */
int undoMove(char board[ROWS][COLS], int rows, int columns, int column) {
    //invalid column
    if (column >= columns || column < 0) {
        return 0;
    }
    //empty column
    if (board[rows - 1][column] == SPACE) {
        return 0;
    }
    for (int i = 0; i < rows; ++i) {
        //will always reach the if because board[rows - 1][column] != SPACE
        if (board[i][column] != SPACE) {
            board[i][column] = SPACE;
            return 1;
        }
    }
    //will never reach here (causes error)
    return 0;
}

#define FALSE -1

/*
 * @brief the function gets a board and checks if there is a row winner
 * by checking all the possible winners the function finds if one of them wins
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param connect the number of characters in a row to win
 * @return the character of the winner or FALSE if there isn't one
 */
char rowWinner(char board[ROWS][COLS], int rows, int columns, int connect) {
    for (int i = 0; i < rows; ++i) {
        //we need to check until we can't move connect-1 steps
        for (int j = 0; j < columns - connect + 1; ++j) {
            //every potential winner
            if (board[i][j] != SPACE) {
                char winner = board[i][j];
                int flag = 1;
                //we have one we need connect-1 more
                for (int k = 1; k < connect; ++k) {
                    if (board[i][j + k] != winner) {
                        flag = 0;
                    }
                }
                //we got connect in row
                if (flag == 1) {
                    return winner;
                }
            }
        }
    }
    return FALSE;
}

/*
 * @brief the function gets a board and checks if there is a column winner
 * by checking all the possible winners the function finds if one of them wins
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param connect the number of characters in a row to win
 * @return the character of the winner or FALSE if there isn't one
 */
char columnWinner(char board[ROWS][COLS], int rows, int columns, int connect) {
    //we need to check until we can't move connect-1 steps
    for (int i = 0; i < rows - connect + 1; ++i) {
        for (int j = 0; j < columns; ++j) {
            //every potential winner
            if (board[i][j] != SPACE) {
                char winner = board[i][j];
                int flag = 1;
                //we have one we need connect-1 more
                for (int k = 1; k < connect; ++k) {
                    if (board[i + k][j] != winner) {
                        flag = 0;
                    }
                }
                //we got connect in column
                if (flag == 1) {
                    return winner;
                }
            }
        }
    }
    return FALSE;
}

/*
 * @brief the function gets a board and checks if there is a (left to right- \) diagonal winner
 * by checking all the possible winners the function finds if one of them wins
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param connect the number of characters in a row to win
 * @return the character of the winner or FALSE if there isn't one
 */
char diagonalWinner1(char board[ROWS][COLS], int rows, int columns, int connect) {
    for (int i = 0; i < rows - connect + 1; ++i) {
        for (int j = 0; j < columns - connect + 1; ++j) {
            //every potential winner
            if (board[i][j] != SPACE) {
                char winner = board[i][j];
                int flag = 1;
                //we have one we need connect-1 more
                for (int k = 1; k < connect; ++k) {
                    if (board[i + k][j + k] != winner) {
                        flag = 0;
                    }
                }
                //we got connect in diagonal1
                if (flag == 1) {
                    return winner;
                }
            }
        }

    }
    return FALSE;
}

/*
 * @brief the function gets a board and checks if there is a (right to left- /) diagonal winner
 * by checking all the possible winners the function finds if one of them wins
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param connect the number of characters in a row to win
 * @return the character of the winner or FALSE if there isn't one
 */
char diagonalWinner2(char board[ROWS][COLS], int rows, int columns, int connect) {
    //from the end of the row to 0 + connect -1
    for (int i = rows - 1; i >= connect - 1; --i) {
        for (int j = 0; j < columns - connect + 1; ++j) {
            //every potential winner
            if (board[i][j] != SPACE) {
                char winner = board[i][j];
                int flag = 1;
                //we have one we need connect-1 more
                for (int k = 1; k < connect; ++k) {
                    if (board[i - k][j + k] != winner) {
                        flag = 0;
                    }
                }
                //we got connect in diagonal2
                if (flag == 1) {
                    return winner;
                }
            }
        }
    }
    return FALSE;
}

/*
 * @brief the function gets a board and return the board's winner
 * the function uses rowWinner, columnWinner, diagonalWinner1, diagonalWinner2
 * in order to decide if there is a winner
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @param connect the number of characters in a row to win
 * @return the character of the winner or FALSE if there isn't one
 */
char getWinner(char board[ROWS][COLS], int rows, int columns, __attribute__((__unused__)) int players, int connect) {
    char winner;
    winner = rowWinner(board, rows, columns, connect);
    //checks for row winner
    if (winner != FALSE) {
        return winner;
    }
    winner = columnWinner(board, rows, columns, connect);
    //checks for column winner
    if (winner != FALSE) {
        return winner;
    }
    winner = diagonalWinner1(board, rows, columns, connect);
    //checks for diagonal1 winner
    if (winner != FALSE) {
        return winner;
    }
    winner = diagonalWinner2(board, rows, columns, connect);
    //checks for diagonal2 winner
    if (winner != FALSE) {
        return winner;
    }
    return FALSE;
}

/*
 * @brief the function gets a board and return the board's status: win, tie, in progress
 * the function uses getWinner
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @param connect the number of characters in a row to win
 * @return 1 if there is a winner 0 if there is a tie and -1 if the game is still going
 */
int getStatus(char board[ROWS][COLS], int rows, int columns, __attribute__((__unused__)) int players, int connect) {
    if (getWinner(board, rows, columns, players, connect) == FALSE) {
        for (int i = 0; i < columns; ++i) {
            //checks if there is a not empty column
            if (board[0][i] == SPACE) {
                return -1;
            }
        }
        return 0;
    }
    return 1;
}

/*
 * @brief the function gets a board and decides if the character in this board are legal
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @return 1 if all the characters are valid else 0
 */
int validPlayers(char board[ROWS][COLS], int rows, int columns, int players) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            //invalid char
            if ((board[i][j] < 'A' || board[i][j] > 'A' + players - 1) && board[i][j] != SPACE) {
                return 0;
            }
        }

    }
    return 1;
}

/*
 * @brief the function gets a board and returns the number of plays that have been played
 * to get to that board
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @return the number of plays that have been played so far
 */
int numOfPlays(char board[ROWS][COLS], int rows, int columns) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            //every char that is not space
            if (board[i][j] != SPACE) {
                sum++;
            }
        }

    }
    return sum;
}

/*
 * @brief the function gets a board and a column
 * and returns the character of the last player to play in that column if there isn't one
 * then it returns FALSE
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param column
 * @return the last character to play in that column (FALSE if there isn't one)
 */
char getTop(char board[ROWS][COLS], int rows, int column) {
    for (int i = 0; i < rows; ++i) {
        if (board[i][column] != SPACE) {
            return board[i][column];
        }
    }
    return FALSE;
}

/*
 * @brief the function gets a board and checks if there is a sequence of moves that can reach this board
 * the function uses numOfPlays, getTop, undoMove and recursion
 * it has the character of the last turn and checks for every possible last turn if it leads to an empty board
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @param last the character of the last player that has played
 * @return 1 if the board is legal else 0
 */
int CheckLegalMoves(char board[ROWS][COLS], int rows, int columns, int players, char last) {
    if (numOfPlays(board, rows, columns) == 0) {
        return 1;
    }
    int sum = 0;
    //checks every column
    for (int j = 0; j < columns; ++j) {
        //the potential last turn
        char currentTop = getTop(board, rows, j);
        if (currentTop != FALSE && currentTop == last) {
            undoMove(board, rows, columns, j);
            if (last == 'A') {
                // new last = the last digit on the players
                sum += CheckLegalMoves(board, rows, columns, players, 'A' + players - 1);
            } else {
                // new last = last - 1 : 'Z' - 1 = 'Y'
                sum += CheckLegalMoves(board, rows, columns, players, last - 1);
            }
            makeMove(board, rows, columns, players, currentTop, j);
            //there is a valid move sequence
            if (sum != 0) {
                return sum;
            }
        }
    }
    return sum;
}

/*
 * @brief the function solves the case which the board has a valid move sequence but has a winner
 * it checks if one of the last moves make the winner "go away" and if there is one it will return 1
 * else 0
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @param connect the number of characters in a row to win
 * @param winner the last character that has been played
 * @return 1 if the board is valid else 0
 */
int solveWinner(char board[ROWS][COLS], int rows, int columns, int players, int connect, char winner) {
    for (int j = 0; j < columns; ++j) {
        //potential winner move
        char currentTop = getTop(board, rows, j);
        if (currentTop != FALSE && currentTop == winner) {
            undoMove(board, rows, columns, j);
            if (getStatus(board, rows, columns, players, connect) != 1) {
                makeMove(board, rows, columns, players, currentTop, j);
                //game is not winning anymore
                return 1;
            }
            makeMove(board, rows, columns, players, currentTop, j);

        }
    }
    return 0;
}

/*
 * @brief the function checks for "flying" characters
 * "flying" character is a character that has been played but didn't reach the end of the column
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @return 1 if there aren't any "flying" character else 0
 */
int validPlacement(char board[ROWS][COLS], int rows, int columns) {
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i < rows; ++i) {
            //reaches first character
            if (board[i][j] != SPACE) {
                i++;
                //checks for a space underneath
                while (i < rows) {
                    if (board[i][j] == SPACE) {
                        return 0;
                    }
                    i++;
                }
            }

        }

    }
    //no one has spaces underneath
    return 1;
}

/*
 * @brief the function gets a board and checks if it could happen in the start middle or end of the game
 *the function uses: validPlayers, validPlacement, numOfPlays, CheckLegalMoves, getStatus, solveWinner
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param columns the number of columns in the board
 * @param players the number of players playing the game
 * @param connect the number of characters in a row to win
 * @return 1 if the board is valid else 0
 */
int isValidBoard(char board[ROWS][COLS], int rows, int columns, int players, int connect) {
    //checks for invalid characters
    if (validPlayers(board, rows, columns, players) == 0) {
        return 0;
    }
    //checks for "flying" characters
    if (validPlacement(board, rows, columns) == 0) {
        return 0;
    }
    //if we know the number of plays that have been played
    //and the number of players we can know which character was played last
    int numberOfPlays = numOfPlays(board, rows, columns);
    int modLast = numberOfPlays % players;
    char last;
    if (modLast == 0) {
        // last = the last digit on the players
        last = 'A' + players - 1;
    } else {
        // last = the last digit to play
        last = 'A' + modLast - 1;
    }
    int check = CheckLegalMoves(board, rows, columns, players, last);
    if (check == 0) {
        return 0;
    }
    //tie or still going
    if (getStatus(board, rows, columns, players, connect) != 1) {
        return 1;
    }
    //winner situation: check all the possible undo for last and if one removes winner then legal
    return solveWinner(board, rows, columns, players, connect, last);
}

/*
 * @brief the function gets a number and returns the character representing that number in base 64
 *
 * @param number the number for conversion
 * @return the character representing that number in base 64
 */
char numberTo64(int number) {
    switch (number) {
        case 0 ... 25:
            return 'A' + number;
        case 26 ... 51:
            return 'a' + number;
        case 52 ... 61:
            return '0' + number;
        case 62:
            return '+';
        case 63:
            return '/';
    }
    //will never reach here
    return -1;
}

/*
 * @brief the function gets a number a char a pointer to char and an index
 * and it puts the number (converted to base 64) and the character in the pointer in the specified index
 *
 * @param count the number before the conversion to base 64
 * @param current the other character that will be added to the pointer
 * @param code the char pointer
 * @param index the place the two characters enter the pointer
 * @return the index plus 2
 */
int addCouple(int count, char current, char *code, int index) {
    code[index] = numberTo64(count);
    index++;
    code[index] = current;
    return ++index;
}

/*
 * @brief the function gets a board and decodes it by the specified format
 * / represents the end of a line
 * XY every two letters represent a sequence of X (to base 64) characters of Y in a row
 *
 * @param board the playing board
 * @param rows the number of rows in the board
 * @param cols the number of columns in the board
 * @param code the pointer which will get the encoded string
 */
void encode(const char board[ROWS][COLS], int rows, int cols, char *code) {
    //for changing code
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        //start of a sequence
        char current = board[i][0];
        int count = 1;
        for (int j = 0; j < cols - 1; ++j) {
            if (current == board[i][j + 1]) {
                count++;
            } else {
                //end of a sequence
                index = addCouple(count, current, code, index);
                current = board[i][j + 1];
                count = 1;
            }
            //either case the j+1 will be added
            if (j + 1 == cols - 1) {
                index = addCouple(count, current, code, index);
            }
        }
        code[index] = '/';
        index++;

    }
    //last character
    code[index] = '\0';
}

#define LOWER_CASE_TO64 26
#define UPPER_CASE_TO64 0
#define PLUS_TO64 62
#define SLASH_TO64 63
#define NUM_TO64 52

/*
 * @brief the function gets a character and returns the number representing that character in base 64
 *
 * @param now the specified character
 * @return the number representing that character
 */
int convertTo64(char now) {
    switch (now) {
        case '0' ... '9':
            return now - '0' + NUM_TO64;
        case 'a' ... 'z':
            return (now - 'a' + LOWER_CASE_TO64);
        case 'A' ... 'Z':
            return (now - 'A' + UPPER_CASE_TO64);
        case '+':
            return PLUS_TO64;
        case '/':
            return SLASH_TO64;
    }
    //will never reach here
    return -1;
}

/*
 * @brief the function gets a string representing a board and inserts it to the board
 * / represents the end of a line
 * XY every two letters represent a sequence of X (to base 64) characters of Y in a row
 *
 * @param code the string
 * @param board the board we insert the string to
 */
void decode(const char *code, char board[ROWS][COLS]) {
    //for the code
    int index = 0;
    //for the board
    int row = 0;
    //for the board
    int column = 0;
    while (code[index] != '\0') {
        //every row
        while (code[index] != '/') {
            int length = convertTo64(code[index]);
            for (int i = 0; i < length; ++i) {
                // the character
                board[row][column] = code[index + 1];
                column++;
            }
            //next couple
            index += 2;
        }
        //resets for the next row
        column = 0;
        row++;
        //next char in code
        index++;
    }

}
