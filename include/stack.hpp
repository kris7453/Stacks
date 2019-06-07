#pragma once

namespace WSTI
{
    template<typename T>
    class stack
    {
        public:
            stack(){};
            virtual ~stack(){};
            
            enum stackException
            {
                stackOverflow,
                emptyStack
            };

            virtual bool    push( T item ) = 0;
            virtual T       pop() = 0;
            virtual T       peek() = 0;
            virtual bool    empty() = 0;
            virtual size_t  size() = 0;
            virtual size_t  maxSize() = 0;
            virtual void    clear() = 0;


        protected:
            size_t length;
    };
}