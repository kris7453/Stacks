#pragma once
#include "../include/stack.hpp"
#include <iostream>

namespace WSTI
{
    template<typename T>
    class arrayStack : public stack<T>
    {
        public:
            arrayStack();
            ~arrayStack();

            bool    push( T item );
            T*      pop();
            T*      peek();
            bool    empty();
            int     size();
            void    clear();

    };
}

#include "../src/arrayStack.tpp"