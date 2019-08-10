/*
 * File: infiniteArithmetic.cpp
 * --------------------
 * This file implements members of a class for arbitrary-size integer arithmetic.
 * It is meant to help get around the maximum value limit for int.
 */

#ifndef HW2V2_STACK_H
#define HW2V2_STACK_H

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/// Function Prototypes:
// Tokenize Methods
string addSpaces(const string& line);
string tokenize(const string& in);
string infixToPostfix(string infix);
string calculate(string n1, string n2, const string& operand);
string readEquation(const string& line);
void readNode(const string& line);

// Arithmetic Methods
string add(string& n1, string& n2);
string addHelper(const string& n1, const string& n2);
string sub(string& n1, string& n2);
string subHelper(const string& n1, const string& n2);
string multiply(string& n1, string& n2);
string multiplyHelper(const string& n1, const string& n2);
string divide(string& n1, string& n2);
string divideHelper(const string& n1, const string& n2, string carryover = "0");

// Utility Functions
void insertZeros(string& n1, string& n2);
string cleanAnswer(const string& n1);
void negateNum(string& n1);
bool isNegative(const string& n1);
bool isOperator(char n);
bool isGreater(const string& n1, const string& n2);
bool priority(char leftOperator, char rightOperator);
bool isBalanced(const string& in);

/// ============================================================================================
///                                                             Beginning of Node Class Interface
/// ============================================================================================

template <class T>
class Node {
public:
    T aData;
    Node<T> *next;
    Node<T> *prev;

    Node(T x);
    Node(const Node<T>& object);

    bool operator== (Node<T>& ob1)const;
};

/// ============================================================================================
/// End of Node Class Interface
/// ============================================================================================
///                                                 Circular Doubly Linked List Class Interface
/// ============================================================================================

template <class T>
class LinkedList {
public:
    Node<T>* head;
    Node<T>* tail;
    int counter;                                // Keeps track of the number of nodes in the list.

    LinkedList();                               // Default Constructor
    LinkedList(const LinkedList<T>& object);    // Deep Copy Constructor
    ~LinkedList();                              // Destructor

    void insert(T aValue);                      // Will invoke the appropriate node insertion method
    bool pushForward(T newEntry);               // Inserts a new node at the front.
    void placeInside(Node<T>* here, T aValue);  // Inserts a new node in the middle.
    bool pushBack(Node<T> newEntry);            // Inserts a new node at the back.

    bool isEmpty() const;                       // Checks if the list is empty

    bool contains(const T& anEntry) const;      // Checks if a node exists in the list.
    Node<T>* search(const T& aValue) const;     // Returns a pointer to the node before insertion.
    void checkLoop() const;                     // Prints backwards to check prev node pointers.
    void print() const;                         // Prints the list from head to tail.

    void remove(Node<T>* discard);              // Deletes a node from the linked list by pointer.
    void remove(T value);                       // Deletes a node from the linked list by value.
    void destroy();                             // Deletes the contents of the entire linked list.

    void readFile(string path);
    void evaluate() const;

};

/// ============================================================================================
/// End of Circular Doubly Linked List Class Interface
/// ============================================================================================
///                                                                 Begin Stack Class Interface
/// ============================================================================================
template <class ValueType>
class Stack {           /// Data Structure to store information dynamically in a LIFO collection.
public:
    Node<ValueType>* top;
    int counter;

    Stack();
    void copyStack(const Stack<ValueType>& otherStack);
    void print();

    ~Stack();
    void initialize();                                  // Removes all elements from this stack.
    void setTo(string in);
    void charToInt(const string& line);
    ValueType pop();                                    // Removes the top element from this stack and returns it.
    ValueType& getTop();

    bool isEmpty() const;                               // Returns true if this stack contains no elements.
    ValueType peek() const;                             // Returns the top element from the stack w/o removing it.
    void push(const ValueType &value);                  // Pushes the specified value onto the top of this stack.
    int size() const;                                   // Returns the number of values in this stack.
};

/// ============================================================================================
/// End of Stack Interface
/// ============================================================================================
///                                                           Begin Node Class Implementation:
/// ============================================================================================

template <class T>
Node<T>::Node(T x){
    aData = x;
    next = nullptr;
    prev = nullptr;
}

// Creates a node that has the same data but it does not return the same pointers
// This is to ensure a full deep copy of the node and linked list collection classes.
// The linked list copy constructor will initialize the node pointers to their respective copies.
template <class T>
Node<T>::Node(const Node<T>& object){
    this->aData = object.aData;
    this->next = nullptr;
    this->prev = nullptr;
}

//Overloaded Boolean Equality Operator
template <class T>
bool Node<T>::operator== (Node<T>& ob1)const{
    return (this->aData == ob1.aData);
}

/// ============================================================================================
/// End of Node Interface
/// ============================================================================================
///                                                     Beginning of Linked List Implementation
/// ============================================================================================

template <class T>
LinkedList<T>::LinkedList() {                          /// Default Linked List Constructor
    head = nullptr;
    tail = nullptr;
    counter = 0;
}

template <class T>                                          /// Deep Copy Constructor
LinkedList<T>::LinkedList(const LinkedList<T>& object){

    head = nullptr;
    tail = nullptr;
    counter = 0;

    if (!object.isEmpty()) {
        Node<T>* cu = object.head;

        int size = object.counter;

        for (int i = 0 ; i < size ; i++) {
            insert(cu->aData);
            cu = cu->next;
        }
    }
}

