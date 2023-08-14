#ifndef _SIMPLE_CHECKSUM_H_
#define _SIMPLE_CHECKSUM_H_


#include <stdint.h>



class SimpleChecksum
{
    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private:
        const int checksumLength;
        int8_t* checksum;  // checksum that arrives with the incoming message
        
    
    
    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        SimpleChecksum( int numberOfBytes );
    


    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    
    public:
        void setByte( int8_t newByte , int index );
        int8_t* getBytes();
        int getBytesLength();
        // computes the checksum from the provided message
        void computeFrom( int8_t* message , int messageLength );
        bool equals( const SimpleChecksum& other ) const;
    
    
    
    ////////////////////////////////////////////////////////////////
    // PRIVATE METHODS
    ////////////////////////////////////////////////////////////////
    private:
        void initialize();

};


#endif  // #ifndef _SIMPLE_CHECKSUM_H_
