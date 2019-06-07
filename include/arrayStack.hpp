#pragma once
#include <iostream>
#include <new>
#include "../include/stack.hpp"

namespace WSTI
{
    template<typename T>
    class arrayStack : public stack<T>
    {
        public:
            arrayStack();
            arrayStack( size_t initialSize );
            ~arrayStack();

            bool    push( T item ); 
            T       pop();
            T       peek();
            bool    empty();
            size_t  size();
            size_t  maxSize();
            void    clear();

        protected:
            // Double stack size and return true if stack has been resizes or false when there isnt enaught memory to resize
            bool resize();

        private:
            T*  items;
            size_t maxLength;
    };
}

#include "../src/arrayStack.tpp"