template <class T>
bool LinkedList<T>::pushForward(T newEntry) {           /// Adds a new node to the front.
    Node<T>* cu = new Node<T>(newEntry);                // Declare a new pointer.

    if (isEmpty()) {	                                // If list empty, newNode is both the head and tail.
        cu->next = cu;
        cu->prev = cu;

        head = cu;                                      // Set the Head and Tail to the newNode.
        tail = cu;
    } else {                                            // If the list is not empty then insert after the tail.
        cu->prev = tail;
        cu->next = head;
        tail->next = cu;
        head->prev = cu;
        head = cu;
    }

    counter++;
    return true;
}

template <class T>
void LinkedList<T>::placeInside(Node<T>* here, T aValue) {  /// Insert a node in the middle of the list.
    Node<T>* before = here->prev;
    Node<T>* cu = new Node<T>(aValue);

    if (!isEmpty()) {
        if(head != tail)
        {
            before->next = cu;
            here->prev = cu;
            cu->next = here;
            cu->prev = before;
            counter++;
        } else {
            if (head->aData >= aValue){
                pushForward(aValue);
            } else{
                pushBack(aValue);
            }
        }
    }
}

template <class T>
bool LinkedList<T>::pushBack(Node<T> newEntry) {                 /// Add a node to the end of the list
    Node<T>* cu = new Node<T>(newEntry);         // Declare a new pointer.

    if (isEmpty()) {	                         // If list empty, newNode is both the head and tail.
        cu->next = cu;
        cu->prev = cu;

        head = cu;                               // Set the Head and Tail to the newNode.
        tail = cu;
    } else {                                     // If the list is not empty then insert after the tail.
        cu->prev = tail;
        tail->next = cu;

        tail = cu;
        cu->next = head;
        head->prev = cu;
    }

    counter++;
    return true;
}

template <class T>
void LinkedList<T>::insert(T aValue){                      /// Unified Insert Mode Method invokes the proper function.

    Node<T>* here = search(aValue);

    if ( isEmpty() ) {                                  // If the list is empty then add a node to the head.
        pushForward(aValue);
    } else if( here == head ){
        if (head->aData < aValue){
            placeInside(here, aValue);
        } else{
            pushForward(aValue);
        }
    } else if (here == tail) {
        if (aValue < tail->aData){
            placeInside(here, aValue);
        } else {
            pushBack(aValue);
        }
    } else{
        placeInside(here, aValue);
    }
}

template <class T>
bool LinkedList<T>::isEmpty() const {                                 /// Checks if the list is empty
    return head == nullptr;
}

template <class T>
bool LinkedList<T>::contains(const T& anEntry) const{                  /// Checks if the list contains the given entry.
    bool  found = false;                                // Initialize a variable as false (argument not found).
    Node<T>* cu = head;                                 // Declare a pointer to traverse the linked list.
    if (!isEmpty()) {
        if (tail->aData == anEntry) {
            found = true;
        }
        int i = 0;                                      // While there remains nodes to read:
        while ( (i < counter) && (!found) ) {           // If you find the item:
            if (anEntry == cu->aData) {                 // Negate the boolean value.
                found = true;
            } else {                                    // Otherwise, continue traversing the list.
                cu = cu->next;
                i++;
            }
        }
    }
    return found;
}

template <class T>
Node<T>* LinkedList<T>::search(const T& aValue) const {                          /// Returns a pointer to the proper location.
    bool  found = false;                                        // Initialize a variable as false (argument not found).
    Node<T>* cu = head;                                         // Declare a pointer to traverse the linked list.
    if (!isEmpty()) {                                           // If the list is not empty:
        if (tail->aData <= aValue) {
            cu = tail;
            found = true;
        } else if( head->aData >= aValue) {
            found = true;
        }
        int i = 0;
        while ( (i < counter) && (!found) ) {                 // While there remains nodes to read:
            if (aValue <= cu->aData) {                        // If you find the item:
                found = true;                                 // Negate the boolean value.
            } else {                                          // Otherwise, continue traversing the list.
                cu = cu->next;
                i++;
            }
        }
    }
    return cu;
}

template <class T>
void LinkedList<T>::print() const {                                           /// Displays the contents of the linked list.
    if(counter == 0){
        cout << "Print Error: Can not print the contents of an empty list!"<<endl;
    } else {
        Node<T>* cu = head;
        bool theEnd = false;

        while (!theEnd) {
            if (cu != nullptr) {
                cout << cu->aData << endl;
            }

            if (cu == tail) {
                theEnd = true;
            }
            cu = cu->next;
        }
        cout << endl;
    }
}

template <class T>
void LinkedList<T>::checkLoop() const {                                       /// Displays the contents of the list backwards.
    Node<T>* cu = tail;                                          // Use this to check if the prev pointers work.
    bool theEnd = false;
    int num = 0;

    while (!theEnd) {
        if (cu != nullptr)
            num++;
        cout << "Node " << num <<": " <<cu->aData << endl;

        if (cu == head)
            theEnd = true;

        cu = cu->prev;
    }
}

template <class T>
void LinkedList<T>::remove(T value) {                            /// Deletes a node regardless of location

    Node<T>* entryToRemove = search(value);
    if (entryToRemove->aData == value){
        remove(entryToRemove);
    } else {
        cout << "Error Message from: LinkedList<T>::remove(T value):" << endl;
        cout << "The list does not contain " << value;
        cout << ".\nNo changes to the list were made.\n" << endl;
    }

}

