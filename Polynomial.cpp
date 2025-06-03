#include "Polynomial.h"
#include <iostream>
#include <algorithm> // For std::max

// Constructor to initialize a polynomial of a given size (all coefficients to 0)
Polynomial::Polynomial(int n) : size(n), headNode(nullptr) {
    if (n > 0) {
        headNode = new List(0); // Create the first node
        List* currentNode = headNode;
        for (int i = 1; i < size; ++i) {
            currentNode->nextNode = new List(0);
            currentNode = currentNode->nextNode;
        }
    }
}

// Constructor that takes an array
Polynomial::Polynomial(int a[], int n) : size(n), headNode(nullptr) {
    if (n > 0) {
        headNode = new List(a[0]); // Create the first node
        List* currentNode = headNode;
        for (int i = 1; i < size; ++i) {
            currentNode->nextNode = new List(a[i]);
            currentNode = currentNode->nextNode;
        }
    }
}

// Copy Constructor
Polynomial::Polynomial(const Polynomial& p) : headNode(nullptr), size(0) {
    if (p.headNode != nullptr) {
        size = p.size;
        headNode = new List(p.headNode->coefficient);
        List* currentThis = headNode;
        List* currentOther = p.headNode->nextNode;
        while (currentOther != nullptr) {
            currentThis->nextNode = new List(currentOther->coefficient);
            currentThis = currentThis->nextNode;
            currentOther = currentOther->nextNode;
        }
    }
}

// Destructor
Polynomial::~Polynomial() {
    List* currentNode = headNode;
    while (currentNode != nullptr) {
        List* nextNode = currentNode->nextNode;
        delete currentNode;
        currentNode = nextNode;
    }
    headNode = nullptr; // Ensure coef is null after deletion
    size = 0; // Reset size
}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) { // Handle self-assignment
        return *this;
    }

    // Deallocate existing memory
    List* currentNode = headNode;
    while (currentNode != nullptr) {
        List* nextNode = currentNode->nextNode;
        delete currentNode;
        currentNode = nextNode;
    }

    // Copy new data
    if (other.headNode != nullptr) {
        size = other.size;
        headNode = new List(other.headNode->coefficient);
        List* currentThis = headNode;
        List* currentOther = other.headNode->nextNode;
        while (currentOther != nullptr) {
            currentThis->nextNode = new List(currentOther->coefficient);
            currentThis = currentThis->nextNode;
            currentOther = currentOther->nextNode;
        }
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    int newSize = std::max(size, other.size);
    int* tempCoefs = new int[newSize]();

    List* thisCur = headNode;
    List* otherCur = other.headNode;
    for (int i = 0; i < newSize; ++i) {
        int thisCoef = (thisCur != nullptr) ? thisCur->coefficient : 0;
        int otherCoef = (otherCur != nullptr) ? otherCur->coefficient : 0;
        tempCoefs[i] = thisCoef + otherCoef;
        if (thisCur) thisCur = thisCur->nextNode;
        if (otherCur) otherCur = otherCur->nextNode;
    }

    Polynomial result(tempCoefs, newSize);
    delete[] tempCoefs;
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    int newSize = std::max(this->size, other.size);
    int* tempCoefs = new int[newSize]();

    List* thisCur = this->headNode;
    List* otherCur = other.headNode;
    int i = 0;

    // Subtract corresponding coefficients
    while (i < newSize) {
        int thisCoef = (thisCur != nullptr) ? thisCur->coefficient : 0;
        int otherCoef = (otherCur != nullptr) ? otherCur->coefficient : 0;
        tempCoefs[i] = thisCoef - otherCoef;
        if (thisCur) thisCur = thisCur->nextNode;
        if (otherCur) otherCur = otherCur->nextNode;
        ++i;
    }

    Polynomial result(tempCoefs, newSize);
    delete[] tempCoefs;
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    if (this->size == 0 || other.size == 0) {
        return Polynomial(); // Return an empty polynomial
    }

    int newSize = this->size + other.size - 1;
    int* newCoeffs = new int[newSize](); // Initialize with zeros

    List* thisCur = this->headNode;
    int i = 0;
    while (thisCur != nullptr) {
        List* otherCur = other.headNode;
        int j = 0;
        while (otherCur != nullptr) {
            newCoeffs[i + j] += thisCur->coefficient * otherCur->coefficient;
            otherCur = otherCur->nextNode;
            j++;
        }
        thisCur = thisCur->nextNode;
        i++;
    }

    Polynomial result(newCoeffs, newSize);
    delete[] newCoeffs;
    return result;
}

