
#include "SimpleChecksum.h"



////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS
////////////////////////////////////////////////////////////////
    
SimpleChecksum::SimpleChecksum( int numberOfBytes )
    : checksumLength( numberOfBytes )
{
    this->checksum = new int8_t[ numberOfBytes ];
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

void SimpleChecksum::setByte( int8_t newByte , int index )
{
    this->checksum[index] = newByte;
}


int8_t* SimpleChecksum::getBytes()
{
    return this->checksum;
}


int SimpleChecksum::getBytesLength()
{
    return this->checksumLength;
}


// computes the checksum from the provided message
void SimpleChecksum::computeFrom( int8_t* message , int messageLength )
{
    this->initialize();
    for( int n=0; n<messageLength; n++ ) {
        this->checksum[0] += message[n];
        for( int i=1; i<this->checksumLength; i++ ) {
            this->checksum[i] += this->checksum[i-1];
        }
    }
}


bool SimpleChecksum::equals( const SimpleChecksum& other ) const
{
    for( int i=0; i<this->checksumLength; i++ ) {
        if( this->checksum[i] != other.checksum[i] ) {
            return false;
        }
    }
    return true;
}



////////////////////////////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////////////////////////////

void SimpleChecksum::initialize()
{
    this->checksum[0] = 1;
    for( int i=1; i<this->checksumLength; i++ ) {
        this->checksum[i] = 0;
    }
}