template <class T>
void LinkedList<T>::evaluate() const {                                           /// Displays the contents of the linked list.
    if(counter == 0){
        cout << "Calculate Error: The list is empty."<<endl;
    } else {
        Node<T>* cu = head;
        bool theEnd = false;

        while (!theEnd) {
            if (cu != nullptr) {
                if (isBalanced(cu->aData)){
                    readNode(cu->aData);
                }
            }

            if (cu == tail) {
                theEnd = true;
            }
            cu = cu->next;
        }
        cout << endl;
    }
}

template <class T>
void LinkedList<T>::remove(Node<T>* discard) {                            /// Deletes a node regardless of location
    bool  found = false;

    if (!isEmpty()) {
        if (head == tail)
        {                                                        // If the list has one node:
            head = nullptr;
            tail = nullptr;
            found = true;
        }
        else if (head == discard)
        {                                                        // Delete Head:
            tail->next = head->next;
            head->next->prev = tail;
            head = head->next;
            found = true;
        }
        else if(tail == discard)
        {                                                         // Delete Tail:
            head->prev = tail->prev;
            tail->prev->next = head;
            tail = tail->prev;
            found = true;
        }
        else
        {                                                         // Delete from the middle:
            Node<T>* before = discard->prev;
            before->next = discard->next;
            discard->next->prev = before;
            found = true;
        }
    } else{                                                     // Notify the user that no node was deleted.
        cout << "Delete Node Error: Can not delete from an empty list."<<endl;
        return;
    }

    if (found) {                                                // If you removed a player:
        counter--;                                              // Decrement the counter,
        delete discard;                                         // & free the memory.
    }
}

template <class T>
void LinkedList<T>::destroy() {                                         /// Delete the contents of the list and reset it.
    if (!isEmpty()) {                                           // While there are nodes in the list
        while (tail != head) {                                  // Declare a pointer to free the memory in the node.
            Node<T> *cu = tail;
            tail = tail->prev;
            delete cu;
        }
        Node<T> *cu = tail;
        tail = nullptr;                                         // Reset the pointers to nullptr.
        head = nullptr;
        counter = 0;                                            // Reset the counter to zero.
        delete cu;
    }
}


template <class T>
LinkedList<T>::~LinkedList() {                                               ///Destructor
    destroy();
}

template <class T>
void LinkedList<T>::readFile(string path) {
    string line;
    ifstream input;
    input.open(path);

    while (!input.eof()) {                              // While there remains text to read from the file
        getline(input, line);                           // Check if the line is a balanced equation
        if (isBalanced(line)) {                         // Also, check if the equation has no double negatives.
            Node<T>* current = new Node<T>((line));     // If it is valid then add a node with the line to the list.

            if (head == nullptr) {                      // If th list is empty then place the first node.
                head=current;
                tail=current;
                counter++;
            } else {                                    // Otherwise continue to append to the list form the tail.
                tail->next = current;
                current->prev = tail;
                tail = current;
                counter++;
            }
        }
    }
    input.close();                                      // Close the file after the lines have been read.
}

/// ============================================================================================
/// End Group Doubly Linked List Class Implementation
/// ============================================================================================
///                                                            Begin Stack Class Implementation
/// ============================================================================================

template <class V>
Stack<V>::Stack(){
    top = nullptr;
    counter = 0;
}

template <class V>
Stack<V>::~Stack(){
    initialize();
}

template <class V>
V Stack<V>::pop() {
    Node <V> *cu;
    V temp;
    if (!isEmpty()) {
        cu = top;
        temp = cu->aData;
        top = top->next;
        delete cu;
        counter--;
        return temp;
    } else {
        cout<< "Pop Error: Can not remove a node from an empty stack!" <<endl;
    }
}

template <class V>
bool Stack<V>::isEmpty()const {return top == nullptr;}

template <class V>
V Stack<V>::peek()const { return  top->aData;}

template <class V>
void Stack<V>::push(const V &value){
    Node <V> *newNode;
    newNode = new Node<V>(value);
    newNode->next = top;
    top = newNode;
    counter++;
}

template <class V>
V& Stack<V>::getTop() {
    if (isEmpty()) {
        cout << "Top Error: Attempting to read top of an empty stack" << endl;
    }
    return top->aData;
}

template <class V>
void Stack<V>::copyStack(const Stack<V>& otherStack){
    Node <V> *newNode, *cu, *last;
    if (!isEmpty()){
        initialize();
    }
    if (!otherStack.isEmpty()){
        top = nullptr;
    } else {
        cu = otherStack.top;                    // Set Cu to the top node
        top = new Node<V>(top->aData);          // Copy from other to this.
        top->next = nullptr;
        last = top;
        cu = cu->next;

        while (cu != nullptr){
            newNode = new Node<V>(cu->aData);
            newNode->next = nullptr;
            last->next = newNode;
            cu = cu->next;
            cu->next = nullptr;
        }
    }
}

template <class V>
void Stack<V>::initialize(){
    top = nullptr;
    counter = 0;
}

template <class V>
int Stack<V>::size()const { return counter;}

template <class V>
void Stack<V>::setTo(string in) {
    int size = in.length();
    for (int i=0; i<size;i++){
        push(in[i]);
    }
}

template <class V>
void Stack<V>::charToInt(const string& line){
    int size = line.length();
    int j;
    for (int i = 0; i < size ; i++){
        j = line[i]-'0';
        push(j);
    }
}


template <class V>
void Stack<V>::print(){
    if (!isEmpty()){
        Node<V> *cu = top;
        while (cu != nullptr){
            cout<< cu->aData<< " ";
            cu= cu->next;
        }
        cout<<endl;
    }
}

/// ============================================================================================
/// End Stack Class Implementation
/// ============================================================================================
///                                                           Begin Tokenize Method Definitions
/// ============================================================================================




