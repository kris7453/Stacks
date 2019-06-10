namespace WSTI
{
    template<typename T>
    arrayStack<T>::arrayStack() : arrayStack( 32 )
    {
    }
    
    template<typename T>
    arrayStack<T>::arrayStack( size_t initialSize )
    {
        try
        {
            maxLength = initialSize;
            items = new T[maxLength];
            stack<T>::length = 0;
        }
        catch( const std::bad_alloc& e )
        {
            std::cerr << e.what() << '\n';
            throw stack<T>::stackException::stackOverflow;
        }
    }

    template<typename T>
    arrayStack<T>::~arrayStack()
    {
        delete [] items;
    }

    template<typename T>
    bool arrayStack<T>::push( T item )
    {
        if ( stack<T>::length == maxLength )
        {
            if ( !resize() )
                throw stack<T>::stackException::stackOverflow;
            else
                items[ stack<T>::length++ ] = item;
        }
        else
            items[ stack<T>::length++ ] = item;
        
        return true;
    }

    template<typename T>
    T arrayStack<T>::pop()
    {
        if ( stack<T>::length == 0 )
            throw stack<T>::stackException::emptyStack;
        else
            return items[ --stack<T>::length ];
    }

    template<typename T>
    T arrayStack<T>::peek()
    {
        if ( stack<T>::length == 0 )
            throw stack<T>::stackException::emptyStack;
        else
            return items[ stack<T>::length - 1 ];
    }

    template<typename T>
    bool arrayStack<T>::isEmpty()
    {
        return !stack<T>::length;
    }

    template<typename T>
    size_t arrayStack<T>::size()
    {
        return stack<T>::length;
    }

    template<typename T>
    size_t arrayStack<T>::maxSize()
    {
        return maxLength;
    }

    template<typename T>
    size_t arrayStack<T>::stackItemSize()
    {
        return sizeof(T);
    }

    template<typename T>
    void arrayStack<T>::clear()
    {
        stack<T>::length = 0;
    }

    template<typename T>
    bool arrayStack<T>::resize()
    {
        T* tempItems;

        try
        {
            tempItems = new T[ maxLength * 2 ];
        }
        catch( const  std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        
        for (size_t i = 0; i < maxLength; i++)
        {
            tempItems[i] = items[i];
        }
        
        delete [] items;
        items = tempItems;
        maxLength <<= 1;

        return true;
    }
}