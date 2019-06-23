#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>

#include "../include/arrayStack.hpp"
#include "../include/listStack.hpp"
#include <stack>

    using namespace std;

    typedef unsigned long long size_long_t;

    enum stackType
    {
        arrayStack,
        listStack
    };

    typedef int stackImplementType;

    bool createStack( WSTI::stack<stackImplementType>*& stack, bool infinit, stackType stack_t, const size_t& stackSize);
    bool testStack( WSTI::stack<stackImplementType>* stack, bool infinit, stackType stack_t, clock_t& start, clock_t& end, size_long_t& stackSize, size_t& itemsCount, size_t& itemSize);
    bool testSTLStack( std::stack<stackImplementType>* stack, bool infinit, clock_t& start, clock_t& end, size_long_t& stackSize, size_t& itemsCount, size_t& itemSize);

    void showStackTestResult( const clock_t& start, const clock_t& end, const size_long_t& stackSize, const size_t& itemsCount, const size_t& itemSize);

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> main start <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

int main()
{
    WSTI::stack<stackImplementType> *stack = nullptr;
    clock_t start, end;
    size_long_t stackSize;
    size_t itemsCount;
    size_t itemSize;
    bool isStackInfinit = false;
    bool testGood;

    const short iterationNumber = 15;
    const int startElements = 1'000'000;
    const float elementsMultipler = 1.75;

    cout << setw( 16 ) << left << "(De)+allocating"<< setw( 15 ) << "stack size"   << setw( 6 ) << "Item" << setw( 20 ) << "Stack size" << endl
         << setw( 16 ) << left << "time(s)"        << setw( 15 ) << "(items)<int>" << setw( 6 ) << "size" << setw( 20 ) << "(bytes)"<< endl << endl;

    itemsCount = startElements;
    cout << "Array stack" << endl;
    for ( size_t i = 0; i < iterationNumber; i++)
    {
        if ( createStack( stack, isStackInfinit, stackType::arrayStack, itemsCount) )
        {
            testGood = testStack( stack, isStackInfinit, stackType::arrayStack, start, end, stackSize, itemsCount, itemSize);
            showStackTestResult( start, end, stackSize, itemsCount, itemSize);
        }
        else
        {
            cerr << "Stack couldn't be created!" << endl;
            break;
        }

        if ( !testGood )
            break;

        itemsCount *= elementsMultipler;
        // cout << "Press any key to continue...";
        // getchar();
        sleep( 4 );
    }
    // getchar();

    cout << endl << endl;
    sleep( 4 );

    itemsCount = startElements;
    cout << "List stack" << endl;
    for ( size_t i = 0; i < iterationNumber; i++)
    {
        if ( createStack( stack, isStackInfinit, stackType::listStack, itemsCount) )
        {
            testGood = testStack( stack, isStackInfinit, stackType::listStack, start, end, stackSize, itemsCount, itemSize);
            showStackTestResult( start, end, stackSize, itemsCount, itemSize);
        }
        else
        {
            cerr << "Stack couldn't be created!" << endl;
            break;
        }

        if ( !testGood )
            break;

        itemsCount *= elementsMultipler;
        // cout << "Press any key to continue..." << endl;
        // getchar();
        sleep( 4 );
    }

    cout << endl << endl;
    sleep( 4 );

    itemsCount = startElements;
    std::stack<stackImplementType>* stlStack = nullptr;
    cout << "STL stack" << endl;
    for ( size_t i = 0; i < iterationNumber; i++)
    {
        if ( stlStack = new (std::nothrow) std::stack<stackImplementType>() )
        {
            testGood = testSTLStack( stlStack, isStackInfinit, start, end, stackSize, itemsCount, itemSize);
            showStackTestResult( start, end, stackSize, itemsCount, itemSize);
        }
        else
        {
            cerr << "Stack couldn't be created!" << endl;
            break;
        }

        if ( !testGood )
            break;

        itemsCount *= elementsMultipler;
        // cout << "Press any key to continue..." << endl;
        // getchar();
        sleep( 4 );
    }

    cout << endl;

    return 0;
}

