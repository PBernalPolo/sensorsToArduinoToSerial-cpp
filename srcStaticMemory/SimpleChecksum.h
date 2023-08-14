#ifndef _SIMPLE_CHECKSUM_H_
#define _SIMPLE_CHECKSUM_H_


#define CHECKSUM_MAX_SIZE 2


#include <stdint.h>
#include "StaticArray.h"




class SimpleChecksum
{
    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private:
        StaticArray<int8_t,CHECKSUM_MAX_SIZE> checksum;  // checksum that arrives with the incoming message
        
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        SimpleChecksum( int numberOfBytes );
    


    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    
    public:
        void setByte( const int index , const int8_t newByte );
        int8_t* data() const;
        int size() const;
        // computes the checksum from the provided message
        void computeFrom( const int8_t* message , const int messageLength );
        bool equals( const SimpleChecksum& other ) const;
    
    
    
    ////////////////////////////////////////////////////////////////
    // PRIVATE METHODS
    ////////////////////////////////////////////////////////////////
    private:
        void initialize();

};


#endif  // #ifndef _SIMPLE_CHECKSUM_H_