/*
     * Method: addSpaces
     * ------------------------------------
     * Accepts a string and rewrites it with whitespace in between tokens.
     * Postcondition: The line is ready to be read and tokenized.
*/
string addSpaces(const string& line){
    // Initialize a boolean variable to avoid spacing numerical digits that are meant to be together.
    bool prevChar = false;
    string res = "";
    int size = line.length();
    for (int i = 0; i < size ; i++) {
        // If the current char is not a digit:
        if (!isdigit(line[i])) {
            // If the previous char was a number then allow for double spaces.
            if (prevChar){
                res += " ";
                res += line[i];
                res += " ";
            } else{
                // Otherwise only space after the current char.
                res += line[i];
                res += " ";
            }
            // Switch the boolean to note that the current char is not a digit.
            prevChar = false;
        } else {
            res += line[i];
            // Set the boolean to allow for no spacing between digits.
            prevChar = true;
        }
    }
    // Return the result string.
    return res;
}


/*
     * Method: tokenize
     * ------------------------------------
     * Precondition: The string should have whitespace in between the tokens to be processed.
     * Precondition: The whitespace after '-' signs that represent negative integers will be removed.
     * Precondition: The '+' signs that represent positive integers will be removed from the string.
*/
string tokenize(const string& in){
    string res = "";
    // Put whitespace in the line in between tokens
    string line = addSpaces(in);
    string token;
    // Declare a string stream to parse the newly tokenized string.
    istringstream iss(line);
    // Initialize the previous token variable as '('
    // Some equations do not start with '(' and this will resolve those input cases
    string prevToken = "(";
    // Initialize a boolean variable to control when a digit is negated.
    // When you encounter a '(' you may need to negate the next digit.
    bool negateNext = false;
    // Parse the line by whitespace delimiters.
    while (getline(iss, token, ' ')){
        // If the prevToken was an open parenthesis and the current token is a minus sign then negate the next number.
        if ( (prevToken == "(") && (token == "-") ) {
            negateNext = true;
        } else if ( (prevToken == "(") && (token == "+") ) {
            // Trivial token; skip this.
            // All numbers are considered positive by default so this will remove irrelevant plus signs.
        } else {
            // If the conditions for negating the next number were met then hyphenate the current token.
            if (negateNext) {
                negateNum(token);
                // Switch the boolean to false now that the number has been negated.
                negateNext = false;
            }
            // Append the curent token to the string.
            res = res + token + " ";
            // Overwrite the prevToken with the current token now that we will proceed to the next token in the stream.
            prevToken = token;
        }
    }
    // Return the result string.
    return res;
}

/*
     * Method: infixToPostfix
     * ------------------------------------
     * Precondition: The string is in infix order and tokenized.
     * Postcondition: The string will be in a postfixed order.
*/
string  infixToPostfix(string infix) {
    string res = "";
    Stack<string> stringStack;
    stringStack.push("(");

    string token, rightOperand;
    istringstream iss(infix);
    while (getline(iss, token, ' ')) {
        const string temp = token;

        // If the first char in the token is a digit or if the token is a minus sign and the next char is a digit:
        if ( (isdigit(temp[0])) || ((temp[0] == '-') && (isdigit(token[1])) )) {
            // Concatenate the token to the result string.
            res += " " + token;
        } else if (temp == "(") {
            // If you encounter an opne parenthesis then push it to the operand stack no matter what.
            stringStack.push(temp);
        } else if (isOperator(temp[0])) {
            rightOperand = temp;
            // While the stack is not empty, the token is a valid operand, and has less priority than the stack::top:
            while (!stringStack.isEmpty() && isOperator(stringStack.getTop()[0]) && priority(stringStack.getTop()[0], rightOperand[0])) {
                // Pop the top operand and concatenate it to the result string.
                res += " " + stringStack.pop();
            }
            res += " ";
            // Push the current operand to the stack.
            stringStack.push(rightOperand);
        } else if (temp == ""){
            // if the token is empty then do nothing; skip this token.
        } else if (temp == ")") {
            // If the token is a close parenthesis:
            // Resolve the operands in the stack until you find the open paren.
            while (!stringStack.isEmpty() && "(" != stringStack.getTop()) {
                res += " " + stringStack.pop();
            }
            if (stringStack.isEmpty()) {
                cout << "infixToPostfix Error: Missing open parenthesis." << endl;
            }
            // Discard the open parenthesis that we added in the beginning of the function.
            stringStack.pop();
            res += " ";
        }
        else {
            cout << "infixToPostfix Error: Unrecognized token." << endl;
        }
    }

    // Now that the line has no more tokens you can clear the stack of the remaining operands.
    while (!stringStack.isEmpty() && "(" != stringStack.getTop()) {
        res += " " + stringStack.pop();
    }
    if (stringStack.isEmpty()) {
        cout << "Postfix error: missing left parenthesis" << endl;
    }

    stringStack.pop();

    if (!stringStack.isEmpty()) {
        cout << "Postfix error: no right parenthesis" << endl;
    }

    return res;
}


/*
     * Method: calculate
     * ------------------------------------
     * Precondition: The negative numbers should have the '-' attached already.
     * Precondition: The arguments should be in a postfixed order already.
     * Postcondition: Invokes the appropriate arithmetic function according to the operand given.
*/
string calculate(string n1, string n2, const string& operand){
    if (operand == "+"){
        return add(n1, n2);}
    else if (operand == "-"){
        return sub(n1, n2);}
    else if (operand == "*"){
        return multiply(n1, n2);}
    else if (operand == "/"){
        return divide(n1, n2);}
    else{
        cout << "Equal Error: Operand not recognized." << endl;
        cout << n1 << " " << n2 << " " <<operand;
        return 0; }
}