/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> main end <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */

bool createStack( WSTI::stack<stackImplementType>*& stack, bool infinit, stackType stack_t, const size_t& stackSize)
{
    try
    {
        if( !infinit  && stack_t == stackType::arrayStack )
        {
            stack = new WSTI::arrayStack<stackImplementType>( stackSize );
        }
        else
        {
            switch ( stack_t )
            {
                case stackType::arrayStack:
                    stack = new WSTI::arrayStack<stackImplementType>();
                    break;

                case stackType::listStack:
                    stack = new WSTI::listStack<stackImplementType>();
                    break;
            }
        }
    }
    catch(  const WSTI::stack<stackImplementType>::stackException &e )
    {
        stack = nullptr;
        return false;
    }

    return true;
}

bool testStack( WSTI::stack<stackImplementType>* stack, bool infinit, stackType stack_t, clock_t& start, clock_t& end, size_long_t& stackSize, size_t& itemsCount, size_t& itemSize)
{
    stackSize = 0;
    bool testGood = true;

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
            for (size_t i = 0; i < itemsCount; i++)
                stack->push(i);
        }
    }
    catch( const WSTI::stack<stackImplementType>::stackException &e )
    {
        testGood = false;
        switch ( e )
        {
            case WSTI::stack<stackImplementType>::stackException::stackOverflow:
                cerr << "Stack is overflowed!" << endl;
                break;

            case WSTI::stack<stackImplementType>::stackException::emptyStack:
                cerr << "Stack is empty!" << endl;
                break;

            default:
                break;
        }
    }

    itemSize = stack->stackItemSize();
    itemsCount = stack->size();
    if ( stack_t == stackType::arrayStack )
        stackSize += sizeof( *stack );
    delete stack;
    stack = nullptr;

    end = clock();
    stackSize += itemSize * itemsCount;

    return testGood;
}

bool testSTLStack( std::stack<stackImplementType>* stack, bool infinit, clock_t& start, clock_t& end, size_long_t& stackSize, size_t& itemsCount, size_t& itemSize)
{
    bool testGood = true;

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
            for (size_t i = 0; i < itemsCount; i++)
                stack->push(i);
        }
    }
    catch( const std::exception& e )
    {
        cerr << e.what() << endl;
        testGood = false;
    }

    itemsCount = stack->size();
    stackSize = sizeof(*stack);
    delete stack;
    stack = nullptr;

    end = clock();
    itemSize = sizeof(stackImplementType);
    stackSize += itemSize * itemsCount;

    return testGood;
}

void showStackTestResult( const clock_t& start, const clock_t& end, const size_long_t& stackSize, const size_t& itemsCount, const size_t& itemSize)
{
    // short elementsWeight_t = 0;
    // float elementsWeight = stackSize;
    // string weightPostfix;

    // while( elementsWeight > 1024.0f )
    // {
    //     elementsWeight /= 1024.0f;
    //     elementsWeight_t++;
    // }

    // switch ( elementsWeight_t )
    // {
    //     case 0: weightPostfix = "B"; break;
    //     case 1: weightPostfix = "KB"; break;
    //     case 2: weightPostfix = "MB"; break;
    //     case 3: weightPostfix = "GB"; break;
    //     default:
    //         break;
    // }

    float endTime = static_cast<float>(end - start) / CLOCKS_PER_SEC;

    //printf("%s Its take %f seconds to add %u elements to stack of size %d bytes for item of size %d bytes.\n", title, endTime, itemsCount, stackSize, itemSize);
    cout << setw( 14 ) <<  right << fixed << setprecision( 3 ) << endTime << setw( 15 ) << itemsCount << setw( 6 ) << itemSize << setw( 16 ) << stackSize << endl;
}
