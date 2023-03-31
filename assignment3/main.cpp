#include "interactive.cpp"

int main()
{
    Castle castle("castle.txt");
    Interactor interactor;
    interactor.interact(castle);
    return 0;
}