/*
     * Method: readEquation
     * ------------------------------------
     * Calculates the postfixed linear equation.
     * Precondition: The arguments should be in a postfixed order already.
     * Postcondition: Returns the calculated answer as a large string.
*/
string readEquation(const string& line){
    Stack<string> calculateLine;
    string token, num1, num2, op, result;
    istringstream iss(line);

    while (getline(iss, token, ' ')) {
        // If the token is a number then push it to the stack.
        if ( (isdigit(token[0])) || ((token[0] == '-') && (isdigit(token[1])) )){
            calculateLine.push(token);
        } else if (token == ""){
            // If the token is empty then do nothing.
        } else {
            // If the token is an operand then:
            op = token;
            // Pop two numbers to calculate:
            num2 = calculateLine.pop();
            num1 = calculateLine.pop();
            // Perform the arithmetic operation and push the result to the stack.
            result = calculate(num1, num2, op);
            calculateLine.push(result);
        }
    }

    // Return the result from the stack.
    return calculateLine.pop();

}

/*
     * Method: readNode
     * ------------------------------------
     * Parses the line in order from raw data, spaced, tokenized, postfixed, and calculated.
     * This ensures that all preconditions are met and performed in one unified method invocation.
*/
void readNode(const string& line){
    string temp;
    if (isBalanced(line)){
        //cout << "\tInput: " << line <<endl;
        temp = tokenize(line);
        //cout << "Tokenized: " << temp <<endl;
        temp = infixToPostfix(temp);
        //cout << "Postfixed: " << temp <<endl;
        temp = readEquation(temp);
        cout << line << "=" << temp << endl;
    }
}

/// ============================================================================================
/// End Token Method Definitions
/// ============================================================================================
///                                                        Begin Arithmetic Function Definitions
/// ============================================================================================


/*
     * Method: add
     * Usage: add(number1, string number2)
     * ------------------------------------
     * Precondition: Negative numbers must have the '-' char attached at the front of the string already.
     * Postcondition: Prepares the string arguments by resolving any pertinent preconditions.
     * Postcondition: Invokes the appropriate arithmetic helper function.
*/
string add(string& n1, string& n2) {
    string result;
    //If both numbers are positive then add the two digits:
    if ( (!isNegative(n1)) && (!isNegative(n2)) ) {
        insertZeros(n1, n2);
        // Pad the strings with "0" until both arguments have the same string length.
        result = addHelper(n1, n2);
        // Truncate the superfluous zeros form the string.
        result = cleanAnswer(result);
        return result;
    } else if ( (!isNegative(n1)) && (isNegative(n2)) ) {
        // If the second argument is a negative number then negate that number and subtract:
        negateNum(n2);
        insertZeros(n1, n2);
        if (n2 > n1) {
            //If the second argument is larger than the first integer then negate the difference of the two digits.
            result = subHelper(n2, n1);
            result = cleanAnswer(result);
            negateNum(result);
        } else {
            // Otherwise, if the positive integer is larger than the negative integer, then:
            // Return the result as the positive difference of the two integers.
            result = subHelper(n1, n2);
            result = cleanAnswer(result);
        }
        return result;
    } else if ( (isNegative(n1)) && (!isNegative(n2)) ) {
        // If the first argument is negative then negate the integer and subtract the two digits.
        negateNum(n1);
        insertZeros(n1, n2);
        if (n1 > n2) {
            // If the negative integer is greater than the positive integer then subtract the two digits.
            // Return the negation of the answer.
            result = subHelper(n1, n2);
            result = cleanAnswer(result);
            negateNum(result);
        } else {
            // If the positive integer is greater than the absolute value of the negative integer:
            // Subtract the two digits:
            result = subHelper(n2, n1);
            result = cleanAnswer(result);
        }
        return result;
    } else if ( (isNegative(n1)) && (isNegative(n2)) ) {
        //If both digits are negative then negate both integers.
        negateNum(n1);
        negateNum(n2);
        insertZeros(n1, n2);
        // Add the two digits and negate the sum.
        string result = addHelper(n1, n2);
        result = cleanAnswer(result);
        negateNum(result);
        return result;
    } else {
        // If no such case exists then inform the user that the method failed.
        cout << "Addition Error: No equivalent statement found." << endl;
    }
}

/*
     * Method: addHelper
     * Usage: addHelper(number1, string number2)
     * ------------------------------------
     * Returns the sum of two large integers.
     * Precondition: The string arguments have the same length.
     * Precondition: The string arguments are positive.
     * Postcondition: If the sum is intended to be a negative number then the add() method will negate the result.
*/
string addHelper(const string& n1, const string& n2){
    // Concatenate a "0" at the front of the string to catch any overflowed integers from the carry.
    string n3 = "0"+ n1;
    string n4 = "0"+ n2;
    // Since both arguments are the same length then we only need to track the size of one string.
    int len1 = n3.length();
    // Initialize your addition variables:
    int carry = 0;      // Stores the values of the sum larger than 9 and adds it to the next digit.
    int num1;           // Placeholder for the current value of the first argument.
    int num2;           // Placeholder for the current value of the second argument.
    int answer;         // Placeholder to concatenate the summand of the current digit to the result string.
    string result= "";  // This is the string to be returned after the addition is complete.

    //For every char in the string to be added:
    for (int i = len1-1 ; i >= 0 ; i--) {
        // Convert the char to int by their ASCII value.
        // Subtract by '0' since the chars '0' through '9' are in numerical order starting from '0.'
        num1 = n3[i]-'0';
        num2 = n4[i]-'0';
        // The current answer is the summation of the char from each argument and the carry variable.
        answer = carry + num1 + num2;
        // The carry will store the value of the sum larger than 10.
        carry = answer/10;
        // The answer will store modulo 10 and concatenate it to the result string.
        answer %= 10;
        // Convert answer to a string and concatenate it to the front of the result.
        result = to_string(answer) + result;
    }
    // Remove any irrelevant char from the string.
    result = cleanAnswer(result);
    // Return the summation.
    return result;
}

