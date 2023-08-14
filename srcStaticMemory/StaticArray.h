#ifndef _STATIC_ARRAY_H_
#define _STATIC_ARRAY_H_



template< class T , int SMAX >
class StaticArray
{
    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private:
        T x[SMAX];
        int currentSize;
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        StaticArray();
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        int size() const;
        void add( const T& e );
        void set( const int index , const T& e );
        T& get( const int index );
        T& operator[]( const int index );
        void resize( const int newSize );
        T* data() const;


    ////////////////////////////////////////////////////////////////
    // PUBLIC STATIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        static StaticArray ofSize( int theSize );
    
};



////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS
////////////////////////////////////////////////////////////////

template< class T , int SMAX >
StaticArray<T,SMAX>::StaticArray()
{
    this->currentSize = 0;
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

template< class T , int SMAX >
int StaticArray<T,SMAX>::size() const
{
    return this->currentSize;
}


template< class T , int SMAX >
void StaticArray<T,SMAX>::add( const T& e )
{
    this->x[this->size()] = e;
    this->currentSize++;
}


template< class T , int SMAX >
void StaticArray<T,SMAX>::set( const int index , const T& e )
{
    this->x[index] = e;
}


template< class T , int SMAX >
T& StaticArray<T,SMAX>::get( const int index )
{
    return this->x[index];
}


template< class T , int SMAX >
T& StaticArray<T,SMAX>::operator[]( const int index )
{
    return this->get( index );
}


template< class T , int SMAX >
void StaticArray<T,SMAX>::resize( const int newSize )
{
    this->currentSize = newSize;
}


template< class T , int SMAX >
T* StaticArray<T,SMAX>::data() const
{
    return this->x;
}



////////////////////////////////////////////////////////////////
// PUBLIC STATIC METHODS
////////////////////////////////////////////////////////////////

template< class T , int SMAX >
StaticArray<T,SMAX> StaticArray<T,SMAX>::ofSize( int theSize )
{
    StaticArray<T,SMAX> v;
    v.currentSize = theSize;
    return v;
}



#endif  // #ifndef _STATIC_ARRAY_H_
