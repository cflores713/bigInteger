/*
 * Carlos Flores 03/20/18
 * File: infiniteArithmetic.cpp
 * --------------------
 * This file implements members of a class for arbitrary-size integer arithmetic.
 * It is meant to help get around the maximum value limit for int.
 */


#include <iostream>
#include "Stack.h"
using namespace std;

int main() {
    // Declare an input file path to read the equations.
    string filePath = "/Users/Carlos/Documents/DS Programs/HW2v2/input2.txt";
    // Declare and initialize a linked list.
    LinkedList<string> import;
    // Read the file and store the data in the linked list.
    import.readFile(filePath);
    // Calculate the lines and print to the screen.
    import.evaluate();

    return 0;
}