/*
     * Method: sub
     * Usage: sub(number1, string number2)
     * ------------------------------------
     * Precondition: The arguments that are negative integers must have the minus sign attached already.
     * Postcondition: Prepares the string arguments by resolving any pertinent preconditions and invokes the appropriate
     * arithmetic helper function.
*/
string sub(string& n1, string& n2){
    if ( (!isNegative(n1)) && (!isNegative(n2)) ) {
        // If both arguments are positive integers:
        insertZeros(n1, n2);
        //If the second argument is larger than the first argument:
        if (n2 > n1){
            // Subtract the numbers in reverse (number2 - number1) and negate the difference.
            string result = subHelper(n2, n1);
            result = cleanAnswer(result);
            negateNum(result);
            return result;
        } else {
            // Otherwise, return the difference of the two integers.
            string result = subHelper(n1, n2);
            result = cleanAnswer(result);
            return result;
        }
    } else if ( (isNegative(n1)) && (!isNegative(n2)) ) {
        // If the first argument is negative then negate the integer to return a positive number.
        negateNum(n1);
        insertZeros(n1, n2);
        // Add the two numbers.
        string result = addHelper(n1, n2);
        result = cleanAnswer(result);
        // Return the negation of the sum.
        negateNum(result);
        return result;
    } else if ( (!isNegative(n1)) && (isNegative(n2)) ) {
        // If the second argument is negative then negate the integer to return a positive number.
        negateNum(n2);
        insertZeros(n1, n2);
        string result = addHelper(n1, n2);
        // Return the summation of the two arguments.
        result = cleanAnswer(result);
        return result;
    } else if ( (isNegative(n1)) && (isNegative(n2)) ) {
        // If both strings are negative integers then negate both numbers.
        negateNum(n1);
        negateNum(n2);
        insertZeros(n1, n2);
        if (n1 > n2){
            // If the first argument is greater than the second number:
            // Find the difference of the two numbers:
            string result = subHelper(n1, n2);
            result = cleanAnswer(result);
            // Negate the result and return the difference.
            negateNum(result);
            return result;
        } else {
            // Otherwise return the difference without negating the result.
            string result = subHelper(n2, n1);
            cleanAnswer(result);
            return result;
        }
    } else {
        // If no such case exists then inform the user of a faulty error in the logic.
        cout << "Subtraction Error: No equivalent statement found." << endl;
    }
}

/*
     * Method: subHelper
     * Usage: subHelper(number1, string number2)
     * ------------------------------------
     * Returns the difference of two large integers.
     * Precondition: The string arguments have the same length.
     * Important Precondition: The first argument MUST be greater than n2!
     *      ( sub() will invoke the appropriate method to ensure that the calculation is correct.)
     * Precondition: The string arguments are positive.
     * Postcondition: If the difference is intended to be a negative number then sub() will negate the result.
*/

string subHelper(const string& n1, const string& n2){
    if (n2 > n1) {
        cout << "subHelper Error: The second argument is greater than the first argument." << endl;
        return n2;
    }

    // Since both arguments are the same length then we only need to track the size of one string.
    int len1 = n1.length();
    // Initialize your addition variables:
    int carry = 0;      // Stores the values of the sum larger than 9 and adds it to the next digit.
    int num1;           // Placeholder for the current value of the first argument.
    int num2;           // Placeholder for the current value of the second argument.
    int answer;         // Placeholder to concatenate the summand of the current digit to the result string.
    string result= "";  // This is the string to be returned after the addition is complete.

    // For every char in the string:
    for (int i = len1-1 ; i >= 0 ; i--){
        // Convert the char to int by their ASCII value.
        // Subtract by '0' since the chars '0' through '9' are in numerical order starting from '0.'
        num1 = n1[i]-'0';
        num2 = n2[i]-'0';
        // Update num1 if you had to borrow a radix value for the previous digit-wise subtraction.
        num1 -= carry;

        //If the second number is greater than the first number then borrow 10 from the next radix
        if (num2 > num1){
            // Increment the carry by one since we added an entire radix value to num1.
            carry = 1;
            // Update num1 by the radix value.
            num1 += 10;
        } else {
            // Otherwise, clear the carry value to show that no values were borrowed.
            carry = 0;
        }

        // Subtract the two digits
        answer = num1 - num2;

        // Convert the answer to a string and concatenate it to the front of the result string.
        result = to_string(answer) + result;
    }
    // Return the result string once you are done.
    return result;
}

