// (89110, Spring 2023, Assignment #5, Nadav Rutman Moshe, 325387082, rutmann)


#include <stdio.h>
#include "string.h"
#include "stdlib.h"

typedef struct Node {
    void *data;
    struct Node *next;
} Node;
typedef struct Account {
    unsigned int accountNumber;
    char *accountHolder;
    int balance;
} Account;
typedef struct Transaction {
    unsigned int fromAccount;
    unsigned int toAccount;
    int amount;
} Transaction;
typedef struct Bank {
    Node *accounts;
    Node *transactions;
} Bank;

#define EXIT_VALUE 1

void cleanBuffer();

void printMenu();

void executeTask(char taskNumber, Node *, Node *, Bank *);

void addToList(Node *newNode, Node *headList);

#define GARBAGE_VALUE 'a'
#define ENDING_CHARACTER '0'

/**
* @brief main function that takes input from the user
 * then executes the task of that input
 * until the user inputs 0
 *
* @return 0 if the program runs successfully
*/

int main() {
    //making the bank
    Bank theBank;
    Node *headAccounts = (Node *) malloc(sizeof(Node));
    if (headAccounts == NULL) {
        exit(EXIT_VALUE);
    }
    headAccounts->next = NULL;
    Node *headTransactions = (Node *) malloc(sizeof(Node));
    if (headTransactions == NULL) {
        free(headAccounts);
        exit(EXIT_VALUE);
    }
    headTransactions->next = NULL;
    //for delete transactions which I delete the data
    headTransactions->data = NULL;
    theBank.accounts = headAccounts;
    theBank.transactions = headTransactions;
    //shows which task the user chose
    char taskNumber = GARBAGE_VALUE;
    while (taskNumber != ENDING_CHARACTER) {
        printMenu();
        scanf("%c", &taskNumber);
        executeTask(taskNumber, theBank.accounts, theBank.transactions, &theBank);
    }
    return 0;
}


/**
 * @brief the function frees the memory of the transaction
 *
 * @param headTransactions the pointer to the head of the transactions linked list
 */
void deleteTransactions(Node *headTransactions) {
    Node *delete = headTransactions;
    Node *nextDelete = delete->next;
    //deletes the first transaction
    free(delete->data);
    free(delete);
    //deletes every other transaction
    while (nextDelete != NULL) {
        delete = nextDelete;
        nextDelete = delete->next;
        free(delete->data);
        free(delete);
    }
}

/**
 * @brief the function frees the memory of the accounts
 *
 * @param headAccounts the pointer to the head of the Accounts linked list
 */
void deleteAccounts(Node *headAccounts) {
    Node *delete = headAccounts;
    Node *nextDelete = delete->next;
    //deletes the first account
    free(delete);
    //delete every account on the list
    while (nextDelete != NULL) {
        delete = nextDelete;
        nextDelete = delete->next;
        Account *deleteAccount = (Account *) delete->data;
        //free the name
        free(deleteAccount->accountHolder);
        free(deleteAccount);
        free(delete);
    }
}

/**
 * @brief the function free all the memory
 * uses deleteTransactions and deleteAccounts
 *
 * @param bank the pointer to the entire bank
 */
void freeAll(Bank *bank) {
    deleteTransactions(bank->transactions);
    deleteAccounts(bank->accounts);
}

/**
* @brief Prints the requested menu
* This function prints the options the user can use and asks from him to choose one
*/
void printMenu() {
    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Create account\n");
    printf("2. Delete account\n");
    printf("3. Update account\n");
    printf("4. Deposit / Withdraw money\n");
    printf("5. Transferring\n");
    printf("6. View account\n");
}

/**
* @brief Function to Clean the buffer
* This function scans characters until it reaches a new line
 * by that it erases the characters that stayed in the buffer after other scans
*/
void cleanBuffer() {
    scanf("%*[^\n]");
    scanf("%*c");
}

#define NOTHING '\0'

/**
 * @brief the function gets a char array
 * and a length and resets the array to '\0'
 *
 * @param str the array
 * @param length the length of the array
 */
void resetStr(char str[], int length) {
    for (int i = 0; i < length; ++i) {
        str[i] = NOTHING;
    }
}


#define NEWLINE '\n'

void addToList(Node *newNode, Node *headList);

/**
 * @brief the function gets account number and head accounts
 * if an account with account number exists it returns it else it returns NULL
 *
 * @param accountNumber
 * @param headAccounts the pointer to the head of the Accounts linked list
 *
 * @return the node of the account which the account number is the inserted account number
 */
