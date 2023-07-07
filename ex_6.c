// (89110, Spring 2023, Assignment #6, Nadav Rutman Moshe, 325387082, rutmann)


#include <stdio.h>
#include "string.h"
#include "stdlib.h"


typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Person {
    char *name;
    unsigned int age;
    struct Person *parent1;
    struct Person *parent2;
    struct Person *married;
    //linked list of the children
    Node *firstChild;
    //values 1/0
    int checked;
} Person;


void printMenu();

void cleanBuffer();

void executeTask(char taskNumber, Node *);

void addToList(Node *newNode, Node *headList);

#define EXIT_VALUE 1
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
    //creating the infrastructure
    Node *headPersons;
    Node head;
    head.next = NULL;
    long size = 0;
    //points to the size of the tree
    head.data = &size;
    headPersons = &head;
    char taskNumber = GARBAGE_VALUE;
    while (taskNumber != ENDING_CHARACTER) {
        printMenu();
        scanf("%c", &taskNumber);
        //most cases will have a name as a first input
        cleanBuffer();
        executeTask(taskNumber, headPersons);
    }
    return 0;
}


/**
 * @brief the function free the memory of the whole family tree
 *
 * @param headPersons the head of the family tree
 */
void theApocalypse(Node *headPersons) {
    if (headPersons != NULL) {
        Person *currentAncestor = (Person *) headPersons->data;
        //has children
        if (currentAncestor->firstChild->next != NULL) {
            currentAncestor->married->firstChild->next = NULL;
            theApocalypse(currentAncestor->firstChild->next);
        }
        theApocalypse(headPersons->next);
        //free him at the end - we have freed his children and the rest of his list
        free(currentAncestor->name);
        free(currentAncestor->firstChild);
        free(currentAncestor);
        free(headPersons);
    }
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


/**
* @brief Function to Clean the buffer
* This function scans characters until it reaches a new line
 * by that it erases the characters that stayed in the buffer after other scans
*/
void cleanBuffer() {
    scanf("%*[^\n]");
    scanf("%*c");
}

/**
* @brief Prints the requested menu
* This function prints the options the user can use and asks from him to choose one
*/
void printMenu() {
    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Add a head\n");
    printf("2. Marry two people\n");
    printf("3. New offspring\n");
    printf("4. Print family top-down\n");
    printf("5. Years pass\n");
    printf("6. Count people\n");
    printf("7. Print cousins\n");
}

#define NEW_LINE '\n'

/**
 * @brief the function gets a string from the user
 * 
 * @return the pointer to the start of the string
 */
char *getName() {
    char *name = (char *) malloc(sizeof(char) * 2);
    if (name == NULL) {
        return name;
    }
    //index for inserting to name
    int index = 0;
    scanf("%c", &name[index]);
    while (name[index] != NEW_LINE) {
        char *temp = name;
        //adding more to the size
        int dynamicSize = index + 2;
        name = realloc(name, sizeof(char) * (dynamicSize));
        if (name == NULL) {
            free(temp);
            return name;
        }
        //inputs the name
        scanf("%c", &name[++index]);
    }
    //has new line as the last character
    name[index] = '\0';
    return name;
}

#define EXIT_VALUE 1
#define TRUE 1
#define SWITCH_FLAG 1

/**
 * @brief the function resets the tree to everyone having checked at 0
 * 
 * @param headPersons the head of the family tree
 */
void resetList(Node *headPersons) {
    Node *temp = headPersons;
    while (temp != NULL) {
        Person *currentAncestor = (Person *) temp->data;
        //is marked
        if (currentAncestor->checked == TRUE) {
            currentAncestor->checked ^= SWITCH_FLAG;
            //married
            if (currentAncestor->married != NULL && currentAncestor->married->checked == TRUE) {
                currentAncestor->married->checked ^= SWITCH_FLAG;
            }
        }
        //has children
        if (currentAncestor->firstChild->next != NULL) {
            resetList(currentAncestor->firstChild->next);
        }
        temp = temp->next;
    }
}

#define STR_CMP_TRUE 0
#define FALSE 0


/**
 * @brief the function gets a name and a tree and searches for the person in the
 * tree
 * 
 * @param name the name of the person
 * @param headPersons the head of the family tree
 * @return if it's found it returns the pointer to that person else NULL
 */
Person *getByName(char *name, Node *headPersons) {
    Node *temp = headPersons;
    while (temp != NULL) {
        Person *currentAncestor = (Person *) temp->data;
        //has not been checked yet
        if (currentAncestor->checked == FALSE) {
            //mark him
            currentAncestor->checked ^= SWITCH_FLAG;
            if (strcmp(currentAncestor->name, name) == STR_CMP_TRUE) {
                return currentAncestor;
            }
            //married
            if (currentAncestor->married != NULL && currentAncestor->married->checked == FALSE) {
                currentAncestor->married->checked ^= SWITCH_FLAG;
                if (strcmp(currentAncestor->married->name, name) == STR_CMP_TRUE) {
                    return currentAncestor->married;
                }
            }
            //has children
            if (currentAncestor->firstChild->next != NULL) {
                Person *checkChildren = getByName(name, currentAncestor->firstChild->next);
                //the children have the name
                if (checkChildren != NULL) {
                    return checkChildren;
                }
            }

        }
        temp = temp->next;
    }
    return NULL;
}

/**
 * @brief the function gets attributes for a person and creates it
 * 
 * @param name the name of the person
 * @param age the age of the person
 * @param parent1 the first parent of the person
 * @param parent2 the second parent of the person
 * 
 * @return the pointer to the person created
 */
Person *createPerson(char *name, unsigned int age, Person *parent1, Person *parent2) {
    //allocates memory
    Person *newPerson = malloc(sizeof(Person));
    if (newPerson == NULL) {
        return newPerson;
    }
    //makes the attributes of the person
    newPerson->age = age;
    newPerson->name = name;
    newPerson->checked = FALSE;
    //allocates memory for the children list
    Node *headChildren = createNode(NULL, NULL);
    if (headChildren == NULL) {
        free(newPerson);
        return NULL;
    }
    newPerson->firstChild = headChildren;
    newPerson->married = NULL;
    newPerson->parent1 = parent1;
    newPerson->parent2 = parent2;
    //checks if he is a child
    if (parent1 != NULL && parent1 != NULL) {
        Node *brother = createNode(newPerson, NULL);
        if (brother == NULL) {
            free(newPerson);
            free(headChildren);
            return NULL;
        }
        //adds to parents list
        addToList(brother, parent1->firstChild);
        addToList(brother, parent2->firstChild);
    }
    return newPerson;
}

/**
 * @brief the function gets a name and age from the user
 * and creates it if possible
 * 
 * @param headPersons the head of the family tree
 */
void task1(Node *headPersons) {
    printf("Enter a name:\n");
    //gets a name from the user
    char *name = getName();
    if (name == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    printf("Enter age:\n");
    unsigned int age;
    //gets an age from the user
    scanf("%u", &age);
    cleanBuffer();
    Person *check = getByName(name, headPersons->next);
    resetList(headPersons->next);
    //person doesn't exists
    if (check == NULL) {
        Person *newPersonData = createPerson(name, age, NULL, NULL);
        if (newPersonData == NULL) {
            free(name);
            theApocalypse(headPersons->next);
            exit(EXIT_VALUE);
        }
        //creates a node for the person
        Node *newPersonNode = createNode(newPersonData, NULL);
        if (newPersonNode == NULL) {
            free(name);
            free(newPersonData);
            theApocalypse(headPersons->next);
            exit(EXIT_VALUE);
        }
        //updates the counter
        *((long *) (headPersons->data)) = *((long *) (headPersons->data)) + 1;
        addToList(newPersonNode, headPersons);
    } else {
        free(name);
        printf("The name is already taken\n");
    }
}

/**
 * @brief the function marks the fathers of the person inserted
 * 
 * @param currentPerson 
 */
void markFathers(Person *currentPerson) {
    currentPerson->checked ^= SWITCH_FLAG;
    //we can check only one but just in case we check the other one
    if (currentPerson->parent1 != NULL && currentPerson->parent2 != NULL) {
        markFathers(currentPerson->parent1);
        markFathers(currentPerson->parent2);
    }
}

/**
 * @brief the function checks if the current person has a common 
 * ancestor with the other person
 * 
 * @param currentPerson the person we want to check
 * 
 * @return 1 if the person related else 0
 */
int isRelated(Person *currentPerson) {
    if (currentPerson->checked) {
        return TRUE;
    }
    //we can check only one but just in case we check the other one
    if (currentPerson->parent1 != NULL && currentPerson->parent2 != NULL) {
        return isRelated(currentPerson->parent1) + isRelated(currentPerson->parent2);
    }
    return FALSE;

}


#define MIN_MARRIAGE_AGE 18

/**
 * @brief the function takes 2 names from the user
 * and marries them it if valid
 * 
 * @param headPersons the head of the family tree
 */
void task2(Node *headPersons) {
    printf("Enter the name of the first person:\n");
    //gets a name from the user
    char *name1 = getName();
    if (name1 == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    printf("Enter the name of the second person:\n");
    //gets a name from the user
    char *name2 = getName();
    if (name2 == NULL) {
        free(name1);
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    Person *check1 = getByName(name1, headPersons->next);
    resetList(headPersons->next);
    Person *check2 = getByName(name2, headPersons->next);
    //we don't use name1 and name2 anymore
    free(name1);
    free(name2);
    resetList(headPersons->next);
    //checks if one of the names doesn't exists name
    if (check1 == NULL || check2 == NULL) {
        printf("One of the persons does not exist\n");
        return;
    }
    //edge cases
    if (strcmp(check1->name, check2->name) == STR_CMP_TRUE || check1->age < MIN_MARRIAGE_AGE ||
        check2->age < MIN_MARRIAGE_AGE) {
        printf("Invalid marriage\n");
        return;
    }
    markFathers(check1);
    //more edge cases
    if (isRelated(check2) != FALSE || check1->married != NULL || check2->married != NULL) {
        printf("Invalid marriage\n");
    } else {
        check1->married = check2;
        check2->married = check1;
        printf("%s and %s are now married\n", check1->name, check2->name);
    }
    //in markFathers we made some persons checked
    resetList(headPersons->next);
}


#define STARTING_AGE 0

/**
 * @brief the function takes 3 names from the user
 * married couple and the name of the child and creates it if valid
 * this function is quite long because we input 3 names which each can be NULL
 * 
 * @param headPersons the head of the family tree
 */
void task3(Node *headPersons) {
    printf("Enter the name of the first parent:\n");
    //gets the first parent name
    char *parent1Name = getName();
    if (parent1Name == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    //finds the person and frees the memory for name
    Person *parent1 = getByName(parent1Name, headPersons->next);
    resetList(headPersons->next);
    free(parent1Name);
    printf("Enter the name of the second parent:\n");
    //gets the second parent name
    char *parent2Name = getName();
    if (parent2Name == NULL) {
        free(parent1Name);
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    Person *parent2 = getByName(parent2Name, headPersons->next);
    resetList(headPersons->next);
    free(parent2Name);
    printf("Enter offspring's name:\n");
    //gets the child name
    char *childName = getName();
    if (childName == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    //One of the parents does not exist
    if (parent1 == NULL || parent2 == NULL) {
        free(childName);
        printf("One of the parents does not exist\n");
        return;
    }
    if (parent1->married == parent2 && parent2->married == parent1) {
        Person *child = getByName(childName, headPersons->next);
        resetList(headPersons->next);
        //the name already exists
        if (child != NULL) {
            free(childName);
            printf("The name is already taken\n");
        } else {
            //added him to the parents in createPerson
            if (createPerson(childName, STARTING_AGE, parent1, parent2) == NULL) {
                free(childName);
                theApocalypse(headPersons->next);
                exit(EXIT_VALUE);
            }
            printf("%s was born\n", childName);
            //updating the counter
            *((long *) (headPersons->data)) = *((long *) (headPersons->data)) + 1;
        }
    } else {
        free(childName);
        printf("The parents are not married\n");
    }
}

#define ADD_TABS 1

/**
 * @brief the function prints the family tree of a person adding one tab
 * each time we go down in the tree
 * 
 * @param currentPerson 
 * @param tabs 
 */
void printFamily(Person *currentPerson, int tabs) {
    //hasn't been printed yet
    if (currentPerson->checked == FALSE) {
        for (int i = 0; i < tabs; ++i) {
            printf("\t");
        }
        currentPerson->checked ^= SWITCH_FLAG;
        printf("%s (%u)", currentPerson->name, currentPerson->age);
        //in a marriage
        if (currentPerson->married != NULL && currentPerson->married->checked == FALSE) {
            currentPerson->married->checked ^= SWITCH_FLAG;
            printf(" - %s (%u)", currentPerson->married->name, currentPerson->married->age);
        }
        printf("\n");
        //has children
        if (currentPerson->firstChild->next != NULL) {
            Node *temp = currentPerson->firstChild->next;
            while (temp != NULL) {
                //prints his children
                printFamily(temp->data, tabs + ADD_TABS);
                temp = temp->next;
            }
        }
    }

}

#define STARTING_TABS 0

/**
 * @brief the function asks for the user for a name and then prints 
 * his family if it exists
 * 
 * @param headPersons the head of the family tree
 */
void task4(Node *headPersons) {
    printf("Enter the name of the person:\n");
    //gets the father name
    char *fatherName = getName();
    if (fatherName == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    Person *father = getByName(fatherName, headPersons->next);
    free(fatherName);
    resetList(headPersons->next);
    //the father doesn't exist
    if (father == NULL) {
        printf("The person does not exist\n");
        return;
    }
    //prints his family
    printFamily(father, STARTING_TABS);
    resetList(headPersons->next);
}

/**
 * @brief the function adds the parameter years to all of the family tree
 *
 * @param years the number of years to be added
 * @param headPersons
 */
void addYears(unsigned int years, Node *headPersons) {
    Node *temp = headPersons;
    while (temp != NULL) {
        Person *currentAncestor = (Person *) temp->data;
        //hasn't been added years
        if (currentAncestor->checked == FALSE) {
            currentAncestor->age += years;
            currentAncestor->checked ^= SWITCH_FLAG;
            //married
            if (currentAncestor->married != NULL && currentAncestor->married->checked == FALSE) {
                currentAncestor->married->age += years;
                currentAncestor->married->checked ^= SWITCH_FLAG;
            }
            //has children
            if (currentAncestor->firstChild->next != NULL) {
                addYears(years, currentAncestor->firstChild->next);
            }
        }
        temp = temp->next;
    }
}

/**
 * @brief the function goes down #degree levels. down in the family tree
 * and sends marks them as cousins at the end
 *
 * @param theChildren the current list of children
 * @param currentDegree how much did I go down
 * @param degree how many do I need to go down in total
 * @param count the pointer to the count of cousins
 */
void markChildren(Node *theChildren, unsigned int currentDegree, unsigned int degree, int *count) {
    Node *temp = theChildren;
    while (temp != NULL) {
        Person *currentChild = (Person *) temp->data;
        if (currentDegree == degree) {
            //is a cousin
            if (currentChild->checked == FALSE) {
                currentChild->checked ^= SWITCH_FLAG;
                //add to cousins counter
                (*count)++;
            }
        } else {
            if (currentChild->firstChild->next != NULL) {
                //go down one degree
                markChildren(currentChild->firstChild->next, currentDegree + 1, degree, count);
            }
        }
        temp = temp->next;
    }
}

/**
 * @brief the function goes up #degree levels. up in the family tree
 * and sends them to a function that goes down in the family tree
 *
 * @param thePerson the person chosen for task 7
 * @param currentDegree how much did I go up
 * @param degree how many do I need to go up in total
 * @param count the pointer to the count of cousins
 */
void getParents(Person *thePerson, unsigned int currentDegree, unsigned int degree, int *count) {
    if (currentDegree == degree) {
        if (thePerson->firstChild->next != NULL) {
            //reached degree levels
            markChildren(thePerson->firstChild->next, 1, degree, count);
        }
    }
    if (thePerson->parent1 != NULL && thePerson->parent2 != NULL) {
        //goes up one level
        getParents(thePerson->parent1, currentDegree + 1, degree, count);
        getParents(thePerson->parent2, currentDegree + 1, degree, count);
    }
}

/**
 * @brief the function sets an array of pointers to person
 * by adding the marked people
 *
 * @param list the empty array of pointers to person
 * @param headPersons
 * @param pointerIndex an index to decide the current index for the array
 */
void makeList(Person **list, Node *headPersons, int *pointerIndex) {
    Node *temp = headPersons;
    while (temp != NULL) {
        Person *currentAncestor = (Person *) temp->data;
        //hasn't been added to the list
        if (currentAncestor->checked == TRUE) {
            //adds him to the list and updates the index
            list[(*pointerIndex)++] = currentAncestor;
            currentAncestor->checked ^= SWITCH_FLAG;
            //married
            if (currentAncestor->married != NULL && currentAncestor->married->checked == TRUE) {
                list[(*pointerIndex)++] = currentAncestor->married;
                currentAncestor->married->checked ^= SWITCH_FLAG;
            }
        }
        //has children
        if (currentAncestor->firstChild->next != NULL) {
            makeList(list, currentAncestor->firstChild->next, pointerIndex);
        }
        temp = temp->next;
    }
}

/**
 * @brief the function sorts an array of pointers to
 * Person in an alphabetic order
 *
 * @param list the array of pointers to person
 * @param length the length of the list
 */
void sortList(Person **list, int length) {
    //bubble sort algorithm
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            //if the name is bigger it swaps the two
            if (strcmp(list[j]->name, list[j + 1]->name) > STR_CMP_TRUE) {
                Person *temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief the function prints the array of pointers to
 * Person, names by order in the array
 * 
 * @param list the array of pointers to person
 * @param length the length of the list
 */
void printList(Person **list, int length) {
    printf("Cousins:\n");
    for (int i = 0; i < length; ++i) {
        printf("%s\n", list[i]->name);
    }
}

/**
 * @brief the function gets a name from the user and a degree
 * and prints the cousins of that person in all the degrees until that one
 * 
 * @param headPersons the head of the family tree
 */
void task7(Node *headPersons) {
    printf("Enter the name of the person:\n");
    //gets a name from the user
    char *name = getName();
    if (name == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    unsigned int degree;
    printf("Enter degree:\n");
    //gets degree from the user
    scanf("%u", &degree);
    cleanBuffer();
    Person *thePerson = getByName(name, headPersons);
    free(name);
    resetList(headPersons->next);
    //checks if the person exists
    if (thePerson == NULL) {
        printf("The person does not exist\n");
        return;
    }
    thePerson->checked ^= SWITCH_FLAG;
    int count = 1;
    int *pointerCount = &count;
    for (unsigned int i = 1; i <= degree; ++i) {
        getParents(thePerson, 0, i, pointerCount);
    }
    //allocates memory for the list
    Person **list = malloc(sizeof(Person *) * (*pointerCount));
    if (list == NULL) {
        theApocalypse(headPersons->next);
        exit(EXIT_VALUE);
    }
    int index = 0;
    int *pointerIndex = &index;
    //makes sorts and prints the list
    makeList(list, headPersons->next, pointerIndex);
    sortList(list, count);
    printList(list, count);
    //frees the list
    free(list);
}

/**
* @brief this function gets a task number and executes the task accordingly
 *the function identifies the task number with a switch loop and acts accordingly
 *
 * @param taskNumber The number of the task inserted by the user.
 *
*/
void executeTask(char taskNumber, Node *headPersons) {
    //executes all the task according to task number
    switch (taskNumber) {
        case ENDING_CHARACTER:
            theApocalypse(headPersons->next);
            break;
        case '1':
            task1(headPersons);
            break;
        case '2':
            task2(headPersons);
            break;
        case '3':
            task3(headPersons);
            break;
        case '4':
            task4(headPersons);
            break;
        case '5':
            printf("Enter number of years:\n");
            unsigned int years;
            scanf("%u", &years);
            cleanBuffer();
            //adds years to everyone
            addYears(years, headPersons->next);
            resetList(headPersons->next);
            break;
        case '6':
            //has only one
            if (*(long *) (headPersons->data) == TRUE) {
                printf("There is one person\n");
            } else {
                printf("There are %ld people\n", *(long *) (headPersons->data));
            }
            break;
        case '7':
            task7(headPersons);
            break;
        default:
            //edge cases
            printf("Invalid option\n");
    }
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
    temp->next->next = NULL;
}