/*
     * Method: multiply
     * Usage: multiply(number1, string number2)
     * ------------------------------------
     * Precondition: The arguments that are negative integers must have the minus sign attached already.
     * Postcondition: Prepares the string arguments by resolving any pertinent preconditions and invokes the appropriate
     * arithmetic helper function.
*/
string multiply(string& n1, string& n2) {
    // Remove any irrelevant zeros from the front of the string.
    cleanAnswer(n1);
    cleanAnswer(n2);
    // If either argument is zero then return zero as the product.
    if ( (n1 == "0") || (n2 == "0") ) {
        return "0";
    } else if (n1 == "1"){
        // If the first argument is "1" then return the second argument.
        return n2;
    } else if (n2 == "1"){
        // If the second argument is "1" then return the first argument.
        return n1;
    } else {
        // If both numbers are positive then return the result.
        if ( (!isNegative(n1)) && (!isNegative(n2)) ) {
            string result = multiplyHelper(n1, n2);
            result = cleanAnswer(result);
            return result;
        } else if (isNegative(n1) && !isNegative(n2)) {
            // If the first number is negative then negate it:
            negateNum(n1);
            // Multiply the two numbers:
            string result = multiplyHelper(n1, n2);
            result = cleanAnswer(result);
            // Negate the product:
            negateNum(result);
            // Return the result.
            return result;
        } else if (!isNegative(n1) && isNegative(n2)) {
            // If the second argument is negative then negate it:
            negateNum(n2);
            // Find the product of the two numbers:
            string result = multiplyHelper(n1, n2);
            result = cleanAnswer(result);
            // Negate the final product.
            negateNum(result);
            // Return the result.
            return result;
        }if (isNegative(n1) && isNegative(n2)) {
            // If both numbers are negative then negate both numbers.
            negateNum(n1);
            negateNum(n2);
            // Find the product of the two numbers:
            string result = multiplyHelper(n1, n2);
            // Return the result.
            result = cleanAnswer(result);
            return result;
        }
    }
}

/*
     * Method: multiplyHelper
     * Usage: multiplyHelper(number1, string number2)
     * ------------------------------------
     * Returns the product of two large integers.
     * Precondition: The arguments are positive integers.
     * Postcondition: Multiply will negate the answer if the product is a result of a negative and positive number.
*/
string multiplyHelper(const string& n1, const string& n2) {
    // Pad a zero to the first argument to store any carryover values.
    string n3 = "0" + n1;
    string cumulativeSum = "0";
    string append = "", result = "";
    int answer, carry, num1, num2;
    // Multiply every digit in the second multiplicand by the first digit:
    for (int i = n2.length()-1 ; i >= 0 ; i--) {
        // Initialize the current answer placeholders to zero.
        answer = 0;
        carry = 0;
        // Convert the char to int.
        num2 = n2[i]-'0';

        for (int j = n3.length()-1 ; j >= 0 ; j--) {
            num1 = n3[j]-'0';
            // Add the carryover from the previous multiplication to the current product.
            answer = carry + (num1 * num2);
            // Store the values that are larger than the current radix in the carry variable.
            carry = answer/10;
            // The remainder will be stored in the result string.
            answer %= 10;
            result = to_string(answer) + result;
        }
        //Process the next radix by conatenating "0" at the end of the string for every iteration that has elapsed.
        result = result + append;
        append = append + "0";
        insertZeros(result, cumulativeSum);
        // Add the subproduct of the current radix to the subproducts of the previous digits.
        cumulativeSum = add(result, cumulativeSum);
        // Reset the result string to store the value of the next digit.
        result = "";
    }

    // Remove irrelevant digits from the sum of all subproducts and then return that string value.
    return cleanAnswer(cumulativeSum);
}

/*
     * Method: divide
     * Usage: divide(number1, string number2)
     * ------------------------------------
     * Precondition: The arguments that are negative integers must have the minus sign attached already.
     * Postcondition: Prepares the string arguments by resolving any pertinent preconditions and invokes the appropriate
     * arithmetic helper function.
*/
string divide(string& n1, string& n2) {
    // Inform the user of a div/0 error.
    if (n2 == "0") {
        cout << "You cannot divide by 0!" << endl;
        return n1;
    } else if (n2 == n1){
        // Return 1 if the numerator and denominator are the same.
        return "1";
    }

    // If both numbers are positive then divide the two strings as normal
    if ( (!isNegative(n1)) && (!isNegative(n2)) ) {
        insertZeros(n1, n2);
        string result = divideHelper(n1, n2);
        result = cleanAnswer(result);
        return result;
    } else if (isNegative(n1) && !isNegative(n2)) {
        // If the denominator is negative then negate the number before dividing.
        negateNum(n1);
        insertZeros(n1, n2);
        string result = divideHelper(n1, n2);
        // Negate the quotient before returning the value.
        result = cleanAnswer(result);
        negateNum(result);
        return result;
    } else if (!isNegative(n1) && isNegative(n2)) {
        // If the numerator is negative then negate the number before dividing.
        negateNum(n2);
        insertZeros(n1, n2);
        string result = divideHelper(n1, n2);
        // Negate the quotient before returning the value.
        result = cleanAnswer(result);
        negateNum(result);
        return result;
    }if (isNegative(n1) && isNegative(n2)) {
        // If both numbers are negative then negate both integers.
        negateNum(n1);
        negateNum(n2);
        insertZeros(n1, n2);
        string result = divideHelper(n1, n2);
        result = cleanAnswer(result);
        return result;
    }
}

