#include <iostream>

#include "../include/arrayStack.hpp"

    using namespace std;

int main()
{
    WSTI::stack<int> *stack;
    stack = new WSTI::arrayStack<int>( 1 );

    try
    {
        for (size_t i = 0; i < 200000000; i++)
        {
            stack->push(i);
        }


        printf("Now I have size %d for %d.\n", stack->size(), stack->maxSize());
    }
    catch( WSTI::stack<int>::stackException e )
    {
        switch ( e )
        {
            case WSTI::stack<int>::stackException::stackOverflow:
                cout << "Stack is overflowed!";
                break;

            case WSTI::stack<int>::stackException::emptyStack:
                cout << "Stack is empty!";
                break;

            default:
                break;
        }
    }

    return 0;
}