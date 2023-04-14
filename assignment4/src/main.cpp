#include "pdadd.hpp"
#include "pdlist.hpp"
#include "pdremove.hpp"
#include "pdshow.hpp"

/// @brief Show menu.
/// @param op Pointer to the option.
void show_menu(int* op) {
    cout << "1. Add dairy" << endl;
    cout << "2. List dairy" << endl;
    cout << "3. Show dairy" << endl;
    cout << "4. Remove dairy" << endl;
    cout << "5. Exit" << endl;
    cout << "Please enter your choice: ";
    cin >> *op;
}

/// @brief Main function.
/// @param argc argc
/// @param argv argv
/// @return status code
int main(int argc, char** argv) {
    // Read filename from command line.
    string  filename = "data/dairy.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    // Show menu.
    int op;
    show_menu(&op);
    while (op != 5) {
        switch (op) {
        case 1:
            PDAdd(filename).add(); // Add dairy.
            break;
        case 2:
            PDList(filename).list(); // List dairy.
            break;
        case 3:
            PDShow(filename).show(); // Show dairy.
            break;
        case 4:
            PDRemove(filename).remove(); // Remove dairy.
            break;
        default:
            cout << "Invalid input." << endl; // Invalid input.
            break;
        }
        cout << endl;
        show_menu(&op);
    }
    return 0;
}