Node *getByAccountNumber(unsigned int accountNumber, Node *headAccounts) {
    //first node
    Node *temp = headAccounts->next;
    while (temp != NULL) {
        Account tempAccount = *(Account *) temp->data;
        //finds the node with account number
        if (tempAccount.accountNumber == accountNumber) {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

/**
 * @brief the function gets account number and head transactions
 * if a transaction with account number exists it returns it else it returns NULL
 *
 * @param accountNumber
 * @param headTransaction
 *
 * @return the node of the transaction which the account is involved
 */
Node *getTransactionByAccount(unsigned int accountNumber, Node *headTransaction) {
    //first node
    Node *temp = headTransaction->next;
    while (temp != NULL) {
        Transaction tempTransaction = *(Transaction *) temp->data;
        //finds the node of the transaction which the account was involved
        if (tempTransaction.fromAccount == accountNumber || tempTransaction.toAccount == accountNumber) {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

/**
 * @brief the function allocates memory for a new pointer to account
 * and returns it if possible
 *
 * @param name the requested name of the account
 * @param accountNumber the requested account number of the account
 * @param balance the requested balance of the account
 *
 * @return the new pointer to the Account with the inserted variables
 */
Account *createAccount(char *name, unsigned int accountNumber, int balance) {
    //allocates new memory for the new account
    Account *newAccount = (Account *) malloc(sizeof(Account));
    if (newAccount == NULL) {
        return newAccount;
    }
    //updates the account
    newAccount->balance = balance;
    newAccount->accountNumber = accountNumber;
    newAccount->accountHolder = name;
    return newAccount;
}

/**
 * @brief the function allocates memory for a new pointer to Node
 * and returns it if possible
 *
 * @param data the requested data of the node
 * @param next the requested data of the node
 *
 * @return the new pointer to the Node with the inserted variables
 */
Node *createNode(void *data, Node *next) {
    //allocates new memory for the new node
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return newNode;
    }
    //updates the account
    newNode->next = next;
    newNode->data = data;
    return newNode;
}

#define STARTING_BALANCE 0

/**
 * @brief the function gets a name and account number
 * creates a node with those variables and adds it to the list of accounts
 *
 * @param name the name of the new account
 * @param accountNumber the requested account number of the account
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param bank the pointer to the entire bank
 */
void addAccount(char *name, unsigned int accountNumber, Node *headAccounts, Bank *bank) {
    //creating the new account
    Account *newAccount = createAccount(name, accountNumber, STARTING_BALANCE);
    if (newAccount == NULL) {
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //node for the new account
    Node *newAccountNode = createNode(newAccount, NULL);
    if (newAccountNode == NULL) {
        free(newAccount);
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    addToList(newAccountNode, headAccounts);
}

/**
 * @brief the function gets an account name
 * and add it to the existing linked list of accounts
 *
 * @param accountNumber the requested account number of the account
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param bank the pointer to the entire bank
 */
void task1(unsigned int accountNumber, Node *headAccounts, Bank *bank) {
    printf("Enter account holder:\n");
    //two spaces one for '\0'
    char *name = (char *) malloc(sizeof(char) * 2);
    if (name == NULL) {
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //index for inserting to name
    int index = 0;
    scanf("%c", &name[index]);
    while (name[index] != NEWLINE) {
        char *temp = name;
        int dynamicSize = index + 2;
        name = realloc(name, sizeof(char) * (dynamicSize));
        if (name == NULL) {
            free(temp);
            freeAll(bank);
            exit(EXIT_VALUE);
        }
        //inputs the name
        scanf("%c", &name[++index]);
    }
    //has new line as the last character
    name[index] = '\0';
    addAccount(name, accountNumber, headAccounts, bank);
    printf("Account created successfully\n");
}

#define TRUE 1
#define FALSE 0

/**
 * @brief the function gets an account number
 * and pointer to the head list and returns 1 if the account is in the list
 *
 * @param accountNumber the requested account number from the user
 * @param headAccounts the pointer to the head of the Accounts linked list
 *
 * @return 1 if the account is in the list else 0
 */
int inTheList(unsigned int accountNumber, Node *headAccounts) {
    //first account
    Node *temp = headAccounts->next;
    while (temp != NULL) {
        Account tempAccount = *(Account *) temp->data;
        //the account exists
        if (tempAccount.accountNumber == accountNumber) {
            return TRUE;
        }
        temp = temp->next;
    }
    return FALSE;
}

/**
 * @brief the function deletes the entered account number
 * from the list of accounts by setting the node before.next to his next
 *
 * @param accountNumber the requested account number of the account
 * @param headAccounts the pointer to the head of the Accounts linked list
 */
void task2(unsigned int accountNumber, Node *headAccounts) {
    Node *temp = headAccounts;
    //first account
    Node *next = temp->next;
    while (next != NULL) {
        Account nextAccount = *(Account *) next->data;
        if (nextAccount.accountNumber == accountNumber) {
            //the node we delete
            Node *temp2 = next;
            //making the next of the node before the node after
            temp->next = next->next;
            Account *deleteAccount = (Account *) temp2->data;
            //deleting account
            free(deleteAccount->accountHolder);
            free(temp2->data);
            free(temp2);
            return;
        }
        temp = next;
        next = next->next;
    }
}

void updateName(char *name, unsigned int accountNumber, Node *headAccounts) {
    //first account
    Node *temp = headAccounts->next;
    Account *tempAccount = (Account *) temp->data;
    //we know it will end because we got 1 from in the list
    while (tempAccount->accountNumber != accountNumber) {
        temp = temp->next;
        tempAccount = (Account *) temp->data;
    }
    //on the node in the account we have the number so we free the current and change the pointer
    free(tempAccount->accountHolder);
    tempAccount->accountHolder = name;
}

/**
 * @brief the function gets a name from the user
 * and updates the name for accountNumber
 *
 * @param accountNumber the requested account number of the account
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param bank the pointer to the entire bank
 */
void task3(unsigned int accountNumber, Node *headAccounts, Bank *bank) {
    //two spaces one for '\0'
    char *name = (char *) malloc(sizeof(char) * 2);
    if (name == NULL) {
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //index for inserting to name
    int index = 0;
    scanf("%c", &name[index]);
    while (name[index] != NEWLINE) {
        char *temp = name;
        int dynamicSize = index + 2;
        name = realloc(name, sizeof(char) * (dynamicSize));
        if (name == NULL) {
            free(temp);
            freeAll(bank);
            exit(EXIT_VALUE);
        }
        //inputs the name
        scanf("%c", &name[++index]);
    }
    //has new line as the last character
    name[index] = '\0';
    updateName(name, accountNumber, headAccounts);
}

/**
 * @brief the function allocates memory for a new pointer to transaction
 * and returns it if possible
 *
 * @param amount the requested to amount the transaction
 * @param from the requested to from the transaction
 * @param to the requested to of the transaction
 *
 * @return the new pointer to the Transaction with the inserted variables
 */
Transaction *createTransaction(int amount, unsigned int from, unsigned int to) {
    //allocates new memory for the new node
    Transaction *newTransaction = (Transaction *) malloc(sizeof(Transaction));
    if (newTransaction == NULL) {
        return newTransaction;
    }
    //updates the transaction
    newTransaction->amount = amount;
    newTransaction->fromAccount = from;
    newTransaction->toAccount = to;
    return newTransaction;
}

/**
 * @brief gets a new node and adds it to end of the list
 *
 * @param newNode the new node
 * @param headList the head of the linked list
 */
void addToList(Node *newNode, Node *headList) {
    //pointer to the first node
    Node *temp = headList->next;
    //case which the first node is NULL (this is the first node)
    if (temp == NULL) {
        headList->next = newNode;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    //the temp->next is NULL so we add our account there
    temp->next = newNode;
}

#define MONEY_SIZE 12
#define MIN_AMOUNT 0
#define DEPOSIT 0
#define BANK 0

/**
 * @brief the function makes a deposit if possible and updates the account
 *
 * @param tempAccount the account which will get the money
 * @param moneyNumber the amount of money
 * @param headTransactions the pointer to the head of the transactions linked list
 * @param accountNumber the requested account number from the user
 * @param bank the pointer to the entire bank
 */
void addDeposit(Account *tempAccount, int moneyNumber, Node *headTransactions, unsigned accountNumber, Bank *bank) {
    //creates a new transaction
    Transaction *newTransaction = createTransaction(moneyNumber, BANK, accountNumber);
    if (newTransaction == NULL) {
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //creates a new node
    Node *transactionNode = createNode(newTransaction, NULL);
    if (transactionNode == NULL) {
        free(newTransaction);
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //adds the node to the list
    addToList(transactionNode, headTransactions);
    tempAccount->balance += moneyNumber;
    printf("Money deposited successfully; your new balance is %d\n", tempAccount->balance);
}

/**
 * @brief the function makes a withdraw if possible and updates the account
 *
 * @param tempAccount the account which will give the money
 * @param moneyNumber the amount of money
 * @param headTransactions the pointer to the head of the transactions linked list
 * @param accountNumber the requested account number from the user
 * @param bank the pointer to the entire bank
 */
void addWithdraw(Account *tempAccount, int moneyNumber, Node *headTransactions, unsigned accountNumber, Bank *bank) {
    //doesn't have enough money
    if (tempAccount->balance < (int) (moneyNumber)) {
        printf("Not enough money\n");
        return;
    }
    //creates a new transaction
    Transaction *newTransaction = createTransaction((int) (moneyNumber), accountNumber, BANK);
    if (newTransaction == NULL) {
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //creates a new node
    Node *transactionNode = createNode(newTransaction, NULL);
    if (transactionNode == NULL) {
        free(newTransaction);
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //adds the node to the list
    addToList(transactionNode, headTransactions);
    tempAccount->balance -= (int) moneyNumber;
    printf("Money withdrawn successfully; your new balance is %d\n", tempAccount->balance);
}

/**
 * @brief the function gets the amount of money
 * to deposit/withdraw from the account and executes it if valid
 *
 * @param accountNumber the requested account number from the user
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param action the action the user chose deposit/withdraw
 * @param headTransactions the pointer to the head of the transactions linked list
 * @param bank the pointer to the entire bank
 */
void task4(unsigned int accountNumber, Node *headAccounts, int action, Node *headTransactions, Bank *bank) {
    if (action == DEPOSIT) {
        printf("How much money would you like to deposit?\n");
    } else {
        printf("How much money would you like to withdraw?\n");
    }
    // max characters of int is 10 so 12 spaces one for the end and one extra to check if it's too long
    char money[MONEY_SIZE];
    resetStr(money, MONEY_SIZE);
    scanf("%11[^\n]", money);
    cleanBuffer();
    //too long
    if (money[MONEY_SIZE - 2] != NOTHING) {
        printf("Invalid amount\n");
        return;
    }
    char *end;
    const int BASE = 10;
    long moneyNumber = strtol(money, &end, BASE);
    //the money is invalid
    if (*end != NOTHING || moneyNumber <= MIN_AMOUNT || money[0] < '0' || money[0] > '9') {
        printf("Invalid amount\n");
        return;
    }
    Node *temp = getByAccountNumber(accountNumber, headAccounts);
    Account *tempAccount = (Account *) temp->data;
    //makes the action deposit/withdraw
    if (action == DEPOSIT) {
        addDeposit(tempAccount, (int) moneyNumber, headTransactions, accountNumber, bank);

    } else {
        addWithdraw(tempAccount, (int) moneyNumber, headTransactions, accountNumber, bank);
    }

}

#define MAX_CHAR_INT 12
#define CANCEL 'A'
#define FLAG 'P'
#define ERROR -1
#define FLAG_INDEX 0
#define FIRST_DIGIT 0

/**
 * @brief the function returns the first index of the array
 *
 * @param from the array
 *
 * @return the first index of the array -1 error , 1 if there was a triple before 0 if it's the first
 */
int getIndex(char from[]) {
    if (from[FLAG_INDEX] == FLAG) {
        //case of infinite ','
        do {
            scanf("%c", &from[FIRST_DIGIT]);
        } while (from[FIRST_DIGIT] == ',');
        //new line error case
        if (from[FIRST_DIGIT] == NEWLINE) {
            from[FLAG_INDEX] = CANCEL;
            return ERROR;
        }
        //regular error case
        if (from[FIRST_DIGIT] < '0' || from[FIRST_DIGIT] > '9') {
            cleanBuffer();
            from[FLAG_INDEX] = CANCEL;
            return ERROR;
        }
        return TRUE;
    }
    return FALSE;
}

#define LAST_INDEX 10

/**
 * @brief the function sets the last character for the array
 *
 * @param str the array
 * @param wantedChar which character is accepted
 */
void getLastCharacter(char str[], char wantedChar) {
    scanf("%c", &str[LAST_INDEX]);
    //new line error case
    if (str[LAST_INDEX] == NEWLINE) {
        str[FLAG_INDEX] = CANCEL;
        return;
    }
    if (str[LAST_INDEX] == wantedChar) {
        return;
    }
    //regular error case
    cleanBuffer();
    str[FLAG_INDEX] = CANCEL;
}

#define DASH '-'
#define MIN_CHAR '0'
#define MAX_CHAR '9'
#define NUMBER_LENGTH 10

/**
 * @brief the function sets the array from
 * to be the number account of from in the transaction if it's valid
 *
 * @param from the array
 */
void getFrom(char from[]) {
    int index = getIndex(from);
    if (index == ERROR) {
        return;
    }
    //the ten digits of the numbers
    for (; index < NUMBER_LENGTH; ++index) {
        scanf("%c", &from[index]);
        //new line error case
        if (from[index] == NEWLINE) {
            from[FLAG_INDEX] = CANCEL;
            return;
        }
        if (from[index] == DASH) {
            //reached the end
            return;
        }
        //regular error case
        if (from[index] < MIN_CHAR || from[index] > MAX_CHAR) {
            cleanBuffer();
            from[FLAG_INDEX] = CANCEL;
            return;
        }
    }
    //last character
    getLastCharacter(from, DASH);
}

#define COLON ':'

/**
 * @brief the function sets the array to,
 * to be the number account of to,
 * in the transaction if it's valid
 *
 * @param to
 */
void getTo(char to[]) {
    //the ten digits of the numbers
    for (int i = 0; i < NUMBER_LENGTH; ++i) {
        scanf("%c", &to[i]);
        //new line error case
        if (to[i] == NEWLINE) {
            to[FLAG_INDEX] = CANCEL;
            return;
        }
        if (to[i] == COLON) {
            //reached the end
            return;
        }
        //regular error case
        if (to[i] < MIN_CHAR || to[i] > MAX_CHAR) {
            cleanBuffer();
            to[FLAG_INDEX] = CANCEL;
            return;
        }
    }
    //last character
    getLastCharacter(to, COLON);
}

#define COMMA ','

/**
 * @brief the function sets the array amount to be
 * the number of money in the transaction if it's valid
 *
 * @param amount the array
 *
 * @return index for the end if it's valid else -1
 */
int getAmount(char amount[]) {
    //the ten digits of the numbers
    for (int i = 0; i < NUMBER_LENGTH; ++i) {
        scanf("%c", &amount[i]);
        if (amount[i] == NEWLINE || amount[i] == COMMA) {
            return i;
        }
        //regular error case
        if (amount[i] < MIN_CHAR || amount[i] > MAX_CHAR) {
            cleanBuffer();
            return ERROR;
        }
    }
    //last character
    scanf("%c", &amount[LAST_INDEX]);
    if (amount[LAST_INDEX] == NEWLINE || amount[LAST_INDEX] == COMMA) {
        return LAST_INDEX;
    }
    cleanBuffer();
    return ERROR;
}

/**
 * @brief the function does the transaction if possible
 *
 * @param fromNode the node of the account which gives the money
 * @param toNode the node of the account which gets the money
 * @param amount the amount of money transferred  in the transaction
 * @param last the pointer to the last transaction before the changes
 * @param bank the pointer to the entire bank
 *
 * @return 1 if the transaction has been done successfully else 0
 */
int doTransaction(Node *fromNode, Node *toNode, int amount, Node *last, Bank *bank) {
    Account *fromAccount = (Account *) fromNode->data;
    Account *toAccount = (Account *) toNode->data;
    //creates a new transaction
    Transaction *transactionInfo = createTransaction(amount,
                                                     fromAccount->accountNumber,
                                                     toAccount->accountNumber);
    if (transactionInfo == NULL) {
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //creates a new node
    Node *transactionNode = createNode(transactionInfo, NULL);
    if (transactionNode == NULL) {
        free(transactionInfo);
        freeAll(bank);
        exit(EXIT_VALUE);
    }
    //adds the new node to the list (after last)
    addToList(transactionNode, last);
    fromAccount->balance -= amount;
    toAccount->balance += amount;
    return TRUE;
}

/**
 * @brief the function checks if the transaction from,
 * from, to, to, amount of money is valid
 *
 * @param from the array of the account which gives the money
 * @param to the array of the account which gets the money
 * @param amount the array of the amount of money transferred  in the transaction
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param last the pointer to the last transaction before the changes
 * @param bank the pointer to the entire bank
 *
 * @return 1 if it is valid else 0
 */
int checkValid(char from[], char to[], char amount[], Node *headAccounts, Node *last, Bank *bank) {
    unsigned int fromNumber = atoi(from);
    unsigned int toNumber = atoi(to);
    int amountNumber = atoi(amount);
    //the number zero or same from and to
    if (toNumber == 0 || fromNumber == 0 || amountNumber == 0 || toNumber == fromNumber) {
        return FALSE;
    }
    Node *fromNode = getByAccountNumber(fromNumber, headAccounts);
    Node *toNode = getByAccountNumber(toNumber, headAccounts);
    //doesn't exist
    if (fromNode == NULL || toNode == NULL) {
        return FALSE;
    }
    Account *fromAccount = (Account *) fromNode->data;
    //doesn't have enough money
    if (fromAccount->balance < amountNumber) {
        return FALSE;
    }
    return doTransaction(fromNode, toNode, amountNumber, last, bank);
}

/**
 * @brief undo all the transactions from last (gets last->next)
 *
 * @param last the first node of the first transaction to undo
 * @param headAccounts the pointer to the head of the Accounts linked list
 */
void undoTransactions(Node *last, Node *headAccounts) {
    //first transaction
    Node *transactionNode = last;
    while (transactionNode != NULL) {
        //extracts the info from the transaction
        Transaction *currentTransaction = (Transaction *) transactionNode->data;
        Node *fromAccountNode = getByAccountNumber(currentTransaction->fromAccount, headAccounts);
        Node *toAccountNode = getByAccountNumber(currentTransaction->toAccount, headAccounts);
        Account *fromAccount = (Account *) fromAccountNode->data;
        Account *toAccount = (Account *) toAccountNode->data;
        //reverse the transaction
        fromAccount->balance += currentTransaction->amount;
        toAccount->balance -= currentTransaction->amount;
        transactionNode = transactionNode->next;
    }
}

/**
 * @brief executes the option which the instructions are not valid
 *
 * @param last the pointer to the last transaction before the changes
 * @param headAccounts the pointer to the head of the Accounts linked list
 */
void invalidInstructions(Node *last, Node *headAccounts) {
    //reverses the transactions the deletes them
    if (last->next != NULL) {
        undoTransactions(last->next, headAccounts);
        deleteTransactions(last->next);
    }
    //updates the list
    last->next = NULL;
    printf("Invalid instructions\n");
}

/**
 * @brief the function checks if the triple (from)-(to):(amount) is valid
 *
 * @param last the pointer to the last transaction before the changes
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param stillGoing indicates if it is not the first call
 * @param from the array of the account which gives the money
 * @param to the array of the account which gets the money
 * @param amount the array of the amount of money transferred  in the transaction
 *
 * @return 1 if it's valid else 0
 */
int checkTriple(Node *last, Node *headAccounts, int stillGoing, char from[], char to[], char amount[]) {
    resetStr(from, MAX_CHAR_INT);
    //case of not the first transaction
    if (stillGoing) {
        from[FLAG_INDEX] = FLAG;
    }
    getFrom(from);
    //invalid from
    if (from[FLAG_INDEX] == CANCEL) {
        invalidInstructions(last, headAccounts);
        return FALSE;
    }
    resetStr(to, MAX_CHAR_INT);
    getTo(to);
    //invalid to
    if (to[FLAG_INDEX] == CANCEL) {
        invalidInstructions(last, headAccounts);
        return FALSE;
    }
    resetStr(amount, MAX_CHAR_INT);
    int endAmount = getAmount(amount);
    //invalid amount
    if (amount[FLAG_INDEX] == CANCEL || endAmount == ERROR) {
        invalidInstructions(last, headAccounts);
        return FALSE;
    }
    return TRUE;
}

/**
 * @brief gets an array and returns the last index which is not '\0'
 *
 * @param string the array
 *
 * @return the index of the last character
 */
int getEnd(char string[]) {
    int index = 0;
    while (string[index] != NOTHING) {
        index++;
    }
    const int ENDING = index - 1;
    //doesn't have '\0'
    return ENDING;
}

/**
 * @brief the function executes every transaction from the user
 * if it's valid, recursively until the end or until an error if there is an error
 * all the transaction until now will be reversed and then deleted (free)
 *
 * @param last the pointer to the last transaction before the changes
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param stillGoing indicates if it is not the first call
 * @param bank the pointer to the entire bank
 */
void getString(Node *last, Node *headAccounts, int stillGoing, Bank *bank) {
    //from , to , amount have 12 characters - 10 for the number , 1 for after the number and 1 for the end
    char from[MAX_CHAR_INT];
    char to[MAX_CHAR_INT];
    char amount[MAX_CHAR_INT];
    //gets the input of to,from and amount
    int validTriple = checkTriple(last, headAccounts, stillGoing, from, to, amount);
    if (validTriple == FALSE) {
        return;
    }
    int endAmount = getEnd(amount);
    //validity of account number and if the task is executable (not enough money in from)
    if (checkValid(from, to, amount, headAccounts, last, bank) == TRUE) {
        if (amount[endAmount] == NEWLINE) {
            printf("Instructions executed successfully\n");
        } else {
            //get more input from the user
            getString(last, headAccounts, TRUE, bank);
        }
    } else {
        invalidInstructions(last, headAccounts);
        //regular error case
        if (amount[endAmount] != NEWLINE) {
            cleanBuffer();
        }
    }
}

/**
 * @brief the function uses gets the last transaction
 * and then uses getstring() to input and execite the instructions
 *
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param headTransactions the pointer to the head of the transactions linked list
 * @param bank the pointer to the entire bank
 */
void task5(Node *headAccounts, Node *headTransactions, Bank *bank) {
    Node *last = headTransactions;
    //getting the last node before the changes
    while (last->next != NULL) {
        last = last->next;
    }
    getString(last, headAccounts, FALSE, bank);
}

/**
 * @brief the function prints the transaction details of the transaction node
 *
 * @param accountNumber the requested account number from the user
 * @param transactionNode the requested transaction to print
 */
void writeTransaction(unsigned int accountNumber, Node *transactionNode) {
    Transaction tempTransaction = *(Transaction *) transactionNode->data;
    if (tempTransaction.toAccount == accountNumber) {
        //deposit case
        if (tempTransaction.fromAccount == BANK) {
            printf("Deposited %d\n", tempTransaction.amount);
        } else {
            printf("%d from %u\n", tempTransaction.amount, tempTransaction.fromAccount);
        }
        //withdraw case
    } else {
        if (tempTransaction.toAccount == BANK) {
            printf("Withdrew %d\n", tempTransaction.amount);
        } else {
            printf("%d to %u\n", tempTransaction.amount, tempTransaction.toAccount);
        }
    }
}

/**
 * @brief the function prints the account details
 * (number , #name, balance and their transaction)
 *
 * @param accountNode the requested account to print
 * @param headTransactions the pointer to the head of the transactions linked list
 */
void task6(Node *accountNode, Node *headTransactions) {
    Account *nowAccount = (Account *) accountNode->data;
    //prints account number , name and number
    printf("Account #%u (%s)\n", nowAccount->accountNumber, nowAccount->accountHolder);
    printf("Balance: %d\n", nowAccount->balance);
    Node *currentTransaction = getTransactionByAccount(nowAccount->accountNumber, headTransactions);
    //doesn't have any transactions
    if (currentTransaction == NULL) {
        printf("No transactions\n");
    } else {
        printf("Transactions:\n");
        //prints the first transaction
        writeTransaction(nowAccount->accountNumber, currentTransaction);
        currentTransaction = getTransactionByAccount(nowAccount->accountNumber, currentTransaction);
        //prints all the transaction
        while (currentTransaction != NULL) {
            writeTransaction(nowAccount->accountNumber, currentTransaction);
            currentTransaction = getTransactionByAccount(nowAccount->accountNumber, currentTransaction);
        }
    }
}

/**
 * @brief the function gets
 * an account number from the user
 * and executes task1 accordingly
 * 
 * @param headAccounts the pointer to the head of the Accounts linked list
 * @param bank the pointer to the entire bank
 */
void executeTask1(Node *headAccounts, Bank *bank) {
    printf("Enter account number:\n");
    unsigned int accountNumber;
    //gets account number
    scanf("%u", &accountNumber);
    cleanBuffer();
    //checks if it's valid for task1
    if (accountNumber == 0 || inTheList(accountNumber, headAccounts)) {
        printf("Account number already exists\n");
    } else {
        task1(accountNumber, headAccounts, bank);
    }
}

/**
 * @brief the function gets
 * an account number from the user
 * and executes task2 accordingly
 * 
 * @param headAccounts the pointer to the head of the Accounts linked list 
 */
void executeTask2(Node *headAccounts) {
    printf("Enter account number:\n");
    unsigned int accountNumber2;
    //gets account number
    scanf("%u", &accountNumber2);
    //checks if it's valid for task2
    if (inTheList(accountNumber2, headAccounts)) {
        task2(accountNumber2, headAccounts);
        printf("Account deleted successfully\n");

    } else {
        printf("Account not found\n");
    }
    cleanBuffer();
}

/**
 * @brief the function gets
 * an account number from the user
 * and executes task3 accordingly
 * 
 * @param headAccounts the pointer to the head of the Accounts linked list 
 * @param bank the pointer to the entire bank
 */
void executeTask3(Node *headAccounts, Bank *bank) {
    printf("Enter account number:\n");
    unsigned int accountNumber3;
    //gets account number
    scanf("%u", &accountNumber3);
    cleanBuffer();
    //checks if it's valid for task3
    if (inTheList(accountNumber3, headAccounts)) {
        printf("Enter new account holder:\n");
        task3(accountNumber3, headAccounts, bank);
    } else {
        printf("Account not found\n");
    }
}

#define ACTION_LENGTH 9
#define WITHDRAW 1

/**
 * @brief the function gets an account number
 * and a string from the user
 * and executes task4 accordingly
 *
 * @param headAccounts the pointer to the head of the Accounts linked list 
 * @param headTransactions the pointer to the head of the transactions linked list 
 * @param bank the pointer to the entire bank
 */
void executeTask4(Node *headAccounts, Node *headTransactions, Bank *bank) {
    printf("Enter account number:\n");
    unsigned int accountNumber4;
    //gets account number
    scanf("%u", &accountNumber4);
    cleanBuffer();
    //checks if it's valid to get a string of deposit/withdraw
    if (inTheList(accountNumber4, headAccounts)) {
        printf("Would you like to deposit or withdraw money?\n");
        char action[ACTION_LENGTH];
        resetStr(action, ACTION_LENGTH);
        scanf("%9[^\n]", action);
        cleanBuffer();
        //checks if the string is deposit/withdraw here 0 is true
        if (strcmp(action, "withdraw") == 0 || strcmp(action, "deposit") == 0) {
            if (strcmp(action, "withdraw") == 0) {
                //withdraw will be marked as 1 and deposit as 0
                task4(accountNumber4, headAccounts, WITHDRAW, headTransactions, bank);
            } else {
                task4(accountNumber4, headAccounts, DEPOSIT, headTransactions, bank);
            }
        } else {
            printf("Invalid action\n");
        }

    } else {
        printf("Account not found\n");
    }
}

/**
 * @brief the function cleans the buffer and uses task5 to execute it
 * 
 * @param headAccounts the pointer to the head of the Accounts linked list 
 * @param headTransactions the pointer to the head of the transactions linked list 
 * @param bank the pointer to the entire bank
 */
void executetask5(Node *headAccounts, Node *headTransactions, Bank *bank) {
    scanf("%*c");
    printf("Enter instructions:\n");
    //calls task 5
    task5(headAccounts, headTransactions, bank);
}

/**
 * @brief the function gets
 * an account number and a string from the user
 * and executes task6 accordingly
 *
 * @param headAccounts the pointer to the head of the Accounts linked list 
 * @param headTransactions the pointer to the head of the transactions linked list 
 */
void executeTask6(Node *headAccounts, Node *headTransactions) {
    printf("Enter account number:\n");
    unsigned int accountNumber6;
    //gets account number
    scanf("%u", &accountNumber6);
    cleanBuffer();
    //checks if it's valid for task6
    if (inTheList(accountNumber6, headAccounts)) {
        Node *accountNode = getByAccountNumber(accountNumber6, headAccounts);
        task6(accountNode, headTransactions);
    } else {
        printf("Account not found\n");
    }
}

/**
* @brief this function gets a task number and executes the task accordingly
 *the function identifies the task number with a switch loop and acts accordingly
 *
 * @param taskNumber The number of the task inserted by the user.
 * @param bank the pointer to the entire bank
 *
*/
void executeTask(char taskNumber, Node *headAccounts, Node *headTransactions, Bank *bank) {
    //executes all the task according to task number
    switch (taskNumber) {
        case ENDING_CHARACTER:
            freeAll(bank);
            break;
        case '1':
            executeTask1(headAccounts, bank);
            break;
        case '2':
            executeTask2(headAccounts);
            break;
        case '3':
            executeTask3(headAccounts, bank);
            break;
        case '4':
            executeTask4(headAccounts, headTransactions, bank);
            break;
        case '5':
            executetask5(headAccounts, headTransactions, bank);
            break;
        case '6':
            executeTask6(headAccounts, headTransactions);
            break;
        default:
            //edge cases
            cleanBuffer();
            printf("Invalid option\n");
    }
}