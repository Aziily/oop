#ifndef INTERACTIVE_CPP
#define INTERACTIVE_CPP

#include "castle.cpp"

class Interactor {
private:
    
public:
    /// @brief Constructor
    Interactor() {}
    // ~Interactor() {}

    /// @brief Interact with the player
    /// @param castle: the castle
    void interact(Castle &castle);
};

void Interactor::interact(Castle &castle)
{
    // Print information
    cout << "Welcome to the lobby!" << endl;
    castle.print_info();
    cout << endl;
    castle.print_state();
    int state = castle.get_state();

    // Interact
    while (state != 2 && state != 3 && state != 4)
    {
        string commend, direction;
        cin >> commend >> direction;
        cout << endl;

        // judge commend
        if (commend == "go")
        {
            if (direction == "up")
            {
                castle.move('N');
            }
            else if (direction == "east")
            {
                castle.move('E');
            }
            else if (direction == "down")
            {
                castle.move('S');
            }
            else if (direction == "west")
            {
                castle.move('W');
            }
            else
            {
                cout << "Invalid direction!" << endl;
            }
        }
        else if (commend == "quit")
        {
            break;
        }
        else
        {
            cout << "Invalid commend!" << endl;
        }

        // update state and print prompt
        state = castle.get_state();
        castle.print_state();
    }
}

#endif