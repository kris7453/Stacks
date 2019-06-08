#pragma once

#include "../include/stack.hpp"

namespace WSTI
{
    template<typename T>
    class listStack: public stack<T> 
    {

    public:
        listStack();
        ~listStack();

        bool    push( T item );
        T       pop();
        T       peek();
        bool    empty();
        size_t  size();
        size_t  maxSize();
        void    clear();

    private:
        
        struct listItem
        {
            public:
                T           item;
                listItem*   prevItem;
        };

        listItem*   top;

        inline void removeLast();
    };
}

#include "../src/listStack.tpp"