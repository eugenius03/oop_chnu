#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

struct List {
    int coefficient;
    List* nextNode;
    List(int val = 0, List* n = nullptr) : coefficient(val), nextNode(n) {} // Constructor for List node
};

class Polynomial {
private:
    List* headNode; // Pointer to the head of the linked list
    int size;   // Number of terms (degree + 1)
public:
    // Default constructor
    Polynomial() : headNode(nullptr), size(0) {}

    // Constructor to initialize a polynomial of a given size (all coeffs to 0)
    explicit Polynomial(int n); // Use explicit to prevent accidental conversions

    // Constructor to initialize a polynomial from an array
    Polynomial(int a[], int n);

    // Copy constructor
    Polynomial(const Polynomial& p);

    // Assignment operator
    Polynomial& operator=(const Polynomial& other);

    // Destructor
    ~Polynomial();

    // Member functions
    int is_equal(const Polynomial& p) const; // Pass by const reference
    // Returns a deep copy of the linked list representing the polynomial
    List* get_list() const; // Returns a deep copy of the linked list
    int get_size() const { return size; }

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;

    int at(int b) const; // Should be const as it doesn't modify the object
    Polynomial x_plus_b(int b) const; // Should be const
    Polynomial deriative() const; // Should be const
    Polynomial idk(int b) const; // Should be const

    // Friend functions for I/O
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p); // Pass by const reference
    friend std::istream& operator>>(std::istream& is, Polynomial& p);

    // Removed the problematic copy member function, as assignment operator already handles this
    // Polynomial copy(const Polynomial p) { *this = Polynomial(p); return *this; }
};

#endif //POLYNOMIAL_H