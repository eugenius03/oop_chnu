# C++ Polynomial Class
## This project implements a Polynomial class in C++ using a linked list to store coefficients. It provides various functionalities for polynomial manipulation, including arithmetic operations, evaluation, differentiation, and input/output.

[Features](#features)

[Project Structure](#project-structure)

[Building the Project](#building-the-project)

[Usage](#usage)

[Polynomial Representation](#polynomial-representation)

[Class Methods and Operators](#class-methods-and-operators)

[Example Usage](#example-usage)

----------------------------------
# Features

The Polynomial class supports the following operations:

    Initialization:

        Default constructor (creates a zero polynomial).

        Constructor to create a polynomial of a specific degree (all coefficients initialized to zero).

        Constructor to create a polynomial from an array of coefficients.

        Copy constructor for deep copying.

    Memory Management: Proper handling of dynamic memory with a destructor and assignment operator to prevent memory leaks.

    Arithmetic Operations:

        Addition (+ operator)

        Subtraction (- operator)

        Multiplication (* operator)

    Evaluation:

        at(int b): Evaluates the polynomial at a given point x = b.

    Calculus:

        deriative(): Computes the first derivative of the polynomial, P′(x).

    Comparison:

        is_equal(const Polynomial& p): Checks if two polynomials are equal.

    Input/Output:

        operator<<: Overloaded output stream operator to print polynomials in a readable format.

        operator>>: Overloaded input stream operator to read polynomial coefficients from the console.

# Project Structure

The project consists of three files:

    Polynomial.h: Contains the declaration of the List struct and the Polynomial class.

    Polynomial.cpp: Contains the implementation of the Polynomial class methods and overloaded operators.

    main.cpp: Contains the main function demonstrating the usage of the Polynomial class.

# Building the Project

To compile and link the project using g++ (common on Linux, macOS, and MinGW/MSYS2 on Windows), navigate to the project directory in your terminal and run the following command:
```sh
g++ main.cpp Polynomial.cpp -o polynomial_app
```

    main.cpp: Your main application file.

    Polynomial.cpp: The implementation file for the Polynomial class.

    -o polynomial_app: Specifies the name of the executable output file (you can choose any name).

## For VS Code Users:

If you are using VS Code, ensure your tasks.json file is configured to compile both main.cpp and Polynomial.cpp. An example tasks.json entry for building might look like this:

    {
        "version": "2.0.0",
        "tasks": [
            {
                "type": "cppbuild",
                "label": "C/C++: g++.exe build project",
                "command": "C:\\msys64\\ucrt64\\bin\\g++.exe", // Adjust path to your g++
                "args": [
                    "-fdiagnostics-color=always",
                    "-g",
                    "${fileDirname}\\main.cpp",
                    "${fileDirname}\\Polynomial.cpp",
                    "-o",
                    "${fileDirname}\\polynomial_app.exe" // Or .out on Linux/macOS
                ],
                "options": {
                    "cwd": "${fileDirname}"
                },
                "problemMatcher": [
                    "$gcc"
                ],
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "detail": "Builds the entire Polynomial project."
            }
        ]
    }

# Usage

After successfully building the project, you can run the executable from your terminal:
```sh
./polynomial_app
```
(On Windows, you might need to use polynomial_app.exe)

The main.cpp file provides interactive prompts and demonstrations of the Polynomial class functionalities.
# Polynomial Representation

Polynomials are represented using a singly linked list where each node (List struct) stores a coefficient. The coefficients are stored in ascending order of their corresponding powers of x. For example, for the polynomial P(x)=a0​+a1​x+a2​x^2:

    The first node in the linked list (headNode) stores a0​.

    The second node stores a1​.

    The third node stores a2​, and so on.

The size member variable stores the total number of terms (which is degree+1).
# Class Methods and Operators
Constructors:

    Polynomial(): Default constructor. Creates a zero polynomial.

    Polynomial(int n): Creates a polynomial of n terms, with all coefficients initialized to 0.

    Polynomial(int a[], int n): Creates a polynomial from an integer array a of size n. a[0] is the constant term, a[1] is the coefficient of x1, etc.

    Polynomial(const Polynomial& p): Copy constructor. Performs a deep copy of polynomial p.

Destructor:

    ~Polynomial(): Frees all dynamically allocated memory used by the linked list.

Assignment Operator:

    Polynomial& operator=(const Polynomial& other): Overloaded assignment operator. Performs a deep copy from other to the current polynomial, handling self-assignment and proper memory deallocation.

Arithmetic Operators:

    Polynomial operator+(const Polynomial& other) const: Returns a new polynomial representing the sum of the current polynomial and other.

    Polynomial operator-(const Polynomial& other) const: Returns a new polynomial representing the difference between the current polynomial and other.

    Polynomial operator*(const Polynomial& other) const: Returns a new polynomial representing the product of the current polynomial and other.

Member Functions:

    int is_equal(const Polynomial& p) const: Returns 1 if the current polynomial is equal to p, 0 otherwise.

    List* get_list() const: Returns a deep copy of the linked list

    int get_size() const: Returns the number of terms in the polynomial.

    int at(int b) const: Evaluates the polynomial at x=b using Horner's method.

    Polynomial deriative() const: Returns a new polynomial representing the first derivative P′(x).

Friend Functions (Input/Output):

    std::ostream& operator<<(std::ostream& outputStream, const Polynomial& p): Allows printing Polynomial objects to an output stream (e.g., std::cout).

    std::istream& operator>>(std::istream& inputStream, Polynomial& p): Allows reading Polynomial objects from an input stream (e.g., std::cin). It will prompt for the degree and then coefficients.

# Example Usage

The main.cpp file demonstrates how to use the Polynomial class:
```cpp
#include <iostream>
#include "Polynomial.h"
using namespace std;


int main()
{
    // Corrected initialization for Polynomial p:
    // It's better to let the istream operator handle the size and allocation.
    Polynomial p;
    Polynomial p2; // Initialize p2 as well

    int b_arr[] = { 4,5,6 };
    Polynomial p3_from_array(b_arr, 3); // Example: create a polynomial from an array

    cout << "Enter polynomial p (degree and then coefficients):" << endl;
    cin >> p; // This will now prompt for degree and coefficients

    cout << "Polynomial p: " << p;

    // Example of another polynomial for comparisons/operations
    int b_coeffs[] = { 1, 2, 3 }; // Example coefficients for p2
    p2 = Polynomial(b_coeffs, 3); // Assign p2 with some values

    cout << "Polynomial p2: " << p2;

    cout << "Is P equal to P2? ";
    cout << p.is_equal(p2) << endl;


    Polynomial p_copied_from_p2 = p2;
    cout << "p_copied_from_p2 (copy of p2): " << p_copied_from_p2;

    cout << "Value of P at the point 4: " << p.at(4) << endl;

    cout << "P'(x) (derivative of P): " << endl;
    cout << p.deriative();

    // Example of addition and multiplication
    int poly1_coeffs[] = {1, 2}; // 2x + 1
    int poly2_coeffs[] = {3, 4}; // 4x + 3
    Polynomial poly1(poly1_coeffs, 2);
    Polynomial poly2(poly2_coeffs, 2);

    cout << "Poly1: " << poly1;
    cout << "Poly2: " << poly2;
    cout << "Poly1 + Poly2: " << poly1 + poly2;
    cout << "Poly1 * Poly2: " << poly1 * poly2;

    List *list_copy = p.get_list();
    cout << "Deep copy of the linked list representing polynomial p: ";
    List* current = list_copy;
    while (current != nullptr) {
        cout << current->coefficient << " ";
        current = current->nextNode;
    }

    return 0;
}
```
