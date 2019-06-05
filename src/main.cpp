#include <iostream>

#include "../include/arrayStack.hpp"

    using namespace std;

int main()
{
    WSTI::stack<int> *stack;
    stack = new WSTI::arrayStack<int>();

    cout << "Its work!" << endl;

    return 0;
}