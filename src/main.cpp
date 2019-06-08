#include <iostream>

#include "../include/arrayStack.hpp"
#include "../include/listStack.hpp"

    using namespace std;

    typedef int stackType;

int main()
{
    WSTI::stack<stackType> *stack;
    stack = new WSTI::listStack<stackType>( );

    try
    {
        size_t stackSize = 200;

        for (size_t i = 0; i < stackSize; i++)
        {
            stack->push(i);
        }  

        for (size_t i = 0; i < stackSize; i++)
        {
            cout << stack->pop() << endl;
        }
    }
    catch( WSTI::stack<stackType>::stackException e )
    {
        switch ( e )
        {
            case WSTI::stack<stackType>::stackException::stackOverflow:
                cout << "Stack is overflowed!" << endl;
                printf("actual size of stack is %d elements %d.\n", stack->size(), stack->maxSize());
                break;

            case WSTI::stack<stackType>::stackException::emptyStack:
                cout << "Stack is empty!" << endl;
                break;

            default:
                break;
        }
    }

    return 0;
}