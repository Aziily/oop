#include "interactive.cpp"

int main(int argc, char const *argv[])
{   
    // Get file name
    string file_name = "./data/castle.txt";
    if (argc > 1)
    {
        file_name = argv[1];
    }
    // Create castle and interactor
    Castle castle(file_name);
    Interactor interactor;
    // Interact
    interactor.interact(castle);
    return 0;
}