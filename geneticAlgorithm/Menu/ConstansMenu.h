#pragma once

// error codes for user inputs 
#define WITHOUT_ERROR 0
#define WRONG_VALUE 1
#define ALLOCATION_ERROR 2
#define WRONG_TYPE 3

#define UNKNOWN_ERROR "Unknown error."
#define WRONG_VALUE_MSG "Wrong value. Try again"
#define ALLOCATION_ERROR_MSG "Allocation error."
#define WRONG_TYPE_MSG "Invalid input. Try again."
#define WRONG_COMMAND "Wrong command. Try again."
#define NO_COMMAND_NAME "command name is missing."
#define MENU_COMMAND "This is CMenu command. \"Help\" is available only for CMenuCommand commands."
#define COMMAND_NOT_EXIST "This command does not exist."
#define ERROR_LOAD_DATA "Error reading data. Problem and AG cannot be initialised."

#define EMPTY_COMMAND "Empty command."
#define DEFAULT_COMMAND "Default command."
#define MENUITEM_ALREADY_EXIST "This menu item already exists."
#define NONEXISTENT_MENUITEM "Such menuitem does not exist."

// messages for reading menu from string / string from file
#define READ_FROM_FILE_SUCCESS "Menu was successfully read from file."
#define ERROR_STRING_MSG "Error occured in string at position: "
#define CHARS_EXPECTED_INFO ". Expected chars: "

// what chars expected or missing in menu string reading format
#define	LEFT_BRACKET "("
#define RIGHT_BRACKET ")"
#define COMMA ","
#define SEMICOLON ";"
#define APOSTROPHE "'"
#define COMMA_OR_RIGHT_BRACKET ",)"
#define COMMA_OR_SEMICOLON ",;"
#define LEFT_SQUARE_BRACKET_OR_SEMICOLON "([;"
#define NUMERIC_CHARS "numeric chars"
#define LEFT_SQUARE_OR_RIGHT_BRACKET "([)"
#define NUMERIC_CHAR_OVER_ZERO "numeric chars >  0"
#define CHILD_NUMBER "number of child"
#define CORRECT_NUM_OF_CHILD "Correct number of child."

// data of menu and commands
#define MAIN_MENU "Choose knapsack problem"
#define BOOL_KNAPSACK "Bool knapsack problem"
#define INTEGER_KNAPSACK "Integer knapsack problem"
#define DOUBLE_KNAPSACK "Double knapsack problem"

#define MAIN_CMD "main"
#define BOOL_KNAPSACK_CMD "bool"
#define INTEGER_KNAPSACK_CMD "int"
#define DOUBLE_KNAPSACK_CMD "double"

#define DEFAULT_RUN "Run with default data."
#define	DEFAULT_RUN_CMD "default"
#define DEFAULT_RUN_BOOL_HELP_MSG "Run bool problem - each item can be taken only once."
#define DEFAULT_RUN_INT_HELP_MSG "Run int problem - each item can be taken several times."
#define DEFAULT_RUN_DOUBLE_HELP_MSG "Run double problem - each item can be taken in such amount as we wish."
#define ADD_ITEM "Add item to default problem."
#define ADD_ITEM_CMD "add"
#define ADD_ITEM_HELP_MSG "Adds one item data to already existing default vector of items."
#define PARAM_RUN "Run with input parameters."
#define PARAM_RUN_CMD "param"
#define PARAM_RUN_HELP_MSG "Runs algorithm with user input parameters."

#define ASK_KNAPSACK_DATA " -- Knapsack problem data: "
#define ASK_WEIGHT_ITEM "Enter weight of item: "
#define ASK_VALUE_ITEM "Enter value of item: "
#define ASK_ITEM_AMOUNT "Enter item amount: "
#define ASK_MAX_WEIGHT "Enter max weight: "
#define ASK_AG_DATA " -- Genetic algorithm data: "
#define ASK_POP_SIZE "Enter population size: "
#define ASK_CROSS_PROB "Enter crossover probability: "
#define ASK_MUT_PROB "Enter mutation probability: "
#define ASK_TIME_ITER "Enter time in secunds: "