/*
     * Method: divideHelper
     * Usage: divideHelper(number1, string number2)
     * ------------------------------------
     * Returns the quotient of two large integers by continuously subtracting the denominator.
     * Precondition: The arguments are positive integers with the same amount of digits.
     * Postcondition: Multiply will negate the answer if the product is a result of a negative and positive number.
*/
string divideHelper(const string& n1, const string& n2, string carryover){
    if (n2 > n1) {
        // If the denominator is greater than the numerator then return the carryover (it is set to 0 by default).
        return carryover;
    } else if (n2 == n1) {
        // If the current numerator equals the denominator then add 1 to the carryover and return the sum.
        return addHelper("1", carryover);
    } else {
        // Otherwise continue to decrement the numerator:
        string denominator = cleanAnswer(n2);
        string count = "1";
        // Append "0" to the denominator and count strings while the denominator is less than the numerator.
        if ( isGreater(n1, denominator) ) {
            while (n1.length() > denominator.length()) {
                denominator = denominator + "0";
                count = count + "0";
            }
        } else {
            // If the denominator is greater than the numerator:
            // Append zeros until the length is 1 less than the
            if (n1.length()-1 > denominator.length()) {
                while (n1.length()-1 > denominator.length()) {
                    denominator = denominator + "0";
                    count = count + "0";
                }
            }
        }

        string n3 = "", n5 = n1;
        insertZeros(n5, denominator);
        n3 = subHelper(n5, denominator);
        n3 = cleanAnswer(n3);
        insertZeros(count, carryover);
        carryover = addHelper(count, carryover);
        carryover = cleanAnswer(carryover);
        string n4 = cleanAnswer(n2);
        insertZeros(n3, n4);

        if (n3 < n4) {
            return carryover;
        } else if (n3 == n4){
            string one = "1";
            insertZeros(carryover, one);
            return addHelper(carryover, one);

        } else {
            return divideHelper(n3, n4, carryover);
        }
    }
}

/// ============================================================================================
/// End Arithmetic Function Definitions
/// ============================================================================================
///                                                           Begin Utility Function Definitions
/// ============================================================================================

/*
     * Method: insertZeros
     * Usage: insertZeros(number1, string number2)
     * ------------------------------------
     * Concatenates "0" to the smaller string until both arguments have the same string length.
     * Postcondition: Both numbers will have the same string length. This will ensure that the
     * string comparison operators will properly evaluate which string is greater.
*/

void insertZeros(string& n1, string& n2) {
    if (n1.length() > n2.length()) {
        int size = n1.length() - n2.length();
        for (int i = 0 ; i < size ; i++) {
            n2 = "0" + n2;
        }
    } else if (n1.length() < n2.length()) {
        int size = n2.length() - n1.length();
        for (int i = 0 ; i < size ; i++) {
            n1 = "0" + n1;
        }
    }
}

/*
     * Method: cleanAnswer
     * Usage: addHelper(number1, string number2)
     * ------------------------------------
     * Removes the zeros at the front of a string until it reaches a non-zero digit.
     * Postcondition: Returns "0" if the string contains only "0" (literal) digits.
*/
string cleanAnswer(const string& n1) {
    if (n1[0] == '0'){
        // Find the first char in the string that is not "0."
        int cut = n1.find_first_not_of('0',0);
        // If the string does not contain non-zero digits then return "0."
        if (cut == string::npos){
            return "0";
        } else {
            // Otherwise, cut the string from the first non-zero digit, and return the string.
            return n1.substr(cut,n1.length()-cut);
        }
    } else {
        //If the all of the digits in the integer are all significant digits then return the string as-is.
        return n1;
    }
}

/*
     * Method: negateNum
     * ------------------------------------
     * Postcondition: If the first char in the argument is not '-' then return a string with "-" appended to the front.
     * Postcondition: Removes the '-' from the argument if it is already hyphenated.
*/
void negateNum(string& n1){
    if (n1[0] == '-'){
        n1 =  n1.substr(1,n1.length()-1);
    } else {
        n1 = "-" + n1;
    }
}

/*
     * Method: isNegative
     * ------------------------------------
     * Returns a bool value if the argument is a negative integer or not.
*/
bool isNegative(const string& n1){
    return n1[0] == '-';
}

/*
     * Method: priority
     * ------------------------------------
     * Returns TRUE if the priority of the first argument is greater or the same as the second argument.
*/
bool priority(char leftOperator, char rightOperator) {
    if (leftOperator == '*' || leftOperator == '/') {
        return true;
    }
    else if (rightOperator == '*' || rightOperator == '/') {
        return false;
    }
    return true;
}

/*
     * Method: isOperator
     * ------------------------------------
     * Returns TRUE if the argument is a valid operand symbol.
*/
bool isOperator(char n) {
    switch (n) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

/*
     * Method: isGreater
     * ------------------------------------
     * Returns TRUE if the second argument is less than the first argument.
*/
bool isGreater(const string& n1, const string& n2) {
    for (int i = 0 ; i < n2.length() ; i++){
        if ( n1[i] < n2[i] ) {
            return false;
        }
    }
    return true;

}

/*
     * Method: isBalanced
     * ------------------------------------
     * Returns TRUE if the parentheses in an equation are in a valid position and are all paired.
     * It also returns FALSE if the equation has a double minus sign.
*/
bool isBalanced(const string& in) {
    Stack<char> parens;
    parens.initialize();
    int size = in.length();
    char temp;
    int lastSub = 0;

    // Use a stack collection to ensure that the pairs of parenthesis do not overlap within the line.
    for (int i = 0; i<size ; i++){
        if (in[i] == '(' ) {
            parens.push(in[i]);
        } else if ( (in[i] == ')' )  && (!parens.isEmpty()) ) {
            parens.pop();
        }
        // Check for unbalanced close parenthesis.
        else if ( (in[i] == ')' )  && (parens.isEmpty()) ){
            return false;
        }
            // Check for Double Operands.
            if (i !=0) {
            if ( (isOperator(in[i])) && (isOperator(in[i-1])) ) {
                return false;
            }
        }
    }

    // If the stack is empty then the equation is valid. Otherwise it is an invalid equation.
    return parens.isEmpty();
}

#endif //HW2V2_STACK_H
