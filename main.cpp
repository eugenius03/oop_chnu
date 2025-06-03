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