std::ostream& operator<<(std::ostream& outputStream, const Polynomial& p) {
    if (p.size == 0 || p.headNode == nullptr) {
        outputStream << "0\n"; // Represent an empty polynomial as 0
        return outputStream;
    }

    List* currentNode = p.headNode;
    int i = 0;

    // Handle the constant term
    outputStream << currentNode->coefficient;
    currentNode = currentNode->nextNode;
    i++;

    // Handle other terms
    while (currentNode != nullptr) {
        if (currentNode->coefficient != 0) { // Only print if coefficient is not zero
            if (currentNode->coefficient > 0) {
                outputStream << " + ";
            } else {
                outputStream << " - ";
            }
            outputStream << std::abs(currentNode->coefficient); // Print absolute value, sign handled by " + " or " - "

            if (i == 1) {
                outputStream << "x";
            } else {
                outputStream << "x^" << i;
            }
        }
        currentNode = currentNode->nextNode;
        i++;
    }
    outputStream << "\n";
    return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Polynomial& p) {
    // Deallocate any existing memory in p
    List* currentNode = p.headNode;
    while (currentNode != nullptr) {
        List* nextNode = currentNode->nextNode;
        delete currentNode;
        currentNode = nextNode;
    }

    std::cout << "Enter the degree of the polynomial: ";
    int degree;
    inputStream >> degree;
    p.size = degree + 1;

    if (p.size > 0) {
        std::cout << "Enter " << p.size << " coefficients (from x^0 to x^" << degree << "): ";
        int val;
        inputStream >> val;
        p.headNode = new List(val);
        List* current_node = p.headNode;
        for (int i = 1; i < p.size; ++i) {
            inputStream >> val;
            current_node->nextNode = new List(val);
            current_node = current_node->nextNode;
        }
    }
    return inputStream;
}

int Polynomial::is_equal(const Polynomial& p) const {
    if (size != p.size) {
        return 0;
    }
    List* currentNode = headNode;
    List* othercur = p.headNode;
    while (currentNode != nullptr) {
        if (currentNode->coefficient != othercur->coefficient) {
            return 0;
        }
        currentNode = currentNode->nextNode;
        othercur = othercur->nextNode;
    }
    return 1;
}

int Polynomial::at(int b) const {
    if (size == 0 || headNode == nullptr) {
        return 0; // Value of empty polynomial at any point is 0
    }

    // Convert linked list to array for easier Horner's method
    int* coeff_array = new int[size];
    List* currentNode = headNode;
    for (int i = 0; i < size; ++i) {
        coeff_array[i] = currentNode->coefficient;
        currentNode = currentNode->nextNode;
    }

    // Horner's method: P(x) = a_n*x^n + ... + a_1*x + a_0
    // Evaluate from highest degree term to constant term
    int result = 0;
    for (int i = size - 1; i >= 0; i--) {
        result = result * b + coeff_array[i];
    }

    delete[] coeff_array;
    return result;
}


Polynomial Polynomial::deriative() const {
    if (size <= 1 || headNode == nullptr) {
        return Polynomial(); // Derivative of a constant or empty polynomial is 0
    }

    Polynomial deriative(size - 1);
    List* deriativeNode = deriative.headNode;

    List* currentNode = headNode->nextNode; // Start from the coefficient of x^1
    for (int i = 0; i < size-1; i++) {
        deriativeNode->coefficient = currentNode->coefficient * (i + 1); // Coefficient of x^(i+1) in original * (i+1)
        currentNode = currentNode->nextNode;
        deriativeNode = deriativeNode->nextNode;
    }

    return deriative;
}

List* Polynomial::get_list() const {
        if (!headNode) return nullptr;
        List* newHead = new List(headNode->coefficient);
        List* currSrc = headNode->nextNode;
        List* currDest = newHead;
        while (currSrc) {
            currDest->nextNode = new List(currSrc->coefficient);
            currDest = currDest->nextNode;
            currSrc = currSrc->nextNode;
        }
        return newHead;
    }