#include <iostream>
#include <ctime>

#include "../include/arrayStack.hpp"
#include "../include/listStack.hpp"

    using namespace std;


    enum stackType
    {
        arrayStack,
        listStack
    };

    typedef int stackImplementType;

    bool createStack( WSTI::stack<stackImplementType> *&stack, bool infinit, stackType stack_t, const size_t &stackSize);
    void testStack( WSTI::stack<stackImplementType> *stack, bool infinit, clock_t &start, clock_t &end, size_t &stackSize, size_t &stackItemSize);

    void showStackTestResult( const char* title, const clock_t &start, const clock_t &end, const size_t &stackSize, const size_t &stackItemSize);

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> main start <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

int main()
{
    WSTI::stack<stackImplementType> *stack = nullptr;
    clock_t start, end;
    size_t stackSize;
    size_t stackItemSize;
    bool isStackInfinit = false;

    const short iterationNumber = 7;
    const int startElements = 1000;
    const int elementsMultipler = 10;

    stackSize = startElements;
    for ( size_t i = 0; i < iterationNumber; i++)
    {
        if ( createStack( stack, isStackInfinit, stackType::arrayStack, stackSize) )
        {
            testStack( stack, isStackInfinit, start, end, stackSize, stackItemSize);
            showStackTestResult( "Array stack: ", start, end, stackSize, stackItemSize);
        }
        else
            cout << "Stack couldn't be created!" << endl;

        stackSize *= elementsMultipler;
        cout << "Press any key to continue...";
        getchar();
    }

    cout << endl;

    stackSize = startElements;
    for ( size_t i = 0; i < iterationNumber; i++)
    {
        if ( createStack( stack, isStackInfinit, stackType::listStack, stackSize) )
        {
            testStack( stack, isStackInfinit, start, end, stackSize, stackItemSize);
            showStackTestResult( "List stack: ", start, end, stackSize, stackItemSize);
        }
        else
            cout << "Stack couldn't be created!" << endl;

        stackSize *= elementsMultipler;
        cout << "Press any key to continue..." << endl;
        getchar();
    }

    return 0;
}

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> main end <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

bool createStack( WSTI::stack<stackImplementType> *&stack, bool infinit, stackType stack_t, const size_t &stackSize)
{
    if( !infinit  && stack_t == stackType::arrayStack )
    {
        try
        {
            stack = new WSTI::arrayStack<stackImplementType>( stackSize );
        }
        catch(  const WSTI::stack<stackImplementType>::stackException &e )
        {
            stack = nullptr;
            return false;
        }

        return true;
    }

    switch ( stack_t )
    {
        case stackType::arrayStack:
            stack = new WSTI::arrayStack<stackImplementType>();
            break;

        case stackType::listStack:
            stack = new WSTI::listStack<stackImplementType>();
            break;
    }

    return true;
}

void testStack( WSTI::stack<stackImplementType> *stack, bool infinit, clock_t &start, clock_t &end, size_t &stackSize, size_t &stackItemSize)
{
    try
    {
        if ( infinit )
        {
            start = clock();
            for (size_t i = 0; ; i++)
                stack->push(i);
        }
        else
        {
            start = clock();
            for (size_t i = 0; i < stackSize; i++)
                stack->push(i);
        }
    }
    catch( const WSTI::stack<stackImplementType>::stackException &e )
    {
        switch ( e )
        {
            case WSTI::stack<stackImplementType>::stackException::stackOverflow:
                cout << "Stack is overflowed!" << endl;
                break;

            case WSTI::stack<stackImplementType>::stackException::emptyStack:
                cout << "Stack is empty!" << endl;
                break;

            default:
                break;
        }
    }

    end = clock();
    stackSize = stack->size();
    stackItemSize = stack->stackItemSize();

    delete stack;
    stack = nullptr;
}

void showStackTestResult( const char* title, const clock_t &start, const clock_t &end, const size_t &stackSize, const size_t &stackItemSize)
{
    short elementsWeight_t = 0;
    float elementsWeight = stackSize * stackItemSize;
    string weightPostfix;

    while( elementsWeight > 1024.0f )
    {
        elementsWeight /= 1024.0f;
        elementsWeight_t++;
    }

    switch ( elementsWeight_t )
    {
        case 0: weightPostfix = "B"; break;
        case 1: weightPostfix = "KB"; break;
        case 2: weightPostfix = "MB"; break;
        case 3: weightPostfix = "GB"; break;
        default:
            break;
    }

    float endTime = static_cast<float>(end - start) / CLOCKS_PER_SEC;

    printf("%s Its take %f seconds to add %u elements to stack of weight %f %s\n", title, endTime, stackSize, elementsWeight, weightPostfix.c_str());
}
