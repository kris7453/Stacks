namespace WSTI
{
    template<typename T>
    listStack<T>::listStack()
    {
        top = nullptr;
        stack<T>::length = 0;
    }

    template<typename T>
    listStack<T>::~listStack()
    {
        clear();
    }

    template<typename T>
    bool listStack<T>::push( T item )
    {
        listItem*   newItem;

        try
        {
            newItem = new listItem();
        }
        catch ( const std::bad_alloc &e )
        {
            std::cerr << e.what() << '\n';
            throw stack<T>::stackException::stackOverflow;
        }
        
        newItem->item = item;
        newItem->prevItem = top;

        top = newItem;
        stack<T>::length++;

        return true;
    }

    template<typename T>
    T listStack<T>::pop()
    {
        if ( top != nullptr )
        {
            T item = top->item;
            removeLast();
            
            return item;
        }
        else
            throw stack<T>::stackException::emptyStack;
    }

    template<typename T>
    T listStack<T>::peek()
    {
        if ( top != nullptr )
            return top->item;
        else
            throw stack<T>::stackException::emptyStack;
    }

    template<typename T>
    bool listStack<T>::isEmpty()
    {
        return (top == nullptr);
    }

    template<typename T>
    size_t listStack<T>::size()
    {
        return stack<T>::length;
    }

    template<typename T>
    size_t listStack<T>::maxSize()
    {
        return size();
    }

    template<typename T>
    size_t listStack<T>::stackItemSize()
    {
        return sizeof(listItem);
    }

    template<typename T>
    void listStack<T>::clear()
    {
        while ( top != nullptr )
            removeLast();
    }

    template<typename T>
    inline void listStack<T>::removeLast()
    {
        listItem* temp = top;
        top = temp->prevItem;
        stack<T>::length--;
        
        delete temp;
    }
}