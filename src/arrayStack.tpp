namespace WSTI
{
    template<typename T>
    arrayStack<T>::arrayStack()
    {
        std::cout << "Hello arrayStack!" << std::endl;
    }

    template<typename T>
    arrayStack<T>::~arrayStack()
    {
    }

    template<typename T>
    bool arrayStack<T>::push( T item )
    {
        item = 1;
        return true;
    }

    template<typename T>
    T* arrayStack<T>::pop()
    {
        return nullptr;
    }

    template<typename T>
    T* arrayStack<T>::peek()
    {
        return nullptr;
    }

    template<typename T>
    bool arrayStack<T>::empty()
    {
        return true;
    }

    template<typename T>
    int arrayStack<T>::size()
    {
        return 0;
    }

    template<typename T>
    void arrayStack<T>::clear()
    {
        
    }
}