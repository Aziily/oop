#include "castle.cpp"

class Interactor {
private:
    
public:
    Interactor() {}
    ~Interactor() {}
    void interact(Castle &castle);
};

void Interactor::interact(Castle &castle)
{
    cout << "Welcome to the lobby!" << endl;
    castle.print_state();
    int state = castle.get_state();
    while (state != 2 || state != 3 || state != 4)
    {
        string commend, direction;
        cin >> commend >> direction;
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
        castle.print_state();
    }
}