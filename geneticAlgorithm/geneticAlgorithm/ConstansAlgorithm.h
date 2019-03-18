#pragma once
#define ERROR_POPULATION_SIZE "Population size cannot be negative or less than 0."
#define ERROR_PARAMETERS_FOR_MUT_CROSS  "Paramters for crossover or mutation cannot be negative or greater than 1."
#define ERROR_ITER_TIME "Time number cannot be negative."
#define ERROR_NULLPTR_PROBLEM "Problem defined is missing."
#define ERROR_ITEMS_AMOUNT "Item amount cannot be negative or less than 1."
#define ERROR_MAX_WEIGHT "Max weight cannot be negative or equal to 0."
#define ERROR_WRONG_DATA_FOR_WEIGHTS_OR_VALUES "Wrong input data for weights or values."
#define ERROR_NEGATIVE_WEIGHTS_OR_VALUES "Weights or values for items cannot be negative."
#define ERROR_ITEM_DATA "Wrong item data."

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define	MAX_INTEGER_ITEM_TO_TAKE 3
#define	MAX_DOUBLE_ITEM_TO_TAKE 3

#define DEFAULT_VALUES { 5, 1, 4, 3, 6, 3, 4, 2 }
#define DEFAULT_WEIGHTS { 1, 1, 3, 2, 1, 1, 3, 2 }
#define DEFAULT_ITEM_AMOUNT 8
#define DEFAULT_MAX_WEIGHT 10
#define DEFAULT_POP_SIZE 20
#define DEFAULT_TIME_ITER 5
#define DEFAULT_MUT_PROB 0.1
#define DEFAULT_CROSS_PROB 0.6

#define BEST_SOLUTION "best solution: "
#define VALUE "Value: "